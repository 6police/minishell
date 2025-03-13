/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:47:26 by nuno              #+#    #+#             */
/*   Updated: 2025/02/12 20:36:09 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

void	export_var(char *var, t_env *env)
{
	t_env_var	*env_var;

	env_var = find_env_var(env, var);
	if (!env_var)
	{
		add_env_var(&env);
		env_var = env->last;
		assign_env_var(env_var, var);
	}
	else
		assign_env_var(env_var, var);
}


void	export_no_args(t_env *env)
{
    t_env_var	*env_var;

    sort_env_list(env);

    env_var = env->head;
    while (env_var)
    {
        if (!env_var->value)
            printf("declare -x " RED"%s"RESET "=\n", env_var->key);
        else
            printf("declare -x  " RED"%s"RESET  "=\"%s\"\n", env_var->key, env_var->value);
        env_var = env_var->next;
    }
}

void ft_export(char *var, char  *value, t_env *env)
{
    char *var_value;

    if (!var)
    {
        export_no_args(env); 
        return ;
    }
    if (!value)
    {
        export_var(var, env);
        return ;
    }
    var_value = ft_strjoin(var, "=");
    var_value = ft_strjoin(var_value, value);
    export_var(var_value, env);
    free(var_value);
}

void export_builtin(t_cmd *cmd, t_shell *shell)
{
    int i;

    (void)cmd;
    if (!shell->tokens[1])
    {
        export_no_args(shell->env);
        return ;
    }

    i = 1;
    while (shell->tokens[i])
    {
        ft_export(shell->tokens[i], NULL, shell->env);
        i++;
    }
}