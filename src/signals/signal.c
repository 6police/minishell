/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:06 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 23:35:04 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"

static void	siginfo_handler(int sig, siginfo_t *info, void *context);
static void	siginfo_handler_heredoc(int sig, siginfo_t *info, void *context);
static void	clean_exit_heredoc(t_shell **shell);

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
		t_pid()->status = 130;
		close(t_pid()->shull->status);
		if (t_pid()->shull->is_pipe)
			close_pipes(t_pid()->shull->cmds);
		clean_exit_heredoc(&t_pid()->shull);
	}
}

static void	clean_exit_heredoc(t_shell **shell)
{
	int	status;

	if (!shell|| !(*shell))
		return ;
	status = t_pid()->status;
	if ((*shell)->debug)
	{
		ft_printf(RED "exiting shell with status: %d\n" RESET, status);
		printf(EMOJI_BRAIN "exiting shell\n\n");
	}
	if (!(*shell)->is_child)
		ft_printf_fd(STDERR_FILENO, "exit\n - K THX BYE - \n");
	if (shell && *shell)
		free_shell(shell);
	clear_history();
	exit(status);
}
