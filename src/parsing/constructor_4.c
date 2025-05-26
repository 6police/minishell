#include "ft_parsing.h"

void assemble_cmd_path(t_cmd *cmd, char **args)
{
    cmd->path = ft_strdup(cmd->name);
    cmd->is_valid = true;
    cmd->args = copy_array(args);
    cmd->builtin_func = execute_external;
}

void assemble_cmd(t_cmd *cmd, char **args, t_shell *shell)
{
    char *path;

    path = checkforpath(cmd->name, shell->env);
    if (path)
    {
        cmd->path = path;
        cmd->is_valid = true;
        cmd->args = copy_array(args);
        cmd->builtin_func = execute_external;
    }
    else
    {
        cmd->path = NULL;
        cmd->is_valid = false;
        cmd->args = copy_array(args);
        cmd->builtin_func = NULL;
    }
}
