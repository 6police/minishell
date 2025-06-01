/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_no_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:13:54 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 17:19:47 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_run.h"

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
	if (cmd->is_valid)
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
