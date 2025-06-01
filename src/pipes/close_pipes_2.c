/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:41 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 18:09:28 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipes.h"

// Close pipe ends in child process after dup2
void	close_child_pipes(t_cmd *cmd)
{
	if (cmd->prev)
	{
		if (cmd->prev->fd_pipe[0] > 2)
		{
			close_safe(cmd->prev->fd_pipe[0]);
			cmd->prev->fd_pipe[0] = -1;
		}
		if (cmd->prev->fd_pipe[1] > 2)
		{
			close_safe(cmd->prev->fd_pipe[1]);
			cmd->prev->fd_pipe[1] = -1;
		}
	}
	if (cmd->fd_pipe[0] > 2)
	{
		close_safe(cmd->fd_pipe[0]);
		cmd->fd_pipe[0] = -1;
	}
	if (cmd->fd_pipe[1] > 2)
	{
		close_safe(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
}

// Close parent pipes after fork
void	close_parent_pipes(t_cmd *cmd)
{
	if (cmd->prev)
	{
		close_safe(cmd->prev->fd_pipe[0]);
		cmd->prev->fd_pipe[0] = -1;
	}
	if (cmd)
	{
		close_safe(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
}
