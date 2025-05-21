#include "ft_signal.h"

static void	siginfo_handler(int sig, siginfo_t *info, void *context);

void	setup_signals(t_shell *shell)
{
	struct sigaction	sa;

	(void)shell;
	signal(SIGQUIT, SIG_IGN);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = siginfo_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == 0)
		shell->exit_value = 130;
}

static void	siginfo_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;

	if (!info)
		return ;
	if (sig == SIGINT)
		new_prompt();
}
