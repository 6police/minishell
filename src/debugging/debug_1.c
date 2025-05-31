/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:31:33 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/31 19:35:05 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"

// Print the enviroment variables
void	print_env(t_env *env, t_cmd *cmd)
{
	t_env_var	*tmp;

	(void)cmd;
	tmp = env->head;
	while (tmp)
	{
		if (tmp->value)
			ft_printf_fd(STDOUT_FILENO, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

// Print the exported environment variables
void	print_export(t_env *env, t_cmd *cmd)
{
	t_env_var	*tmp;

	(void)cmd;
	tmp = env->head;
	while (tmp)
	{
		ft_printf_fd(STDOUT_FILENO, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

// Print the arguments of a command
void	print_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		ft_printf_fd(STDOUT_FILENO, "[%s]", cmd->args[i]);
		i++;
	}
	ft_printf("\n");
}

// Print the redirections
void	print_redirs(char **redirs)
{
	int	i;

	i = 0;
	while (redirs && redirs[i])
	{
		ft_printf("[" GREEN "%s" RESET "] ", redirs[i]);
		i++;
	}
	ft_printf("\n");
}

// Print the command redirections
void	print_cmd_redirs(t_cmd *cmd)
{
	t_fd	*tmp;

	tmp = cmd->fd_struct;
	while (tmp)
	{
		if (tmp)
		{
			ft_printf(RED "type:" GREEN "%d\n" RESET, tmp->type);
			ft_printf(YELLOW "file:" GREEN "%s\n" RESET, tmp->file);
			ft_printf(BLUE "file pointer:" GREEN "%p\n" RESET, tmp->file);
			ft_printf("\n");
		}
		if (tmp->type == HERE_DOC_)
			ft_printf("heredoc: %s\n", tmp->file);
		if (tmp->type == REDIR_IN)
			ft_printf("redir in: %s\n", tmp->file);
		if (tmp->type == REDIR_OUT)
			ft_printf("redir out: %s\n", tmp->file);
		if (tmp->type == REDIR_APPEND)
			ft_printf("redir append: %s\n", tmp->file);
		if (tmp->type == NONE)
			ft_printf("redir none: %s\n", tmp->file);
		tmp = tmp->next;
	}
}
