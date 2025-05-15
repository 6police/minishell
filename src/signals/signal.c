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

// void save_terminal_state(t_shell *shell)
// {
//     tcgetattr(STDIN_FILENO, &shell->orig_termios);
// }

// void restore_terminal_state(t_shell *shell)
// {
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->orig_termios);
// }

// void disable_raw_mode(void)
// {
//     // Restore original terminal settings before exit
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig_termios);
// }

// void enable_raw_mode(void)
// {
//     struct termios raw;

//     // Get current terminal attributes and save them globally
//     if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1)
//         perror("tcgetattr");

//     // Copy to raw to modify
//     raw = g_orig_termios;

//     // Disable canonical mode and echo
//     raw.c_lflag &= ~(ICANON | ECHO);

//     // Optionally disable ISIG if you want to handle signals yourself
//     // raw.c_lflag &= ~(ISIG);

//     // Apply raw mode settings immediately
//     if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
//         perror("tcsetattr");
// }
