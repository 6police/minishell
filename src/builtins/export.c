/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:47:26 by nuno              #+#    #+#             */
/*   Updated: 2025/01/15 21:10:37 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void export_no_args(t_env *env)
{
    t_env_var	*env_var;

    env_var = env->head;
    while (env_var)
    {
        if (env_var->exported)
        {
            if (env_var->value)
                ft_printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
            else
                ft_printf("declare -x %s\n", env_var->key);
        }
        env_var = env_var->next;
    }
}

void	export_bi(char *value, t_shell *shell)
{
	char	**vars;
	int		i;

    vars = ft_split(value, ' ');

    if (!vars[1])
    {
        export_no_args(shell->env);
        free(vars);
        return ;
    }
    
	i = 0;
	while (vars[i])
	{
		export_var(vars[i], shell->env);
		i++;
	}
	free(vars);
}
