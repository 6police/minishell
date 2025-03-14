/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:50:50 by joamiran          #+#    #+#             */
/*   Updated: 2024/04/12 17:44:35 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strjoin() function

Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
*/

static void	word_copy(char *s1, char *s2, size_t *i)
{
	size_t	j;

	j = *i;
	while (*s2)
	{
		s1[j] = *s2;
		j++;
		s2++;
	}
	*i = j;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	new_str = malloc((sizeof(char) * (ft_strlen(str1) + ft_strlen(str2))) + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		word_copy(new_str, str1, &i);
	if (s2)
		word_copy(new_str, str2, &i);
	new_str[i] = '\0';
	return (new_str);
}
