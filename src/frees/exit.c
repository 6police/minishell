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

// free the redirections
void free_redir_structs(t_fd *redirs)
{
	t_fd	*tmp;
	t_fd	*next;

	if (!redirs)
		return ;
	tmp = redirs;
	while (tmp)
	{
		if(tmp->file)
			free(tmp->file);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	ft_printf("redirs freed\n");
}


// free ONE cmd
void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->line)
	{
		free(cmd->line);
		cmd->line = NULL;
	}
	if (cmd->redirs)
	{
		free_split(cmd->redirs);
		cmd->redirs = NULL;
	}

	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	if (cmd->args)
	{
		free_split(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	if (cmd->fd_struct)
	{
		free_redir_structs(cmd->fd_struct);
		cmd->fd_struct = NULL;
	}
	free(cmd);
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

 	status = (*shell)->exit_value;
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
