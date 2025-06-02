/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:12 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 16:53:45 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RUN_H
# define FT_RUN_H

# include "../minishell.h"

// function to run the shell
void	run_shell(t_shell *shell);

// function to run the shell in debug mode
void	run_shell_debug(t_shell *shell);

// function to print harambe
void	ft_print_harambe(void);

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

// function to run a builtin command
void	run_builtin_cmd(t_cmd *cmd, t_shell *shell);

// wrapper for running the shell commands
void	minishellers(t_shell *shell);

#endif