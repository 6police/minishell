/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:31:01 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/19 19:44:35 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// free one array
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// close the file descriptors
void	close_fds(t_fds *fds)
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
void	free_redir(t_redir *redir)
{

    if (redir->input)
        free(redir->input);
    if (redir->output)
        free(redir->output);
    free(redir);
}

// free ALL redirs
void	free_redirs(t_redir **redirs)
{
    int	i;

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
void	free_cmds(t_cmd **cmds)
{
    int	i;

    i = 0;
    while (cmds[i])
    {
        free_cmd(cmds[i]);
        i++;
    }
    free(cmds);
}

// free ONE env var
void	free_env_var(t_env_var *env_var)
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
    t_env_var	*tmp;
    t_env_var	*next;

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
void	free_tokens(char **tokens)
{
    int	i;

    i = 0;
    if (!tokens)
        return ;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

// free the shell
void	free_shell(t_shell *shell)
{
    if (shell->line)
        free(shell->line);
    if (shell->cmds)
        free_cmds(shell->cmds);
    if (shell->env)
        free_env(shell->env);
    if (shell->fds)
        close_fds(shell->fds);
    free(shell);
}

// exit the shell
void	clean_exit(t_shell *shell)
{
    int    status;

    status = shell->status;

	if (shell)
		free_shell(shell);
	
    exit(status);
}
