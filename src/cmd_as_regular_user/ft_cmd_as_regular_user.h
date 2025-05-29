#ifndef FT_CMD_AS_REGULAR_USER_H
#define FT_CMD_AS_REGULAR_USER_H

#include "../minishell.h"

void	dollar_sign(t_cmd *cmd, t_shell *shell);
char	*handle_dollar(char *arg, t_shell *shell);

#endif