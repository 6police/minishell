/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:52:15 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 17:45:25 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

static int	here_doc_helper(int fd, t_shell *shell);

// function to handle heredoc in a child process
void	do_heredoc_child(char *limiter, t_shell *shell)
{
	char	*line;
	int		fd;

	fd = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0 || here_doc_helper(fd, shell) == 1)
		return (shell->exit_value = 1, (void)1);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, limiter) == 0)
			|| shell->exit_value == 130)
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
	}
	rl_done = 0;
	setup_signals(shell);
	close(fd);
}

static int	here_doc_helper(int fd, t_shell *shell)
{
	t_pid()->fd = fd;
	shell->super_heredoc_fd = fd;
	setup_signals_heredoc(shell);
	rl_event_hook = rl_hook;
	if (t_pid()->fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: " NOFILE "\n", HERE_DOC);
		shell->exit_value = 1;
		return (1);
	}
	return (0);
}

// function to handle heredoc in the main process
int	ft_handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	do_heredoc_child(fd_struct->file, shell);
	return (shell->exit_value);
}

int	rl_hook(void)
{
	if (t_pid()->exit_value == 130)
	{
		rl_done = 1;
	}
	return (0);
}
