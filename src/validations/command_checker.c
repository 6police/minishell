
# include "ft_validations.h"

char *checkforpath(char *cmd, t_env *env)
{
    t_env_var *tmp;
    int i;
    char **paths;

    tmp = find_env_var(env, "PATH");
    if (!tmp || !tmp->value)
        return (NULL);
    paths = ft_split(tmp->value, ':');
    i = 0;
    while (paths[i])
    {
        cmd = ft_strjoin(paths[i], cmd);
        if (access(cmd, F_OK) == 0)
            return (cmd);
        free(cmd);
        i++;
    }
    return (NULL);
}