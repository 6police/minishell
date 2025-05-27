#include "ft_cmd_as_regular_user.h"

char	*handle_dollar(char *arg, t_shell *shell);
static int	check_quotes_type(char *str);
static char	*ft_strstr(const char *haystack, const char *needle);

void	dollar_sign(t_shell *shell, int n_toks)
{
	int	i;
	int		quote_type;
	bool	has_dollar;

	i = 0;
	quote_type = 0;
	has_dollar = false;
	while (i < n_toks)
	{
		if (shell->tokens[i] == NULL)
			i++;
		if (ft_strstr(shell->tokens[i], "$") != NULL)
		{
			quote_type = check_quotes_type(shell->tokens[i]);
			has_dollar = true;
		}
		if ((quote_type != 2) && has_dollar == true)
		{
			if (quote_type == 1)
				shell->tokens[i] = remove_quotes(shell->tokens[i]);
			shell->tokens[i] = handle_dollar(shell->tokens[i], shell);
		}
		i++;
	}
}
char	*handle_dollar(char *arg, t_shell *shell)
{
	int			i;
	int			delete;
	int			start;
	int			env_key_len;
	char		*tmp;
	char		*arg2;
	t_env_var	*env_var;

	i = 0;
	start = 0;
	env_key_len = 0;
	tmp = NULL;
	arg2 = ft_strdup(arg);
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			if (ft_isalpha(arg[i + 1]) == 1 || (arg[i + 1] == '_'))
			{
				if ((env_var = find_env_var(shell->env, (arg + (i + 1)))) != NULL)
				{
					start = i;
					env_key_len = ft_strlen(env_var->key) + 1; // +1 to catch the $
					tmp = str_replace_segment(arg, env_var->value, i, env_key_len);
					if (tmp[i + ft_strlen(env_var->value)] != '\0' && (ft_isalnum(tmp[i + ft_strlen(env_var->value)]) == 1 || tmp[i + ft_strlen(env_var->value)] == '_')) // we want to check 
					{
						i += ft_strlen(env_var->value);
						delete = 0;
						while ((ft_isalnum(tmp[i]) == 1 || tmp[i] == '_'))
						{	
							i++;
							delete++;
						}
						arg = str_replace_segment(arg, "", start, env_key_len + delete);
						i = start - 1;
					}
					else
					{	
						arg = str_replace_segment(arg, env_var->value, start, env_key_len); // ver os leaks do str_replace_segment
						i += ft_strlen(env_var->value) - 1;
					}
					free(tmp);
				}
				else // env not found, env == NULL
				{
					start = i;
					i += 1; // we want to skip the $
					while (arg[i])
					{
						if (ft_isalnum(arg[i]) == 1 || arg[i] == '_')
							i++;
						else
							break ;
					}
					arg = str_replace_segment(arg, "", start, i - start);
					i = start - 1;
				}
			}
			else if (arg[i + 1] == '?')
			{
				arg = str_replace_segment(arg, ft_itoa(shell->exit_value), i, 2);
				i = i + ft_strlen(ft_itoa(shell->exit_value)) - 2;
			}
			else if (arg[i + 1] == '$')
			{	
				arg = str_replace_segment(arg, ft_itoa(shell->main_pid), i, 2);
				i = i + ft_strlen(ft_itoa(shell->main_pid)) - 2;
			}
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

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (
			haystack[i + j] &&
			needle[j] &&
			haystack[i + j] == needle[j]
		)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
