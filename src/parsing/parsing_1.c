
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
static bool	check_redir_validity(t_shell *shell)
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

static void	invalidate_cmds(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		tmp->is_valid = false;
		tmp = tmp->next;
	}
}

static bool invalidate_tokens(char **tokens)
{
	int i;
	int j;
	
	i= 0;
	if (!tokens || !(*tokens))
		return (true);
	while (tokens[i])
	{
		j = 0;
		if (tokens[i][0] == '\0')
		{
			free_tokens(tokens);
			return (true);
		}
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
	{
		free_tokens(tokens);
		return (true);
	}
	return (false);
}

// parse the line according to priority
void	parse(t_shell *shell)
{
	int	sub;
	int token_count;

	token_count = 0;
	sub = 7; // the character to replace the separator
	shell->tokens = parse_line(shell->line, shell->separators[0], sub);
	if(invalidate_tokens(shell->tokens))
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error\n");
		return ;
	}
	while(shell->tokens && shell->tokens[token_count])
		token_count++;
	if (token_count >= MAX_PIPES)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: too many pipes (max %d)\n", MAX_PIPES);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		return ;
	}
	if (!shell->tokens)
		return ;
	dollar_sign(shell, token_count);
	build_cmds(shell);
	if (shell->tokens[0] && shell->tokens[1])
		shell->is_pipe = true;
	else
		shell->is_pipe = false;
	if (!check_redir_validity(shell))
		invalidate_cmds(shell);
	if (shell->debug)
	{
		print_tokens(shell);
		ft_printf("pipe: %d\n", shell->is_pipe);
		print_all_commands(shell);
	}
}

// ver onde estao os redirections, e para onde e que manda.
