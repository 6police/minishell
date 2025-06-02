/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:18:46 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 03:05:34 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to process command arguments by removing invalid ones
void	process_cmd_args(t_cmd *cmd)
{
	char	**splitargs;
	char	**newargs;
	int		valid_count;
	int		i;

	if (!cmd || !cmd->args || !(*cmd->args))
		return ;
	i = 0;
	valid_count = count_valid_args(cmd->args);
	newargs = copy_valid_args(cmd->args, valid_count);
	if (!newargs)
		return ;
	splitargs = copy_array(newargs);
	if (!splitargs)
		return (free_split(newargs), (void)0);
	free_split(cmd->args);
	while (splitargs[i])
	{
		if (ft_strlen(splitargs[i]) >= 3)
			splitargs[i] = remove_quotes_beg_end(splitargs[i]);
		i++;
	}
	free_split(newargs);
	cmd->args = splitargs;
}

t_cmd	*invalid_exit(t_cmd *cmd, t_shell *shell)
{
	shell->exit_value = 127;
	if (ft_strcmp(cmd->name, "kekers") != 0)
		ft_printf_fd(STDERR_FILENO, "minishell: invalid command: %s\n",
			cmd->name);
	return (cmd);
}

// function to find the head of the command linked list
static t_cmd	*find_head(t_shell *shell)
{
	t_cmd	*head_cmd;

	if (!shell || !shell->cmds)
		return (NULL);
	head_cmd = shell->cmds;
	while (head_cmd && head_cmd->prev)
		head_cmd = head_cmd->prev;
	return (head_cmd);
}

// funciton that takes tokens and assembles into commands
t_cmd	*build_cmds(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*head_cmd;
	int		i;

	i = 0;
	head_cmd = NULL;
	if (!shell || !shell->tokens)
		return (NULL);
	while (shell->tokens[i])
	{
		if (is_all_quotes(shell->tokens[i]))
			return (ft_printf_fd(2, REDIR_FAILURE "\n"), NULL);
		cmd = parse_cmd(shell, i);
		if (cmd == NULL)
			return (NULL);
		i++;
	}
	if (head_cmd == NULL)
		head_cmd = shell->cmds;
	else
		head_cmd = find_head(shell);
	if (head_cmd == NULL)
		return (ft_printf_fd(2, "Error: No commands found.\n"), NULL);
	return (head_cmd);
}
