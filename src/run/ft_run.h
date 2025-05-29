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

// function to shell
void	shelling(t_shell *shell);

// function to run the commands
void	run_commands(t_shell *shell);

// wrapper for executing commands
void	eggxecutor(t_cmd *cmd, t_shell *shell, int flag);

// function to run a command with pipes
// void run_pipe(t_cmd *cmd, t_shell *shell);

// function to run a command without pipes
void	run_no_pipe(t_cmd *cmd, t_shell *shell);

// function to handle the execution of a command
void	processor(t_cmd *cmd, t_shell *shell);

// function to wait for all commands to finish
void	wait_commands(t_shell *shell);

// function to close all file descriptors
void	close_fds(t_cmd *cmd);

#endif