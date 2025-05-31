/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:15:13 by nuno              #+#    #+#             */
/*   Updated: 2025/05/30 02:15:14 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include "../minishell.h"

// cd.c
// cd builtin
void		cd_shell(t_cmd *cmd, t_shell *shell);

// echo.c
// echo builtin
void		echo_shell(t_cmd *cmd, t_shell *shell);

// pwd.c
// pwd builtin
void		pwd_shell(t_cmd *cmd, t_shell *shell);

// export.c
// export an environment variable
void		export_var(char *var, t_env *env);

// export env var without arguments
void		export_no_args(t_env *env, t_cmd *cmd);

// export env var with arguments
void		ft_export(char *var, char *value, t_env *env);

// export builtin
void		export_builtin(t_cmd *cmd, t_shell *shell);

// unset.c
// find an environment variable
t_env_var	*find_env_var(t_env *env, char *key);

// remove an environment variable
void		remove_env_var(t_env *env, char *key);

// unset an environment variable
void		unset_env_var(t_shell *shell, char *key);

// unset multiple environment variables
void		unset_vars(t_cmd *cmd, t_shell *shell);

// env.c
// print the environment variables
void		env(t_cmd *cmd, t_shell *shell);

// exit.c
// exit builtin
void		exit_shell(t_cmd *cmd, t_shell *shell);

// execve.c
// exeternal_cmd.c
void		execute_external(t_cmd *cmd, t_shell *shell);
#endif