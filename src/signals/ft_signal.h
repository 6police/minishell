#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "../minishell.h"

typedef struct s_sig
{
	int status;
} t_sig;

t_sig* t_pid();

// Setup signals
void	setup_signals(t_shell *shell);

#endif