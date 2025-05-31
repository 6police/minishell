/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:20:37 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:20:39 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to count the number of quotes
int	count_quotes(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !count)
			count = line[i];
		else if (count && line[i] == count)
			count = 0;
		i++;
	}
	return (count);
}

// function to mark and switch a set of characters in the line for another
void	mark_and_replace(char *line, int letter, int sub)
{
	int	j;
	int	c;

	j = -1;
	c = 0;
	while (line[++j])
	{
		if ((line[j] == '\'' || line[j] == '"') && !c)
			c = line[j];
		else if (c && line[j] == c)
			c = 0;
		else if ((line[j] == letter) && !c)
			line[j] = sub;
	}
}

// function to check if the token is not empty
bool	is_all_whitespace(const char *s)
{
	if (!s)
		return (true);
	while (*s)
	{
		if (!ft_isspace(*s))
			return (false);
		s++;
	}
	return (true);
}

// function to split the line into tokens
char	**ft_parse_split(char *line, int letter, int sub)
{
	char	**tokens;
	int		nbrpipes;
	int		i;

	i = 0;
	nbrpipes = 0;
	i = 0;
	(void)letter;
	if (!line || !(*line))
		return (NULL);
	if (count_quotes(line) != 0)
		return (ft_printf_fd(2, "Error: Odd number of quotes\n"), NULL);
	nbrpipes = mark_pipes(line);
	tokens = ft_split(line, sub);
	while (tokens && tokens[i] != NULL && token_not_empty(tokens[i]))
		i++;
	if (nbrpipes + 1 != i)
	{
		free_tokens(tokens);
		return (ft_printf_fd(2,
				"Error: syntax error near unexpected token `|'\n"), NULL);
	}
	return (tokens);
}
