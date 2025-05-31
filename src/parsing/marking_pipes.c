/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marking_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:20:29 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:20:32 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

int	count_pipers(char *line)
{
	int	count;
	int	i;
	int	c;

	count = 0;
	i = 0;
	c = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && !c)
			c = line[i];
		else if (c && line[i] == c)
			c = 0;
		else if (line[i] == '|' && !c)
			count++;
		i++;
	}
	return (count);
}

bool	token_not_empty(const char *token)
{
	int	i;

	if (!token || !(*token))
		return (false);
	i = 0;
	while (token[i])
	{
		if (!ft_isspace(token[i]))
			return (true);
		i++;
	}
	return (false);
}

// function to check for the existence of a pipe in the line.
// it cant be followed by another |
int	mark_pipes(char *line)
{
	int	i;
	int	c;
	int	nbr;

	i = 0;
	c = 0;
	nbr = 0;
	if (!line || !(*line) || line[0] == '\0' || line[0] == '|')
		return (-1);
	nbr = count_pipers(line);
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"') && !c)
			c = line[i];
		else if (c && line[i] == c)
			c = 0;
		else if (line[i] == '|' && !c && line[i + 1] != '\0')
		{
			if (line[i + 1] != '|' && line[i - 1] != '|')
				line[i] = 7;
		}
		i++;
	}
	return (nbr);
}
