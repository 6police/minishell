/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:19:31 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:19:42 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to add a t_cmd to the t_cmd linked list
void	add_last_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
		*head = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

// function to create a new command structure
void	check_builtin(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd->name, "env") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "exit") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "export") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "unset") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "pwd") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "cd") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "echo") == 0)
		cmd->is_builtin = true;
}

// function to build a command structure
void	build_cmd(t_cmd *cmd, char **args, t_shell *shell)
{
	if (is_command_path(cmd->name))
		return (assemble_cmd_path(cmd, args));
	else
		return (assemble_cmd(cmd, args, shell));
}

// function to build a builtin command
void	build_builtin(t_cmd *cmd, char **args)
{
	cmd->is_valid = true;
	if (ft_strcmp(cmd->name, "cd") == 0)
		cmd->builtin_func = cd_shell;
	if (ft_strcmp(cmd->name, "echo") == 0)
		cmd->builtin_func = echo_shell;
	if (ft_strcmp(cmd->name, "pwd") == 0)
		cmd->builtin_func = pwd_shell;
	if (ft_strcmp(cmd->name, "export") == 0)
		cmd->builtin_func = export_builtin;
	if (ft_strcmp(cmd->name, "unset") == 0)
		cmd->builtin_func = unset_vars;
	if (ft_strcmp(cmd->name, "exit") == 0)
		cmd->builtin_func = exit_shell;
	if (ft_strcmp(cmd->name, "env") == 0)
		cmd->builtin_func = env;
	cmd->args = copy_array(args + 1);
}
