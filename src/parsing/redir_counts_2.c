/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_counts_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:14 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:51:16 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function that checks if the single > is valid
static int	is_valid_single_forward(char *token, int i)
{
	if (i > 0)
	{
		if (token[i + 1] != '>' && token[i + 1] != '\0' && token[i - 1] != '>')
			return (1);
	}
	else
	{
		if (token[i + 1] != '>' && token[i + 1] != '\0')
			return (1);
	}
	return (0);
}

// function that counts the number of > redirects in the token
int	forward_redir_count(char *token)
{
	int	i;
	int	count;
	int	quotes;

	i = 0;
	count = 0;
	quotes = 0;
	while (token[i] != '\0')
	{
		if ((token[i] == '"' || token[i] == '\'') && quotes == 0)
			quotes = token[i];
		else if (quotes && token[i] == quotes)
			quotes = 0;
		if (token[i] == '>' && quotes == 0)
		{
			if (is_valid_single_forward(token, i))
				count++;
		}
		i++;
	}
	return (count);
}

// // function that checks if the double >> is valid
static int	is_valid_double_forward(char *token, int i)
{
	if (token[i + 1] != '>')
		return (0);
	if (token[i + 2] == '\0')
		return (0);
	if (i > 0 && token[i - 1] == '>')
		return (0);
	return (1);
}

// function that counts the number of >> redirects in the token
int	dbl_forward_redir_count(char *token)
{
	int	i;
	int	count;
	int	quotes;

	i = 0;
	count = 0;
	quotes = 0;
	while (token[i] != '\0')
	{
		if ((token[i] == '"' || token[i] == '\'') && quotes == 0)
			quotes = token[i];
		else if (quotes && token[i] == quotes)
			quotes = 0;
		if (token[i] == '>' && quotes == 0)
		{
			if (is_valid_double_forward(token, i))
				count++;
		}
		i++;
	}
	return (count);
}
