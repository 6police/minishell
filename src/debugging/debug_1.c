#include "ft_debug.h"

// Print the enviroment variables
void	print_env(t_env *env)
{
	t_env_var	*tmp;

	tmp = env->head;
	while (tmp)
	{
		if (tmp->value)
			printf(RED "%s" RESET "=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	print_export(t_env *env)
{
	t_env_var	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
static void	print_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		ft_printf("[%s]", cmd->args[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_command(t_cmd *cmd)
{
	ft_printf(RED "\n <-0-0->\n" RESET);
	ft_printf(GREEN "is_command_path ???\n" RESET);
	ft_printf("%d\n", is_command_path(cmd->name));
	ft_printf(GREEN "name: " RESET "%s\n", cmd->name);
	ft_printf(GREEN "args: " RESET);
	print_args(cmd);
	ft_printf(GREEN "cmd_nb: " RESET "%d\n", cmd->cmd_nb);
	ft_printf(GREEN "path: " RESET "%s\n", cmd->path);
	ft_printf(GREEN "is_builtin: " RESET "%d\n", cmd->is_builtin);
	ft_printf(GREEN "is_valid: " RESET "%d\n", cmd->is_valid);
	ft_printf(GREEN "redirs: " RESET "%p\n", cmd->redirs);
	ft_printf(GREEN "last_fd: " RESET "%d\n", cmd->last_fd);
	ft_printf(GREEN "last_read: " RESET "%d\n", cmd->last_read);
	ft_printf(GREEN "has_heredoc: " RESET "%d\n", cmd->has_heredoc);
	// print function pointer
	ft_printf(MAGENTA "builtin_func: " RESET "%p\n", cmd->builtin_func);
	ft_printf("\n");
	if (cmd->next)
		ft_printf(CYAN "next: " RESET "%s\n", cmd->next->name);
	if (cmd->prev)
		ft_printf(CYAN "prev: " RESET "%s\n", cmd->prev->name);
	ft_printf(RED "<-0-0->\n\n" RESET);
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