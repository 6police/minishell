#include "ft_parsing.h"

int	forward_redir_count(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], ">") == 0)
		{
			if (ft_strcmp(token[i + 1], ">") != 0)
				count++;
		}
		else if (ft_strcmp(token[i++], ">") == 0)
		{
			if (ft_strcmp(token[i + 1], ">") != 0)
				count++;
			else if (ft_strcmp(token[i + 1], ">") == 0)
				return (ft_printf_fd(2,
						"syntax error near unexpected token `>>'\n"), -1);
		}
		i++;
	}
	return (count);
}

// function that counts the number of < or redirects in the token
int	backward_redir_count(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "<") == 0)
		{
			if (ft_strcmp(token[i++], "<") != 0)
				count++;
		}
		i++;
	}
}

// function that counts the number of here_docs in the token
int	here_doc_count(char *token)
{
}
