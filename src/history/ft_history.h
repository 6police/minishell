/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:17:24 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 17:17:25 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORY_H
# define FT_HISTORY_H

# include "../minishell.h"

typedef struct s_history
{
	HISTORY_STATE	*state;
	HIST_ENTRY		**list;
}					t_history;

#endif // Display the history
