#include "ft_parsing.h"


// function that counts the number of > redirects in the token
int	forward_redir_count(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '>')
		{
			if ((token[i + 1] != '>') && (token[i + 1] != '\0') && (token[i
					- 1] != '>'))
				count++;
		}
		i++;
	}
	return (count);
}

// function that counts the number of >> redirects in the token
int	dbl_forward_redir_count(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '>')
		{
			if ((token[i + 1] == '>') && (token[i + 2] != '>') && (token[i
					+ 2] != '\0'))
				count++;
		}
		i++;
	}
	return (count);
}

// function that counts the number of < or redirects in the token
int	back_redir_count(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '<')
		{
			if ((token[i + 1] != '<') && (token[i + 1] != '\0') && (token[i
					- 1] != '<'))
				count++;
		}
		i++;
	}
	return (count);
}

// function that counts the number of here_docs in the token
int	here_doc_count(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '<')
		{
			if ((token[i + 1] == '<') && (token[i + 2] != '\0')
				&& ft_isascii(token[i + 2]))
				count++;
		}
		i++;
	}
	return (count);
}
