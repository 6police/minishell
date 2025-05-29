#include "ft_parsing.h"

// function to set the name of the command from the arguments

// function to check if the argument is a redirection without an argument
static char	*get_redir_name(char **args)
{
	if (!args[1])
		return (NULL);
	if (ft_strlen(args[0]) > 2)
		return (ft_strdup(args[1]));
	if (!args[2])
		return (NULL);
	return (ft_strdup(args[2]));
}

// function to assign the name of the command from the arguments
char	*set_name(char **args)
{
	char	*str;
	char	*name;
	int		redir_flag;

	if (!args || !args[0])
		return (NULL);
	redir_flag = check_for_redirs(args[0]);
	if (redir_flag > 0)
		str = get_redir_name(args);
	else
		str = ft_strdup(args[0]);
	if (!str)
		return (NULL);
	name = remove_all_quotes(str);
	return (name);
}
