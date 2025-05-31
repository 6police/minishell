/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:21 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 18:17:22 by joao             ###   ########.fr       */
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
