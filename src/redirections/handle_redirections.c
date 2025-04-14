#include "redirections.h"

void	handle_redirections(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->fd_struct)
		return;
	if (cmd->fd_struct->type == HERE_DOC_)
		cmd->fd_struct->fd = open(cmd->fd_struct->file, O_RDONLY);
	else if (cmd->fd_struct->type == REDIR_OUT)
		cmd->fd_struct->fd = open(cmd->fd_struct->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (cmd->fd_struct->type == REDIR_APPEND)
		cmd->fd_struct->fd = open(cmd->fd_struct->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (cmd->fd_struct->type == REDIR_IN)
		cmd->fd_struct->fd = open(cmd->fd_struct->file, O_RDONLY);
	if (cmd->fd_struct->fd == -1)
	{
		perror("minishell: open");
		shell->exit_value = 1;
		return;
	}
	if (cmd->fd_struct->fd != STDIN_FILENO)
	{
		if (dup2(cmd->fd_struct->fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 input");
			shell->exit_value = 1;
			return;
		}
		close(cmd->fd_struct->fd); // Close original FD
	}
	if (cmd->fd_struct->type == REDIR_OUT || cmd->fd_struct->type == REDIR_APPEND)
	{
		if (dup2(cmd->fd_struct->fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 output");
			shell->exit_value = 1;
			return;
		}
		close(cmd->fd_struct->fd); // Close original FD
	}
	if (cmd->fd_struct->type == HERE_DOC_)
	{
		if (dup2(cmd->fd_struct->fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 heredoc");
			shell->exit_value = 1;
			return;
		}
		close(cmd->fd_struct->fd); // Close original FD
	}
	// Close the file descriptor after redirection
	close(cmd->fd_struct->fd);
	cmd->fd_struct->fd = -1; // Reset the file descriptor
	cmd->fd_struct->type = 0; // Reset the type
	cmd->fd_struct->file = NULL; // Reset the file name
	cmd->fd_struct = NULL; // Reset the file descriptor struct
}


			// Redirect input (e.g., < or heredoc)

/*
void	reset_redirections(t_cmd *cmd, t_shell *shell)
{
	if (cmd->fd[0] != STDIN_FILENO)
	{
		if (dup2(STDIN_FILENO, cmd->fd[0]) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: dup2 input");
			//confirmar exit value
			shell->exit_value = 1;
		}
		close(STDIN_FILENO); // Close original FD
	}
	if (cmd->fd[1] != STDOUT_FILENO)
	{
		if (dup2(STDOUT_FILENO, cmd->fd[1]) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: dup2 output");
			// confirmar exit value
			shell->exit_value = 1;
		}
		close(STDOUT_FILENO);
	}
}*/

/*
	if (cmd->fd-> != STDIN_FILENO)
	{
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 input");
		}
		close(cmd->fd[0]); // Close original FD
	}
	// tavamos a testar
		cmd->fd[1] = open(cmd->args[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		printf("cmd->fd[1]: %d\n", cmd->fd[1]);
	// Redirect output (e.g., >, >>, or pipe)
	if (cmd->fd[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 output");
			shell->exit_value = 1; // confirmar valor
		}
		close(cmd->fd[1]); // Close original FD
	}
}
*/