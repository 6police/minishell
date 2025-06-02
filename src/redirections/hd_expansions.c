/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:52:30 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 19:51:09 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

// function to check if the line has any expansion
bool	has_expansion(char *line)
{
	int		i;
	int		count_quotes;
	bool	expansion;

	i = 0;
	count_quotes = 0;
	expansion = false;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && !count_quotes)
			count_quotes = line[i];
		else if (count_quotes && line[i] == count_quotes)
			count_quotes = 0;
		else if (line[i] == '$' && !count_quotes)
		{
			expansion = true;
			break ;
		}
		i++;
	}
	return (expansion);
}

// function to free the allocated memory for the line, arg, and tmp
static void	free_wrapper(char *line, char *arg, t_cmd *tmp)
{
	(void)arg;
	if (line)
		free(line);
	if (tmp)
		free(tmp);
}

// // function to expand the line
char	*ft_expand(char *line, t_shell *shell)
{
	char	*expanded_line;
	t_cmd	*tmp;
	char	*arg;
	char	*aux;

	if (!line)
		return (NULL);
	expanded_line = NULL;
	tmp = NULL;
	arg = ft_strdup(line);
	aux = arg;
	if (!arg)
		return (NULL);
	tmp = ft_calloc(sizeof(t_cmd), 1);
	if (!tmp)
		return (free(arg), NULL);
	tmp->args = &arg;
	dollar_sign_here_doc(tmp, shell);
	expanded_line = ft_strdup(tmp->args[0]);
	free(line);
	tmp->args = NULL;
	free_wrapper(arg, aux, tmp);
	return (expanded_line);
}
