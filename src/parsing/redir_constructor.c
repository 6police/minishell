#include "ft_parsing.h"

void	add_last_redir(t_fd **head, t_fd *new_redir)
{
	t_fd	*tmp;

	tmp = *head;
	if (!tmp)
		*head = new_redir;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

int	assign_redir_type(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '>' && str[1] != '\0')
	{
		if (str[1] == '>')
			return (REDIR_APPEND);
		else
			return (REDIR_OUT);
	}
	else if (str[0] == '<' && str[1] != '\0')
	{
		if (str[1] == '<')
			return (HERE_DOC_);
		else
			return (REDIR_IN);
	}
	else
		return (NONE);
}

void	assign_redir_file(t_fd *redir)
{
	int		i;
	char	*new_file;

    new_file = NULL;
	i = 0;
	if (redir->type == NONE)
	{
		free(redir->file);
		redir->file = NULL;
		return ;
	}
	else
	{
		while (redir->file[i] != '\0' && (redir->file[i] == '>'
				|| redir->file[i] == '<'))
			i++;
		while (redir->file[i] == ' ')
			i++;
		new_file = ft_substr(redir->file, i, ft_strlen(redir->file) - i);
	}
	if (!new_file)
	{
		ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
		return ;
	}
	free(redir->file);
	redir->file = new_file;
	if (redir->file[0] == '\0')
	{
		free(redir->file);
		redir->file = NULL;
		redir->type = 0;
	}
}

// function that creates a redirection structure
t_fd	*create_redir(char *str)
{
	t_fd	*redir;

	if (!str)
		return (NULL);
	redir = ft_calloc(sizeof(t_fd), 1);
	if (redir == NULL)
	{
		ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
		return (NULL);
	}
	redir->type = 0;
	redir->fd = -1;
	redir->file = ft_strdup(str);
	redir->next = NULL;
	return (redir);
}

t_fd	*assemble_redirs(char **redirs)
{
	t_fd	*redir;
	t_fd	*head;
	int		i;

	head = NULL;
	i = 0;
	while (redirs[i])
	{
		redir = create_redir(redirs[i]);
		if (redir == NULL)
			return (NULL);
		redir->type = assign_redir_type(redirs[i]);
		assign_redir_file(redir);
		add_last_redir(&head, redir);
		i++;
	}
	return (head);
}
