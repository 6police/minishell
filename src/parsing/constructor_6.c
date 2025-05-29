#include "ft_parsing.h"

// function to check if the argument is a redirection without an argument
static int	count_valid_args(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!args || !args[0] || args[0][0] == '\0')
		return (0);
	while (args[i] && args[i][0] != '\0')
	{
		if (is_redir_noarg(args[i]))
			i += 2;
		else if (is_redir(args[i]))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

// function to copy valid arguments from the original args array
static char	**copy_valid_args(char **args, int count)
{
	char	**newargs;
	int		i;
	int		j;

	newargs = ft_calloc(sizeof(char *), count + 1);
	if (!newargs)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i] && args[i][0] != '\0')
	{
		if (is_redir_noarg(args[i]))
			i += 2;
		else if (is_redir(args[i]))
			i++;
		else
		{
			newargs[j] = ft_strdup(args[i]);
			j++;
			i++;
		}
	}
	return (newargs);
}

// function to process command arguments by removing invalid ones
void	process_cmd_args(t_cmd *cmd)
{
	char	**splitargs;
	char	**newargs;
	int		valid_count;
	int		i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	valid_count = count_valid_args(cmd->args);
	newargs = copy_valid_args(cmd->args, valid_count);
	splitargs = copy_array(newargs);
	free_split(cmd->args);
	while (splitargs[i])
	{
		splitargs[i] = remove_quotes_beg_end(splitargs[i]);
		i++;
	}
	cmd->args = splitargs;
	free_split(newargs);
}
