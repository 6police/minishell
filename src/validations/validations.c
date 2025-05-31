/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:18:34 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 21:28:29 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_validations.h"

// Check if the command is empty
bool	is_empty(char *command)
{
	if (command[0] == '\0')
		return (true);
	return (false);
}

// Check if the command is a built-in command
bool	is_builtin(char *cmd)
{
	int			i;
	const char	**builtins;

	i = 0;
	builtins = (const char *[]){"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (true);
	}
	return (false);
}

// Check if the command is valid
bool	validate_command(char *command)
{
	if (is_empty(command))
		return (false);
	if (!is_builtin(command))
		return (false);
	return (true);
}

// bool ft_validation(t_cmd *cmd, t_shell *shell)
// {
// 	char *path;

// 	path = NULL;
// 	if (!cmd || !cmd->name)
// 		return (false);
// 	if (cmd->is_builtin)
// 		return (true);
// 	if (is_empty(cmd->name))
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: command not found\n");
// 		return (false);
// 	}
// 	path = checkforpath(cmd->name, shell->env);
// 	if (!path)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: command not found: %s\n", cmd->name);
// 		return (false);
// 	}
// 	free(path);
// 	return (true);
// }

bool is_all_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			return (false);
		i++;
	}
	return (true);
}