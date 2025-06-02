/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:52:15 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 17:21:56 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

// function to handle heredoc in a child process
void	do_heredoc_child(char *limiter, t_shell *shell)
{
	char	*line;
	int		fd;

	fd = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, limiter) == 0))
		{
			free(line);
			break ;
		}
		if (has_expansion(line))
			line = ft_expand(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

// function to handle heredoc in the main process
int	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	do_heredoc_child(fd_struct->file, shell);
	return (shell->exit_value);
}
