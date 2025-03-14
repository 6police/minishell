
# include "ft_validations.h"

char *checkforpath(char *cmd, t_env *env)
{
	t_env_var *tmp;
	struct stat	st;
	int i;
	char **paths;

    tmp = find_env_var(env, "PATH");
    if (!tmp || !tmp->value || !tmp->value[0])
        return (NULL);
    paths = ft_split(tmp->value, ':');
    i = 0;
    while (paths[i] != NULL && paths[i][0] != '\0') 
    {
        cmd = ft_strjoin(paths[i], cmd);
        if (access(cmd, F_OK) == 0)
            return (cmd);
        free(cmd);
        cmd = NULL;
        i++;
    }
    return (NULL);
}





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
