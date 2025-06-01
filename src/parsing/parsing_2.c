/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:20:48 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 17:59:14 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to check if the tokens are invalid or if the syntax is incorrect
static bool	is_invalid_token_syntax(t_shell *shell)
{
	if (invalidate_tokens(shell->tokens) || !check_syntax(shell->tokens))
	{
		if (shell->tokens)
		{
			free_tokens(shell->tokens);
			shell->tokens = NULL;
		}
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error\n");
		return (true);
	}
	return (false);
}

// function to check if the number of pipes exceeds the limit
static bool	exceeds_pipe_limit(t_shell *shell)
{
	int	count;

	count = 0;
	while (shell->tokens && shell->tokens[count])
		count++;
	if (count >= MAX_PIPES)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: too many pipes (max %d)\n",
			MAX_PIPES);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		return (true);
	}
	return (false);
}

// function to set the pipe flag based on the tokens
static void	set_pipe_flag(t_shell *shell)
{
	if (shell->tokens[0] && shell->tokens[1])
		shell->is_pipe = true;
	else
		shell->is_pipe = false;
}

// function to parse the line and build commands
void	parse(t_shell *shell)
{
	int	sub;

	sub = 7;
	if (!shell->line[0])
		return ;
	shell->tokens = parse_line(shell->line, shell->separators[0], sub);
	if (is_invalid_token_syntax(shell))
		return ;
	if (exceeds_pipe_limit(shell))
		return ;
	if (!shell->tokens)
		return (ft_printf_fd(STDERR_FILENO, "minishell: syntax error\n"),
			(void)0);
	dollar_sign(shell);
	build_cmds(shell);
	set_pipe_flag(shell);
	if (!check_redir_validity(shell))
		invalidate_cmds(shell);
	if (shell->debug)
	{
		print_tokens(shell);
		ft_printf("pipe: %d\n", shell->is_pipe);
		print_all_commands(shell);
	}
}
