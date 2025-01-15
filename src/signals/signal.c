/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:05:05 by nuno              #+#    #+#             */
/*   Updated: 2025/01/15 19:25:07 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	siginfo_handler(int sig, siginfo_t *info, void *context);

void	setup_signals(void)
{
	struct sigaction	sa;

	// Ignore SIGQUIT (Ctrl+\) to prevent core dump
	signal(SIGQUIT, SIG_IGN);
	
    
	sa.sa_sigaction = siginfo_handler; // Use sa_sigaction instead of sa_handler
	
	sigemptyset(&sa.sa_mask); // Block all signals while in the handler
	sa.sa_flags = SA_SIGINFO; // Use SA_SIGINFO to get detailed info
	sigaction(SIGINT, &sa, NULL); // Handle SIGINT
}

void	siginfo_handler(int sig, siginfo_t *info, void *context)
{
	// aqui adicionas o que quiseres para o minishell
	(void)context;
	if (sig == SIGINT)
		new_prompt(); // Print new prompt
	else if (sig == SIGQUIT)
		ft_printf("\nCaught SIGQUIT (Ctrl+\\) - Ignored\n"); // Ignore SIGQUIT (Ctrl+\)
	else if (sig == SIGTSTP)
		ft_printf("\nCaught SIGSTP (Ctrl+Z) - Ignored\n"); // Ignore SIGTSTP (Ctrl+Z)
	else
		ft_printf("\nCaught signal %d from PID: %d\n", sig, info->si_pid);
}

/* Handling the Signals

Here’s how to handle the required signals:
Signals to Handle

	SIGINT (Ctrl+C):
		Interrupts the current process.
		it should interrupt the current command input or running child process

	SIGQUIT (Ctrl+\):
		Sends a quit signal. Typically terminates the process and creates a core dump.
		ignore it while idle or allow child processes to handle it.

	SIGTSTP (Ctrl+Z):
		Suspends the foreground process.
		you might need to handle job control (advanced feature) or just ignore it for simplicity.

	SIGCHLD:
		Signals that a child process has terminated or changed state.
		use it to clean up zombie processes.

	Ctrl+D (EOF):
		Should gracefully terminate the process by checking EOF on input. */
