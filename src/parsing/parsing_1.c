/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:07:52 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/10 19:21:31 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// parsing the line into tokens
void parse_line(t_shell *shell)
{
    char **tokens;

    if (!shell->line)
        return;
    tokens = ft_parse_split(shell->line);
    if (!tokens)
        return;

    shell->tokens = tokens;
}

// parsing to make tokens so we can later parse the tokens into commands
void parse_tokens(t_shell *shell) // this function is not complete
{
    // for now it just prints the tokens
    int i;

    i = 0;
    while (shell->tokens[i])
    {
        if (ft_strcmp(shell->tokens[i], "env") == 0)
            print_env(shell->env);
        if (ft_strcmp(shell->tokens[i], "exit") == 0)
            exit_shell(shell, 0);
        if (ft_strcmp(shell->tokens[i], "export") == 0)
            export_builtin(shell);
        if (ft_strcmp(shell->tokens[i], "unset") == 0)
            unset_env_var(shell, shell->tokens[i + 1]);
        if (ft_strcmp(shell->tokens[i], "pwd") == 0)
            pwd_shell();
        if (ft_strcmp(shell->tokens[i], "cd") == 0)
        {
            t_cmd *cmd =(t_cmd*) malloc(sizeof(t_cmd));
            cmd->name = "cd";
            cmd->args = shell->tokens;
            cd_shell(cmd, shell->env);
        }
        i++;
    }
    shell->cmds = malloc(sizeof(t_cmd *) * (i + 1));
}

// print the tokens
static void print_tokens(t_shell *shell)
{
    int i;

    i = 0;
    while (shell->tokens[i])
    {
        ft_printf(GREEN "token" RESET" [ "RED"%d"RESET" ] --> %s\n",i ,shell->tokens[i]);
        i++;
    }
}

// parse the line and tokens
void parse(t_shell *shell, int debug)
{
    parse_line(shell); // parse the line
    if (shell->tokens)
    {
        if (debug == 1)
            print_tokens(shell); // print the tokens
        parse_tokens(shell);     // parse the tokens
    }
    else
        ft_printf_fd(2, "Error"); // print error message
}