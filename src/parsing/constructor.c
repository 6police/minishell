#include "ft_parsing.h"

// function that takes the shell->token and parses it into commands

// function to add a t_cmd to the t_cmd linked list
static void	add_last_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
		*head = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

static char	**copy_array(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array[i])
		i++;
	new_array = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

// function to create a new t_cmd
static t_cmd	*init_cmd(char *name, char **args)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->name = ft_strdup(name);
	cmd->args = args;
	cmd->path = NULL;
	cmd->is_builtin = false;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd[0] = STDIN_FILENO;
	cmd->fd[1] = STDOUT_FILENO;
	cmd->fd_struct = ft_calloc(sizeof(t_fd), 1);
	cmd->fd_struct->type = NONE;
	cmd->fd_struct->fd = -1;
	cmd->fd_struct->file = NULL;
	cmd->fd_struct->next = NULL;
	cmd->is_valid = false;
	cmd->builtin_func = NULL;
	cmd->pid = 0;
	cmd->has_heredoc = false;
	return (cmd);
}

static void	check_builtin(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd->name, "env") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "exit") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "export") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "unset") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "pwd") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "cd") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "echo") == 0)
		cmd->is_builtin = true;
	if (ft_strcmp(cmd->name, "$?") == 0)
		cmd->is_builtin = true;
}

void	build_cmd(t_cmd *cmd, char **args, t_shell *shell)
{
	char	*path;

	if (is_command_path(cmd->name))
	{
		cmd->path = ft_strdup(cmd->name);
		cmd->is_valid = true;
		cmd->args = copy_array(args);
		cmd->builtin_func = execute_external;
		return ;
	}
	else
	{
		path = checkforpath(cmd->name, shell->env);
		if (path)
		{
			cmd->path = path;
			cmd->is_valid = true;
			cmd->args = copy_array(args);
			cmd->builtin_func = execute_external;
		}
		else
		{
			cmd->path = NULL;
			cmd->is_valid = false;
			cmd->args = copy_array(args);
			cmd->builtin_func = NULL;
		}
	}
}

void	build_builtin(t_cmd *cmd, char **args)
{
	cmd->is_valid = true;
	if (ft_strcmp(cmd->name, "cd") == 0)
		cmd->builtin_func = cd_shell;
	if (ft_strcmp(cmd->name, "echo") == 0)
		cmd->builtin_func = echo_shell;
	if (ft_strcmp(cmd->name, "pwd") == 0)
		cmd->builtin_func = pwd_shell;
	if (ft_strcmp(cmd->name, "export") == 0)
		cmd->builtin_func = export_builtin;
	if (ft_strcmp(cmd->name, "unset") == 0)
		cmd->builtin_func = unset_vars;
	if (ft_strcmp(cmd->name, "exit") == 0)
		cmd->builtin_func = exit_shell;
	if (ft_strcmp(cmd->name, "env") == 0)
		cmd->builtin_func = env;
	if (ft_strcmp(cmd->name, "$?") == 0)
		cmd->builtin_func = exit_code_printer;
	cmd->args = copy_array(args + 1);
}

// funciton that takes tokens and assembles into commands
// we check if the command is a built-in command and if it is we set the is_builtin to true
// we also check if the command is a redirection
// then we check if the command is a pipe
// we then look for the path of the command,
// if found we set the path of the command and build the command
// if not found we set the path to NULL and command is now invalid
t_cmd	*build_cmds(t_shell *shell)
{
	int i;
	t_cmd *cmd;
	t_cmd *head_cmd;
	char **args;
	char **redirs;

	i = 0;
	head_cmd = NULL;
	redirs = NULL;
	while (shell->tokens[i])
	{
		mark_and_replace(shell->tokens[i], ' ', 2);
		args = ft_split(shell->tokens[i], 2);
		cmd = init_cmd(args[0], args);
		check_builtin(cmd);
		if (cmd->is_builtin)
			build_builtin(cmd, args);
		else
			build_cmd(cmd, args, shell);
		add_last_cmd(&shell->cmds, cmd);
		cmd->line = ft_strdup(shell->tokens[i]);
		free_split(args);

		check_for_redirs(cmd->line);
		if (check_for_redirs(cmd->line) > 0)
		{
			cmd->redirs = split_into_redirs(cmd->line);
			redirs = cmd->redirs;
			cmd->fd_struct = assemble_redirs(redirs);
			if (cmd->fd_struct == NULL)
			{
				free_cmd(cmd);
				return (NULL);
			}
			if (cmd->fd_struct->type == HERE_DOC_)
				cmd->has_heredoc = true;
			//handle_args_n_redirs(cmd->args, cmd->redirs);
		}
		else
		{
			cmd->redirs = NULL;
			cmd->fd_struct = NULL;
		}
		i++;
	}
	return (head_cmd);
}