#include "ft_builtins.h"

void pwd_shell(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)))
	{
			ft_putendl_fd(cwd, STDOUT_FILENO);
		shell->exit_value = 0;
		}
			else
		perror("getcwd() error");
}