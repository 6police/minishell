
#include "ft_parsing.h"

// parsing the line into tokens
char	**parse_line(char *line, int letter, int sub)
{
	char	**tokens;

	if (!line)
		return (NULL);
	tokens = ft_parse_split(line, letter, sub);
	if (!tokens)
		return (NULL);
	return (tokens);
}

// print the tokens
void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell || !shell->tokens)
		return ;
	if (shell->tokens[0] == NULL)
	{
		ft_printf(RED "No tokens found\n" RESET);
		return ;
	}
	while (shell->tokens[i])
	{
		ft_printf(GREEN "token" RESET " [ " RED "%d" RESET " ] --> %s\n", i,
			shell->tokens[i]);
		i++;
	}
}

// check if the redirection is valid
bool	check_redir_validity(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->fd_struct != NULL)
		{
			if (tmp->fd_struct->file == NULL)
			{
				ft_printf(RED REDIR_FAILURE " %s\n" RESET, tmp->name);
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}
