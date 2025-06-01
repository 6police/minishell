/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:05 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 17:22:21 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_run.h"

// function to run the shell in debug mode
void	run_shell_debug(t_shell *shell)
{
	while (1)
	{
		shell->line = readline(PROMPT RED "DEBUG" RESET EMOJI_HAMMER);
		if (!shell->line)
		{
			printf(EMOJI_BRAIN "exiting shell\n");
			exit_shell(&(t_cmd){0}, shell);
		}
		else
		{
			add_history(shell->line);
			parse(shell);
			run_commands(shell);
			if (shell->tokens)
			{
				free_tokens(shell->tokens);
				shell->tokens = NULL;
			}
			flush_commands(shell);
			free(shell->line);
			shell->is_pipe = false;
		}
	}
}

// wrapper for running the shell commands
void	minishellers(t_shell *shell)
{
	if (!shell->line || !(*shell->line))
		return ;
	add_history(shell->line);
	parse(shell);
	run_commands(shell);
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	flush_commands(shell);
	free(shell->line);
	shell->is_pipe = false;
}

// function to set up signal handling
void	shelling(t_shell *shell)
{
	setup_signals(shell);
	if (shell->debug)
		run_shell_debug(shell);
	else
		run_shell(shell);
}
