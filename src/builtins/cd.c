/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:04:45 by nuno              #+#    #+#             */
/*   Updated: 2025/01/15 21:05:36 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd(char *cmd, t_env *env);
void	change_dir(char *path, t_env *env);

void	cd_shell(char *cmd, t_env *env)
{
	char *path;

	path = cd(cmd, env);
	if (!path)
		return ;
	change_dir(path, env);
}

char	*cd(char *cmd, t_env *env)
{
	t_env_var	*home;
	char		*path;

	if (!cmd) // No argument: go to $HOME
	{
		home = find_env_var(env, "HOME");
		if (!home || !home->value)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		path = home->value;
	}
	else
		path = cmd;
	return (path);
}
void	change_dir(char *path, t_env *env)
{
	char		cwd[PATH_MAX];
	t_env_var	*oldpwd;
	t_env_var	*pwd;

	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			oldpwd = find_env_var(env, "OLDPWD");
			pwd = find_env_var(env, "PWD");
			if (oldpwd)
			{
				free(oldpwd->value);
				if (pwd)
					oldpwd->value = ft_strdup(pwd->value);
				else
					oldpwd->value = ft_strdup("");
			}
			if (pwd)
				free(pwd->value), pwd->value = ft_strdup(cwd);
		}
	}
	else
		printf("minishell: cd: %s: No sush file or directory", path);
}
