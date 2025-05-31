/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:58 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 19:47:39 by nneves-a         ###   ########.fr       */
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

// Setup signals
void	setup_signals(t_shell *shell);

void	setup_signals_heredoc(t_shell *shell);

#endif