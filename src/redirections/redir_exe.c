/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:09:36 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 17:49:52 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

// function to close the specific pipes
static void	close_specific_pipe(t_cmd *cmd)
{
	if (cmd->prev)
	{
		close_safe(cmd->prev->fd_pipe[0]);
		close_safe(cmd->prev->fd_pipe[1]);
	}
}

// function to close all the redirections in a single command
void	close_cmd_redirs(t_cmd *cmd)
{
	t_fd	*tmp;

	if (!cmd->fd_struct)
		return ;
	tmp = cmd->fd_struct;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->fd != -1)
		{
			close(tmp->fd);
			tmp->fd = -1;
		}
		if (tmp->type == HERE_DOC_)
		{
			unlink(HERE_DOC);
			free(tmp->file);
			tmp->file = NULL;
		}
		tmp = tmp->next;
	}
	close_specific_pipe(cmd);
}

// function to update the last input and output redirections
static void	update_last_in_out(t_fd *redir, t_fd **in, t_fd **out)
{
	if (redir->type == REDIR_IN || redir->type == HERE_DOC_)
		*in = redir;
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		*out = redir;
}

// function to handle all redirections in a command
static int	handle_all_redirs(t_cmd *cmd, t_shell *shell, t_fd **last_in,
		t_fd **last_out)
{
	t_fd	*tmp;
	int		status;

	tmp = cmd->fd_struct;
	while (tmp)
	{
		status = handle_redirections(tmp, shell);
		if (status == 1 || status == 130)
			return (status);
		update_last_in_out(tmp, last_in, last_out);
		tmp = tmp->next;
		shell->exit_value = 0;
	}
	return (0);
}

// function to set up the redirections for a command
int	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	t_fd	*last_in;
	t_fd	*last_out;
	int		status;

	if (!cmd || !cmd->fd_struct)
		return (0);
	last_in = NULL;
	last_out = NULL;
	status = handle_all_redirs(cmd, shell, &last_in, &last_out);
	if (status != 0)
		return (status);
	if (last_in && last_in->fd != -1)
		cmd->fd[0] = last_in->fd;
	if (last_out && last_out->fd != -1)
		cmd->fd[1] = last_out->fd;
	return (0);
}
