/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:14 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/13 17:31:45 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// function to check if there are quotes or double quotes
int look_for_quotes(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
// function to count the number of quotes
int count_quotes(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

// function to handle quotes and double quotes
// split the line into tokens
// if there is a quote or double quote then the token should be everything inside the quotes
// if there is a space inside the quotes then it should be considered part of the token
// if theres quotes inside quotes then it should be considered part of the token
//
char **split_with_quotes(char *line)
{
	if (!line)
		return (NULL);
	if (count_quotes(line) % 2 != 0)
	{
		(ft_printf_fd(2, "Error: Odd number of quotes\n"));
		return (NULL);
	}

	char **tokens;
	int i;

	i = 0;
	tokens = malloc(sizeof(char *) * (count_quotes(line) / 2 + 1));
	if (!tokens)
		return (NULL);

	// split the line into tokens
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			line++;
			tokens[i] = ft_strchr(line, *line);
			if (!tokens[i])
			{
				free(tokens);
				return (NULL);
			}
			*tokens[i] = '\0';
			line++;
			i++;
		}
		else
		{
			tokens[i] = line;
			line = ft_strchr(line, ' ');
			if (!line)
				break;
			*line = '\0';
			line++;
			i++;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}
    // split the line into tokens
// need to use split but take into consideration the quotes and double quotes
// if there is a quote or double quote then the token should be everything inside the quotes
// if there is a space inside the quotes then it should be considered part of the token
// if theres quotes inside quotes then it should be considered part of the token
char **ft_parse_split(char *line)
{
    if (!line)
        return (NULL);

    if (look_for_quotes(line) != 0)             // if there are quotes or double quotes
        return (split_with_quotes(line));       // split the line into tokens
    else
        return (ft_split(line, ' '));           // split the line into tokens
}
