/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:06 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 20:49:40 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include <sys/ioctl.h>

static void	siginfo_handler(int sig, siginfo_t *info, void *context);
static void	siginfo_handler_heredoc(int sig, siginfo_t *info, void *context);
//static void	clean_exit_heredoc(t_shell **shell);

t_sig	*t_pid(void)
{
	static t_sig	pid;

	return (&pid);
}

void	setup_signals(t_shell *shell)
{
	struct sigaction	sa;

	(void)shell;
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = siginfo_handler;
	sigaction(SIGINT, &sa, NULL);
}

static void	siginfo_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
		t_pid()->exit_value = 130;
		new_prompt();
	}
}

void	setup_signals_heredoc(t_shell *shell)
{
	struct sigaction	sa;

	t_pid()->shull = shell;
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = siginfo_handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

static void	siginfo_handler_heredoc(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
		t_pid()->shull->exit_value = 130;
		rl_done = 1;
	}
}
