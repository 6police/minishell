/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:08:04 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/30 20:15:09 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	// declare the shell
	ft_printf("Initializing shell\n");     // print initializing shell
	shell = ft_calloc(1, sizeof(t_shell)); // allocate memory for the shell
	if (!shell)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	// copy the environment
	ft_printf("Copying the environment\n");
    shell->env = copy_env(env);
    ft_printf("Environment copied\n");
	// initialize the file descriptors
	// initialize the commands
	ft_printf("Shell initialized\n");
    ft_print_minishell();
	return (shell);
}
