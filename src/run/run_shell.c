
#include "ft_run.h"

void	run_shell_debug(t_shell *shell)
{
	// for now it just starts the shell
	while (1)
	{
		// read the input
		shell->line = readline(PROMPT RED "DEBUG" RESET EMOJI_HAMMER);
		if (!shell->line)
		{
			printf(EMOJI_BRAIN "exiting shell\n");
			exit_shell(&(t_cmd){0}, shell);
		}
		if (shell->line)
		{
			add_history(shell->line);
			parse(shell); // parse the line and tokens
			if (shell->tokens)
			{
				free_tokens(shell->tokens); // free the tokens
				ft_printf(EMOJI_COOL "tokens cleared \n");
			}
			if (shell->cmds)
			{
				run_commands(shell);
				free_cmds(shell->cmds);
				ft_printf(EMOJI_COOL "commands cleared \n");
			}
			free(shell->line);
			ft_printf(EMOJI_COOL "line cleared \n");
		}
	}
}

void	run_shell(t_shell *shell)
{
	// for now it just starts the shell
	while (1)
	{
		// read the input
		shell->line = readline(PROMPT);
		if (!shell->line)
			exit_shell(&(t_cmd){0}, shell);
		if (shell->line)
		{
			parse(shell); // parse the line and tokens
			if (shell->tokens)
			{
				printf(EMOJI_COOL "PLACEHOLDER \n something will happen here\n");
			}
			free_tokens(shell->tokens); // free the tokens
			if (shell->cmds)
			{
				run_commands(shell);
				free_cmds(shell->cmds);
			}
			free(shell->line);
		}
	}
}

void	shelling(t_shell *shell)
{
	setup_signals();
	if (shell->debug)
		run_shell_debug(shell);
	else
		run_shell(shell);
}