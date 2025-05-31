/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_failure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:18:03 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 18:18:05 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

// function to handle malloc failure
void	handle_malloc_failure(void)
{
	ft_putstr_fd("Error: malloc failed\n", 2);
	exit(1);
}

// function to handle malloc failure for redirection array
void	*handle_redir_malloc_error(char **redirs)
{
	ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
	free(redirs);
	return (NULL);
}
