#include "ft_signal.h"

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
	if (!info)
		return ;
	if (sig == SIGINT)
		new_prompt(); // ctrl-C - Print new prompt
}


/*  durante a execucao do minishell, se der um ctrl+\ (SIGQUIT) o shell vai dar core dump
	e vai dar o seguinte erro:
➜  minishell_this_one git:(feature/wildcards) ✗ cat
^\[1]    705615 quit (core dumped)  cat
 

handle nisto*/