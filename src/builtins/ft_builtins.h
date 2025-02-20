#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include "../minishell.h"

// cd.c
// cd builtin
void	cd_shell(t_cmd *cmd, t_env *env);

// echo.c
// echo builtin
void	echo_shell(t_cmd *cmd);

// pwd.c
// pwd builtin
void	pwd_shell(void);

// export.c
// export an environment variable
void	export_var(char *var, t_env *env);

// export env var without arguments
void	export_no_args(t_env *env);

// export env var with arguments
void    ft_export(char *var, char *value, t_env *env);

// export builtin
void	export_builtin(t_shell *shell);

// unset.c
// find an environment variable
t_env_var	*find_env_var(t_env *env, char *key);

// remove an environment variable
void	remove_env_var(t_env *env, char *key);

// unset an environment variable
void	unset_env_var(t_shell *shell, char *key);

// unset multiple environment variables
void	unset_vars(t_shell *shell, char **keys);

// exit.c
// exit builtin
void	exit_shell(t_shell *shell, int debug);

// execute_command.c
// execute the command

#endif