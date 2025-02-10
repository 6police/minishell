/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 01:03:47 by nuno              #+#    #+#             */
/*   Updated: 2025/02/10 18:34:11 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void execute_builtin(t_cmd *cmd, t_shell *shell);
static void execute_external(t_cmd *cmd, t_shell *shell);

void execute_command(t_shell *shell)
{
	// check if the command is a built-in command
	if (is_builtin(shell->cmds->cmd->name))
	{
		// execute the built-in command
		execute_builtin(shell);
	}
	else
	{
		// execute the external command
		execute_external(shell);
	}
}

static void execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->name, "cd") == 0)
		builtin_cd(cmd, shell->env);
	else if (ft_strcmp(cmd->name, "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->name, "export") == 0)
		builtin_export(cmd, shell->env);
	else if (ft_strcmp(cmd->name, "ls") == 0)
		builtin_ls(cmd);
	else
		execute_external(cmd, shell); // Handle external commands
}

static void execute_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->path, cmd->args, shell->env->envp) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(cmd->command, 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
	}
	else if (pid < 0)
	{
		ft_putstr_fd("minishell: fork failed\n", 2);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
