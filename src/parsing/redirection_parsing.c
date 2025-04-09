#include "ft_parsing.h"

void	check_for_redirs(char *token)
{
	int	fwd;
	int	bwd;
	int	dbl_fwd;
	int	hd;

	fwd = 0;
	bwd = 0;
	dbl_fwd = 0;
	hd = 0;
	fwd = forward_redir_count(token);
	bwd = back_redir_count(token);
	dbl_fwd = dbl_forward_redir_count(token);
	hd = here_doc_count(token);
	ft_printf_fd(STDIN_FILENO, "Forward redirection found: %d\n", fwd);
	ft_printf_fd(STDIN_FILENO, "Backward redirection found: %d\n", bwd);
	ft_printf_fd(STDIN_FILENO, "Double forward redirection found: %d\n",
		dbl_fwd);
	ft_printf_fd(STDIN_FILENO, "Here document found: %d\n", hd);
}
