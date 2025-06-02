/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:18:26 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 18:09:23 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_validations.h"

// function to check if a file exists and is accessible
int	file_access_check(char *file)
{
	if (access(file, F_OK) == -1)
		return (ft_printf("Error: %s: No such file or directory\n", file));
	return (0);
}

// function to join two strings with a '/' in between
char	*ft_strjoin2(char *paths, char *cmd)
{
	char	*path1;
	char	*path2;

	path1 = ft_strjoin(paths, "/");
	path2 = ft_strjoin(path1, cmd);
	free(path1);
	return (path2);
}

// function to check if a command is in the PATH environment variable
char	*checkforpath(char *cmd, t_env *env)
{
	t_env_var	*tmp;
	int			i;
	char		**paths;
	char		*full_cmd;

	if (ft_valid_pather(cmd) == false)
		return (NULL);
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

// check if command sent is in path format
// ex: /bin/ls
bool	is_command_path(char *cmd)
{
	if (check_file(cmd) == false)
		return (false);
	if (access(cmd, F_OK) == 0)
		return (true);
	return (false);
}
