/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:00:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/15 21:10:25 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// function to find the env variable in the list
t_env_var	*find_env_var(t_env *env, char *key)
{
	t_env_var	*tmp;

	tmp = env->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}


// function to remove a variable from the list
void	remove_env_var(t_env *env, char *key)
{
	t_env_var	*tmp;
	t_env_var	*prev;

	tmp = env->head;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
		if (prev)
			prev->next = tmp->next;
		else
			env->head = tmp->next;
		if (!tmp->next)
			env->last = prev;
		free_env_var(tmp);
		return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

// function to unset an environment variable
void unset_env_var(t_shell *shell, char *key)
{
	t_env_var	*env_var;

	env_var = find_env_var(shell->env, key);
	if (env_var)
		remove_env_var(shell->env, key);
}

// function to unset multiple environment variables
void unset_vars(t_shell *shell, char **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		unset_env_var(shell, keys[i]);
		i++;
	}
}
