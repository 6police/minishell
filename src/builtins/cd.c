/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:57:15 by nuno              #+#    #+#             */
/*   Updated: 2025/05/30 17:27:39 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

static char	*get_cd_path(t_cmd *cmd, t_shell *shell);
static void	change_dir(char *path, t_shell *shell);
static void	update_pwd_env_vars(t_shell *shell, t_env_var *pwd);

// cd_shell - Change the current directory in the shell
void	cd_shell(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = get_cd_path(cmd, shell);
	if (!path)
	{
		shell->exit_value = 1;
		return ;
	}
	change_dir(path, shell);
}

static char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	t_env_var	*dest;

	dest = NULL;
	if (!cmd->args[0])
	{
		dest = find_env_var(shell->env, "HOME");
		if (!dest || !dest->value)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
			return (NULL);
		}
		return (dest->value);
	}
	else if (ft_strcmp(cmd->args[0], "-") == 0)
	{
		printf("%s\n", cmd->args[0]);
		dest = find_env_var(shell->env, "OLDPWD");
		if (!dest || !dest->value || dest->value[0] == '\0')
		{
			ft_printf_fd(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
			return (NULL);
		}
		return (dest->value);
	}
	return (cmd->args[0]);
}

static void	change_dir(char *path, t_shell *shell)
{
	if (chdir(path))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: \
			cd: %s: No such file or directory\n", path);
		shell->exit_value = 1;
		return ;
	}
	shell->exit_value = 0;
	update_pwd_env_vars(shell, find_env_var(shell->env, "PWD"));
}

static void	update_pwd_env_vars(t_shell *shell, t_env_var *pwd)
{
	char	cwd[PATH_MAX];
	char	*pwd_value;
	char	*oldpwd_value;

	oldpwd_value = NULL;
	pwd_value = NULL;
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (pwd)
			oldpwd_value = ft_strjoin("OLDPWD=", pwd->value);
		else
			oldpwd_value = ft_strdup("OLDPWD=");
		pwd_value = ft_strjoin("PWD=", cwd);
		ft_export(pwd_value, NULL, shell->env);
		ft_export(oldpwd_value, NULL, shell->env);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: getcwd failed\n");
		shell->exit_value = 1;
	}
	free(pwd_value);
	free(oldpwd_value);
}
