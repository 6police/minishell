/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:21 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 20:57:01 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

// function to copy an array of strings
char	**copy_array(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!array || !(*array))
		return (NULL);
	while (array[i])
		i++;
	new_array = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

// // function to check if a string starts with a redirection symbol
bool	starts_with_redir(char *str)
{
	if (!str || !str[0])
		return (false);
	return (str[0] == '<' || str[0] == '>');
}

// function to strip quotes from a string
char	*strip_quotes(const char *s)
{
	char	*result;
	int		i = 0, j = 0;
	char	in_quote = 0;

	if (!s)
		return (NULL);
	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && (!in_quote || s[i] == in_quote))
		{
			if (in_quote == 0)
				in_quote = s[i];
			else
				in_quote = 0;
		}
		else
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}