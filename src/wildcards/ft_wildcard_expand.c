/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 01:14:18 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 15:05:08 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

static void	scan_directory(char **comps, int lvl,
		const char *base, t_collect *out)
{
	int				nch;
	DIR				*d;
	struct dirent	*entry;
	char			*next;

	nch = 0;
	d = open_directory(base);
	if (!d)
		return ;
	entry = readdir(d);
	while (entry != NULL)
	{
		if (!should_skip_entry(entry))
		{
			if (match_pat(entry->d_name, comps[lvl], nch))
			{
				next = join_path(base, entry->d_name);
				process_matching_entry(comps, lvl, out, next);
			}
		}
		entry = readdir(d);
	}
	closedir(d);
}

void	expand_recursive(char **comps, int lvl,
		const char *base, t_collect *out)
{
	if (comps[lvl] && !has_wildcard(comps[lvl]))
	{
		handle_literal_component(comps, lvl, base, out);
		return ;
	}
	if (!comps[lvl])
	{
		handle_end_of_path(base, out);
		return ;
	}
	scan_directory(comps, lvl, base, out);
}

void	collect_add(t_collect *c, char *s)
{
	if (c->len + 1 >= c->cap)
	{
		c->cap *= 2;
		c->arr = realloc(c->arr, sizeof(char *) * c->cap);
	}
	c->arr[c->len++] = s;
}

bool	path_exists(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0);
}
