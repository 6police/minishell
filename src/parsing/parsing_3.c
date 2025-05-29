#include "ft_parsing.h"

// function to invalidate all commands in the shell
void	invalidate_cmds(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		tmp->is_valid = false;
		tmp = tmp->next;
	}
}

// function to check the syntax of the tokens
bool	check_syntax(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens || !tokens[0])
		return (false);
	while (tokens[i])
	{
		if ((i == 0 || tokens[i + 1] == NULL) && ft_strcmp(tokens[i], "|") == 0)
			return (false);
		if (ft_strcmp(tokens[i], "|") == 0 && tokens[i + 1]
			&& ft_strcmp(tokens[i + 1], "|") == 0)
			return (false);
		if (ft_strcmp(tokens[i], "|") == 0 && tokens[i + 1]
			&& ft_strlen(tokens[i + 1]) == 0)
			return (false);
		i++;
	}
	return (true);
}

// function that handles invalid tokens and frees them
bool	invalidate_tokens(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	if (!tokens || !(*tokens))
		return (true);
	while (tokens[i])
	{
		j = 0;
		if (tokens[i][0] == '\0')
			return (free_tokens(tokens), true);
		while (tokens[i][j])
		{
			if (tokens[i][j] == ' ')
				j++;
			else
				break ;
		}
		i++;
	}
	if (i == 0)
		return (free_tokens(tokens), true);
	return (false);
}
