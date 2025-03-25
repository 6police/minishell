#include "ft_builtins.h"

void exit_shell(t_cmd *cmd, t_shell *shell)
{
  (void)cmd;
  clean_exit(shell);
} 
