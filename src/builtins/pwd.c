/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:14:07 by nuno              #+#    #+#             */
/*   Updated: 2025/05/30 02:14:58 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

// pwd_shell - Print the current working directory
void	pwd_shell(t_cmd *cmd, t_shell *shell)
{
	char	cwd[PATH_MAX];

	(void)cmd;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		shell->exit_value = 0;
	}
	else
	{
		perror("getcwd() error");
		shell->exit_value = 1;
	}
}
