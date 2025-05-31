/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:15:08 by nuno              #+#    #+#             */
/*   Updated: 2025/05/31 17:15:01 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

void	exit_shell(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	if (!shell->is_child)
		shell->exit_value = 0;
	clean_exit(&shell);
}
