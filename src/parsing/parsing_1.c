
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
static void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens[i])
	{
		ft_printf(GREEN "token" RESET " [ " RED "%d" RESET " ] --> %s\n", i,
			shell->tokens[i]);
		i++;
	}
}
static bool	check_redir_validity(t_shell *shell)
{
	int	i;
	t_cmd *tmp;

	i = 0;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->fd_struct)
			if (!tmp->fd_struct->file)
			{
				ft_printf_fd(STDOUT_FILENO,
					"minishell: syntax error near unexpected token %s\n",
					tmp->name);
				return (false);
			}
		tmp = tmp->next;
	}
	return (true);
}

static void invalidate_cmds(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		tmp->is_valid = false;
		tmp = tmp->next;
	}
}


// parse the line according to priority
void	parse(t_shell *shell)
{
	int		sub;

	sub = 7; // the character to replace the separator
	shell->tokens = parse_line(shell->line, shell->separators[0], sub);
	if (!shell->tokens)
		return ;
	build_cmds(shell);
	if (shell->tokens[0] && shell->tokens[1])
		shell->is_pipe = true;
	else
		shell->is_pipe = false;
	if (shell->debug)
	{
		print_tokens(shell);
		ft_printf("pipe: %d\n", shell->is_pipe);
		print_all_commands(shell);
	}
	if (!check_redir_validity(shell))
		invalidate_cmds(shell);
}

// ver onde estao os redirections, e para onde e que manda.
