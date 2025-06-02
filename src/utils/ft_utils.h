/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:18:00 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 20:57:31 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../minishell.h"

// handle malloc failure
void	handle_malloc_failure(void);

// function to handle malloc failure for redirection array
void	*handle_redir_malloc_error(char **redirs);

// new prompt
void	new_prompt(void);

// remove quotes from the beggining and end of the str,
// frees the old str and returns a new allocated one without quotes
char	*remove_quotes_beg_end(char *arg);

// another function to remove quotes,
// frees the old str and returns a new allocated one without quotes
char	**ft_removequotes(char **args);

// removes all quotes from a string,
// frees the old str and returns a new allocated one without quotes
char	*remove_all_quotes(char *arg);

// removes a segment from a string with a new one
char	*str_rplc_sgmt(char *src, const char *replace, int start,
			int len_to_delete);

// get_pid, but ours, since its not permitted to use get_pid();
int		ft_get_pid(void);

// function to check if a character is a space
bool	ft_isspace(char c);

// function to copy an array of strings
char	**copy_array(char **array);

// ft_str_r_cmp.c
int		ft_str_r_cmp(const char *s1, const char *s2);

// ft_strstr.c
char	*ft_strstr(const char *haystack, const char *needle);

// ft_strcat.c
char	*ft_strcat(char *dest, const char *src);

// ft_realloc.c
char	**ft_realloc_arr(char **ptr, size_t new_cap);

// function to check if a string starts with a redirection symbol
bool	starts_with_redir(char *str);

// function to strip quotes from a string
char	*strip_quotes(const char *s);

#endif