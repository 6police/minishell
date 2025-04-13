#include "ft_builtins.h"

static void	do_echo(char *arg, int wild_card_type, t_cmd *cmd);
static bool	has_wildcard(char *arg);
static void	do_wildcard(char *arg, t_cmd *cmd);
static int	check_wildcard_type(char *str);
static bool	is_there_quotes(char *str);
static void	echoing(t_cmd *cmd, int newline);
static char	*remove_quotes(char *arg);
static void	organize_wildcard(t_wildcard *wc);
static int ft_strcasecmp(const char *s1, const char *s2);

void	echo_shell(t_cmd *cmd, t_shell *shell)
{
	int	newline;

	newline = 1;
	if (!cmd || !cmd->args)
	{
		ft_putchar_fd('\n', cmd->FD[1]);
		shell->exit_value = 0;
		return ;
	}
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "-n") == 0)
		newline = 0;
	echoing(cmd, newline);
	if (newline)
		ft_putchar_fd('\n', cmd->FD[1]);
}

static void	echoing(t_cmd *cmd, int newline)
{
	int	i;
	bool	wildcard;
	bool	quotes;

	i = -1;
	wildcard = false;
	if (newline == 0)
		i++;
	while (cmd->args[++i])
	{
		wildcard = has_wildcard(cmd->args[i]);
		quotes = is_there_quotes(cmd->args[i]);
		cmd->args[i] = remove_quotes(cmd->args[i]);
		if (wildcard == true && quotes == false)
			do_wildcard(cmd->args[i], cmd);
		else
			do_echo(cmd->args[i], 0, cmd);
		// check if there is more so we can put a space ' '
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', cmd->FD[1]);
	}
}

static bool	has_wildcard(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '*')
			return (true);
	}
	return (false);
}

static void	do_wildcard(char *arg_str, t_cmd *cmd)
{
	int	wild_card_type;
	
	wild_card_type = 0;
	wild_card_type = check_wildcard_type(arg_str);
	do_echo(arg_str, wild_card_type, cmd);
}

static bool	is_there_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			return (true);
		if (str[i] == '\'')
			return (true);
	}
	return (false);
}

static int	check_wildcard_type(char *str)
{
	int	wild_card_type;

	wild_card_type = 0;
	// * .* *. *.* '\"'
	if (str[0] == '*' && !str[1]) // *
		wild_card_type = 1;
	else if (str[0] == '*' && str[1] != '\0') // *.
		wild_card_type = 2;
	else if (str[0] != '\0' && str[ft_strlen(str) - 1] == '*') // .*
		wild_card_type = 3;
	else if (str[0] == '*' && str[ft_strlen(str) - 1] == '*') // *.*
		wild_card_type = 4;
	return (wild_card_type);
}

static void do_echo(char *arg, int a, t_cmd *cmd)
{
    DIR *dir;
    struct dirent *entry;
    bool first;
    t_wildcard wc;
    int i;

    first = true;
    if (a == 0) // No wildcard
    {
        ft_printf_fd(cmd->FD[1], "%s", arg);
        return;
    }

    dir = opendir(".");
    if (!dir)
        return;

    wc.nbr_of_dir = 0;
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] != '.')
            wc.nbr_of_dir++;
    }
    rewinddir(dir); // nao posso usar, fdps

    wc.wildcard = malloc(sizeof(char *) * (wc.nbr_of_dir));
    if (!wc.wildcard)
    {
        closedir(dir);
        return;
    }

    i = 0;
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] != '.')
            wc.wildcard[i++] = ft_strdup(entry->d_name);
    }

    organize_wildcard(&wc);

    for (i = 0; i < wc.nbr_of_dir; i++)
    {
        if (!first)
            ft_putchar_fd(' ', cmd->FD[1]);
        first = false;
        ft_printf_fd(cmd->FD[1], "%s", wc.wildcard[i]);
        free(wc.wildcard[i]);
    }
    free(wc.wildcard);
	/* else if (a == 2) // Caso 2: *.ext (extensão específica)     // ta a dar erro
	{
		suffix = strndup(arg + 1, ft_strlen(arg) - 2); // Remove * inicial e final
		suffix_len = ft_strlen(suffix);
		while (entry)
		{
			name_len = ft_strlen(entry->d_name);
			if (name_len > suffix_len && 
				strncmp(entry->d_name + name_len - suffix_len, suffix, suffix_len) == 0)
			{
				if (!first) ft_putchar_fd(' ', cmd->FD[1]);
				ft_putstr_fd(entry->d_name, cmd->FD[1]);
				first = 0;
			}
			entry = readdir(dir);
		}
		free(suffix);
	}
	else if (a == 3) // Caso 3: prefixo* (começa com padrão) // ta a dar erro
	{// atencao fazer ft_strndup no libft
		prefix = strndup(arg, ft_strlen(arg) - 1); // Remove último *
		prefix_len = ft_strlen(prefix);
		while (entry)
		{
			// Se prefixo não for oculto, ignora ficheiros ocultos
			if (prefix[0] != '.' && entry->d_name[0] == '.')
				continue;
				
			if (ft_strncmp(entry->d_name, prefix, prefix_len) == 0)
			{
				if (!first) ft_putchar_fd(' ', cmd->FD[1]);
				ft_putstr_fd(entry->d_name, cmd->FD[1]);
				first = 0;
			}
			entry = readdir(dir);
		}
		free(prefix);
	}
	else if (a == 4) // Caso 4: *padrão* (contém padrão no meio) // ta a dar erro
	{
		substring = strndup(arg + 1, ft_strlen(arg) - 2); // Remove * inicial e final
		while (entry)
		{
			// Ignora ocultos e verifica substring
			if (entry->d_name[0] != '.' && 
				strstr(entry->d_name, substring) != NULL) // criar ft_strstr, que localiza uma substring
			{
				if (!first) ft_putchar_fd(' ', cmd->FD[1]);
				ft_putstr_fd(entry->d_name, cmd->FD[1]);
				first = 0;
			}
			entry = readdir(dir);
		}
		free(substring);
	} */
	closedir(dir);
}

static char	*remove_quotes(char *arg)
{
	char	*new_str;

	if (!arg)
		return (NULL);
	if (arg[0] == '\"')
	{
		new_str = ft_strtrim(arg, "\"");
		free(arg); // Free the old arg
		return (new_str);
	}
	else if (arg[0] == '\'')
	{
		new_str = ft_strtrim(arg, "\'");
		free(arg); // Free the old arg
		return (new_str);
	} // Duplicate the string if no quotes
	 // Return the new string
	return (arg);
}
// use strtrim and free old arg, replace with new one.


static void organize_wildcard(t_wildcard *wc)
{
	int i;
	int j;
	char *temp;
	bool swapped;

	if (!wc || wc->nbr_of_dir <= 1)
		return;

	swapped = true;
	i = 0;

	while (swapped)
	{
		swapped = false;
		j = 0;
		while (j < wc->nbr_of_dir - i - 1)
		{
			if (ft_strcasecmp(wc->wildcard[j], wc->wildcard[j + 1]) > 0)
			{
				temp = wc->wildcard[j];
				wc->wildcard[j] = wc->wildcard[j + 1];
				wc->wildcard[j + 1] = temp;
				swapped = true;
			}
			j++;
		}
		i++;
	}
}

#include <ctype.h> // For tolower()

static int ft_strcasecmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
            return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
        s1++;
        s2++;
    }
    return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
}