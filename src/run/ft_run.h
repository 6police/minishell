#ifndef FT_RUN_H
# define FT_RUN_H

# include "../minishell.h"

// function to run the shell
void	run_shell(t_shell *shell);

// function to run the shell in debug mode
void	run_shell_debug(t_shell *shell);

// function to print harambe
void	ft_print_harambe(void);

// function to print minishell
void	ft_print_minishell(void);

#endif