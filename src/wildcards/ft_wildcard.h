/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:46 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 15:05:12 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WILDCARD_H
# define FT_WILDCARD_H

# include "../minishell.h"

//— Collector struct —---------
typedef struct s_collect
{
	char	**arr;
	int		len;
	int		cap;
}	t_collect;

// Wildcard function
void	ft_wildcard(t_cmd *cmd, t_shell *shell);

//— Helpers —------------------------------------------------------------
bool	has_wildcard(const char *s);
bool	is_quoted(const char *s);
char	**split_path(const char *path);
void	free_strarr(char **a);
int		tolower_ci(int c);
int		strcmp_ci(const char *a, const char *b);
void	sort_strs(char **arr, int n);
bool	match_pat(const char *name, const char *pat, int nch);
char	*join_path(const char *a, const char *b);
void	collect_init(t_collect *c);
void	expand_recursive(char **comps, int lvl,
			const char *base, t_collect *out);
void	restore_literal_pattern(t_cmd *cmd, int i, char *arg);
int		count_chunks(char **chunks);
void	handle_literal_component(char **comps, int lvl,
			const char *base, t_collect *out);
void	handle_end_of_path(const char *base, t_collect *out);
DIR		*open_directory(const char *base);
bool	should_skip_entry(struct dirent *entry);
void	process_matching_entry(char **comps, int lvl,
			t_collect *out, char *next);
void	collect_add(t_collect *c, char *s);
bool	path_exists(const char *path);

#endif