#include "ft_utils.h"

void	new_prompt(void)
{
	write(STDERR_FILENO, "\n", 1); // Use write to ensure atomic operation
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
