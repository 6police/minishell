#include "ft_free.h"

// free the whole env
void	free_env(t_env *env)
{
	t_env_var	*tmp;
	t_env_var	*next;

	if (!env)
		return ;
	tmp = env->head;
	while (tmp)
	{
		next = tmp->next;
		free_env_var(tmp);
		tmp = next;
	}
	free(env);
}

// free tokens
void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens || !(*tokens))
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

// free the shell
void	free_shell(t_shell **shell)
{
	if (!shell || !(*shell))
		return ;
	if ((*shell)->line && *(*shell)->line)
		free((*shell)->line);
	if ((*shell)->cmds && (*shell)->cmds->name)
		free_cmds((*shell)->cmds);
	if ((*shell)->env && (*shell)->env->head)
		free_env((*shell)->env);
	if ((*shell)->tokens)
		free_tokens((*shell)->tokens);
	if ((*shell)->separators && *(*shell)->separators)
		free((*shell)->separators);
	if ((*shell)->current_heredoc_file)
		free((*shell)->current_heredoc_file);
	free(*shell);
}

void	flush_commands(t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*next;

	if (!shell->cmds)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		next = tmp->next;
		free_cmd(tmp);
		tmp = next;
	}
	shell->cmds = NULL;
	shell->is_pipe = false;
}

// exit the shell
void	clean_exit(t_shell **shell)
{
	int	status;

	status = (*shell)->exit_value;
	if ((*shell)->debug)
	{
		ft_printf(RED "exiting shell with status: %d\n" RESET, status);
		printf(EMOJI_BRAIN "exiting shell\n\n");
	}
	if (!(*shell)->is_child)
		ft_printf_fd(STDERR_FILENO, "exit\n - K THX BYE - \n");
	if (shell && *shell)
		free_shell(shell);
	clear_history();
	exit(status);
}
