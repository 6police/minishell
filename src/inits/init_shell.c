#include "ft_inits.h"

// assign the values for the parsing separators
int *init_separator(void)
{
    int *separators;

    // allocate memory for the separators
    separators = ft_calloc(6, sizeof(int));
    if (!separators)
    {
        ft_putstr_fd("Error: malloc failed\n", 2);
        exit(1);
    }
    // assign the values for the separators
    separators[0] = '|'; // pipe
    separators[1] = '<'; // input redirection
    separators[2] = '>'; // output redirection
    separators[3] = '\''; // single quote
    separators[4] = '\"'; // double quote
    separators[5] = ' '; // space
    return (separators);
}

// initialize the shell
t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	// declare the shell
	ft_printf("Initializing shell\n");     // print initializing shell
	shell = ft_calloc(1, sizeof(t_shell)); // allocate memory for the shell
	if (!shell)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	// copy the environment
	ft_printf("Copying the environment\n");
    shell->env = copy_env(env);
    shell->separators = init_separator();
    shell->token = NULL;
    shell->main_shell_pid = getpid();
    shell->in_child = false;
    ft_printf("Environment copied\n");
	// initialize the file descriptors
	// initialize the commands
	ft_printf("Shell initialized\n");
    ft_print_minishell();
	return (shell);
}
