/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:47:26 by nuno              #+#    #+#             */
/*   Updated: 2025/05/29 22:08:36 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

// Function to handle the environment variables
static void	handle_env_vars(t_env_var *env_var, char *var, t_env *env,
		char *equal_sign)
{
	if (!env_var)
	{
		add_env_var(&env);
		env_var = env->last;
		if (equal_sign)
			assign_env_var(env_var, var);
		else
		{
			env_var->key = ft_strdup(var);
			env_var->value = NULL;
		}
		env_var->exported = true;
	}
	else
	{
		if (equal_sign)
			assign_env_var(env_var, var);
		env_var->exported = true;
	}
}

// Function to export a variable
void	export_var(char *var, t_env *env)
{
	t_env_var	*env_var;
	char		*equal_sign;
	char		*key;

	if (!var || !env)
		return ;
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
		key = ft_substr(var, 0, equal_sign - var);
	else
		key = ft_strdup(var);
	if (!key)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return ;
	}
	if (!ft_isalpha(key[0]) && (key[0] != '_'))
		return ;
	env_var = find_env_var(env, key);
	handle_env_vars(env_var, var, env, equal_sign);
	free(key);
}

// Function to export environment variables without arguments
void	export_no_args(t_env *env, t_cmd *cmd)
{
	t_env_var	*env_var;

	(void)cmd;
	sort_env_list(env);
	env_var = env->head;
	while (env_var)
	{
		if (!env_var->value)
			ft_printf_fd(cmd->fd[1], "declare -x " RED "%s" RESET "=\n",
				env_var->key);
		else
			ft_printf_fd(cmd->fd[1], "declare -x  " RED "%s" RESET "=\"%s\"\n",
				env_var->key, env_var->value);
		env_var = env_var->next;
	}
}

// Function to export a variable with a value
void	ft_export(char *var, char *value, t_env *env)
{
	char	*var_value;

	if (!var)
		return ;
	else if (!value)
	{
		export_var(var, env);
		return ;
	}
	var_value = ft_strjoin(var, "=");
	var_value = ft_strjoin(var_value, value);
	export_var(var_value, env);
	free(var_value);
}

// export_builtin function processes the export command
void	export_builtin(t_cmd *cmd, t_shell *shell)
{
	int		i;
	t_env	*sorted_env;

	i = 0;
	sorted_env = NULL;
	if (cmd->args[0] == NULL)
	{
		sorted_env = copy_env_list(shell->env);
		export_no_args(sorted_env, cmd);
		free_env(sorted_env);
		shell->exit_value = 1;
		return ;
	}
	while (cmd->args[i])
	{
		ft_export(cmd->args[i], NULL, shell->env);
		i++;
	}
	shell->exit_value = 0;
}
