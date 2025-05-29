#include "ft_utils.h"

// function to handle malloc failure
void	handle_malloc_failure(void)
{
	ft_putstr_fd("Error: malloc failed\n", 2);
	exit(1);
}

// function to handle malloc failure for redirection array
void	*handle_redir_malloc_error(char **redirs)
{
	ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
	free(redirs);
	return (NULL);
}
