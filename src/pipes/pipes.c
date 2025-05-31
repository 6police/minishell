/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:52 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 19:29:56 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipes.h"

// function to create pipes for the commands
int	make_pipes(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;

	if (!cmd || shell->is_pipe == false)
		return (0);
	tmp = cmd;
	while (tmp->next)
	{
		if (pipe(tmp->fd_pipe) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: pipe failed\n");
			shell->exit_value = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// function to manage pipes
void	manage_pipes(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell->is_pipe)
		return ;
	if (cmd->prev)
		dup2(cmd->prev->fd_pipe[0], STDIN_FILENO);
	if (cmd->next)
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
}
