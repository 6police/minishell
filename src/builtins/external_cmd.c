/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:59:08 by nuno              #+#    #+#             */
/*   Updated: 2025/05/30 02:13:13 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

static void		free_env_array(char **envp);
static size_t	count_env_vars(t_env *env);
static char		**convert_env_to_array(t_env *env);
static void		free_envp(char **envp, int i);

// function to execute the command
void	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	**envp;

	envp = convert_env_to_array(shell->env);
	if (!envp)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: malloc failed\n");
		return ;
	}
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		if (errno == ENOENT)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: command not found: %s\n",
				cmd->name);
			shell->exit_value = 127;
			exit(127);
		}
		else
		{
			shell->exit_value = 126;
			exit(126);
		}
	}
	free_env_array(envp);
}

// Function to count the number of environment variables
static size_t	count_env_vars(t_env *env)
{
	size_t		count;
	t_env_var	*current;

	count = 0;
	current = env->head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// Function to convert the linked list to an array of strings
static char	**convert_env_to_array(t_env *env)
{
	size_t		i;
	char		**envp;
	t_env_var	*current;
	char		*temp;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (count_env_vars(env) + 1));
	if (!envp)
		return (NULL);
	current = env->head;
	while (current)
	{
		temp = ft_strjoin(current->key, "=");
		if (!temp)
			return (free_envp(envp, i), NULL);
		envp[i] = ft_strjoin(temp, current->value);
		free(temp);
		if (!envp[i])
			return (free_envp(envp, i), NULL);
		current = current->next;
		i++;
	}
	return (envp[i] = NULL, envp);
}

static void	free_envp(char **envp, int i)
{
	while (i > 0)
		free(envp[i--]);
	free(envp);
	return ;
}

static void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
