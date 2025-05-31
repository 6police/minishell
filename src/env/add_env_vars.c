/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:10 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:32:12 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

static void	chng_env_var(t_env_var *env_var, char *env, char *equal_sign)
{
	if (equal_sign)
	{
		if (env_var->key)
			free(env_var->key);
		if (env_var->value)
			free(env_var->value);
		env_var->key = ft_substr(env, 0, equal_sign - env);
		env_var->value = ft_strdup(equal_sign + 1);
		if (!env_var->key || !env_var->value)
		{
			ft_putstr_fd("Error: malloc failed\n", 2);
			exit(1);
		}
	}
	else if (!env_var->key)
	{
		env_var->key = ft_strdup(env);
		if (!env_var->key)
		{
			ft_putstr_fd("Error: malloc failed\n", 2);
			exit(1);
		}
	}
}

// function to assign the key and value to the environment variable
void	assign_env_var(t_env_var *env_var, char *env)
{
	char	*equal_sign;

	if (!env_var || !env)
		return ;
	equal_sign = ft_strchr(env, '=');
	chng_env_var(env_var, env, equal_sign);
}

// Function to add an env variable to the list
void	add_env_var(t_env **env)
{
	t_env_var	*new_var;

	if (!env || !*env)
	{
		ft_putstr_fd("Error: invalid environment\n", 2);
		exit(1);
	}
	new_var = ft_calloc(1, sizeof(t_env_var));
	if (!new_var)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	if (!(*env)->head)
	{
		(*env)->head = new_var;
		(*env)->last = new_var;
	}
	else
	{
		(*env)->last->next = new_var;
		(*env)->last = new_var;
	}
}
