#include "ft_utils.h"

void	new_prompt(void)
{
    ft_printf("\n");
    rl_on_new_line();
    rl_replace_line("", 14);
    rl_redisplay();
}
