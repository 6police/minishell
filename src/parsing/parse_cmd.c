/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:56:20 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 17:57:00 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parsing.h"

// function to count valid arguments in the command
static int	preprocess_tokens(t_shell *shell, int i, char ***args)
{
	if (!shell || !shell->tokens || !shell->tokens[i])
		return (0);
	mark_and_replace(shell->tokens[i], ' ', 2);
	*args = ft_split(shell->tokens[i], 2);
	mark_and_replace(shell->tokens[i], 2, ' ');
	if (!*args || !(*args)[0])
		return (0);
	return (1);
}

// function to set up the command structure
static t_cmd	*setup_cmd(char **args, t_shell *shell, int i)
{
	int		valid_count;
	char	**clean_args;
	char	*name;
	t_cmd	*cmd;

	valid_count = count_valid_args(args);
	clean_args = copy_valid_args(args, valid_count);
	name = set_name(clean_args);
	cmd = init_cmd(name, clean_args);
	free(name);
	built_in_handle(cmd, shell, clean_args);
	free_split(clean_args);
	add_last_cmd(&shell->cmds, cmd);
	cmd_processor_a(cmd, shell, i);
	return (cmd);
}

// function to finalize the command after processing
static t_cmd	*finalize_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->is_valid)
		return (invalid_exit(cmd, shell));
	ft_wildcard(cmd, shell);
	if (cmd->args && cmd->args[0] && cmd->args[0][0] != '\0')
		process_cmd_args(cmd);
	return (cmd);
}

// Main function to parse a command from the shell tokens
t_cmd	*parse_cmd(t_shell *shell, int i)
{
	t_cmd	*cmd;
	char	**args;

	cmd = NULL;
	args = NULL;
	if (!preprocess_tokens(shell, i, &args))
		return (NULL);
	cmd = setup_cmd(args, shell, i);
	free_split(args);
	return (finalize_cmd(cmd, shell));
}
