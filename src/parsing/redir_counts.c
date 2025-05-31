/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_counts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:22 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:51:23 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function that checks if the single < is valid
static int	is_valid_single_back(char *token, int i)
{
	if (token[i + 1] == '<' || token[i + 1] == '\0')
		return (0);
	if (i > 0 && token[i - 1] == '<')
		return (0);
	return (1);
}

// function that counts the number of < or redirects in the token
int	back_redir_count(char *token)
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
		if (token[i] == '<' && quotes == 0)
		{
			if (is_valid_single_back(token, i))
				count++;
		}
		i++;
	}
	return (count);
}

// function that counts the number of here_docs in the token
int	here_doc_count(char *token)
{
	int	i;
	int	count;
	int	quotes;

	i = 0;
	quotes = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if ((token[i] == '"' || token[i] == '\'') && quotes == 0)
			quotes = token[i];
		else if (quotes == token[i])
			quotes = 0;
		if (token[i] == '<' && !quotes)
		{
			if ((token[i + 1] == '<') && (token[i + 2] != '\0')
				&& ft_isascii(token[i + 2]))
				count++;
		}
		i++;
	}
	return (count);
}
