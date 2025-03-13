#include "ft_builtins.h"

static char *cd(t_cmd *cmd, t_env *env);
static void change_dir(char *path, t_env *env);
static void update_pwd_env_vars(t_env *env, t_env_var *oldpwd, t_env_var *pwd);

void cd_shell(t_cmd *cmd, t_shell *shell)
{
	char *path;

	path = cd(cmd, shell->env);
	if (!path)
		return;
	change_dir(path, shell->env);
	return ;
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
}