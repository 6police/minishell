#include "ft_cmd_as_regular_user.h"

char	*handle_doller(char *arg, t_shell *shell)
{
	int i;
	char **tmp;
	char **toks;
	t_env_var *env_var;

	env_var = NULL;
	tmp = ft_special_split(arg, '$');
	if (!tmp || !tmp[0])
		return (arg);
	toks = check_validation(tmp, shell);
	return (toks);
}

static char **ft_special_split(char *arg, char c)
{
	int i;
	int j;
	int k;
	char **tokens;

	if (!arg)
		return (NULL);
	tokens = malloc(sizeof(char *) * (ft_strlen(arg) + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (arg[i])
	{
		if (arg[i] == c)
		{
			tokens[j] = ft_substr(arg, k, i - k);
			j++;
			k = i + 1;
		}
		i++;
	}
	tokens[j] = ft_substr(arg, k, i - k);
	tokens[j + 1] = NULL;
	return (tokens);
}

static char **check_validation(char **tokens, t_shell *shell)
{
	int i;
	t_env_var *env_var;
	char *aux;
	char *ch;

	i = 0;
	env_var = NULL;
	if (!tokens || !(*tokens))
		return ;
	while (tokens[i])
	{
		ch = ft_substr(tokens[i], 0, ft_strlen(tokens[i]) - 1);
		env_var = find_env_var(shell->env, ch(tokens[i], shell));
		if (!env_var)
			i++;
		else
		{
			aux = ft_strdup(env_var->value);
			if (!aux)
			{
				ft_printf_fd(STDERR_FILENO, "minishell: memory allocation error\n");
				shell->exit_value = 1; // Memory allocation error exit code
				return ;
			}
			free(tokens[i]);
			tokens[i] = aux;
			i++;
		}
	}
	return (tokens);
}

static char	*check_alpha_numeric(char *token, t_shell *shell)
{
	int i;

	i = 0;
	if (!token || !(*token))
		return ;
	while (token[i])
	{
		if (ft_isalpha(token[i]) || token[i] == '_')
		{
				i++;
				while (ft_isalnum(token[i]) || token[i] == '_')
					i++;
		}
		else
		{
				ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `%c'\n", token[i]);
				shell->exit_value = 258; // Syntax error exit code
				return ;
		}
			i++;
	}
}
