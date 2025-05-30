/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:33:58 by joamiran          #+#    #+#             */
/*   Updated: 2025/05/30 18:23:52 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
split()
allocates with malloc and returns an array of strings obtained by splitting 's'
using the character 'c' as a delimiter. The array must be ended by NULL.
s - the string to be split
c - the delimiter character
*/

// count the nbr of words
/*
static size_t	ft_word_count(char const *s, char sep)
{
	size_t	words;

	if (!s)
		return (0);
	words = 0;
	while (*s)
	{
		if (*s == sep)
		{
			while (*s == sep && *s)
				s++;
		}
		else
		{
			while (*s != sep && *s)
				s++;
			words++;
		}
	}
	return (words);
}

static void	word_copying(char **vector, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = i;
			while (s[j] && s[j] != c)
				j++;
			vector[k++] = ft_substr(s, i, j - i);
			i = j;
		}
	}
	vector[k] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**words_vector;

	if (s == NULL)
	{
		words_vector = ft_calloc(1, sizeof(char *));
		if (!words_vector)
			return (NULL);
		return (words_vector);
	}
	words_vector = ft_calloc(((ft_word_count(s, c)) + 1), sizeof(char *));
	if (!words_vector)
		return (NULL);
	word_copying(words_vector, s, c);
	return (words_vector);
}

int	main(void)
{
	char	*s;
	char	**words;
	int		i;

	s = NULL;
	words = ft_split(s, ',');
	i = 0;
	while (words[i])
	{
		printf("%s\n", words[i]);
		i++;
	}
	return (0);
}
 */

static int	count_words(const char *s, char c)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	if (!*s)
		return (0);
	while (s[i])
	{
		if (s[0] != c && i == 1)
			result++;
		if (s[i - 1] == c && s[i] != c)
			result++;
		i++;
	}
	if (s[0] != c && i == 1 && ft_strlen(s) == 1)
		result++;
	return (result);
}

static int	find_del(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c || !s[i])
		return (i);
	return (0);
}

static char	**ft_free_malloc(char **ptr, int d)
{
	int	i;

	i = 0;
	while (i < d)
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		words;
	int		pos;
	int		d;
	char	**ptr;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	ptr = ft_calloc((size_t)count_words((char *)s, c) + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	d = -1;
	while (++d < words)
	{
		while (s[i] == c)
			i++;
		pos = find_del((char *)s + i, c);
		ptr[d] = ft_substr(s, (unsigned int)i, (size_t)pos);
		if (!ptr[d])
			return (ft_free_malloc(ptr, d));
		i += pos + 1;
	}
	return (ptr);
}
