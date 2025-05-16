#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "../minishell.h"

// Signal handler
void	siginfo_handler(int sig, siginfo_t *info, void *context);

// Setup signals
void	setup_signals(void);




#endif