#include "ft_signal.h"

void	siginfo_handler(int sig, siginfo_t *info, void *context);

void	setup_signals(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = siginfo_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL); // Handle SIGINT = ctrl-C
	//sigaction(SIGQUIT, &sa, NULL);
}

void	siginfo_handler(int sig, siginfo_t *info, void *context)
{
	// aqui adicionas o que quiseres para o minishell
	(void)context;
	if (!info)
		return ;
/*	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}*/
	if (sig == SIGINT)
	{

		new_prompt(); // ctrl-C - Print new prompt
	}
}
