/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:17:39 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:17:44 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to check if the command is a redirection without an argument
bool	is_redir_noarg(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !c)
			c = str[i];
		while ((str[i] == '<' || str[i] == '>'))
			i++;
		if ((str[i] == '\0' || str[i] == ' ') && !c)
			return (true);
		if ((str[i] != ' ' && str[i] != '\0') && !c)
			return (false);
		i++;
	}
	return (false);
}

// function to check if the command is a redirection
bool	is_redir(char *str)
{
	int		i;
	char	quote;

	if (!str)
		return (false);
	quote = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		else if ((str[i] == '>' || str[i] == '<') && quote == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

// function to build the command
void	built_in_handle(t_cmd *cmd, t_shell *shell, char **args)
{
	check_builtin(cmd);
	if (cmd->is_builtin)
		build_builtin(cmd, args);
	else
		build_cmd(cmd, args, shell);
}
