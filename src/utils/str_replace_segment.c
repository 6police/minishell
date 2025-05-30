#include "ft_utils.h"

// function to replace a segment of a string with another string
char	*str_rplc_sgmt(char *src, const char *replace, int start,
		int len_to_delete)
{
	int		new_len;
	char	*new_str;
	int		i;
	int		j;

	if (!src || !replace || start < 0 || len_to_delete < 0)
		return (NULL);
	new_len = ft_strlen(src) - len_to_delete + ft_strlen(replace);
	new_str = malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (free(src), NULL);
	i = -1;
	while (++i < start)
		new_str[i] = src[i];
	j = 0;
	while (replace[j])
		new_str[i++] = replace[j++];
	j = start + len_to_delete;
	while (src[j])
		new_str[i++] = src[j++];
	new_str[i] = '\0';
	free(src);
	return (new_str);
}
