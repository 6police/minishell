#include "ft_debug.h"

// Print the enviroment variables
void	print_env(t_env *env, t_cmd *cmd)
{
	t_env_var	*tmp;

	tmp = env->head;
	while (tmp)
	{
		if (tmp->value)
			ft_printf_fd(cmd->fd[1],RED "%s" RESET "=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	print_export(t_env *env, t_cmd *cmd)
{
	t_env_var	*tmp;

	tmp = env->head;
	while (tmp)
	{
		ft_printf_fd(cmd->fd[1], "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
static void	print_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		ft_printf_fd(cmd->fd[1], "[%s]", cmd->args[i]);
		i++;
	}
	ft_printf("\n");
}

void print_redirs(char **redirs)
{
	int	i;

	i = 0;
	while (redirs && redirs[i])
	{
		ft_printf("["GREEN"%s"RESET"] ", redirs[i]);
		i++;
	}
	ft_printf("\n");
}

static void print_cmd_redirs(t_cmd *cmd)
{
	t_fd	*tmp;

	tmp = cmd->fd_struct;
	while (tmp)
	{
		if (tmp)
		{
			ft_printf(RED "type:" GREEN "%d\n" RESET, tmp->type);
			ft_printf(YELLOW "file:" GREEN "%s\n" RESET, tmp->file);
			ft_printf(BLUE "file pointer:" GREEN "%p\n" RESET, tmp->file);
			//ft_printf("fd: %d\n", tmp->fd);
			ft_printf("\n");
		}
		if (tmp->type == HERE_DOC_)
			ft_printf("heredoc: %s\n", tmp->file);
		if (tmp->type == REDIR_IN)
			ft_printf("redir in: %s\n", tmp->file);
		if (tmp->type == REDIR_OUT)
			ft_printf("redir out: %s\n", tmp->file);
		if (tmp->type == REDIR_APPEND)
			ft_printf("redir append: %s\n", tmp->file);
		if (tmp->type == NONE)
			ft_printf("redir none: %s\n", tmp->file);
		tmp = tmp->next;
	}
}
static void print_fds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (cmd->fd[i] == -1)
			ft_printf("["RED"%d"RESET"] ", -1);
		else
			ft_printf("["GREEN"%d"RESET"] ", cmd->fd[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_command(t_cmd *cmd)
{
	ft_printf(RED " --- NEW COMMAND ---\n" RESET);
	ft_printf("line :  %s\n", cmd->line);
	ft_printf("redirs: ");
	if (!cmd->redirs)
		ft_printf("NULL\n");
	else
		print_redirs(cmd->redirs);
	ft_printf("\n"); 
	ft_printf("is_command_path ???\n");
	ft_printf("%d\n", is_command_path(cmd->name));
	ft_printf("\n --- \n");
	ft_printf("name: %s\n", cmd->name);
	ft_printf("args: ");
	print_args(cmd);
	ft_printf("path: %s\n", cmd->path);
	ft_printf("is_builtin: %d\n", cmd->is_builtin);
	ft_printf("is_valid: %d\n", cmd->is_valid);
	ft_printf(RED "FDs : "RESET);
	print_fds(cmd);
	ft_printf("\n");
	ft_printf("has_heredoc: %d\n", cmd->has_heredoc);
	// print function pointer
	ft_printf("builtin_func: %p\n", cmd->builtin_func);
	ft_printf("\n");
	ft_printf("\n REDIRS \n");
	print_cmd_redirs(cmd);
	if (cmd->next)
		ft_printf("next: %s\n", cmd->next->name);
	if (cmd->prev)
		ft_printf("prev: %s\n", cmd->prev->name);
	ft_printf("\n");
	ft_printf(RED " --- END ---\n" RESET);

	//print the input and output redirection names
	ft_printf("input redirection: ");
	if (cmd->fd[0] != STDIN_FILENO)
		ft_printf("%s\n", cmd->fd_struct->file);
	else if (cmd->fd[0] == STDIN_FILENO)
		ft_printf("stdin\n");
	else
		ft_printf("NULL\n");
	ft_printf("output redirection: ");
	if (cmd->fd[1] != STDOUT_FILENO)
		ft_printf("%s\n", cmd->fd_struct->file);
	else if (cmd->fd[1] == STDOUT_FILENO)
		ft_printf("stdout\n");
	else
		ft_printf("NULL\n");
	ft_printf("error redirection: ");
	if (cmd->fd[2] != STDERR_FILENO)
		ft_printf("%s\n", cmd->fd_struct->file);
	else if (cmd->fd[2] == STDERR_FILENO)
		ft_printf("stderr\n");
	else
		ft_printf("NULL\n");
	ft_printf("\n");
	ft_printf(" --- END ---\n" RESET);
	ft_printf("\n");
}

// print all the commands
void	print_all_commands(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		print_command(cmd);
		cmd = cmd->next;
	}
}