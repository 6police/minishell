#include "ft_env.h"

// function to assign the key and value to the environment variable
void	assign_env_var(t_env_var *env_var, char *env)
{
    char *equal_sign;
    
    if (!env_var || !env)
        return;

    equal_sign = ft_strchr(env, '=');
    if (equal_sign)
    {
        // Free existing values if they exist
        if (env_var->key)
            free(env_var->key);
        if (env_var->value)
            free(env_var->value);
            
        // Split into key and value
        env_var->key = ft_substr(env, 0, equal_sign - env);
        env_var->value = ft_strdup(equal_sign + 1);
        
        // Verify allocation succeeded
        if (!env_var->key || !env_var->value)
        {
            ft_putstr_fd("Error: malloc failed\n", 2);
            exit(1);
        }
    }
    else if (!env_var->key)  // Only set key if it doesn't exist
    {
        // Just a key, no value
        env_var->key = ft_strdup(env);
        if (!env_var->key)
        {
            ft_putstr_fd("Error: malloc failed\n", 2);
            exit(1);
        }
        // Keep existing value if there was one
    }
}

// function to add an env variable to the list
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
	if (!(*env)->head) // If the list is empty
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

// Function to create a copy of the environment
t_env	*copy_env(char **env)
{
	t_env *env_cpy;
	t_env_var	*shlvl;
	char *shlvl_value;
	int shlvl_int;

	if (!env)
	{
		ft_putstr_fd("Error: invalid environment\n", 2);
		exit(1);
	}

	shlvl_int = 0;
	
	env_cpy = ft_calloc(1, sizeof(t_env)); // Allocate for the environment list
	if (!env_cpy)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}

	while (*env)
	{
		add_env_var(&env_cpy);              
			// Pass pointer to t_env* to add the new variable
		assign_env_var(env_cpy->last, *env);
			// Assign the key and value for the variable
		env++;
	}

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
	// Update the SHLVL value
	 

	return (env_cpy); // Return the t_env list
}

static void	populate_env(t_env *env)
{
	add_env_var(&env);
	assign_env_var(env->last, "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
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


t_env *new_env(void)
{
	t_env *new_env;

	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	populate_env(new_env);
	return (new_env);
}

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