#include "ft_builtins.h"

void	exit_shell(t_cmd *cmd, t_shell *shell)
{
  (void)cmd;
  shell->exit_value = 0;
  //disable_echo(0);
  clean_exit(&shell);
}
