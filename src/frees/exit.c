#include "ft_free.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
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
	if (redir)
		free(redir);
}

// free ALL redirs
void	free_redirs(t_redir **redirs)
{
	int	i;

	if (!redirs)
		return ;
	i = 0;
	while (redirs[i])
	{
		free_redir(redirs[i]);
		i++;
	}
	free(redirs);
}

// free ONE cmd
void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("freeing args[%d]: %p -> %s\n", i, (void *)cmd->args[i],
				cmd->args[i]);
			i++;
		}
		printf("freeing args array: %p\n", (void *)cmd->args);
		free_split(cmd->args);
		cmd->args = NULL;
		printf("args freed: %p\n", (void *)cmd->args);
	}
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	if (cmd->redirs)
	{
		free_redirs(cmd->redirs);
		cmd->redirs = NULL;
	}
	free(cmd);
	ft_printf("cmd freed\n");
}

// free ALL cmds
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_cmd	*next;

	if (!cmds)
		return ;
	tmp = cmds;
	while (tmp)
	{
		next = tmp->next;
		free_cmd(tmp);
		tmp = next;
	}
}

// free ONE env var
void	free_env_var(t_env_var *env_var)
{
	if (env_var)
	{
		free(env_var->key);
		free(env_var->value);
		free(env_var);
	}
}

// free the whole env
void	free_env(t_env *env)
{
	t_env_var	*tmp;
	t_env_var	*next;

	if (!env)
		return ;
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

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

// free the shell
void	free_shell(t_shell **shell, int debug)
{
	if (!shell)
		return ;
	if ((*shell)->line && *(*shell)->line)
	{
		if (debug)
			printf("freeing line\n");
		free((*shell)->line);
	}
	if ((*shell)->cmds && (*shell)->cmds->name)
	{
		if (debug)
			printf("freeing cmds\n");
		free_cmds((*shell)->cmds);
	}
	if ((*shell)->env && (*shell)->env->head)
	{
		if (debug)
			printf("freeing env\n");
		free_env((*shell)->env);
	}
	if ((*shell)->fds && (*shell)->fds->fd_in != 0)
	{
		if (debug)
			printf("freeing fds\n");
		close_fds((*shell)->fds);
	}
	if ((*shell)->tokens)
	{
		if (debug)
			printf("freeing tokens\n");
		free_tokens((*shell)->tokens);
	}
	if ((*shell)->separators && *(*shell)->separators)
	{
		if (debug)
			printf("freeing separator\n");
		free((*shell)->separators);
	}
	if (debug)
		printf("freeing shell\n");
	free(*shell);
}

void	flush_commands(t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*next;

	if (!shell->cmds)
		return ;
	tmp = shell->cmds;
	while (tmp)
	{
		next = tmp->next;
		free_cmd(tmp);
		tmp = next;
	}
	shell->cmds = NULL;
	shell->is_pipe = false;
}

// exit the shell
void	clean_exit(t_shell **shell)
{
	int	status;

	status = (*shell)->status;
	if ((*shell)->debug)
	{
		// in red
		ft_printf(RED "exiting shell with status: %d\n" RESET, status);
		printf(EMOJI_BRAIN "exiting shell\n\n");
	}
	if (shell)
		free_shell(shell, (*shell)->debug);
	clear_history();
	exit(status);
}
