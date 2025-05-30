/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:44 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 18:02:27 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

//--- Helpers ----------------------------------------------------------------
bool	has_wildcard(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == '*')
			return (true);
	return (false);
}

bool	is_quoted(const char *s)
{
	int	i;

	if (!s)
		return (false);
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

char	**split_path(const char *path)
{
	return (ft_split(path, '/'));
}

void	free_strarr(char **a)
{
	int	i;

	if (!a)
		return ;
	if (!*a)
	{
		free(a);
		return ;
	}
	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}

int	tolower_ci(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
