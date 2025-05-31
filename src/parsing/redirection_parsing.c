/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:51:27 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:51:29 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// Function to check for the number of all redirections in a token
int	check_for_redirs(char *token)
{
	int	fwd;
	int	bwd;
	int	dbl_fwd;
	int	hd;
	int	result;

	if (token == NULL)
		return (-1);
	fwd = 0;
	bwd = 0;
	dbl_fwd = 0;
	hd = 0;
	fwd = forward_redir_count(token);
	bwd = back_redir_count(token);
	dbl_fwd = dbl_forward_redir_count(token);
	hd = here_doc_count(token);
	result = fwd + bwd + dbl_fwd + hd;
	if (result > 0)
		return (result);
	else
		return (0);
}

// function to check if there is a redirection in the token
void	check_redir(char *token, int *j)
{
	int	i;
	int	c;

	c = 0;
	i = *j;
	while (token[i] != '\0')
	{
		if ((token[i] == '"' || token[i] == '\'') && !c)
			c = token[i];
		else if ((token[i] == '>' || token[i] == '<' || token[i] == ' ') && !c)
			break ;
		else if (token[i] == c)
			c = 0;
		i++;
	}
	*j = i;
}
