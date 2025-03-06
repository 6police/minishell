#include "ft_parsing.h"

// function that takes the shell->token and parses it into commands

// function to add a t_cmd to the t_cmd linked list
static void add_last_cmd (t_cmd **head, t_cmd *new_cmd)
{
    t_cmd *tmp;

    tmp = *head;
    if (!tmp)
        *head = new_cmd;
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
        new_cmd->prev = tmp;
    }
}

// function to create a new t_cmd
static t_cmd *init_cmd(char *name, char **args)
{
    t_cmd *cmd;

    cmd = ft_calloc(sizeof(t_cmd), 1);
    cmd->name = name;
    cmd->args = args;
    cmd->path = NULL;
    cmd->is_builtin = false;
    cmd->next = NULL;
    cmd->prev = NULL;
    cmd->redirs = NULL;
    cmd->last_fd = -1;
    cmd->last_read = -1;
    cmd->has_heredoc = false;
    return (cmd);
}

// function to check if its a built-in command
static void check_builtin(t_cmd *cmd)
{
    if (!cmd)
        return;
    if (ft_strcmp(cmd->name, "env") == 0)
        cmd->is_builtin = true;
    if (ft_strcmp(cmd->name, "exit") == 0)
        cmd->is_builtin = true;
    if (ft_strcmp(cmd->name, "export") == 0)
        cmd->is_builtin = true;
    if (ft_strcmp(cmd->name, "unset") == 0)
        cmd->is_builtin = true;
    if (ft_strcmp(cmd->name, "pwd") == 0)
        cmd->is_builtin = true;
    if (ft_strcmp(cmd->name, "cd") == 0)
        cmd->is_builtin = true;
}

void build_cmd(t_cmd *cmd, char **args)
{
    cmd->is_valid = true;
}

void build_builtin(t_cmd *cmd, char **args)
{
    cmd->is_valid = true;
    if (ft_strcmp(cmd->name, "cd") == 0)
        cmd->builtin_func = cd_shell;
    if (ft_strcmp(cmd->name, "echo") == 0)
        cmd->builtin_func = &echo_shell;
    if (ft_strcmp(cmd->name, "pwd") == 0)
        cmd->builtin_func = pwd_shell;
    if (ft_strcmp(cmd->name, "export") == 0)
        cmd->builtin_func = export_builtin;
    if (ft_strcmp(cmd->name, "unset") == 0)
        cmd->builtin_func = unset_env_var;
    if (ft_strcmp(cmd->name, "exit") == 0)
        cmd->builtin_func = exit_shell;
    
    
}


// funciton that takes tokens and assembles into commands
// we check if the command is a built-in command and if it is we set the is_builtin to true
// we also check if the command is a redirection
// then we check if the command is a pipe
// we then look for the path of the command, if found we set the path of the command and build the command
// if not found we set the path to NULL and command is now invalid
t_cmd **build_cmds(t_shell *shell)
{
    int i;
    t_cmd *cmd;
    t_cmd *head_cmd;
    char **args#include "ft_builtins.h"

static char *cd(t_cmd *cmd, t_env *env);
static void change_dir(char *path, t_env *env);
static void update_pwd_env_vars(t_env *env, t_env_var *oldpwd, t_env_var *pwd);

void cd_shell(t_cmd *cmd, t_env *env)
{
	char *path;

	path = cd(cmd, env);
	if (!path)
		return;
	change_dir(path, env);
}

static char *cd(t_cmd *cmd, t_env *env)
{
	t_env_var *home;

	if (!cmd->args[1])
	{
		home = find_env_var(env, "HOME");
		if (!home || !home->value)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (home->value);
	}
	else if (strcmp(cmd->args[1], "-") == 0)
	{
		return ("-");
	}
	return (cmd->args[1]);
}

static void change_dir(char *path, t_env *env)
{
	t_env_var *oldpwd;
	t_env_var *pwd;
	char *new_path;

	oldpwd = find_env_var(env, "OLDPWD");
	pwd = find_env_var(env, "PWD");
	new_path = path;
	if (strcmp(path, "-") == 0)
	{
		if (!oldpwd || !oldpwd->value || oldpwd->value[0] == '\0')
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return;
		}
		new_path = oldpwd->value;
		ft_putstr_fd(new_path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	if (chdir(new_path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(new_path, STDERR_FILENO); // joao troca por printf_fd
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return;
	}
	update_pwd_env_vars(env, oldpwd, pwd);
}

static void update_pwd_env_vars(t_env *env, t_env_var *oldpwd, t_env_var *pwd)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		if (oldpwd)
		{
			free(oldpwd->value);
			if (pwd && pwd->value)
				oldpwd->value = ft_strdup(pwd->value);
			else
				oldpwd->value = ft_strdup("");
			ft_export("OLDPWD", oldpwd->value, env);
		}
		if (pwd)
		{
			free(pwd->value);
			pwd->value = ft_strdup(cwd);
			ft_export("PWD", pwd->value, env);
		}
	}
};

    i = 0;
    head_cmd = NULL;
    while (shell->tokens[i])
    {
        args = ft_split(shell->tokens[i], ' ');
        cmd = init_cmd(args[0], args);
        check_builtin(cmd);
        if (cmd->is_builtin)
            build_builtin(cmd, args);
        else
        {
            cmd->path = checkforpath(cmd->name, shell->env);
            if (cmd->path)
                build_cmd(cmd, args);
            cmd->next = NULL;
            add_last_cmd(&head_cmd, cmd);
        }
        i++;
    }
    return (head_cmd);
}
