#include "../minishell.h"

void	siginfo_handler(int sig, siginfo_t *info, void *context);

void	setup_signals(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN); // SIG_IGN = Ignore Signal, SIGQUIT (Ctrl+\) to prevent core dump
	sa.sa_sigaction = siginfo_handler; // Use sa_sigaction instead of sa_handler
	sigemptyset(&sa.sa_mask); // Block all signals while in the handler
	sa.sa_flags = SA_SIGINFO; // Use SA_SIGINFO to get detailed info
	sigaction(SIGINT, &sa, NULL); // Handle SIGINT = ctrl-C
}

void	siginfo_handler(int sig, siginfo_t *info, void *context)
{
	// aqui adicionas o que quiseres para o minishell
	(void)context;
	if (sig == SIGINT)
		new_prompt(); // ctrl-C - Print new prompt
	else
		ft_printf("\nCaught signal %d from PID: %d\n", sig, info->si_pid); // para apagar mais tarde!! nao fica no minishell final!
}
