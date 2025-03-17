
#include "ft_validations.h"

int	file_access_check(char *file)
{
	if (access(file, F_OK) == -1)
		return (ft_printf("Error: %s: No such file or directory\n", file));
	return (0);
}

char	*ft_strjoin2(char *paths, char *cmd)
{
	char	*path1;
	char	*path2;

	path1 = ft_strjoin(paths, "/");
	path2 = ft_strjoin(path1, cmd);
	free(path1);
	return (path2);
}

char	*checkforpath(char *cmd, t_env *env)
{
	t_env_var *tmp;
	int i;
	char **paths;
	char *full_cmd;

	tmp = find_env_var(env, "PATH");
	if (!tmp || !tmp->value || !tmp->value[0])
		return (NULL);
	paths = ft_split(tmp->value, ':');
	i = 0;
	while (paths[i] != NULL && paths[i][0] != '\0')
	{
		full_cmd = ft_strjoin2(paths[i], cmd);
		if (access(full_cmd, F_OK) == 0)
		{
			free_split(paths);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_split(paths);
	return (NULL);
}