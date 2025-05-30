/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:31:37 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:31:38 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEBUG_H
# define FT_DEBUG_H

# include "../minishell.h"

// Print the enviroment variables
void	print_env(t_env *env, t_cmd *cmd);

// Print the exported enviroment variables
void	print_export(t_env *env, t_cmd *cmd);

// print the redirections
void	print_redirs(char **redirs);

// print the command arguments
void	print_args(t_cmd *cmd);

// print the command redirections
void	print_cmd_redirs(t_cmd *cmd);

// Print the command
void	print_command(t_cmd *cmd);

// Print all the commands
void	print_all_commands(t_shell *shell);

#endif