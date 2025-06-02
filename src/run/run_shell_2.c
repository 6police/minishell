/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:21:02 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 19:19:52 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_run.h"

/*static char	*build_prompt(void)
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
}*/

static void	handle_status(t_shell *shell)
{
	if (t_pid()->exit_value == 130)
	{
		shell->exit_value = 130;
		t_pid()->exit_value = 0;
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
		prompt = ft_strdup(PROMPT);
		if (!prompt)
			exit_shell(&(t_cmd){0}, shell);
		if (isatty(STDIN_FILENO))
			shell->line = readline(prompt);
		else
			clean_exit(&shell);
		free(prompt);
		handle_status(shell);
		if (!check_line_length(shell->line))
			continue ;
		if (!shell->line)
			exit_shell(&(t_cmd){0}, shell);
		minishellers(shell);
	}
}
