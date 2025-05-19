
#include "ft_run.h"

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

void	run_shell(t_shell *shell)
{
	while (1)
	{
		// read the input
		shell->line = readline(PROMPT);
		if (shell->line && ft_strlen(shell->line) > MAX_LINE_LENGTH)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: input too long (max %d chars)\n", MAX_LINE_LENGTH);
			free(shell->line);
			continue;
		}
		if (!shell->line)
			exit_shell(&(t_cmd){0}, shell);
		else
		{
			add_history(shell->line); // add the line to history
			parse(shell); // parse the line and tokens
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
	
void	shelling(t_shell *shell)
{
	setup_signals();
	if (shell->debug)
		run_shell_debug(shell);
	else
		run_shell(shell);
}