#include "ft_parsing.h"

// function to set the name of the command from the arguments
char	*set_name(char **args)
{
	int		i;
	char	*str;
	char	*name;
	int		redir_flag;

	i = 0;
	str = NULL;
	if (!args)
		return (NULL);
	if (!args[0])
		return (NULL);
	redir_flag = check_for_redirs(args[0]);
	if (redir_flag > 0 )
	{
		if (!args[1])
			return (NULL);
		if (ft_strlen(args[0]) > 2)
			str = ft_strdup(args[1]);
		else
		{
			if (!args[2])
				return (NULL);
			str = ft_strdup(args[2]);
		}
	}
	else
		str = ft_strdup(args[0]);
	if (str == NULL)
		return (NULL);
	name = remove_all_quotes(str);
	return (name);
}

 