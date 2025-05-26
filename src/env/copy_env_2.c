#include "ft_env.h"

t_env	*copy_env_list(t_env *env)
{
	t_env *copy;
	t_env_var *curr;
	t_env_var *new_var;

	if (!env)
		return (NULL);
	copy = ft_calloc(1, sizeof(t_env));
	if (!copy)
		return (NULL);
	curr = env->head;
	while (curr)
	{
		add_env_var(&copy);
		new_var = copy->last;
		if (!new_var)
		{
			ft_putstr_fd("Error: malloc failed\n", 2);
			exit(1);
		}
		assign_env_var(new_var, curr->key);
		if (curr->value)
		{
			new_var->value = ft_strdup(curr->value);
			if (!new_var->value)
			{
				ft_putstr_fd("Error: malloc failed\n", 2);
				exit(1);
			}
		}
		new_var->exported = curr->exported;
		curr = curr->next;
	}
	return (copy);
}