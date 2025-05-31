/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:06 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 20:20:46 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"

static void	siginfo_handler(int sig, siginfo_t *info, void *context);
static void	siginfo_handler_heredoc(int sig, siginfo_t *info, void *context);

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
		t_pid()->status = 130;
		new_prompt();
	}
}

void	setup_signals_heredoc(t_shell *shell)
{
	struct sigaction	sa;

	(void)shell;
	signal(SIGQUIT, SIG_DFL);
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
		t_pid()->status = 130;
		close(t_pid()->shull->status);
		if (t_pid()->shull->is_pipe)
			close_pipes(t_pid()->shull->cmds);
		clean_exit(&t_pid()->shull);
	}
}