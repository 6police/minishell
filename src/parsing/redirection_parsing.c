#include "ft_parsing.h"

int	check_for_redirs(char *token)
{
	int	fwd;
	int	bwd;
	int	dbl_fwd;
	int	hd;
	int	result;

	// check if the token is NULL
	if (token == NULL)
	{
		ft_printf_fd(STDIN_FILENO, "Token is NULL\n");
		return (-1);
	}
	fwd = 0;
	bwd = 0;
	dbl_fwd = 0;
	hd = 0;
	fwd = forward_redir_count(token);
	bwd = back_redir_count(token);
	dbl_fwd = dbl_forward_redir_count(token);
	hd = here_doc_count(token);
	ft_printf_fd(STDIN_FILENO, "Forward redirection found: %d\n", fwd);
	ft_printf_fd(STDIN_FILENO, "Backward redirection found: %d\n", bwd);
	ft_printf_fd(STDIN_FILENO, "Double forward redirection found: %d\n",
		dbl_fwd);
	ft_printf_fd(STDIN_FILENO, "Here document found: %d\n", hd);
	result = fwd + bwd + dbl_fwd + hd;
	if (result > 0)
		return (result);
	else
		return (0);
}

t_redir_struct	*create_redir(char *token)
{
	t_redir_struct	*redir;

	(void)token;
	redir = ft_calloc(1, sizeof(t_redir_struct));
	if (redir == NULL)
	{
		ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
		return (NULL);
	}
	redir->type = 0;
	redir->file = NULL;
	redir->next = NULL;
	return (redir);
}

// function to treat tokens and corresponding redirections
// it searches for the next redir
// takes the token and separates it by redirections
char	**split_into_redirs(char *token)
{
	int		total_redirs;
	char	**redirs;
	int		i;
	int		j;
	int		k;

	total_redirs = (check_for_redirs(token));
	if (total_redirs == 0)
		return (NULL);
	redirs = ft_calloc(total_redirs + 1, sizeof(char *));
	if (redirs == NULL)
	{
		ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
		return (NULL);
	}
	k = 0;
	i = 0;
	j = 0;
	while (k < total_redirs)
	{
		while (token[i] != '\0' && (token[i] != '>' && token[i] != '<'))
			i++;
		j = i + 1;
		while (token[j] != '\0' && (token[j] != '>' && token[j] != '<'))
			j++;
		redirs[k] = ft_substr(token, i, j - i);
		if (redirs[k] == NULL)
		{
			ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
			free(redirs);
			return (NULL);
		}
		i = j;
		k++;
	}
	redirs[k] = NULL;
	return (redirs);
}
