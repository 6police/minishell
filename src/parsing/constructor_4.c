/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:19:44 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:19:48 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to assemble a command with a valid path
void	assemble_cmd_path(t_cmd *cmd, char **args)
{
	cmd->path = ft_strdup(cmd->name);
	cmd->is_valid = true;
	cmd->args = copy_array(args);
	cmd->builtin_func = execute_external;
}

// function to check if the command is a valid external command
void	assemble_cmd(t_cmd *cmd, char **args, t_shell *shell)
{
	char	*path;

	path = checkforpath(cmd->name, shell->env);
	if (path)
	{
		cmd->path = path;
		cmd->is_valid = true;
		cmd->args = copy_array(args);
		cmd->builtin_func = execute_external;
	}
	else
	{
		cmd->path = NULL;
		cmd->is_valid = false;
		cmd->args = NULL;
		cmd->builtin_func = NULL;
	}
}
