#include "ft_parsing.h"

// function to strip the redirection prefix from the file name
static char	*strip_redir_prefix(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0' && (file[i] == '>' || file[i] == '<'))
		i++;
	while (file[i] == ' ')
		i++;
	return (ft_substr(file, i, ft_strlen(file) - i));
}

// function to assign the file name to the redirection structure
void	assign_redir_file(t_fd *redir)
{
	char	*new_file;

	new_file = NULL;
	if (redir->type == NONE)
	{
		free(redir->file);
		redir->file = NULL;
		return ;
	}
	new_file = strip_redir_prefix(redir->file);
	if (!new_file)
	{
		ft_printf_fd(STDERR_FILENO, "Error: malloc failed\n");
		return ;
	}
	free(redir->file);
	redir->file = new_file;
	if (redir->file[0] == '\0')
	{
		free(redir->file);
		redir->file = NULL;
		redir->type = NONE;
	}
}
