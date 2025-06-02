/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:29 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 18:32:06 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

static size_t	ft_arrsize(char **arr);

char	**ft_realloc_arr(char **ptr, size_t new_cap)
{
	char	**new_arr;
	size_t	old_len;
	size_t	i;

	old_len = ft_arrsize(ptr);
	if (new_cap < old_len)
		return (NULL);
	new_arr = malloc(sizeof(char *) * (new_cap + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_len)
	{
		new_arr[i] = ptr[i];
		i++;
	}
	while (i < new_cap + 1)
		new_arr[i++] = NULL;
	if (ptr)
		free(ptr);
	return (new_arr);
}

static size_t	ft_arrsize(char **arr)
{
	size_t	count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}
