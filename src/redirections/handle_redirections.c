#include "redirections.h"

void	handle_redirections(t_cmd *cmd, t_shell *shell)
{
	if (cmd->redirs->append != NULL)
		cmd->fd[0] = open(cmd->redirs->append, O_RDONLY);
	// Redirect input (e.g., < or heredoc)
	if (cmd->fd[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 input");
		}
		close(cmd->fd[0]); // Close original FD
	}
	// tavamos a testar
	/*	cmd->fd[1] = open(cmd->args[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		printf("cmd->fd[1]: %d\n", cmd->fd[1]);*/
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
