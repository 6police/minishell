#include "ft_parsing.h"

// function to create a new t_cmd
t_cmd	*init_cmd(char *name, char **args)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (name)
		cmd->name = ft_strdup(name);
	else
		cmd->name = ft_strdup("kekers");
	cmd->args = args;
	cmd->path = NULL;
	cmd->is_builtin = false;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd_pipe[0] = -1;
	cmd->fd_pipe[1] = -1;
	cmd->fd[0] = STDIN_FILENO;
	cmd->fd[1] = STDOUT_FILENO;
	cmd->fd[2] = STDERR_FILENO;
	cmd->fd_struct = NULL;
	cmd->redirs = NULL;
	cmd->is_valid = false;
	cmd->builtin_func = NULL;
	cmd->pid = 0;
	cmd->has_heredoc = false;
	return (cmd);
}

// function to process the command arguments
static void	cmd_processor_a(t_cmd *cmd, t_shell *shell, int i)
{
	int	redir_check;

	redir_check = 0;
	cmd->line = ft_strdup(shell->tokens[i]);
	redir_check = check_for_redirs(cmd->line);
	if (redir_check > 0)
	{
		cmd->redirs = split_into_redirs(cmd->line);
		cmd->fd_struct = assemble_redirs(cmd->redirs);
		if (cmd->fd_struct == NULL)
		{
			free_cmd(cmd);
			return ;
		}
		if (cmd->fd_struct->type == HERE_DOC_)
			cmd->has_heredoc = true;
	}
}

static t_cmd	*invalid_exit(t_cmd *cmd, t_shell *shell)
{
	shell->exit_value = 1;
	if (ft_strcmp(cmd->name, "kekers") != 0)
		ft_printf_fd(STDERR_FILENO, "minishell: invalid command: %s\n", cmd->name);
	return (cmd);
}

// function to check if a file exists and is a regular file 
bool check_file(char *cmd)
{
	struct stat st;
	if (stat(cmd, &st) != 0)
		return (false);
	if (S_ISREG(st.st_mode) != 0)
		return (true) ;
	return (false);
}

// function to parse and populate a command from the tokens
static t_cmd	*parse_cmd(t_shell *shell, int i)
{
	t_cmd	*cmd;
	char	**args;
	char	*name;

	if (!shell || !shell->tokens || !shell->tokens[i])
		return (NULL);
	args = NULL;
	name = NULL;
	mark_and_replace(shell->tokens[i], ' ', 2);
	args = ft_split(shell->tokens[i], 2);
	// lol
	mark_and_replace(shell->tokens[i], 2, ' ');
	if (args && args[0])
		name = set_name(args);
	cmd = init_cmd(name, args);
	free(name);
	built_in_handle(cmd, shell, args);
	add_last_cmd(&shell->cmds, cmd);
	cmd_processor_a(cmd, shell, i);
	free_split(args);
	if (!cmd->is_valid)
	 	return(invalid_exit(cmd, shell));	
	ft_new_wildcard(cmd, shell);
	if (cmd->args && cmd->args[0] && cmd->args[0][0] != '\0')
		process_cmd_args(cmd);
	return (cmd);
}

// function to find the head of the command linked list
static t_cmd	*find_head(t_shell *shell)
{
	t_cmd	*head_cmd;

	if (!shell || !shell->cmds)
		return (NULL);
	head_cmd = shell->cmds;
	while (head_cmd && head_cmd->prev)
		head_cmd = head_cmd->prev;
	return (head_cmd);
}

// funciton that takes tokens and assembles into commands
t_cmd	*build_cmds(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*head_cmd;
	int		i;

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
