#include "ft_builtins.h"

static bool	is_there_quotes(char *str);
static void	do_echo(char *arg, int wild_card_type);
static bool	check_wildcard(char *arg);
static void	do_wildcard(char *arg);
static int	check_wildcard_type(char *str);
static bool	is_there_quotes(char *str);
static void	print_entry(char *name, bool *first);


void	echo_shell(t_cmd *cmd, t_shell *shell)
{
	int	newline;
	int	i;

	(void)shell;
	newline = 1;
	i = -1;
	if (!cmd || !cmd->args)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "-n") == 0)
		newline = 0;
	while (cmd->args[++i])
	{
		if (check_wildcard(cmd->args[i]))
			do_wildcard(cmd->args[i]);
		else 
			do_echo(cmd->args[i], 0);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
static void	do_echo(char *arg, int wild_card_type)
{
	DIR				*dir;
	struct dirent	*entry;
	bool			first;
	char			*pattern;
	size_t			pattern_len;
	size_t			entry_len;

	first = true;
	dir = opendir(".");
	if (!dir)
		return;

	if (wild_card_type == 0)
	{  // No wildcard - print raw argument
		ft_putstr_fd(arg, STDOUT_FILENO);
		closedir(dir);
		return;
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.') // Skip hidden files
			continue;
		if (wild_card_type == 1) // Case 1: *
			print_entry(entry->d_name, &first);
		else if (wild_card_type == 2) // Case 2: *.ext
		{
			pattern = arg + 1;
			pattern_len = ft_strlen(pattern);
			entry_len = ft_strlen(entry->d_name);
			if (entry_len >= pattern_len && 
				!ft_strncmp(entry->d_name + (entry_len - pattern_len), pattern, pattern_len))
				print_entry(entry->d_name, &first);
		}
		else if (wild_card_type == 3) // Case 3: prefix*
		{
			pattern = strndup(arg, ft_strlen(arg) - 1); // Remove last *
			pattern_len = ft_strlen(pattern);
			if (!ft_strncmp(entry->d_name, pattern, pattern_len))
				print_entry(entry->d_name, &first);
			free(pattern);
		}
		else if (wild_card_type == 4) // Case 4: *substr*
		{
			pattern = strndup(arg + 1, ft_strlen(arg) - 2); // Remove * at both ends
			if (strstr(entry->d_name, pattern))
				print_entry(entry->d_name, &first);
			free(pattern);
		}
		entry = readdir(dir);
	}
	closedir(dir); //gotta make a ft_strnudp
}

static void	print_entry(char *name, bool *first)
{
	if (!*first)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(name, STDOUT_FILENO);
	*first = false;
}

static bool	check_wildcard(char *arg)
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

static void	do_wildcard(char *arg)
{
	int	wild_card_type;
	
	wild_card_type = 0;
	if (is_there_quotes(arg) == true)
		return ;
	wild_card_type = check_wildcard_type(arg);
	do_echo(arg, wild_card_type);
}

static bool	is_there_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
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