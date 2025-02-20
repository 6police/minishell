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
    separators[0] = ';'; // semicolon
    separators[1] = '|'; // pipe
    separators[2] = '<'; // input redirection
    separators[3] = '>'; // output redirection
    separators[4] = '\''; // single quote
    separators[5] = '\"'; // double quote
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
    ft_printf("Environment copied\n");
	// initialize the file descriptors
	// initialize the commands
	ft_printf("Shell initialized\n");
    ft_print_minishell();
	return (shell);
}
