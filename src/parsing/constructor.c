#include "ft_parsing.h"


static void	process_cmd_args(t_cmd *cmd);

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
	if (name)
		cmd->name = ft_strdup(name);
	else
		cmd->name = ft_strdup("KEKW");
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
	int c;

	i = 0;
	c = 0;

	if (!str)
		return (false);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !c)
			c = str[i];
		while ((str[i] == '<' || str[i] == '>'))
			i++;
		if ((str[i] == '\0' || str[i] == ' ') && !c)
			return (true);
		if ((str[i] != ' ' && str[i] != '\0') && !c)
			return (false);
		i++;
	}
	return (false);
}

// static bool	is_redir(char *str)
// {
// 	int	i;
// 	int c;

// 	i = 0;
// 	c = 0;

// 	if (!str)
// 		return (false);
// 	while (str[i])
// 	{
// 		if ((str[i] == '"' || str[i] == '\'') && !c)
// 			c = str[i];
		
// 		if (str[i] == '>' || str[i] == '<')
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

static bool	is_redir(char *str)
{
	int	i;
	char	quote;

	if (!str)
		return (false);
	quote = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		else if ((str[i] == '>' || str[i] == '<') && quote == 0)
		{
			return (true);
		}
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
	if (!args[0])
		return (NULL);
	redir_flag = check_for_redirs(args[0]);
	if (redir_flag > 0)
	{
		while (args[i] != NULL)
		{
			j = 0;
			while (args[i][0] != '\0' && (args[i][0] == '<' || args[i][0] == '>') && ft_strlen(args[i]) <= 1)
				i++;
			if (args[i][j] != '\0' && ft_strlen(args[i]) >= 2)
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
	//printf("PASSOU !!!!! cmd->name: %s\n cmd->args: %s\n", str, args[1]);
	name = remove_all_quotes(str);
	return (name);
}

static void built_in_handle(t_cmd *cmd, t_shell *shell, char **args)
{
	check_builtin(cmd);
	if (cmd->is_builtin)
	build_builtin(cmd, args);
	else
	build_cmd(cmd, args, shell);
}

static void cmd_processor_a(t_cmd *cmd, t_shell *shell, int i)
{
	int redir_check;
	
	redir_check = 0;
	cmd->line = ft_strdup(shell->tokens[i]);
	dollar_sign(cmd, shell);
	redir_check = check_for_redirs(cmd->line);
	if (redir_check > 0)
	{
		cmd->redirs = split_into_redirs(cmd->line);
		cmd->fd_struct = assemble_redirs(cmd->redirs);
		if (cmd->fd_struct == NULL)
		{
			free_cmd(cmd);
			return;
		}
		if (cmd->fd_struct->type == HERE_DOC_)
		cmd->has_heredoc = true;
	}
}

static t_cmd *parse_cmd(t_shell *shell, int i)
{
	t_cmd *cmd;
	char **args;
	char *name;
	
	if (!shell || !shell->tokens || !shell->tokens[i])
	return (NULL);
	args = NULL;
	name = NULL;
	mark_and_replace(shell->tokens[i], ' ', 2);
	args = ft_split(shell->tokens[i], 2);
	if (args && args[0])
		name = set_name(args);
	cmd = init_cmd(name, args);
	free(name);
	
	built_in_handle(cmd, shell, args);
	add_last_cmd(&shell->cmds, cmd);
	cmd_processor_a(cmd, shell, i);
	free_split(args);
	if (cmd->args && cmd->args[0] && cmd->args[0][0] != '\0')
		process_cmd_args(cmd);
	return (cmd);
}

static t_cmd *find_head(t_shell *shell)
{
	t_cmd *head_cmd;
	
	if (!shell || !shell->cmds)
	return (NULL);
	head_cmd = shell->cmds;
	while (head_cmd && head_cmd->prev)
	head_cmd = head_cmd->prev;
	return (head_cmd);
}

// funciton that takes tokens and assembles into commands
t_cmd *build_cmds(t_shell *shell)
{
	t_cmd *cmd;
	t_cmd *head_cmd;
	int i;

	i = 0;
	head_cmd = NULL;
	if (!shell || !shell->tokens)
		return (NULL);
	while (shell->tokens[i])
	{
		cmd = parse_cmd(shell, i);
		if (cmd == NULL)
			return (NULL);
		i++;
	}
	if (head_cmd == NULL)
		head_cmd = shell->cmds;
	else
		head_cmd = find_head(shell);
	if (head_cmd == NULL)
		return (ft_printf_fd(2, "Error: No commands found.\n"), NULL);
	return (head_cmd);
}
