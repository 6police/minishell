#include "ft_utils.h"

// function to print a newline and reset the prompt
void	new_prompt(void)
{
	ft_printf_fd(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 14);
	rl_redisplay();
}
