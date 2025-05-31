/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:46 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:54:16 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WILDCARD_H
# define FT_WILDCARD_H

# include "../minishell.h"
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>

//— Collector struct —---------
typedef struct s_collect
{
	char	**arr;
	int		len;
	int		cap;
}	t_collect;

// Wildcard function
void	ft_new_wildcard(t_cmd *cmd, t_shell *shell);

//— Helpers —------------------------------------------------------------
bool	has_wildcard(const char *s);
bool	is_quoted(const char *s);
char	**split_path(const char *path);
void	free_strarr(char **a);
int		tolower_ci(int c);
int		strcmp_ci(const char *a, const char *b);
void	sort_strs(char **arr, int n);
bool	match_pat(const char *name, const char *pat);
char	*join_path(const char *a, const char *b);

//— Collector functions —-----------------------------------------------
void	collect_init(t_collect *c);

#endif