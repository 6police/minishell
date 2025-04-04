#include "redirections.h"

void reset_redirections(t_cmd *cmd, t_shell *shell, bool child_process)
{
	// Redirect input (e.g., < or heredoc)
	if (cmd->FD[0] != STDIN_FILENO)
	{
		if (dup2(cmd->FD[0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 input");
			if (child_process)
				exit(1);
			shell->exit_value = 1; //confirmar valor
		}
		close(cmd->FD[0]); // Close original FD
	}
	// Redirect output (e.g., >, >>, or pipe)
	if (cmd->FD[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->FD[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 output");
			if (child_process)
				exit(1);
			shell->exit_value = 1; // confirmar valor
		}
		close(cmd->FD[1]); // Close original FD
	}
}

void	handle_redirections(t_cmd *cmd, t_shell *shell, bool child_process)
{
	if (cmd->FD[1] != STDOUT_FILENO)
	{
		if (dup2(STDOUT_FILENO, cmd->FD[1]) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: dup2 output");
			// confirmar exit value
			if (child_process)
				exit(1);
			shell->exit_value = 1;
		}
		close(STDOUT_FILENO);
	}
	if (cmd->FD[0] != STDIN_FILENO)
	{
		if (dup2(STDIN_FILENO, cmd->FD[0]) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: dup2 input");
			//confirmar exit value
			if (child_process)
				exit(1);
			shell->exit_value = 1;
		}
		close(STDIN_FILENO); // Close original FD
	}
}
