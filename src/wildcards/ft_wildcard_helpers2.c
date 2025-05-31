/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_helpers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:53:48 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 18:20:26 by nneves-a         ###   ########.fr       */
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

void	sort_strs(char **arr, int n)
{
	int		i;
	int		j;
	char	*t;

	i = 0;
	while (i + 1 < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (strcmp_ci(arr[i], arr[j]) > 0)
			{
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
			j++;
		}
		i++;
	}
}

bool	match_pat(const char *name, const char *pat)
{
	int		nl;
	int		len;
	int		pos;
	int		idx;
	int		nch;
	int		limit;
	bool	must_end;
	bool	must_start;
	char	*p;
	char	**chunks;

	must_start = pat[0] != '*';
	must_end = pat[ft_strlen(pat)-1] != '*';
	chunks = ft_split(pat, '*');
	nch = 0;
	pos = 0;
	idx = 0;
	while (chunks[nch])
		nch++;
	if (must_start && nch > 0)
	{
		len = ft_strlen(chunks[0]);
		if (ft_strncmp(name, chunks[0], len))
		{
			free_strarr(chunks);
			return (false);
		}
		pos = len;
		idx = 1;
	}
	if (must_end == true)
		limit = 1;
	else
		limit = 0;
	while (idx < nch - limit)
	{
		p = ft_strstr(name + pos, chunks[idx]);
		if (!p)
		{
			free_strarr(chunks);
			return (false);
		}
		pos = (int)(p - name) + ft_strlen(chunks[idx]);
		idx++;
	}
	if (must_end && nch > 0)
	{
		len = ft_strlen(chunks[nch -1]);
		nl = ft_strlen(name);
		if (nl < len || ft_strncmp(name + nl - len, chunks[nch - 1], len))
		{
			free_strarr(chunks);
			return (false);
		}
	}
	free_strarr(chunks);
	return (true);
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

void	collect_init(t_collect *c)
{
	c->cap = 16;
	c->len = 0;
	c->arr = malloc(sizeof(char *) * c->cap);
}
