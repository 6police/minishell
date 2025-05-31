/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_pattern2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 01:29:40 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/31 01:29:50 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"

void	restore_literal_pattern(t_cmd *cmd, int i, char *arg)
{
	char	*literal;

	literal = ft_strdup(arg);
	free(cmd->args[i]);
	cmd->args[i] = literal;
}

int	count_chunks(char **chunks)
{
	int	count;

	count = 0;
	while (chunks[count])
		count++;
	return (count);
}