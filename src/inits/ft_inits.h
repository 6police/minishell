/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:17:28 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:17:30 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INITS_H
# define FT_INITS_H

# include "../minishell.h"

// function to initialize the shell
t_shell	*init_shell(char **env);
t_shell	*init_shell_no_env(void);

#endif