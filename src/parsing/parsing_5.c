#include "ft_parsing.h"

// function to set the name of the command from the arguments
char	*set_name(char **args)
{
	int		i;
	int		j;
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
	if (redir_flag > 0)
	{
		while (args[i] != NULL)
		{
			j = 0;
			while (args[i][0] != '\0' && (args[i][0] == '<'
					|| args[i][0] == '>') && ft_strlen(args[i]) <= 1)
				i++;
			if (args[i][j] != '\0' && ft_strlen(args[i]) >= 2)
			{
				while (args[i][j] == '<' || args[i][j] == '>')
					j++;
				str = ft_substr(args[i], j, ft_strlen(args[i]) - j);
				if (str == NULL)
					return (NULL);
				break ;
			}
			i++;
		}
	}
	else
		str = ft_strdup(args[0]);
	if (str == NULL)
		return (NULL);
	name = remove_all_quotes(str);
	return (name);
}