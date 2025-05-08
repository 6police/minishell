#include "ft_run.h"

/* static void	pipe_builtin(t_cmd *cmd, t_shell *shell);

void	run_commands(t_shell *shell)
{
	t_cmd	*tmp;

	if (!shell->cmds)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->fd_struct)
			setup_redirections(tmp, shell);
		tmp = tmp->next;
	}
	tmp = shell->cmds;
	if (shell->is_pipe)
		make_pipes(tmp, shell);
	while (tmp)
	{
		if (tmp->is_valid)
			pipe_builtin(tmp, shell);
		tmp = tmp->next;
	}
} */
/* 
void	pipe_builtin(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*walker;
	int		status;

	status = 0;
	tmp = cmd;
	if (shell->is_pipe)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			shell->is_child = true;
			if (tmp->prev)
			{
				dup2(tmp->prev->fd[0], STDIN_FILENO);
				close(tmp->prev->fd[0]);
			}
			if (tmp->next)
			{
				dup2(tmp->fd[1], STDOUT_FILENO);
				close(tmp->fd[1]);
			}
			walker = shell->cmds;
			while (walker)
			{
				if (walker->fd[0] != -1)
					close(walker->fd[0]);
				if (walker->fd[1] != -1)
					close(walker->fd[1]);
				walker = walker->next;
			}
			// --- EXECUTION ---
			tmp->builtin_func(tmp, shell);
			clean_exit(&shell);
		}
		else if (tmp->pid < 0)
		{
			ft_printf_fd(tmp->fd[1], "minishell: fork failed\n");
			shell->exit_value = 1;
		}
		else
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				shell->exit_value = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				shell->exit_value = WEXITSTATUS(status);
			if (tmp->prev && tmp->prev->fd[0] != -1)
				close(tmp->prev->fd[0]);
			if (tmp->fd[1] != -1)
				close(tmp->fd[1]);
		}
	}
	else
		cmd->builtin_func(tmp, shell);
} */

void	pipe_builtin(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*walker;

	if (!shell->is_pipe)
	{
		cmd->builtin_func(cmd, shell);
		return;
	}

	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
		shell->exit_value = 1;
		return;
	}

	if (cmd->pid == 0)
	{
		// --- CHILD ---
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		shell->is_child = true;

		if (cmd->prev && cmd->prev->fd[0] != -1)
		{
			if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
			{
				perror("dup2 in");
				clean_exit(&shell);
			}
		}

		if (cmd->next && cmd->fd[1] != -1)
		{
			if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2 out");
				clean_exit(&shell);
			}
		}

		// Close all pipe fds to avoid leaks or zombie fds
		for (walker = shell->cmds; walker; walker = walker->next)
		{
			if (walker->fd[0] != -1)
				close(walker->fd[0]);
			if (walker->fd[1] != -1)
				close(walker->fd[1]);
		}

		// Builtin execution
		cmd->builtin_func(cmd, shell);
		clean_exit(&shell);
	}
	else
	{
		// --- PARENT ---

		// Close parent's copies of pipe ends
		if (cmd->prev && cmd->prev->fd[0] != -1)
		{
			close(cmd->prev->fd[0]);
			cmd->prev->fd[0] = -1;
		}

		if (cmd->fd[1] != -1)
		{
			close(cmd->fd[1]);
			cmd->fd[1] = -1;
		}

		// DO NOT wait here; let run_commands() wait for all later
	}
}

void	run_commands(t_shell *shell)
{
	t_cmd	*tmp;

	if (!shell->cmds)
		return ;

	// Setup redirs
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->fd_struct)
			setup_redirections(tmp, shell);
		tmp = tmp->next;
	}

	// Setup pipes
	tmp = shell->cmds;
	if (shell->is_pipe)
		make_pipes(tmp, shell);

	// Launch commands
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->is_valid)
			pipe_builtin(tmp, shell);
		tmp = tmp->next;
	}

	// Wait for all children
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->pid > 0)
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}

