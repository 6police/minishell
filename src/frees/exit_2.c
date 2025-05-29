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
void	free_redir_structs(t_fd *redirs)
{
	t_fd	*tmp;
	t_fd	*next;

	if (!redirs)
		return ;
	tmp = redirs;
	while (tmp)
	{
		if (tmp->file)
			free(tmp->file);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

// free ONE cmd
void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->line)
		free(cmd->line);
	if (cmd->redirs)
		free_split(cmd->redirs);
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		free_split(cmd->args);
	if (cmd->path)
		free(cmd->path);
	if (cmd->fd_struct)
		free_redir_structs(cmd->fd_struct);
	cmd->line = NULL;
	cmd->redirs = NULL;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->fd_struct = NULL;
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
