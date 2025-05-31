/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:17:18 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:17:21 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_H
# define FT_FREE_H

# include "../minishell.h"

// free functions

// free one array
void	free_array(char **array);

// free the redirections
void	free_redir_structs(t_fd *redirs);

// free ONE cmd
void	free_cmd(t_cmd *cmd);

// free ALL cmds
void	free_cmds(t_cmd *cmds);

// free ONE env var
void	free_env_var(t_env_var *env_var);

// free the whole env
void	free_env(t_env *env);

// free tokens
void	free_tokens(char **tokens);

// free the shell
void	free_shell(t_shell **shell);

// exit functions
void	flush_commands(t_shell *shell);

// exit the shell
void	clean_exit(t_shell **shell);

// free split
void	free_split(char **split);

#endif