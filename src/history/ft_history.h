#ifndef FT_HISTORY_H
# define FT_HISTORY_H

# include "../minishell.h"

typedef struct s_history
{
	HISTORY_STATE	*state;
	HIST_ENTRY		**list;
}					t_history;

#endif // Display the history
