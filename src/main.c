/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:56:43 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/10 18:28:46 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int argc, char **argv, char **env)
{
    (void)argv;


    // if it has any arguments, print the error message
    if (argc == 1)
    {
        t_shell *shell;
        
        shell = init_shell(env);
        run_shell(shell);
    }
    else if (argc == 2)
    {
        if ((ft_strncmp(argv[1], "-d", 2) == 0) || (ft_strncmp(argv[1], "--debug", 7) == 0))
        {
            t_shell *shell;

            shell = init_shell(env);
            run_shell_debug(shell);
        }
        else
        {
            ft_putstr_fd(EMOJI_CROSS EMOJI_CROSS " Error: minishell does not accept arguments\n", 2);
            return (1);
        }
    }
    else
    {
        ft_putstr_fd(EMOJI_CROSS EMOJI_CROSS " Error: minishell does not accept arguments\n", 2);
        return (1);
    }
    return (0);    
}

