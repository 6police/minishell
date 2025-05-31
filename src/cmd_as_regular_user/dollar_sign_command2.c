/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_command2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:06:18 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:30:09 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd_as_regular_user.h"

// This function processes the argument to replace the dollar sign
//if an environment variable is found.
char	*found_env_var(t_dollar *d, char *arg)
{
	d->start = d->i;
	d->env_key_len = ft_strlen(d->env_var->key) + 1;
	d->aux = ft_strdup(arg);
	d->tmp = str_rplc_sgmt(d->aux, d->env_var->value, d->i, d->env_key_len);
	if (d->tmp[d->i + ft_strlen(d->env_var->value)] != '\0'
		&& (ft_isalnum(d->tmp[d->i + ft_strlen(d->env_var->value)]) == 1
			|| d->tmp[d->i + ft_strlen(d->env_var->value)] == '_'))
	{
		d->i += ft_strlen(d->env_var->value);
		d->delete = 0;
		while ((ft_isalnum(d->tmp[d->i]) == 1 || d->tmp[d->i] == '_'))
		{
			d->i++;
			d->delete++;
		}
		arg = str_rplc_sgmt(arg, "", d->start, d->env_key_len + d->delete);
		d->i = d->start - 1;
	}
	else
	{
		arg = str_rplc_sgmt(arg, d->env_var->value, d->start, d->env_key_len);
		d->i += ft_strlen(d->env_var->value) - 1;
	}
	free(d->tmp);
	return (arg);
}

// This function processes the argument to replace the dollar sign
//when no environment variable is found.
char	*no_env_var_found(t_dollar *d, char *arg)
{
	d->start = d->i;
	d->i += 1;
	while (arg[d->i])
	{
		if (ft_isalnum(arg[d->i]) == 1 || arg[d->i] == '_')
			d->i++;
		else
			break ;
	}
	arg = str_rplc_sgmt(arg, "", d->start, d->i - d->start);
	d->i = d->start - 1;
	return (arg);
}

void	ft_initiate_dollar(t_dollar *d)
{
	d->i = 0;
	d->delete = 0;
	d->start = 0;
	d->env_key_len = 0;
	d->tmp = NULL;
	d->aux = NULL;
	d->env_var = NULL;
}

// This function checks the type of quotes in the string.
int	check_quotes_type(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			return (1);
		else if (str[i] == '\'')
			return (2);
	}
	return (0);
}
