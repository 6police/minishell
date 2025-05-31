/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:58 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/31 17:27:54 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "../minishell.h"


typedef struct s_sig
{
	int		status;
	t_shell	*shull;
}	t_sig;

t_sig	*t_pid(void);

void	setup_signals(t_shell *shell);

void	setup_signals_heredoc(t_shell *shell);

#endif