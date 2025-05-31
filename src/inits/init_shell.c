#include "ft_inits.h"

// assign the values for the parsing separators
int	*init_separator(void)
{
	int	*separators;

	separators = ft_calloc(6, sizeof(int));
	if (!separators)
	{
		ft_printf_fd(2, "Error: malloc failed\n");
		exit(1);
	}
	separators[0] = '|';
	separators[1] = '<';
	separators[2] = '>';
	separators[3] = '\'';
	separators[4] = '\"';
	separators[5] = ' ';
	return (separators);
}

// initialize the shell
t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	shell->env = copy_env(env);
	shell->separators = init_separator();
	shell->token = NULL;
	shell->main_pid = ft_get_pid();
	shell->is_child = false;
	shell->exit_value = 0;
	shell->main_pid = ft_get_pid();
	shell->wait = false;
	shell->current_heredoc_file = NULL;
	return (shell);
}

t_shell	*init_shell_no_env(void)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	shell->env = new_env();
	shell->separators = init_separator();
	shell->token = NULL;
	shell->main_pid = ft_get_pid();
	shell->is_child = false;
	shell->exit_value = 0;
	return (shell);
}
