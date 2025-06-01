/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:09 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 18:11:50 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_run.h"

// function to wait for all commands to finish
void	wait_commands(t_shell *shell)
{
	t_cmd	*tmp;
	int		status;

	if (!shell->cmds)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					ft_putstr_fd("\n", STDERR_FILENO);
				else if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				shell->exit_value = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				shell->exit_value = WEXITSTATUS(status);
		}
		tmp = tmp->next;
	}
	setup_signals(shell);
}

// function to run commands in the shell
void	run_commands(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;

	if (!shell || !shell->cmds)
		return ;
	tmp = shell->cmds;
	if (shell->is_pipe && make_pipes(tmp, shell) == 1)
		return ;
	while (tmp)
	{
		i = setup_redirections(tmp, shell);
		if (i == 1 || i == 130)
			return (shell->exit_value = i, (void)i);
		if (tmp->is_valid)
			processor(tmp, shell);
		close_cmd_redirs(tmp);
		tmp = tmp->next;
	}
	if (shell->is_pipe)
		close_pipes(shell->cmds);
	if (shell->wait)
		wait_commands(shell);
}
