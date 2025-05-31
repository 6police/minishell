#ifndef FT_INITS_H
# define FT_INITS_H

# include "../minishell.h"

// function to initialize the shell
t_shell	*init_shell(char **env);
t_shell	*init_shell_no_env(void);

#endif