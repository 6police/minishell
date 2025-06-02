/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_here_doc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:41:31 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/02 19:42:46 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd_as_regular_user.h"

static char	*handle_dollar(char *arg, t_shell *shell);
static char	*expanding_exit_value(char *arg, t_dollar *d, t_shell *shell);
static char	*expanding_shell_main_pid(char *arg, t_dollar *d, t_shell *shell);

void	dollar_sign_here_doc(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		quote_type;
	bool	has_dollar;

	i = 0;
	quote_type = 0;
	has_dollar = false;
	while (cmd->args[i])
	{
		if (ft_strstr(cmd->args[i], "$") != NULL)
		{
			has_dollar = true;
			quote_type = check_quotes_type(cmd->args[i]);
		}
		if ((quote_type != 2) && has_dollar == true)
			cmd->args[i] = handle_dollar(cmd->args[i], shell);
		i++;
	}
}

// Processes the argument to replace dollar signs with their 
//corresponding environment variable values or special values.
static char	*handle_dollar(char *arg, t_shell *shell)
{
	t_dollar	d;

	ft_initiate_dollar(&d);
	while (arg[d.i])
	{
		if (arg[d.i] == '$' && arg[d.i + 1])
		{
			if (ft_isalpha(arg[d.i + 1]) == 1 || (arg[d.i + 1] == '_'))
			{
				d.env_var = find_env_var(shell->env, (arg + (d.i + 1)));
				if (d.env_var != NULL)
					arg = found_env_var(&d, arg);
				else
					arg = no_env_var_found(&d, arg);
			}
			else if (arg[d.i + 1] == '?')
				arg = expanding_exit_value(arg, &d, shell);
			else if (arg[d.i + 1] == '$')
				arg = expanding_shell_main_pid(arg, &d, shell);
		}
		d.i++;
	}
	return (arg);
}

// Expands the exit value of the shell and replaces it in the argument string.
static char	*expanding_exit_value(char *arg, t_dollar *d, t_shell *shell)
{
	d->aux = ft_itoa(shell->exit_value);
	arg = str_rplc_sgmt(arg, d->aux, d->i, 2);
	d->i += ft_strlen(d->aux) - 2;
	free(d->aux);
	return (arg);
}

// Expands the main process ID of the shell
//and replaces it in the argument string.
static char	*expanding_shell_main_pid(char *arg, t_dollar *d, t_shell *shell)
{
	d->aux = ft_itoa(shell->main_pid);
	arg = str_rplc_sgmt(arg, d->aux, d->i, 2);
	d->i += ft_strlen(d->aux) - 2;
	free(d->aux);
	return (arg);
}
