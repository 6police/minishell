#include "ft_builtins.h"

void	exit_shell(t_cmd *cmd, t_shell *shell)
{
  (void)cmd;
  int pid;

  if (shell->is_pipe == true)
  {
    pid = fork();
    if (pid == 0)
    {
      clean_exit(&shell);
      shell->exit_value = 0;
    }
    else
    {
      waitpid(pid, &shell->exit_value, 0);
      if (WIFEXITED(shell->exit_value))
        shell->exit_value = WEXITSTATUS(shell->exit_value);
      else
        shell->exit_value = 1;
      return ;
    }
  }
  else
  {
    shell->exit_value = 0;  
    clean_exit(&shell);
  }
}
