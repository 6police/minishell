
#include "ft_run.h"


void run_shell_debug(t_shell *shell)
{
	// setup the signal handler
	setup_signals();
	// for now it just starts the shell
	while (1)
	{
		// read the input
		shell->line = readline(PROMPT RED "DEBUG" RESET EMOJI_HAMMER);
		if (!shell->line)
		{
			printf(EMOJI_BRAIN "exiting shell\n");
			exit_shell(shell, 1);
		}
		if (shell->line)
		{
			add_history(shell->line);
			parse(shell, 1); // parse the line and tokens
			if (shell->tokens)
			{
				free_tokens(shell->tokens); // free the tokens
				printf(EMOJI_COOL "tokens cleared \n");
				free(shell->line);
				printf(EMOJI_COOL "line cleared \n");
			}
		}
	}
}

void run_shell(t_shell *shell)
{
	// setup the signal handler
	setup_signals();
	// for now it just starts the shell
	while (1)
	{
		// read the input
		shell->line = readline(PROMPT);
		if (!shell->line)
			exit_shell(shell, 0);
		if (shell->line)
		{
			parse(shell, 0); // parse the line and tokens
			if (shell->tokens)
			{
				printf(EMOJI_COOL "PLACEHOLDER \n something will happen here\n");
			}

			free_tokens(shell->tokens); // free the tokens
			free(shell->line);
		}
	}
}
