#ifndef FT_FREE_H
# define FT_FREE_H

# include "../minishell.h"

// free functions

// free one array
void free_array(char **array);

// close the file descriptors
void close_fds(t_fds *fds);

// free ONE redir
void free_redir(t_redir *redir);

// free ALL redirs
void free_redirs(t_redir **redirs);

// free ONE cmd
void free_cmd(t_cmd *cmd);

// free ALL cmds
void free_cmds(t_cmd **cmds);

// free ONE env var
void free_env_var(t_env_var *env_var);

// free the whole env
void free_env(t_env *env);

// free tokens
void free_tokens(char **tokens);

// free the shell
void free_shell(t_shell *shell, int debug);

//exit functions

// exit the shell
void clean_exit(t_shell *shell, int debug);

#endif