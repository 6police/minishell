#include "ft_builtins.h"

// we need to somehow convert the linked list of env variables to an array of strings
// so that we can pass it to the execve function
// we will use the following function to convert the linked list to an array of strings

static void free_env_array(char **envp);
static size_t	count_env_vars(t_env *env);
static char	**convert_env_to_array(t_env *env);

// function to execute the command
void	execute_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = convert_env_to_array(shell->env);
	if (!envp)
	{
		ft_putstr_fd("minishell: malloc failed\n", 2);
		//shell->exit_value = 1; ?? confirmar
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		shell->is_child = true;
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (execve(cmd->path, cmd->args, envp) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(cmd->name, 2);
			ft_putstr_fd("\n", 2);
			free_env_array(envp); // confirmar que é necessário
			//shell->exit_value = 127; adicionar??
			exit(127);
		}
	}
	else if (pid < 0)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			shell->exit_value = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
			shell->exit_value = WEXITSTATUS(status);
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
		{
			while (i > 0)
				free(envp[i--]);
			free(envp);
			return (NULL);
		}
		envp[i] = ft_strjoin(temp, current->value);
		free(temp);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[i--]);
			free(envp);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

static void free_env_array(char **envp)
{
	int i = 0;
	if (!envp) return;

	while (envp[i])
		free(envp[i++]);
	free(envp);
}