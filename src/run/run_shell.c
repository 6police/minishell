
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
		else
		{
			add_history(shell->line);
			parse(shell); // parse the line and tokens
			print_all_commands(shell);
			if (shell->is_pipe)
			{
				if (make_pipes(shell) != 0)
					return ((void)ft_printf_fd(2, "Error: pipe failed\n"));
			}
			run_commands(shell);
			if (shell->is_pipe)
				close_all_pipes(shell);
			if (shell->tokens)
			{
				free_tokens(shell->tokens);
				shell->tokens = NULL;
			}
			flush_commands(shell);
			free(shell->line);
			shell->line = NULL;
			shell->is_pipe = false;
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
		else
		{
			add_history(shell->line);
			/* 			parse(shell); // parse the line and tokens
						if (shell->tokens)
							printf(EMOJI_COOL "PLACEHOLDER \n something will happen here\n");
						if (shell->cmds)
							run_commands(shell);
						free_cmds(shell->cmds); */
			ft_printf(RED "please use the debug mode to test the shell\n" RESET);
			free(shell->line);
		}
		free_tokens(shell->tokens); // free the tokens
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