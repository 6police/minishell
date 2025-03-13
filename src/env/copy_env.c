#include "ft_env.h"

// function to assign the key and value to the environment variable
void	assign_env_var(t_env_var *env_var, char *env)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (equal_sign != 0)
	{
		env_var->key = ft_substr(env, 0, equal_sign - env);
		env_var->value = ft_strdup(equal_sign + 1); // Value starts after '='
	}
	else
	{
		// Handle the case where there's no '=' in the string
		env_var->key = ft_substr(env, 0, ft_strlen(env));
		env_var->value = NULL;
	}
}

// function to add an env variable to the list
// Function to add an env variable to the list
void	add_env_var(t_env **env)
{
	if (!(*env)->head)  // If the list is empty, initialize it
	{
		(*env)->head = ft_calloc(1, sizeof(t_env_var));  // Allocate the first variable
		if (!(*env)->head)
		{
			ft_putstr_fd("Error: malloc failed\n", 2);
			exit(1);
		}
		(*env)->last = (*env)->head;  // Set last to head (first element)
	}
	else  // If the list is not empty, append the new variable
	{
		(*env)->last->next = ft_calloc(1, sizeof(t_env_var));  // Allocate a new variable
		if (!(*env)->last->next)
		{
			ft_putstr_fd("Error: malloc failed\n", 2);
			exit(1);
		}
		(*env)->last = (*env)->last->next;  // Update last pointer to the new element
	}
}


// Function to create a copy of the environment
t_env	*copy_env(char **env)
{
	t_env	*env_cpy;

	env_cpy = ft_calloc(1, sizeof(t_env));  // Allocate for the environment list
	if (!env_cpy)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}

	while (*env)
	{
		add_env_var(&env_cpy);  // Pass pointer to t_env* to add the new variable
		assign_env_var(env_cpy->last, *env);  // Assign the key and value for the variable
		env++;
	}
	return (env_cpy);  // Return the t_env list
}
