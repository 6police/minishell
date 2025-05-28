#include "ft_env.h"

static void	copy_env_var(t_env *copy, t_env_var *curr)
{
	t_env_var	*new_var;

	add_env_var(&copy);
	new_var = copy->last;
	if (!new_var)
		handle_malloc_failure();
	assign_env_var(new_var, curr->key);
	if (curr->value)
	{
		new_var->value = ft_strdup(curr->value);
		if (!new_var->value)
			handle_malloc_failure();
	}
	new_var->exported = curr->exported;
}

t_env	*copy_env_list(t_env *env)
{
	t_env		*copy;
	t_env_var	*curr;

	if (!env)
		return (NULL);
	copy = ft_calloc(1, sizeof(t_env));
	if (!copy)
		return (NULL);
	curr = env->head;
	while (curr)
	{
		copy_env_var(copy, curr);
		curr = curr->next;
	}
	return (copy);
}
