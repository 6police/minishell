/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 01:13:20 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 18:30:24 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

static bool	check_pattern_start(const char *name, char **chunks)
{
	int	len;

	len = ft_strlen(chunks[0]);
	if (ft_strncmp(name, chunks[0], len) == 0)
		return (true);
	return (false);
}

static bool	check_pattern_end(const char *name, char **chunks, int nch)
{
	int	len;
	int	nl;

	len = ft_strlen(chunks[nch - 1]);
	nl = ft_strlen(name);
	if (nl < len)
		return (false);
	if (ft_strncmp(name + nl - len, chunks[nch - 1], len) == 0)
		return (true);
	return (false);
}

static bool	find_chunk_in_name(const char *name, const char *chunk, int *pos)
{
	char	*found;

	found = ft_strstr(name + *pos, chunk);
	if (!found)
		return (false);
	*pos = (int)(found - name) + ft_strlen(chunk);
	return (true);
}

static bool	match_middle_chunks(const char *name, char **chunks,
				int start_idx, int end_idx)
{
	int	pos;
	int	idx;

	pos = 0;
	idx = start_idx;
	while (idx < end_idx)
	{
		if (!find_chunk_in_name(name, chunks[idx], &pos))
			return (false);
		idx++;
	}
	return (true);
}

/*
What it does:
Splits the pattern by * into chunks (like in shell globbing).
Then checks if:
	The filename starts with the first chunk (if pattern doesn't start with *).
	Ends with the last chunk (if it doesn't end with *).
	All middle chunks appear in order.

Example:
Pattern: a*b*c
	chunks = {"a", "b", "c"}
	matches: abc, a123b456c
	doesn't match: ab, acb
*/
bool	match_pat(const char *name, const char *pat, int nch)
{
	bool	must_end;
	bool	must_start;
	int		start_idx;
	int		end_idx;
	char	**chunks;

	must_start = (pat[0] != '*');
	must_end = (pat[ft_strlen(pat) - 1] != '*');
	chunks = ft_split(pat, '*');
	nch = count_chunks(chunks);
	if (must_start && nch > 0 && !check_pattern_start(name, chunks))
		return (free_strarr(chunks), false);
	if (must_end && nch > 0 && !check_pattern_end(name, chunks, nch))
		return (free_strarr(chunks), false);
	start_idx = 0;
	if (must_start)
		start_idx = 1;
	end_idx = nch;
	if (must_end)
		end_idx = nch - 1;
	if (!match_middle_chunks(name, chunks, start_idx, end_idx))
		return (free_strarr(chunks), false);
	return (free_strarr(chunks), true);
}
