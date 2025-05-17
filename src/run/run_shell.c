
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
			parse(shell); // builds tokens and cmd structs

			// Optional: track if redirs were added during parsing or setup
			bool has_redirs = false;
			t_cmd *tmp = shell->cmds;
			while (tmp)
			{
				if (tmp->fd_struct)
					has_redirs = true;
				tmp = tmp->next;
			}

			int backup_stdin = -1;
			int backup_stdout = -1;

			if (has_redirs)
			{
				printf(RED"---/n---/n---/nHAS REDIRS/n---/n---/n"RESET);
				backup_stdin = dup(STDIN_FILENO);
				backup_stdout = dup(STDOUT_FILENO);
			}

			run_commands(shell);

			if (backup_stdin != -1)
			{
				dup2(backup_stdin, STDIN_FILENO);
				close(backup_stdin);
			}
			if (backup_stdout != -1)
			{
				dup2(backup_stdout, STDOUT_FILENO);
				close(backup_stdout);
			}

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
	t_cmd	*tmp;
	int backup_stdin;
	int backup_stdout;
	bool has_redirs;

	backup_stdin = -1;
	backup_stdout = -1;
	has_redirs = false;
	tmp = NULL;


	while (1)
	{
		// read the input
		shell->line = readline(PROMPT);
		if (!shell->line)
			exit_shell(&(t_cmd){0}, shell);
		else
		{
			add_history(shell->line); // add the line to history
			parse(shell); // parse the line and tokens
			
			tmp = shell->cmds;
			while (tmp)
			{
				if (tmp->fd_struct)
					has_redirs = true;
				tmp = tmp->next;
			}
			if (has_redirs)
			{
				backup_stdin = dup(STDIN_FILENO);
				backup_stdout = dup(STDOUT_FILENO);
			}

			run_commands(shell);
			if (backup_stdin != -1)
			{
				dup2(backup_stdin, STDIN_FILENO);
				close(backup_stdin);
			}
			if (backup_stdout != -1)
			{
				dup2(backup_stdout, STDOUT_FILENO);
				close(backup_stdout);
			}
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