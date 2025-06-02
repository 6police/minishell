/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:58 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/01 21:58:05 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "../minishell.h"

typedef struct s_sig
{
	int		exit_value;
	int		fd;
	t_shell	*shull;
}			t_sig;

t_sig		*t_pid(void);

void		setup_signals(t_shell *shell);

void		setup_signals_heredoc(t_shell *shell);

#endif