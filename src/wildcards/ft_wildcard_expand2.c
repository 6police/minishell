/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_expand2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:00:58 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 15:03:25 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

void	handle_literal_component(char **comps, int lvl,
		const char *base, t_collect *out)
{
	char	*next;

	next = join_path(base, comps[lvl]);
	if (path_exists(next))
		expand_recursive(comps, lvl + 1, next, out);
	free(next);
}

void	handle_end_of_path(const char *base, t_collect *out)
{
	collect_add(out, ft_strdup(base));
}

DIR	*open_directory(const char *base)
{
	if (base[0])
		return (opendir(base));
	return (opendir("."));
}

bool	should_skip_entry(struct dirent *entry)
{
	if (entry->d_name[0] == '.')
		return (true);
	return (false);
}

void	process_matching_entry(char **comps, int lvl,
		t_collect *out, char *next)
{
	bool	is_last;

	is_last = (comps[lvl + 1] == NULL);
	if (is_last)
		collect_add(out, next);
	else
	{
		expand_recursive(comps, lvl + 1, next, out);
		free(next);
	}
}
