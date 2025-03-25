/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_extr_or_bi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 01:03:47 by nuno              #+#    #+#             */
/*   Updated: 2025/03/13 19:53:26 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

void	check_command(t_cmd *cmd, t_shell *shell)
{
	// check if the command is a built-in command
	if (!shell)
		return ;
	if (cmd->is_builtin == false)
		execute_external(cmd, shell);
	else

		printf("hmmm\n"); //substitute for execute Builtin
}
