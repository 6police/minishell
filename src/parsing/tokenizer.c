/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:37 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:51:39 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to add a token to the end of the linked list
static void	add_last(t_token **head, t_token *token)
{
	t_token	*tmp;

	tmp = *head;
	if (!tmp)
		*head = token;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

// function to initialize a linked list of tokens from an array of strings
t_token	*init_token(char **tokens)
{
	t_token	*token;
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (tokens[i])
	{
		if (is_all_whitespace(tokens[i]))
		{
			i++;
			continue ;
		}
		token = ft_calloc(sizeof(t_token), 1);
		token->token = &tokens[i];
		token->next = NULL;
		add_last(&head, token);
		i++;
	}
	return (head);
}
