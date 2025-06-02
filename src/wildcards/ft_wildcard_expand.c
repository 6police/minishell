/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 01:14:18 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 18:29:28 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

/*
This function:
Opens the current directory.
Iterates over all files.
Skips hidden files via should_skip_entry().
	For each entry:
If it matches the pattern via match_pat(...),
build its full path (join_path) and:
If this is the last component, add it to out.
Else, recurse into it.
*/
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

//This is the recursive traversal function that scans directories
//and matches patterns at each level (component).
//Purpose:
//Traverse the path components (comps) level by level.
//If the component contains a *, use pattern matching on directory entries.
//Otherwise, append the literal part of the path and keep going.
//Case 1: Component has no *
//This means the path part is not a wildcard, like "src" in src /*.c.
//It builds the full path and goes to the next component recursively.
//Case 2: Component is NULL
//We've reached the end of the path.
//It adds the final full path to out.
//Case 3: Component has *
//This is where pattern matching happens.
//We scan the directory at base, and for each entry, see if it matches the
//wildcard pattern at level lvl.

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
		c->arr = ft_realloc_arr(c->arr, sizeof(char *) * c->cap);
	}
	c->arr[c->len++] = s;
}

bool	path_exists(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0);
}
