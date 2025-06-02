/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:56:36 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 16:54:07 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to check if the arguments passed to minishell are valid
static int	invalid_args(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putstr_fd(RED " Error: minishell does not accept arguments\n" RESET,
			2);
		return (1);
	}
	if (argc == 2 && ft_strncmp(argv[1], "-d", 3) != 0 && ft_strncmp(argv[1],
			"--debug", 8) != 0)
	{
		ft_putstr_fd(RED " Error: minishell does not accept arguments\n" RESET,
			2);
		return (1);
	}
	return (0);
}

// // Main function to initialize the shell and start the shelling process
int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	if (invalid_args(argc, argv))
		return (1);
	if (!env || !*env)
		shell = init_shell_no_env();
	else
		shell = init_shell(env);
	if (argc == 2)
		shell->debug = 1;
	else
		shell->debug = 0;
	shelling(shell);
	clean_exit(&shell);
	return (0);
}
