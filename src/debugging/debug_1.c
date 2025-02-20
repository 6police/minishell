#include "ft_debug.h"

// Print the enviroment variables
void print_env(t_env *env)
{
    t_env_var *tmp;

    tmp = env->head;
    while (tmp)
	{
		if (tmp->value)
			printf(RED"%s"RESET"=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void print_export(t_env *env)
{
	t_env_var *tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}