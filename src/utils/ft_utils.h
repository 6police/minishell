#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../minishell.h"

// new prompt
void	new_prompt(void);

// remove quotes, frees the old str and returns a new allocated one without quotes
char	*remove_quotes(char *arg);

// removes all quotes from a string, frees the old str and returns a new allocated one without quotes
char	*remove_all_quotes(char *arg);

// removes a segment from a string with a new one
char	*str_replace_segment(char *src, const char *replace, int start, int len_to_delete);

//get_pid, but ours, since its not permitted to use get_pid();
int		ft_get_pid(void);

#endif