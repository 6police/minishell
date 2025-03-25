/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:56:43 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/10 18:28:46 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	if (argc > 2)
	{
		ft_putstr_fd(EMOJI_CROSS EMOJI_CROSS " Error: minishell does not accept arguments\n",
			2);
		return (1);
	}
	shell = init_shell(env);
	if (argc == 2)
	{
		if ((ft_strncmp(argv[1], "-d", 2) == 0) || (ft_strncmp(argv[1],
					"--debug", 7) == 0))
			shell->debug = 1;
		else
		{
			ft_putstr_fd(EMOJI_CROSS EMOJI_CROSS " Error: minishell does not accept arguments\n",
				2);
			return (1);
		}
	}
	else
		shell->debug = 0;
	shelling(shell);
	return (0);
}
