/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:19:52 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 18:03:32 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to set the name of the command from the arguments
static int	is_redirection(const char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str,
			"<") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	if (str[0] == '>' || str[0] == '<')
		return (1);
	return (0);
}

// Function to check if a string starts with redirection but has filen attached
static int	is_combined_redirection(const char *str)
{
	if (!str || ft_strlen(str) <= 1)
		return (0);
	if ((str[0] == '>' && str[1] != '\0' && str[1] != '>') || (str[0] == '<'
			&& str[1] != '\0' && str[1] != '<'))
		return (1);
	if (str[0] == '>' && str[1] == '>' && str[2] != '\0')
		return (1);
	if (str[0] == '<' && str[1] == '<' && str[2] != '\0')
		return (1);
	return (0);
}

// Main function to extract command name from arguments array
char	*set_name(char **args)
{
	int		i;
	char	*name;
	char	*aux;

	i = 0;
	if (!args || !args[0])
		return (NULL);
	while (args[i])
	{
		if (is_redirection(args[i]) && !is_combined_redirection(args[i]))
		{
			if (args[++i])
				i++;
			continue ;
		}
		if (is_combined_redirection(args[i]))
		{
			i++;
			continue ;
		}
		aux = ft_strdup(args[i]);
		name = remove_all_quotes(aux);
		return (name);
	}
	return (NULL);
}
