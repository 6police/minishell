/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validations.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:18:29 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 21:28:38 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VALIDATIONS_H
# define FT_VALIDATIONS_H

# include "../minishell.h"

// validations

// check if the command is empty
bool	is_empty(char *command);

// check if the command is a built-in command
bool	is_builtin(char *cmd);

// check if the command is valid
bool	validate_command(char *command);

// commanmd checker

// check for path
char	*checkforpath(char *cmd, t_env *env);

// check if command sent is in path format
bool	is_command_path(char *cmd);

// check if the command is valid
// bool    ft_validation(t_cmd *cmd, t_shell *shell);

// check if the command is all quotes
bool	is_all_quotes(char *cmd);

#endif