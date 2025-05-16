#ifndef FT_WILDCARD_H
# define FT_WILDCARD_H

# include "../minishell.h"

/**
 * ft_new_wildcard - Updates the `cmd` structure by expanding wildcard patterns.
 * 
 * This function processes wildcard patterns (e.g., `*`, `?`) in the command
 * stored in the `cmd` structure. It uses the `shell` context to resolve these
 * patterns against the filesystem or other relevant sources.
 * 
 * @param cmd: A pointer to the command structure to be updated.
 * @param shell: A pointer to the shell context used for resolving wildcards.
 * 
 * Side effects:
 * - Modifies the `cmd` structure to include expanded wildcard results.
 * - May allocate memory for new strings, requiring proper cleanup.
 */
void	ft_new_wildcard(t_cmd *cmd, t_shell *shell);

#endif