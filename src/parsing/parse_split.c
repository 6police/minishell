
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
	int	j;
	int	c;

	j = -1;
	c = 0;
	while (line[++j])
	{
		if ((line[j] == '\'' || line[j] == '"') && !c)
			c = line[j];
		else if (c && line[j] == c)
			c = 0;
		else if ((line[j] == letter) && !c)
			line[j] = sub;
	}
}

// function to check for the existence of a pipe in the line.
// it cant be followed by another |
void	mark_pipes(char *line)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	if (!line)
		return ;
	if (line[0] == '|')
		ft_printf_fd(2, "Error: syntax error near unexpected token `|'\n");
	while (line[++i])
	{
		if ((line[i] == '\'' || line[i] == '"') && !c)
			c = line[i];
		else if (c && line[i] == c)
			c = 0;
		else if (line[i] == '|' && !c && line[i + 1] != '\0')
		{
			if (line[i + 1] != '|' && line[i - 1] != '|')
				line[i] = 7;
		}
	}
}

char	**ft_parse_split(char *line, int letter, int sub)
{
	(void)letter;
	if (!line)
		return (NULL);
	if (count_quotes(line) != 0)
		return (ft_printf_fd(2, "Error: Odd number of quotes\n"), NULL);
	mark_pipes(line);
	// mark_and_replace(line, letter, sub);
	// printf("line: %s\n", line);
	return (ft_split(line, sub));
}

static void	add_last(t_token **head, t_token *token)
{
	t_token	*tmp;

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

t_token	*init_token(char **tokens)
{
	t_token	*token;
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (tokens[i])
	{
		token = ft_calloc(sizeof(t_token), 1);
		token->token = &tokens[i];
		token->next = NULL;
		add_last(&head, token);
		i++;
	}
	return (head);
}
