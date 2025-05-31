/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:07 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:32:08 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

static void	swap_env_vars(t_env_var *a, t_env_var *b)
{
	char	*temp_key;
	char	*temp_value;
	bool	temp_exported;

	temp_key = a->key;
	temp_value = a->value;
	temp_exported = a->exported;
	a->key = b->key;
	a->value = b->value;
	a->exported = b->exported;
	b->key = temp_key;
	b->value = temp_value;
	b->exported = temp_exported;
}

void	sort_env_list(t_env *env)
{
	t_env_var	*i;
	t_env_var	*j;
	int			swapped;

	if (!env || !env->head || !env->head->next)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = env->head;
		while (i && i->next)
		{
			j = i->next;
			if (ft_strcmp(i->key, j->key) > 0)
			{
				swap_env_vars(i, j);
				swapped = 1;
			}
			i = i->next;
		}
	}
}
