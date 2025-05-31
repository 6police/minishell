/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:15 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/31 02:12:55 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

static int	calculate_total_length(t_collect *coll);
static void	join_matches_to_string(t_collect *coll, char *out);
static void	handle_successful_matches(t_cmd *cmd, int i, t_collect *coll);
static void	process_wildcard_arg(t_cmd *cmd, int i, char *arg);

void	ft_wildcard(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*arg;

	(void)shell;
	i = 0;
	if (!cmd || !cmd->args)
		return ;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		if (has_wildcard(arg) && !is_quoted(arg))
			process_wildcard_arg(cmd, i, arg);
		i++;
	}
}

static int	calculate_total_length(t_collect *coll)
{
	int	total;
	int	j;

	total = 1;
	j = 0;
	while (j < coll->len)
	{
		total += ft_strlen(coll->arr[j]) + 1;
		j++;
	}
	return (total);
}

static void	join_matches_to_string(t_collect *coll, char *out)
{
	int	j;

	out[0] = '\0';
	j = 0;
	while (j < coll->len)
	{
		ft_strcat(out, coll->arr[j]);
		if (j + 1 < coll->len)
			ft_strcat(out, " ");
		free(coll->arr[j]);
		j++;
	}
}

static void	handle_successful_matches(t_cmd *cmd, int i, t_collect *coll)
{
	char	*out;
	int		total;

	if (coll->len > 1)
		sort_strs(coll->arr, coll->len);
	total = calculate_total_length(coll);
	out = malloc(total);
	join_matches_to_string(coll, out);
	free(coll->arr);
	free(cmd->args[i]);
	cmd->args[i] = out;
}

static void	process_wildcard_arg(t_cmd *cmd, int i, char *arg)
{
	t_collect	coll;
	char		**comps;

	collect_init(&coll);
	comps = split_path(arg);
	expand_recursive(comps, 0, "", &coll);
	free_strarr(comps);
	if (coll.len == 0)
	{
		free(coll.arr);
		restore_literal_pattern(cmd, i, arg);
	}
	else
		handle_successful_matches(cmd, i, &coll);
}
