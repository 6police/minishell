/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:15 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 18:22:28 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/wildcards/ft_new_wildcard.c
#include "ft_wildcard.h"

static void	collect_add(t_collect *c, char *s);
static void	expand_recursive(char **comps, int lvl,
				const char *base, t_collect *out);

void	ft_new_wildcard(t_cmd *cmd, t_shell *shell)
{
	int			i;
	int			j;
	int			total;
	char		*arg;
	char		*out;
	char		**comps;
	t_collect	coll;

	i = 0;
	(void)shell;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		if (!has_wildcard(arg) || is_quoted(arg))
		{
			i++;
			continue ;
		}
		collect_init(&coll);
		comps = split_path(arg);
		expand_recursive(comps, 0, "", &coll);
		free_strarr(comps);
		if (coll.len > 1)
			sort_strs(coll.arr, coll.len);
		total = 1;
		j = 0;
		while (j < coll.len)
		{
			total += ft_strlen(coll.arr[j]) + 1;
			j++;
		}
		out = malloc(total);
		out[0] = '\0';
		j = 0;
		while (j < coll.len)
		{
			ft_strcat(out, coll.arr[j]);
			if (j + 1 < coll.len)
				ft_strcat(out, " ");
			free(coll.arr[j]);
			j++;
		}
		free(coll.arr);
		free(cmd->args[i]);
		cmd->args[i] = out;
		i++;
	}
}

static void	collect_add(t_collect *c, char *s)
{
	if (c->len + 1 >= c->cap)
	{
		c->cap *= 2;
		c->arr = realloc(c->arr, sizeof(char *) * c->cap); // LIBFTTT!!
	}
	c->arr[c->len++] = s;
}

//— Recursive traversal —------------------------------------------------------
static void	expand_recursive(char **comps, int lvl, const char *base,
				t_collect *out)
{
	char			*next;
	struct dirent	*e;
	DIR				*d;
	bool			last;

	if (comps[lvl] && !has_wildcard(comps[lvl]))
	{
		next = join_path(base, comps[lvl]);
		expand_recursive(comps, lvl + 1, next, out);
		free(next);
		return ;
	}
	if (!comps[lvl])
	{
		collect_add(out, ft_strdup(base));
		return ;
	}
	if (base[0])
		d = opendir(base);
	else
		d = opendir(".");
	if (!d)
		return ;
	last = comps[lvl + 1] == NULL;
	e = readdir(d);
	while (e)
	{
		if (e->d_name[0] == '.')
		{
			e = readdir(d);
			continue ;
		}
		if (!match_pat(e->d_name, comps[lvl]))
		{
			e = readdir(d);
			continue ;
		}
		next = join_path(base, e->d_name);
		if (last)
			collect_add(out, next);
		else
		{
			expand_recursive(comps, lvl + 1, next, out);
			free(next);
		}
		e = readdir(d);
	}
	closedir(d);
}
