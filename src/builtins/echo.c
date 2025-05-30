/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:58:45 by nuno              #+#    #+#             */
/*   Updated: 2025/05/30 01:58:45 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

static void	echoing(t_cmd *cmd, bool will_remove_nl);

void	echo_shell(t_cmd *cmd, t_shell *shell)
{
	bool	will_remove_nl;

	will_remove_nl = false;
	if (!cmd || !cmd->args)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		shell->exit_value = 0;
		return ;
	}
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "-n") == 0)
		will_remove_nl = true;
	echoing(cmd, will_remove_nl);
	if (will_remove_nl == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	shell->exit_value = 0;
}

static void	echoing(t_cmd *cmd, bool will_remove_nl)
{
	int	i;

	i = -1;
	if (will_remove_nl == true)
		i++;
	while (cmd->args[++i])
	{
		ft_printf_fd(STDOUT_FILENO, "%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}
