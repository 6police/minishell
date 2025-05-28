
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

static void	minishellers(t_shell *shell)
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

void	run_shell(t_shell *shell)
{
	char	*pwd;
	char	*aux;
	char	*cwd;

	pwd = NULL;
	while (1)
	{
		cwd = getcwd(NULL, 0);
		aux = ft_strjoin(BLUE, cwd);
		pwd = ft_strjoin(aux, GREEN "\n" PROMPT RESET);
		free(aux);
		free(cwd);
		shell->line = readline(pwd);
		free(pwd);
		if (shell->line && ft_strlen(shell->line) > MAX_LINE_LENGTH)
		{
			ft_printf_fd(STDERR_FILENO, TOO_LONG_LINE "%d\n", MAX_LINE_LENGTH);
			free(shell->line);
			continue ;
		}
		if (!shell->line)
			exit_shell(&(t_cmd){0}, shell);
		else
			minishellers(shell);
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