/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:29 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 18:13:08 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

static size_t	size_copy(size_t size, size_t old_size)
{
	if (old_size < size)
		return (old_size);
	else
		return (size);
}

char	**ft_realloc_arr(char **ptr, size_t size, size_t old_size)
{
	char	**new_arr;
	size_t	i;
	size_t	new_size;

	if (size == 0)
		return (NULL);
	new_size = size_copy(size, old_size);
	new_arr = malloc(sizeof(char *) * (new_size + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_size && ptr && ptr[i])
	{
		new_arr[i] = ptr[i];
		i++;
	}
	while (i <= size)
		new_arr[i++] = NULL;
	if (ptr)
		free(ptr);
	return (new_arr);
}
