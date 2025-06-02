/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 01:11:47 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 16:21:12 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

int	strcmp_ci(const char *a, const char *b)
{
	int	ca;
	int	cb;

	while (*a && *b)
	{
		ca = tolower_ci((unsigned char)*a);
		cb = tolower_ci((unsigned char)*b);
		if (ca != cb)
			return (ca - cb);
		a++;
		b++;
	}
	return (tolower_ci((unsigned char)*a) - tolower_ci((unsigned char)*b));
}

static void	swap_strings(char **arr, int i, int j)
{
	char	*temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void	sort_strs(char **arr, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i + 1 < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (strcmp_ci(arr[i], arr[j]) > 0)
				swap_strings(arr, i, j);
			j++;
		}
		i++;
	}
}

char	*join_path(const char *a, const char *b)
{
	char	*r;
	int		la;
	int		lb;

	if (!a[0])
		return (ft_strdup(b));
	la = ft_strlen(a);
	lb = ft_strlen(b);
	r = malloc(la + 1 + lb + 1);
	ft_memcpy(r, a, la);
	r[la] = '/';
	ft_memcpy(r + la + 1, b, lb);
	r[la + 1 + lb] = '\0';
	return (r);
}

/*Allocates initial space for matches.
Sets initial capacity and length to 0.*/
void	collect_init(t_collect *c)
{
	c->cap = 16;
	c->len = 0;
	c->arr = malloc(sizeof(char *) * c->cap);
}
