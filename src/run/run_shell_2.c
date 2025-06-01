/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:21:02 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 17:21:11 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_run.h"

static char	*build_prompt(void)
{
	char	*cwd;
	char	*aux;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	aux = ft_strjoin(BLUE, cwd);
	free(cwd);
	if (!aux)
		return (NULL);
	prompt = ft_strjoin(aux, RESET "\n" PROMPT);
	free(aux);
	return (prompt);
}

static void	handle_status(t_shell *shell)
{
	if (t_pid()->status == 130)
	{
		shell->exit_value = 130;
		t_pid()->status = 0;
	}
}

static int	check_line_length(char *line)
{
	if (line && ft_strlen(line) > MAX_LINE_LENGTH)
	{
		ft_printf_fd(STDERR_FILENO, TOO_LONG_LINE "%d\n", MAX_LINE_LENGTH);
		free(line);
		return (0);
	}
	return (1);
}

void	run_shell(t_shell *shell)
{
	char	*prompt;

	while (1)
	{
		prompt = build_prompt();
		if (!prompt)
			exit_shell(&(t_cmd){0}, shell);
		shell->line = readline(prompt);
		free(prompt);
		handle_status(shell);
		if (!check_line_length(shell->line))
			continue ;
		if (!shell->line)
			exit_shell(&(t_cmd){0}, shell);
		minishellers(shell);
	}
}
