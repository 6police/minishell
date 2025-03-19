#include "ft_debug.h"

// Print the enviroment variables
void print_env(t_env *env)
{
	t_env_var *tmp;

	tmp = env->head;
	while (tmp)
	{
		if (tmp->value)
			printf(RED "%s" RESET "=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void print_export(t_env *env)
{
	t_env_var *tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
static void print_args(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		ft_printf("%s ", cmd->args[i]);
		i++;
	}
	ft_printf("\n");
}

void print_command(t_cmd *cmd)
{

	ft_printf("is_command_path ???\n");
	ft_printf("%d\n", is_command_path(cmd->name));
	ft_printf("\n --- \n");

	ft_printf("name: %s\n", cmd->name);
	ft_printf("args: ");
	print_args(cmd);
	ft_printf("path: %s\n", cmd->path);
	ft_printf("is_builtin: %d\n", cmd->is_builtin);
	ft_printf("is_valid: %d\n", cmd->is_valid);
	ft_printf("redirs: %p\n", cmd->redirs);
	ft_printf("last_fd: %d\n", cmd->last_fd);
	ft_printf("last_read: %d\n", cmd->last_read);
	ft_printf("has_heredoc: %d\n", cmd->has_heredoc);

	// print function pointer
	ft_printf("builtin_func: %p\n", cmd->builtin_func);
	ft_printf("\n");
	if (cmd->next)
		ft_printf("next: %s\n", cmd->next->name);
	if (cmd->prev)
		ft_printf("prev: %s\n", cmd->prev->name);
	ft_printf("\n");
}

// print all the commands
void print_all_commands(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		print_command(cmd);
		cmd = cmd->next;
	}
}