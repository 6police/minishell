
#include "ft_parsing.h"

// function to get the index of the next redirection in the line
static int	get_next_redir_index(char *line, int i)
{
	int	j;

	j = i + 1;
	if (line[i] == line[j])
		j++;
	while (line[j] == ' ')
		j++;
	check_redir(line, &j);
	return (j);
}

// function to skip to the next redirection in the line
static int	skip_to_redir(char *line, int i)
{
	while (line[i] && line[i] != '>' && line[i] != '<')
		i++;
	return (i);
}

// function to fill the redirection slot in the redirs array
static int	fill_redir_slot(char **redirs, char *line, int *i, int k)
{
	int	j;

	*i = skip_to_redir(line, *i);
	j = get_next_redir_index(line, *i);
	redirs[k] = ft_substr(line, *i, j - *i);
	if (!redirs[k])
		return (0);
	*i = j;
	return (1);
}

// function to split the line into redirections
char	**split_into_redirs(char *line)
{
	int		total;
	char	**redirs;
	int		i;
	int		k;

	total = check_for_redirs(line);
	if (total == 0)
		return (NULL);
	redirs = ft_calloc(total + 1, sizeof(char *));
	if (!redirs)
		return (handle_redir_malloc_error(NULL));
	i = 0;
	k = 0;
	while (k < total)
	{
		if (!fill_redir_slot(redirs, line, &i, k))
			return (handle_redir_malloc_error(redirs));
		k++;
	}
	redirs[k] = NULL;
	return (redirs);
}
