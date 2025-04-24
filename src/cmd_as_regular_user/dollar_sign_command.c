#include "ft_cmd_as_regular_user.h"

static char	*handle_dollar(char *arg, t_shell *shell);
static int	check_quotes_type(char *str);

/*
	TESTAR VARIAS MERDAS MALUCAS. COMO:

	cat ola"'PIZ$USERZA'"adeus
	echo ola""PIZ$$ZZA""adeus
	etc
*/

void	dollar_sign(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int		quote_type;
	bool	has_dollar;

	i = -1;
	quote_type = 0;
	has_dollar = false;
	while (cmd->args[++i])
	{
		if (strstr(cmd->args[i], "$") != NULL)
		{
			quote_type = check_quotes_type(cmd->args[i]);
			has_dollar = true;
		}
		if ((quote_type == 1 || quote_type == 0) && has_dollar == true)
		{
			if (quote_type == 1)
				cmd->args[i] = remove_quotes(cmd->args[i]);
			cmd->args[i] = handle_dollar(cmd->args[i], shell);
		}
	}
}
static char	*handle_dollar(char *arg, t_shell *shell)
{
	int				i;
	int			delete;
	int			start;
	int			env_key_len;
	t_env_var	*env_var;
	char		*tmp;

	i = 0;
	env_key_len = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			if (ft_isalpha(arg[i + 1]) == 1 || (arg[i + 1] == '_'))
			{
				if ((env_var = find_env_var(shell->env, (arg + (i + 1)))))
				{
					start = i;
					env_key_len = ft_strlen(env_var->key) + 1; // +1 for the $
					tmp = str_replace_segment(arg, env_var->value, i, env_key_len);
					if (tmp[i + ft_strlen(env_var->value)] != '\0' && (ft_isalnum(tmp[i + ft_strlen(env_var->value)]) == 1 || tmp[i + ft_strlen(env_var->value)] == '_')) // we want to check 
					{
						i += ft_strlen(env_var->value);
						delete = 0;
						while ((ft_isalnum(tmp[i]) == 1 || tmp[i] == '_') && tmp[i])
						{	
							i++;
							delete++;
						}
						arg = str_replace_segment(arg, "", start, env_key_len + delete);
					}
					else
						arg = str_replace_segment(arg, env_var->value, start, env_key_len);
					free(tmp);
				}
				else // env not found, env == NULL
				{
					start = i;
					while ((ft_isalnum(arg[i]) == 1 || arg[i] == '_') && arg[i])
						i++;
					i -= 1;
					arg = str_replace_segment(arg, "", start, i - start);
					printf("arg: %s\n", arg);
					fflush(stdout);
				}
			}
			else if (arg[i + 1] == '?')
				arg = str_replace_segment(arg, ft_itoa(shell->exit_value), i, 2);
			else if (arg[i + 1] == '$')
				arg = str_replace_segment(arg, ft_itoa(shell->main_pid), i, 2);
		}
		i++;
	}
	return (arg);
}

static int	check_quotes_type(char *str)
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
