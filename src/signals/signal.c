#include "ft_signal.h"

static void	siginfo_handler(int sig, siginfo_t *info, void *context);

t_sig* t_pid()
{
	static t_sig pid;
	return (&pid);
} 


void	setup_signals(t_shell *shell)
{
	struct sigaction	sa;

	//t_pid()->status = 0;
	(void)shell;
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = siginfo_handler;
	sigaction(SIGINT, &sa, NULL);
	
	//if (g_signal == 1)
	//	shell->exit_value = 130; look better into global variable usage
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
