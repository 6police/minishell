/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:19:21 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 18:00:01 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to create a new t_cmd
t_cmd	*init_cmd(char *name, char **args)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (name)
		cmd->name = ft_strdup(name);
	else
		cmd->name = ft_strdup("kekers");
	cmd->args = args;
	cmd->path = NULL;
	cmd->is_builtin = false;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd_pipe[0] = -1;
	cmd->fd_pipe[1] = -1;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->fd[2] = -1;
	cmd->fd_struct = NULL;
	cmd->redirs = NULL;
	cmd->is_valid = false;
	cmd->builtin_func = NULL;
	cmd->pid = 0;
	cmd->has_heredoc = false;
	return (cmd);
}

// function to process the command arguments
void	cmd_processor_a(t_cmd *cmd, t_shell *shell, int i)
{
	int	redir_check;

	redir_check = 0;
	cmd->line = ft_strdup(shell->tokens[i]);
	redir_check = check_for_redirs(cmd->line);
	if (redir_check > 0)
	{
		cmd->redirs = split_into_redirs(cmd->line);
		cmd->fd_struct = assemble_redirs(cmd->redirs);
		if (cmd->fd_struct == NULL)
		{
			free_cmd(cmd);
			return ;
		}
		if (cmd->fd_struct->type == HERE_DOC_)
			cmd->has_heredoc = true;
	}
}

// function to check if a file exists and is a regular file
bool	check_file(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
		return (false);
	if (S_ISREG(st.st_mode) != 0)
		return (true);
	return (false);
}
