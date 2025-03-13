#include "ft_free.h"

// free one array
void free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// close the file descriptors
void close_fds(t_fds *fds)
{
    if (fds->fd_in != 0)
        close(fds->fd_in);
    if (fds->fd_out != 1)
        close(fds->fd_out);
    if (fds->fd_err != 2)
        close(fds->fd_err);
    if (fds->fd_here_doc != -1)
        close(fds->fd_here_doc);
    free(fds);
}

// free ONE redir
void free_redir(t_redir *redir)
{
    if (redir)
        free(redir);
}

// free ALL redirs
void free_redirs(t_redir **redirs)
{
    int i;

    i = 0;
    while (redirs[i])
    {
        free_redir(redirs[i]);
        i++;
    }
    free(redirs);
}

// free ONE cmd
void free_cmd(t_cmd *cmd)
{
    if (cmd->name)
        free(cmd->name);
    if (cmd->args)
        free_array(cmd->args);
    if (cmd->path)
        free(cmd->path);
    if (cmd->redirs)
        free_redirs(cmd->redirs);
    free(cmd);
}

// free ALL cmds
void free_cmds(t_cmd *cmds)
{
    int i;

    i = 0;
    while (cmds->next)
    {
        free_cmd(cmds);
        cmds = cmds->next;
    }
    free(cmds);
}

// free ONE env var
void free_env_var(t_env_var *env_var)
{
    if (env_var->key)
        free(env_var->key);
    if (env_var->value)
        free(env_var->value);
    free(env_var);
}

// free the whole env
void free_env(t_env *env)
{
    t_env_var *tmp;
    t_env_var *next;

    tmp = env->head;
    while (tmp)
    {
        next = tmp->next;
        free_env_var(tmp);
        tmp = next;
    }
    free(env);
}

// free tokens
void free_tokens(char **tokens)
{
    int i;

    i = 0;
    if (!tokens)
        return;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

// free the shell
void free_shell(t_shell *shell, int debug)
{
    if (shell->line)
    {
        if (debug)
            printf("freeing line\n");
        free(shell->line);
    }
    if (shell->cmds)
    {
        if (debug)
            printf("freeing cmds\n");
        free_cmds(shell->cmds);
    }
    if (shell->env)
    {
        if (debug)
            printf("freeing env\n");
        free_env(shell->env);
    }
    if (shell->fds)
    {
        if (debug)
            printf("freeing fds\n");
        close_fds(shell->fds);
    }
    if (shell->tokens)
    {
        if (debug)
            printf("freeing tokens\n");
        free_tokens(shell->tokens);
    }
    if (debug)
        printf("freeing shell\n");
    free(shell);
}

// exit the shell
void clean_exit(t_shell *shell, int debug)
{
	int status;

	status = shell->status;

	if (debug)
		printf(EMOJI_BRAIN "exiting shell\n");

	if (shell)
		free_shell(shell, debug);
	clear_history();
	exit(status);

}
