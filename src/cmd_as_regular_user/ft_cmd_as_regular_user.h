/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_as_regular_user.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:41:35 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:10:16 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_AS_REGULAR_USER_H
# define FT_CMD_AS_REGULAR_USER_H

# include "../minishell.h"

// Dollar sign command functions:
void	dollar_sign(t_shell *shell);

// Dollar sign here doc functions:
void	dollar_sign_here_doc(t_cmd *cmd, t_shell *shell);

// Dollar sign helper functions:
char	*found_env_var(t_dollar *d, char *arg);
char	*no_env_var_found(t_dollar *d, char *arg);
void	ft_initiate_dollar(t_dollar *d);
int		check_quotes_type(char *str);

#endif