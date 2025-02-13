#include "ft_builtins.h"

void pwd_shell()
{
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		perror("getcwd() error");
}