#include "ft_history.h"

void display_history(t_cmd *cmd)
{
	int			i;
	t_history	*history;

	history = (t_history *)malloc(sizeof(t_history));
	if (!history)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	history->state = history_get_history_state();
	history->list = history_get(history->state->offset);
	i = 0;
	if (ft_strcmp(cmd->name, "history") == 0 && history->list)
	{
		while (i < history->state->length)
		{
			printf("%5d %s\n", i + 1, history->list[i]->line);
			i++;
		}
	}
	free(history->state);
	free(history);
}
