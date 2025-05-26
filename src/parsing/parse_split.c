
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
int	mark_pipes(char *line)
{
	int	i;
	int	c;
	int nbr;

	i = 0;
	c = 0;
	nbr = 0;
	if (!line)
		return (-1);
	if (line[0] == '|')
		return(-1);
	nbr = count_pipers(line);
	while (line[i] != '\0')
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
		i++;
	}
	return (nbr);
}

// int	mark_pipes(char *line)
// {
// 	int	i = -1;
// 	int	c = 0;
// 	int cmd = 0;

// 	if (!line)
// 		return (1);

		
// 	while (line[++i])
// 	{
// 		while (line[i] && ft_isspace(line[i]) && !cmd)
// 			i++; // Skip leading whitespace
// 		if (line[i] != '|' && line[i] != '\'' && line[i] != '"')
// 			cmd = 1; // Mark that we are in a command
// 		else if (line[i] == '|' && cmd)
// 			cmd = 0; // Reset command flag on pipe
// 		if (line[i] == '|' && !cmd)
// 			return 1;
// 		if (line[i] == '\0') // End of line
// 			break;
// 		if ((line[i] == '\'' || line[i] == '"') && !c)
// 			c = line[i];
// 		else if (c && line[i] == c)
// 			c = 0;
// 		else if (line[i] == '|' && !c)
// 		{
// 			if (line[i + 1] == '|') // Double pipe
// 			{
// 				// ft_printf_fd(2, "Error: syntax error near `||'\n");
// 				line[0] = '\0'; // Invalidate input
// 				return 1;
// 			}
// 			if (i == 0 || line[i + 1] == '\0') // Pipe at beginning or end
// 			{
// 				// ft_printf_fd(2, "Error: syntax error near unexpected token `|'\n");
// 				line[0] = '\0';
// 				return 1;
// 			}
// 			// Replace single valid pipe with sub
// 			line[i] = 7;
// 		}
// 	}
// 	return 0; // No syntax error found
// }


static bool is_all_whitespace(const char *s)
{
	if (!s)
		return true;
	while (*s)
	{
		if (!ft_isspace(*s))
			return false;
		s++;
	}
	return true;
}

char	**ft_parse_split(char *line, int letter, int sub)
{
	char **tokens;
	int nbrpipes;
	int i;

	i = 0;
	nbrpipes = 0;
	i = 0;
	
	(void)letter; // letter is not used in this function, but kept for compatibility
	if (!line || !(*line))
		return (NULL);
	if (count_quotes(line) != 0)
		return (ft_printf_fd(2, "Error: Odd number of quotes\n"), NULL);
	nbrpipes = mark_pipes(line);
	tokens = ft_split(line, sub);
	while (tokens && tokens[i] != NULL && token_not_empty(tokens[i]))
		i++;
	if (nbrpipes + 1 != i)
	{
		free_tokens(tokens);
		return (ft_printf_fd(2, "Error: syntax error near unexpected token `|'\n"), NULL);
	}
	return (tokens);
}

// char	**ft_parse_split(char *line, int letter, int sub)
// {
// 	char	**raw_tokens;
// 	char	**clean_tokens;
// 	int		i, count;


// 	(void)letter; // letter is not used in this function, but kept for compatibility
// 	if (!line)
// 		return (NULL);

// 	// Ensure balanced quotes
// 	if (count_quotes(line) != 0)
// 	{
// 		ft_printf_fd(2, "Error: Odd number of quotes\n");
// 		return (NULL);
// 	}

// 	// Mark valid pipes with special char
// 	if (mark_pipes(line))
// 	{
// 		ft_printf_fd(2, "Error: syntax error near unexpected token `|'\n");
// 		return (NULL);
// 	}

// 	// Split using sub char (7)
// 	raw_tokens = ft_split(line, sub);
// 	if (!raw_tokens)
// 		return (NULL);

// 	// Count valid (non-empty, non-whitespace) tokens
// 	count = 0;
// 	for (i = 0; raw_tokens[i]; i++)
// 	{
// 		if (!is_all_whitespace(raw_tokens[i]))
// 			count++;
// 	}

// 	if (count == 0)
// 	{
// 		free_tokens(raw_tokens);
// 		return (NULL);
// 	}

// 	// Allocate and fill clean token array
// 	clean_tokens = malloc(sizeof(char *) * (count + 1));
// 	if (!clean_tokens)
// 		return (free_tokens(raw_tokens), NULL);

// 	int j = 0;
// 	for (i = 0; raw_tokens[i]; i++)
// 	{
// 		if (!is_all_whitespace(raw_tokens[i]))
// 			clean_tokens[j++] = ft_strdup(raw_tokens[i]);
// 	}
// 	clean_tokens[j] = NULL;

// 	free_tokens(raw_tokens);
// 	return (clean_tokens);
// }


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
		if (is_all_whitespace(tokens[i]))
		{
			i++;
			continue;
		}
		token = ft_calloc(sizeof(t_token), 1);
		token->token = &tokens[i];
		token->next = NULL;
		add_last(&head, token);
		i++;
	}
	return (head);
}
