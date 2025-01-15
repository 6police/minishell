/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:07:52 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/15 20:45:15 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// parsing the line into tokens
void	parse_line(t_shell *shell)
{
    char **tokens;

    if (!shell->line)
        return ;
    tokens = ft_parse_split(shell->line);
    if (!tokens)
        return ;

    shell->tokens = tokens; 
}


// parsing to make tokens so we can later parse the tokens into commands
void	parse_tokens(t_shell *shell) // this function is not complete
{
    // for now it just prints the tokens
    int i;

    i = 0;
    while (shell->tokens[i])
    {
        ft_printf("Token %d: %s\n", i, shell->tokens[i]);
		if (ft_strcmp(shell->tokens[i], "env") == 0)
			print_env(shell->env);
        if (ft_strcmp(shell->tokens[i], "exit") == 0)
            exit(0);
        if (ft_strcmp(shell->tokens[i], "export") == 0)
            export_bi(shell->tokens[i + 1], shell);
        if (ft_strcmp(shell->tokens[i], "unset") == 0)
            unset_env_var(shell, shell->tokens[i + 1]);
		i++;
    }
}

// parse the line and tokens
void	parse(t_shell *shell)
{
    parse_line(shell);          // parse the line
    if (shell->tokens)
        parse_tokens(shell);    // parse the tokens
    else
        ft_printf_fd(2, "Error"); // print error message
}

