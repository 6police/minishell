#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../minishell.h"

// handle malloc failure
void	handle_malloc_failure(void);

// function to handle malloc failure for redirection array
void	*handle_redir_malloc_error(char **redirs);

// new prompt
void	new_prompt(void);

// remove quotes,
// frees the old str and returns a new allocated one without quotes
char	*remove_quotes(char *arg);

// another function to remove quotes,
// frees the old str and returns a new allocated one without quotes
char	**ft_removequotes(char **args);

// removes all quotes from a string,
// frees the old str and returns a new allocated one without quotes
char	*remove_all_quotes(char *arg);

// removes a segment from a string with a new one
char	*str_replace_segment(const char *src, const char *replace, int start,
			int len_to_delete);

// get_pid, but ours, since its not permitted to use get_pid();
int		ft_get_pid(void);

// function to check if a character is a space
bool	ft_isspace(char c);

// function to copy an array of strings
char	**copy_array(char **array);

#endif