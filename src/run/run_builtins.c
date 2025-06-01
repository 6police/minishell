/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:15:56 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 17:17:44 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_run.h"

// function to apply redirections from the redirection structure
static void	apply_redirections(t_fd *redir)
{
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
}

// function to close fds in the redirection structure
static void	close_filedes(t_fd *redir)
{
	while (redir)
	{
		if (redir->fd != -1)
		{
			close(redir->fd);
			redir->fd = -1;
		}
		redir = redir->next;
	}
}

// function to run a builtin command
void	run_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	int		saved_stdout;
	int		saved_stdin;
	t_fd	*redir;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	redir = cmd->fd_struct;
	apply_redirections(redir);
	shell->wait = false;
	cmd->builtin_func(cmd, shell);
	restore_std_fds(saved_stdout, saved_stdin);
	redir = cmd->fd_struct;
	close_filedes(redir);
}
