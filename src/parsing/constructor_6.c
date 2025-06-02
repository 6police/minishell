/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:19:57 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 21:10:02 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

int	is_only_redir_symbols(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != '<' && str[i] != '>')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_redir_count(char **args, int *i)
{
	if (is_only_redir_symbols(args[*i]) && !args[*i + 1])
	{
		ft_printf_fd(2, REDIR_FAILURE "\n");
		return (0);
	}
	if (starts_with_redir(args[*i]))
	{
		(*i)++;
		if (args[*i])
			(*i)++;
		return (1);
	}
	return (-1);
}

static int	handle_redir_copy(char **args, int *i)
{
	if (is_only_redir_symbols(args[*i]) && !args[*i + 1])
		return (0);
	if (starts_with_redir(args[*i]))
	{
		(*i)++;
		if (args[*i])
			(*i)++;
		return (1);
	}
	return (-1);
}

int	count_valid_args(char **args)
{
	int	i;
	int	count;
	int	ret;

	i = 0;
	count = 0;
	while (args && args[i] && args[i][0] != '\0')
	{
		ret = handle_redir_count(args, &i);
		if (ret == 0)
			break ;
		if (ret == -1)
		{
			count++;
			i++;
		}
	}
	return (count);
}

// char	**copy_valid_args(char **args, int count)
// {
// 	char	**newargs;
// 	int		i;
// 	int		j;
// 	int		ret;

// 	newargs = ft_calloc(sizeof(char *), count + 1);
// 	if (!newargs)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (args[i] && args[i][0] != '\0')
// 	{
// 		ret = handle_redir_copy(args, &i);
// 		if (ret == 0)
// 			break ;
// 		if (ret == -1)
// 			newargs[j++] = ft_strdup(args[i++]);
// 	}
// 	return (newargs);
// }

char	**copy_valid_args(char **args, int count)
{
	char	**newargs;
	int		i = 0;
	int		j = 0;
	int		ret;
	char	*stripped;

	newargs = ft_calloc(sizeof(char *), count + 1);
	if (!newargs)
		return (NULL);
	while (args[i] && args[i][0] != '\0')
	{
		ret = handle_redir_copy(args, &i);
		if (ret == 0)
			break ;
		if (ret == -1)
		{
			stripped = strip_quotes(args[i]);
			if (!stripped)
			{
				while (j > 0)
					free(newargs[--j]);
				free(newargs);
				return (NULL);
			}
			newargs[j++] = stripped;
			i++;
		}
	}
	return (newargs);
}
