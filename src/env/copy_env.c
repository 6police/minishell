/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:38 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:32:38 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

static void	handle_shell_value(t_env *env_cpy)
{
	char		*shlvl_value;
	int			shlvl_int;
	t_env_var	*shlvl;

	shlvl = find_env_var(env_cpy, "SHLVL");
	shlvl_int = ft_atoi(shlvl->value);
	shlvl_int++;
	shlvl_value = ft_itoa(shlvl_int);
	if (!shlvl_value)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	free(shlvl->value);
	shlvl->value = shlvl_value;
}

// Function to create a copy of the environment
t_env	*copy_env(char **env)
{
	t_env	*env_cpy;

	if (!env)
	{
		ft_putstr_fd("Error: invalid environment\n", 2);
		exit(1);
	}
	env_cpy = ft_calloc(1, sizeof(t_env));
	if (!env_cpy)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	while (*env)
	{
		add_env_var(&env_cpy);
		assign_env_var(env_cpy->last, *env);
		env++;
	}
	handle_shell_value(env_cpy);
	return (env_cpy);
}

static void	populate_env(t_env *env)
{
	add_env_var(&env);
	assign_env_var(env->last,
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	add_env_var(&env);
	assign_env_var(env->last, "PWD=/home/user");
	add_env_var(&env);
	assign_env_var(env->last, "OLDPWD=/home/user");
	add_env_var(&env);
	assign_env_var(env->last, "SHLVL=1");
	add_env_var(&env);
	assign_env_var(env->last, "HOME=/home/user");
	add_env_var(&env);
	assign_env_var(env->last, "USER=user");
	add_env_var(&env);
	assign_env_var(env->last, "LOGNAME=user");
	add_env_var(&env);
	assign_env_var(env->last, "TERM=xterm-256color");
	add_env_var(&env);
	assign_env_var(env->last, "SHELL=/bin/bash");
	add_env_var(&env);
	assign_env_var(env->last, "LANG=en_US.UTF-8");
	add_env_var(&env);
	assign_env_var(env->last, "LC_ALL=en_US.UTF-8");
}

t_env	*new_env(void)
{
	t_env	*new_env;

	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	populate_env(new_env);
	return (new_env);
}
