/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_no_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:13:54 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 19:53:49 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_run.h"

// function to run a command without pipes

// function to handle invalid commands
static void	handle_invalid_cmd(t_cmd *cmd, t_shell *shell)
{
	ft_printf_fd(STDERR_FILENO, "%s command: not found\n", cmd->name);
	shell->exit_value = 127;
}

// function to execute the child process
static void	child_process_exec(t_cmd *cmd, t_shell *shell)
{
	eggxecutor(cmd, shell, 1);
	cmd->builtin_func(cmd, shell);
	clean_exit(&shell);
}

// function to run an external command
static void	run_external_cmd(t_cmd *cmd, t_shell *shell)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	shell->wait = true;
	if (!cmd->is_valid)
		return (handle_invalid_cmd(cmd, shell), (void)0);
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
		shell->exit_value = 1;
		return ;
	}
	if (cmd->pid == 0)
		child_process_exec(cmd, shell);
}

// function to run a built-in command
static void	run_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	int saved_stdout;
	int saved_stdin;
	t_fd *redir;

	saved_stdout = (STDOUT_FILENO);
	saved_stdin = (STDIN_FILENO);
	redir = cmd->fd_struct;
	while (redir)
	{
		if (redir->fd != -1)
		{
			if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
				dup2(redir->fd, STDOUT_FILENO);
			else if (redir->type == REDIR_IN || redir->type == HERE_DOC_)
				dup2(redir->fd, STDIN_FILENO);
		}
		redir = redir->next;
	}
	shell->wait = false;
	cmd->builtin_func(cmd, shell);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

// function to run a command without pipes
void	run_no_pipe(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell || shell->is_pipe)
		return ;
	if (!cmd->is_builtin)
		run_external_cmd(cmd, shell);
	else
		run_builtin_cmd(cmd, shell);
}
