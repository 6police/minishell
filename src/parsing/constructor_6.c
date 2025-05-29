#include "ft_parsing.h"

// function that normalizes the command->arg array.

// void	process_cmd_args(t_cmd *cmd)
// {
// 	char	**newargs;
// 	int		arg_count;
// 	int		i;

// 	if (!cmd || !cmd->args)
// 		return ;
// 	arg_count = 0;
// 	i = 0;
// 	while (cmd->args[i] && cmd->args[i][0] != '\0')
// 	{
// 		if (is_redir_noarg(cmd->args[i]))
// 			i += 2;
// 		else if (is_redir(cmd->args[i]))
// 			i++;
// 		else
// 		{
// 			arg_count++;
// 			i++;
// 		}
// 	}
// 	newargs = ft_calloc(sizeof(char *), arg_count + 1);
// 	i = 0;
// 	arg_count = 0;
// 	while (cmd->args[i] && cmd->args[i][0] != '\0')
// 	{
// 		if (is_redir_noarg(cmd->args[i]))
// 			i += 2;
// 		else if (is_redir(cmd->args[i]))
// 			i++;
// 		else
// 		{
// 			newargs[arg_count] = ft_strdup(cmd->args[i]);
// 			arg_count++;
// 			i++;
// 		}
// 	}
// 	free_split(cmd->args);
// 	cmd->args = ft_removequotes(newargs);
// }

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

void	process_cmd_args(t_cmd *cmd)
{
	char	**newargs;
	int		valid_count;

	if (!cmd || !cmd->args)
		return ;
	valid_count = count_valid_args(cmd->args);
	newargs = copy_valid_args(cmd->args, valid_count);
	free_split(cmd->args);
	cmd->args = ft_removequotes(newargs);
}
