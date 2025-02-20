#include "../minishell.h"
#include <readline/history.h> // adicionar a biblioteca para usar a função add_history

typedef struct s_history
{
	HISTORY_STATE	*state;
	HIST_ENTRY		**list;
} t_history;