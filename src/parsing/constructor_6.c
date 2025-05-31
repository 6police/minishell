/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:19:57 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:35:15 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to check if the argument is a redirection without an argument
int	count_valid_args(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!args || !args[0] || args[0][0] == '\0')
		return (0);
	while (args[i] && args[i][0] != '\0')
	{
		if (is_redir_noarg(args[i]))
			i += 2;
		else if (is_redir(args[i]))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

// function to copy valid arguments from the original args array
char	**copy_valid_args(char **args, int count)
{
	char	**newargs;
	int		i;
	int		j;

	newargs = ft_calloc(sizeof(char *), count + 1);
	if (!newargs)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i] && args[i][0] != '\0')
	{
		if (is_redir_noarg(args[i]))
			i += 2;
		else if (is_redir(args[i]))
			i++;
		else
		{
			newargs[j] = ft_strdup(args[i]);
			j++;
			i++;
		}
	}
	return (newargs);
}
