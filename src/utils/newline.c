#include "ft_utils.h"

void	new_prompt(void)
{
	//disable_echo(0);
    //ft_printf("^C\n");
    ft_printf("\n");
	rl_on_new_line();
    rl_replace_line("", 14);
    rl_redisplay();
	//disable_echo(1);
}
