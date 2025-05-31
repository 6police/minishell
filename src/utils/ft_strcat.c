/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:54 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 18:17:56 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

char	*ft_strcat(char *dest, const char *src)
{
	char		*d;
	const char	*s;

	if (!dest || !src)
		return (NULL);
	d = dest;
	s = src;
	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = '\0';
	return (dest);
}
