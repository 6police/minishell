/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:58:45 by nuno              #+#    #+#             */
/*   Updated: 2025/06/02 20:35:35 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

static void	echoing(t_cmd *cmd, bool will_remove_nl);
static bool	ft_has_nl(char *arg);
static bool	is_all_ns(char *str);

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
	if (cmd->args[0] && ft_has_nl(cmd->args[0]))
		will_remove_nl = true;
	echoing(cmd, will_remove_nl);
	if (will_remove_nl == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	shell->exit_value = 0;
}

static void	echoing(t_cmd *cmd, bool will_remove_nl)
{
	int		i;
	bool	was_n;

	i = 0;
	was_n = true;
	if (will_remove_nl == true)
		i++;
	while (cmd->args[i])
	{
		if (is_all_ns(cmd->args[i]) && was_n)
		{
			i++;
			continue ;
		}
		else
		{
			ft_printf_fd(STDOUT_FILENO, "%s", cmd->args[i]);
			if (cmd->args[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			was_n = false;
		}
		i++;
	}
}

static bool	ft_has_nl(char *arg)
{
	if (!arg || !arg[0])
		return (false);
	if (arg[0] == '-')
	{
		if (is_all_ns(arg))
			return (true);
	}
	return (false);
}

static bool	is_all_ns(char *str)
{
	int	i;

	if (!str || str[0] == '\0' || str[0] != '-')
		return (false);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}
