
#include "ft_parsing.h"

// function to count the number of quotes
int	count_quotes(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !count)
			count = line[i];
		else if (count && line[i] == count)
			count = 0;
		i++;
	}
	return (count);
}

// function to mark and switch a set of characters in the line for another
void	mark_and_replace(char *line, int letter, int sub)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	j = -1;
	c = 0;
	while (line[++j])
	{
		if ((line[j] == '\'' || line[j] == '\"') && !c)
			c = line[j];
		else if (c && line[j] == c)
			c = 0;
		else if ((line[j] == letter) && !c)
			line[j] = sub;
	}
	j = -1;
}


char	**ft_parse_split(char *line, int letter, int sub)
{
	if (!line)
		return (NULL);
	if (count_quotes(line) != 0)
		return (ft_printf_fd(2, "Error: Odd number of quotes\n"), NULL);
	mark_and_replace(line, letter, sub);
	// printf("line: %s\n", line);
	return (ft_split(line, sub));
}

static void    add_last(t_token **head, t_token *token)
{
    t_token *tmp;

    tmp = *head;
    if (!tmp)
        *head = token;
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = token;
    }
}
t_token    *init_token(char **tokens)
{
    t_token	*token;
    t_token	*head;
    int		i;

    i = 0;
    head = NULL;
    while (tokens[i])
    {
        token = (t_token *)malloc(sizeof(t_token));
        token->token = &tokens[i];
        token->next = NULL;
        add_last(&head, token);
        i++;
    }
    return (head);
}