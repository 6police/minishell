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
		// check if there is more so we can put wc_type space ' '
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
		if (str[i] == '\"' || str[i] == '\'')
			return (true);
	}
	return (false);
}

static int	check_wildcard_type(char *str)
{
	int	wild_card_type;

	wild_card_type = 0;
	if (str[0] == '*' && str[1] == '\0') // *
		wild_card_type = 1;
	else if (str[0] == '*' && str[1] != '\0') // *.
		wild_card_type = 2;
	else if ((str[0] != '\0' && str[0] != '*') && str[ft_strlen(str) - 1] == '*') // .*
		wild_card_type = 3;
	else if (str[0] == '*' && str[ft_strlen(str) - 1] == '*') // *.*
		wild_card_type = 4;
	else if (str[0] != '*' && str[ft_strlen(str - 1)] != '*' && ft_strchr(str, '*')) // .*.
		wild_card_type = 5;
	printf(GREEN"Wildcardtype: %d\n"RESET, wild_card_type);
	return (wild_card_type);
}

static void do_echo(char *arg, int wc_type, t_cmd *cmd)
{
	DIR *dir;
	struct dirent *entry;
	bool first;
	t_wildcard wc;
	int i;

	first = true;
	if (wc_type == 0) // No wildcard
	{
		ft_printf_fd(cmd->FD[1], "%s", arg);
		return ;
	}
	dir = opendir(".");
	if (!dir)
		return ;
	if (wc_type == 1)
	{
		wc.nbr_of_files = 0;
		while ((entry = readdir(dir)))
		{
			if (entry->d_name[0] != '.')
			wc.nbr_of_files++;
		}
		ft_printf_fd(cmd->FD[1], "%d\n", wc.nbr_of_files);
		closedir(dir);
		dir = opendir(".");
		wc.wildcard = malloc(sizeof(char *) * (wc.nbr_of_files));
		if (!wc.wildcard)
		{
			closedir(dir);
			ft_printf_fd(cmd->FD[2], "Error: Memory allocation failed\n");
			return;
		}
		i = 0;
		while ((entry = readdir(dir)))
		{
			if (entry->d_name[0] != '.')
				wc.wildcard[i++] = ft_strdup(entry->d_name);
		}
		organize_wildcard(&wc);
		for (i = 0; i < wc.nbr_of_files; i++)
		{
			if (!first)
				ft_putchar_fd(' ', cmd->FD[1]);
			first = false;
			ft_printf_fd(cmd->FD[1], "%s", wc.wildcard[i]);
			free(wc.wildcard[i]);
		}
		free(wc.wildcard);
		closedir(dir);
	}
	else if (wc_type == 2)
	{
		wc.nbr_of_files = 0;
		while ((entry = readdir(dir)))
		{
			if (ft_str_r_cmp((strrchr(arg, '*') +1), entry->d_name) == 0)
				wc.nbr_of_files++;
		}
		ft_printf_fd(cmd->FD[1], "%d\n", wc.nbr_of_files);
		closedir(dir);
		dir = opendir(".");
		wc.wildcard = malloc(sizeof(char *) * (wc.nbr_of_files));
		if (!wc.wildcard)
		{
			closedir(dir);
			ft_printf_fd(cmd->FD[2], "Error: Memory allocation failed\n");
			return;
		} // Caso 2: *.ext (extensão específica)     // ta wc_type dar erro
		i = 0;
		while ((entry = readdir(dir)))
		{
			if (ft_str_r_cmp((strrchr(arg, '*') +1), entry->d_name) == 0)
				wc.wildcard[i++] = ft_strdup(entry->d_name);
		}
		organize_wildcard(&wc);
		for (i = 0; i < wc.nbr_of_files; i++)
		{
			if (!first)
				ft_putchar_fd(' ', cmd->FD[1]);
			first = false;
			ft_printf_fd(cmd->FD[1], "%s", wc.wildcard[i]);
			free(wc.wildcard[i]);
		}
		free(wc.wildcard);
		closedir(dir);
	}
	if (wc_type == 3)
	{// Caso 3: .*
		wc.nbr_of_files = 0;
		while ((entry = readdir(dir)))
		{
			if (ft_strncmp(arg, entry->d_name, (ft_strlen(arg) - 1)) == 0)
				wc.nbr_of_files++;
		}
		ft_printf_fd(cmd->FD[1], "Number of files:%d\n"RESET, wc.nbr_of_files);
		closedir(dir);
		dir = opendir(".");
		wc.wildcard = malloc(sizeof(char *) * (wc.nbr_of_files));
		if (!wc.wildcard)
		{
			closedir(dir);
			ft_printf_fd(cmd->FD[2], "Error: Memory allocation failed\n");
			return;
		}
		i = 0;
		while ((entry = readdir(dir)))
		{
			if (ft_strncmp(arg, entry->d_name, (ft_strlen(arg) - 1)) == 0)
				wc.wildcard[i++] = ft_strdup(entry->d_name);
		}
		organize_wildcard(&wc);
		for (i = 0; i < wc.nbr_of_files; i++)
		{
			if (!first)
				ft_putchar_fd(' ', cmd->FD[1]);
			first = false;
			ft_printf_fd(cmd->FD[1], "%s", wc.wildcard[i]);
			free(wc.wildcard[i]);
		}
		free(wc.wildcard);
		closedir(dir);
	}
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
	int		i;
	int		j;
	char	*temp;
	bool	swapped;

	if (!wc || wc->nbr_of_files <= 1)
		return;
	swapped = true;
	i = -1;

	while (swapped != false)
	{
		swapped = false;
		j = -1;
		while (++j < wc->nbr_of_files - ++i - 1)
		{
			if (ft_strcasecmp(wc->wildcard[j], wc->wildcard[j + 1]) > 0)
			{
				temp = wc->wildcard[j];
				wc->wildcard[j] = wc->wildcard[j + 1];
				wc->wildcard[j + 1] = temp;
				swapped = true;
			}
		}
	}
}

#include <ctype.h> // For tolower()

static int ft_strcasecmp(const char *s1, const char *s2) // add to libft!!
{
	while (*s1 && *s2)
	{
		if (ft_tolower((unsigned char)*s1) != ft_tolower((unsigned char)*s2))
			return (ft_tolower((unsigned char)*s1) - ft_tolower((unsigned char)*s2));
		s1++;
		s2++;
	}
	return (ft_tolower((unsigned char)*s1) - ft_tolower((unsigned char)*s2));
}