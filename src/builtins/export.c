
#include "ft_builtins.h"

void	export_var(char *var, t_env *env)
{
	t_env_var	*env_var;
	char		*equal_sign;
	char		*key;

	if (!var || !env)
		return;
	
	// Find the position of the equals sign
	equal_sign = ft_strchr(var, '=');
	
	// Extract the key (variable name) from the input
	if (equal_sign)
		key = ft_substr(var, 0, equal_sign - var);
	else
		key = ft_strdup(var);
	
	if (!key)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return;
	}
	
	// Find existing variable
	env_var = find_env_var(env, key);
	
	if (!env_var)
	{
		// Variable doesn't exist, create new one
		add_env_var(&env);
		env_var = env->last;
		if (equal_sign)
		{
			// New variable with value
			free(key);
			assign_env_var(env_var, var);
		}
		else
		{
			// New variable without value
			env_var->key = key;
			env_var->value = NULL;
		}
		env_var->exported = true;
	}
	else
	{
		// Variable exists
		free(key);  // Free the temporary key
		if (equal_sign)
		{
			// Update existing variable with new value
			assign_env_var(env_var, var);
		}
		env_var->exported = true;  // Mark as exported
	}
}


void	export_no_args(t_env *env, t_cmd *cmd)
{
    t_env_var	*env_var;

    (void)cmd; // to avoid unused parameter warning
    sort_env_list(env);

    env_var = env->head;
    while (env_var)
    {
        if (!env_var->value)
            ft_printf_fd(cmd->fd[1], "declare -x " RED"%s"RESET "=\n", env_var->key);
        else
            ft_printf_fd(cmd->fd[1], "declare -x  " RED"%s"RESET  "=\"%s\"\n", env_var->key, env_var->value);
        env_var = env_var->next;
    }
}

void ft_export(char *var, char  *value, t_env *env)
{
    char *var_value;

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
    //printf("EXPORTED %s", var);
    free(var_value);
}

void export_builtin(t_cmd *cmd, t_shell *shell)
{
    int i;
    t_env *sorted_env;

    i = 0;
    sorted_env = NULL;
    // add a checker for '*'
    if (cmd->args[0] == NULL)
    {
        sorted_env = copy_env_list(shell->env);
        export_no_args(sorted_env, cmd);
        free_env(sorted_env);
        return;
    }

    while (cmd->args[i])
    {
        ft_export(cmd->args[i], NULL, shell->env);
        i++;
    }
    shell->exit_value = 0;
}
