/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 01:14:18 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/31 01:53:31 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

static void	collect_add(t_collect *c, char *s);
static bool	path_exists(const char *path);

static void	handle_literal_component(char **comps, int lvl,
		const char *base, t_collect *out)
{
	char	*next;

	next = join_path(base, comps[lvl]);
	if (path_exists(next))
		expand_recursive(comps, lvl + 1, next, out);
	free(next);
}

static void	handle_end_of_path(const char *base, t_collect *out)
{
	collect_add(out, ft_strdup(base));
}

static DIR	*open_directory(const char *base)
{
	if (base[0])
		return (opendir(base));
	return (opendir("."));
}

static bool	should_skip_entry(struct dirent *entry)
{
	if (entry->d_name[0] == '.')
		return (true);
	return (false);
}

static void	process_matching_entry(struct dirent *entry,
		char **comps, int lvl, const char *base, t_collect *out)
{
	char	*next;
	bool	is_last;

	next = join_path(base, entry->d_name);
	is_last = (comps[lvl + 1] == NULL);
	if (is_last)
		collect_add(out, next);
	else
	{
		expand_recursive(comps, lvl + 1, next, out);
		free(next);
	}
}

static void	scan_directory(char **comps, int lvl, const char *base, t_collect *out)
{
	int				nch;
	DIR				*d;
	struct dirent	*entry;

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
				process_matching_entry(entry, comps, lvl, base, out);
		}
		entry = readdir(d);
	}
	closedir(d);
}

void	expand_recursive(char **comps, int lvl, const char *base, t_collect *out)
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

static void	collect_add(t_collect *c, char *s)
{
	if (c->len + 1 >= c->cap)
	{
		c->cap *= 2;
		c->arr = realloc(c->arr, sizeof(char *) * c->cap);
	}
	c->arr[c->len++] = s;
}

static bool	path_exists(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0);
}
