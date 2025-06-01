/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:52:15 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 23:02:18 by nuno             ###   ########.fr       */
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
		return (shell->exit_value = 1, (void)0); // changed from exit, since its not a child anymore;
	t_pid()->fd = fd;
	shell->super_heredoc_fd = fd;
	printf("fd: %d\n", fd);
	setup_signals_heredoc(shell);
	while (1)
	{
		line = readline("> ");
		if (shell->exit_value == 130)
		{
			if (line)
				free(line);
			break ;
		}
		if (!line || (ft_strcmp(line, limiter) == 0))
		{
			if (line)
				free(line);
			break ;
		}
		if (has_expansion(line))
			line = ft_expand(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		if (shell->exit_value == 130)
			break ;
	}
	rl_done = 0;
	setup_signals(shell);
	printf(RED"shell->exit_value in heredoc child: %d\n"RESET, shell->exit_value);
	close(fd);
}

// function to handle heredoc in the main process
int	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	printf(RED"shell->exit_value before heredoc: %d\n"RESET, shell->exit_value);
	do_heredoc_child(fd_struct->file, shell);
	printf(RED"shell->exit_value after heredoc: %d\n"RESET, shell->exit_value);
	return (shell->exit_value);
}
