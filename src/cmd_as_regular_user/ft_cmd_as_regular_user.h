#ifndef FT_CMD_AS_REGULAR_USER_H
# define FT_CMD_AS_REGULAR_USER_H

# include "../minishell.h"

void	dollar_sign(t_shell *shell, int n_toks);
void	dollar_sign_here_doc(t_cmd *cmd, t_shell *shell);

#endif