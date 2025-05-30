/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:31:35 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:31:36 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"

static void	print_fds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (cmd->fd[i] == -1)
			ft_printf("[" RED "%d" RESET "] ", -1);
		else
			ft_printf("[" GREEN "%d" RESET "] ", cmd->fd[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_command(t_cmd *cmd)
{
	ft_printf(RED " --- NEW COMMAND ---\n" RESET);
	if (cmd->redirs)
		print_redirs(cmd->redirs);
	ft_printf("%d\n", is_command_path(cmd->name));
	ft_printf("name: %s\n", cmd->name);
	print_args(cmd);
	ft_printf("path: %s\n", cmd->path);
	print_cmd_redirs(cmd);
	print_fds(cmd);
	ft_printf("has_heredoc: %d\n", cmd->has_heredoc);
	ft_printf("builtin_func: %p\n", cmd->builtin_func);
	ft_printf("\n REDIRS \n");
	if (cmd->next)
		ft_printf("next: %s\n", cmd->next->name);
	if (cmd->prev)
		ft_printf("prev: %s\n", cmd->prev->name);
	ft_printf(" --- END ---\n" RESET);
	ft_printf("\n");
}

// print all the commands
void	print_all_commands(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		print_command(cmd);
		cmd = cmd->next;
	}
}
