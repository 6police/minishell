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
t_cmd	*init_cmd(char *name, char **args)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->name = ft_strdup(name);
	cmd->args = args;
	cmd->path = NULL;
	cmd->is_builtin = false;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd_pipe[0] = -1;
	cmd->fd_pipe[1] = -1;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->fd[2] = -1;
	cmd->fd_struct = NULL;
	cmd->redirs = NULL;
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
	cmd->args = copy_array(args + 1);
}

static bool	is_redir_noarg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		while ((str[i] == '<' || str[i] == '>'))
			i++;
		if (str[i] == '\0' || str[i] == ' ')
			return (true);
		if (str[i] != ' ' && str[i] != '\0')
			return (false);
		i++;
	}
	return (false);
}

static bool	is_redir(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			return (true);
		i++;
	}
	return (false);
}

static char	**ft_removequotes(char **args)
{
	char	**newargs;
	int		len;

	int i, j, k;
	// Count number of args
	for (i = 0; args[i]; i++)
		;
	newargs = ft_calloc(i + 1, sizeof(char *));
	if (!newargs)
		return (NULL);
	for (i = 0; args[i]; i++)
	{
		len = 0;
		// Count non-quote characters
		for (j = 0; args[i][j]; j++)
		{
			if (args[i][j] != '\'' && args[i][j] != '"')
				len++;
		}
		newargs[i] = ft_calloc(len + 1, sizeof(char));
		if (!newargs[i])
			return (NULL); // You should free previous on error
		// Copy non-quote characters
		for (j = 0, k = 0; args[i][j]; j++)
		{
			if (args[i][j] != '\'' && args[i][j] != '"')
				newargs[i][k++] = args[i][j];
		}
		newargs[i][k] = '\0';
	}
	newargs[i] = NULL;
	free_split(args);
	return (newargs);
}

// function that normalizes the command->arg array.
// if there are redirs in the args we remove them from the args
// if there are redirs BEFORE the nnevargs we remove them from the args,
// if there are redirs AFTER the args we remove them from the args as well
// if an arg is just a redir symbol, we then remove as well the next arg
static void	process_cmd_args(t_cmd *cmd)
{
	char	**newargs;
	int		arg_count;
	int		i;

	if (!cmd || !cmd->args)
		return ;
	arg_count = 0;
	i = 0;
	while (cmd->args[i] && cmd->args[i][0] != '\0')
	{
		if (is_redir_noarg(cmd->args[i]))
			i += 2;
		else if (is_redir(cmd->args[i]))
			i++;
		else
		{
			arg_count++;
			i++;
		}
	}
	newargs = ft_calloc(sizeof(char *), arg_count + 1);
	i = 0;
	arg_count = 0;
	while (cmd->args[i] && cmd->args[i][0] != '\0')
	{
		if (is_redir_noarg(cmd->args[i]))
			i += 2;
		else if (is_redir(cmd->args[i]))
			i++;
		else
		{
			newargs[arg_count] = ft_strdup(cmd->args[i]);
			arg_count++;
			i++;
		}
	}
	free_split(cmd->args);
	cmd->args = ft_removequotes(newargs);
}

static char	*set_name(char **args)
{
	int		i;
	int		j;
	char	*str;
	char	*name;
	int		redir_flag;

	i = 0;
	str = NULL;
	if (!args)
		return (NULL);
	redir_flag = check_for_redirs(args[0]);
	if (redir_flag > 0)
	{
		while (args[i])
		{
			j = 0;
			while (args[i][0] != '\0' && (args[i][0] == '<' || args[i][0] == '>') && ft_strlen(args[i]) <= 2)
				i++;
			if (args[i][j] != '\0' && ft_strlen(args[i]) > 2)
			{
				while (args[i][j] == '<' || args[i][j] == '>')
					j++;
				str = ft_substr(args[i], j, ft_strlen(args[i]) - j);
				if (str == NULL)
					return (NULL);
				break ;
			}
			i++;
		}
	}
	else
		str = ft_strdup(args[0]);
	if (str == NULL)
		return (NULL);
	name = remove_all_quotes(str);
	return (name);
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
	int		i;
	t_cmd	*cmd;
	t_cmd	*head_cmd;
	char	**args;
	char	**redirs;
	char	*aux;
	char	*str;
	int		redir_check;

	str = NULL;
	i = 0;
	head_cmd = NULL;
	redirs = NULL;
	while (shell->tokens[i])
	{
		aux = ft_strdup(shell->tokens[i]);
		mark_and_replace(shell->tokens[i], ' ', 2);
		args = ft_split(shell->tokens[i], 2);
		str = set_name(args);
		cmd = init_cmd(str, args);
		free(str);
		check_builtin(cmd);
		if (cmd->is_builtin)
			build_builtin(cmd, args);
		else
			build_cmd(cmd, args, shell);
		add_last_cmd(&shell->cmds, cmd);
		cmd->line = ft_strdup(aux);
		free_split(args);
		dollar_sign(cmd, shell);
		ft_new_wildcard(cmd, shell);
		redir_check = check_for_redirs(cmd->line);
		if (redir_check > 0)
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
		}
		i++;
		free(aux);
		process_cmd_args(cmd);
	}
	return (head_cmd);
}
