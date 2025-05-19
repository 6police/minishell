#include "ft_builtins.h"

static char	*cd(t_cmd *cmd, t_shell *shell);
static void	change_dir(char *path, t_shell *shell, t_cmd *cmd);
static void	update_pwd_env_vars(t_env *env, t_env_var *oldpwd, t_env_var *pwd);

void	cd_shell(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = cd(cmd, shell);
	if (!path)
	{
		shell->exit_value = 1;
		return ;
	}
	change_dir(path, shell, cmd);
	return ;
}

static char	*cd(t_cmd *cmd, t_shell *shell)
{
	t_env_var	*home;

	home = NULL;
	if (!cmd->args[0])
	{
		home = find_env_var(shell->env, "HOME");
		ft_printf_fd(cmd->fd[1], "home: %s\n", home->value);
		if (!home || !home->value)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			shell->exit_value = 1;
			return (NULL);
		}
		return (home->value);
	}
	return (cmd->args[0]);
}

static void	change_dir(char *path, t_shell *shell, t_cmd *cmd)
{
	t_env_var	*oldpwd;
	t_env_var	*pwd;
	char		*new_path;

	oldpwd = find_env_var(shell->env, "OLDPWD");
	pwd = find_env_var(shell->env, "PWD");
	new_path = path;
	if (ft_strcmp(path, "-") == 0)
	{
		if (!oldpwd || !oldpwd->value || oldpwd->value[0] == '\0')
			ft_printf_fd(shell->fd[2], "minishell: cd: OLDPWD not set\n");
			shell->exit_value = 1;
			return;
		new_path = oldpwd->value;
		ft_putstr_fd(new_path, cmd->fd[1]);
		ft_putstr_fd("\n", cmd->fd[1]);
		shell->exit_value = 0;
	}
	if (chdir(new_path) != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", new_path);
		shell->exit_value = 1;
		return ;
	}
	update_pwd_env_vars(shell->env, oldpwd, pwd);
}

static void	update_pwd_env_vars(t_env *env, t_env_var *oldpwd, t_env_var *pwd)
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
