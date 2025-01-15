/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:24:35 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/15 21:10:22 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

// Check if the command is empty
bool is_empty(char *command)
{
    if (command[0] == '\0')
        return (true);
    return (false);
}

// Check if the command is a built-in command
bool is_builtin(char *cmd)
{
{	int		i;
	const char	**builtins;
	
	i = 0;
	builtins = (const char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
		return true;
	}
	return false;
}
 /*    if (ft_strcmp(command, "echo") == 0)
        return (true);
    if (ft_strcmp(command, "cd") == 0)
        return (true);
    if (ft_strcmp(command, "pwd") == 0)
        return (true);
    if (ft_strcmp(command, "export") == 0)
        return (true);
    if (ft_strcmp(command, "unset") == 0)
        return (true);
    if (ft_strcmp(command, "env") == 0)
        return (true);
    if (ft_strcmp(command, "exit") == 0)
        return (true);
    return (false); */
}


// Check if the command is valid
bool validate_command(char *command)
{
    if (is_empty(command))
        return (false);
    if (!is_builtin(command))
        return (false);
    return (true);
}
