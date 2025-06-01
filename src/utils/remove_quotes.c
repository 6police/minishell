/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:18:16 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 18:13:20 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

char	*remove_quotes_beg_end(char *arg)
{
	char	*new_str;

	if (!arg)
		return (NULL);
	if ((ft_strlen(arg) == 2 && arg[0] == '\"' && arg[1] == '\"')
		|| (ft_strlen(arg) == 2 && arg[0] == '\'' && arg[1] == '\''))
	{
		new_str = ft_strdup("");
		free(arg);
		return (new_str);
	}
	else if (arg[0] == '\"')
	{
		new_str = ft_strtrim(arg, "\"");
		free(arg);
		return (new_str);
	}
	else if (arg[0] == '\'')
	{
		new_str = ft_strtrim(arg, "\'");
		free(arg);
		return (new_str);
	}
	return (arg);
}

// removes all quotes from a string
char	*remove_all_quotes(char *arg)
{
	char	*new_str;
	char	*temp;

	if (!arg)
		return (NULL);
	new_str = ft_strdup(arg);
	if (!new_str)
		return (NULL);
	temp = new_str;
	while (*temp)
	{
		if (*temp == '\'' || *temp == '\"')
		{
			ft_memmove(temp, temp + 1, ft_strlen(temp));
			continue ;
		}
		temp++;
	}
	free(arg);
	return (new_str);
}

static int	count_unquoted_chars(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			count++;
		i++;
	}
	return (count);
}

// removes quotes from a single argument
static char	*remove_quotes_from_arg(const char *str)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	len = count_unquoted_chars(str);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

// removes quotes from each argument in an array of strings
char	**ft_removequotes(char **args)
{
	int		i;
	char	**newargs;

	i = 0;
	while (args[i])
		i++;
	newargs = ft_calloc(i + 1, sizeof(char *));
	if (!newargs)
		return (NULL);
	i = 0;
	while (args[i])
	{
		newargs[i] = remove_quotes_from_arg(args[i]);
		if (!newargs[i])
			return (NULL);
		i++;
	}
	newargs[i] = NULL;
	free_split(args);
	return (newargs);
}
