
#include "ft_parsing.h"

// parsing the line into tokens
char	**parse_line(char *line, int letter, int sub)
{
	char	**tokens;

	if (!line)
		return (NULL);
	tokens = ft_parse_split(line, letter, sub);
	if (!tokens)
		return (NULL);
	return (tokens);
}

// parsing to make tokens so we can later parse the tokens into commands
void	parse_tokens(t_shell *shell) // this function is not complete
{
	// for now it just prints the tokens
	int i;

	i = 0;
	while (shell->tokens[i])
	{
		if (ft_strcmp(shell->tokens[i], "env") == 0)
			print_env(shell->env);
		if (ft_strcmp(shell->tokens[i], "exit") == 0)
			exit_shell(shell, 1);
		if (ft_strcmp(shell->tokens[i], "export") == 0)
			export_builtin(shell);
		if (ft_strcmp(shell->tokens[i], "unset") == 0)
			unset_env_var(shell, shell->tokens[i + 1]);
		if (ft_strcmp(shell->tokens[i], "pwd") == 0)
			pwd_shell();
		if (ft_strcmp(shell->tokens[i], "cd") == 0)
		{
			t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
			cmd->name = "cd";
			cmd->args = shell->tokens;
			cd_shell(cmd, shell->env);
		}
		i++;
	}
	// shell->cmds = malloc(sizeof(t_cmd *) * (i + 1));
}

// print the tokens
static void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens[i])
	{
		ft_printf(GREEN "token" RESET " [ " RED "%d" RESET " ] --> %s\n", i,
			shell->tokens[i]);
		i++;
	}
}

// parse the line according to priority
void	parse(t_shell *shell, int debug)
{
	int sub;
	int i;
	int j;
	t_token *head_token;

	j = 0;
	i = 0;
	sub = 7; // the character to replace the separator

	shell->tokens = parse_line(shell->line, shell->separators[0], sub);
	if (debug)
		print_tokens(shell);

	head_token = init_token(shell->tokens);
	if (!head_token)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	shell->token = head_token;
	if (debug)
	{
		while (shell->token)
		{
			ft_printf("token: %s\n", shell->token->token[0]);
			char **tokenss = parse_line(shell->token->token[0], shell->separators[5], sub);
			shell->token->token = tokenss;
			while(shell->token->token[j])
			{
				ft_printf("token: %s\n", shell->token->token[j]);
				j++;
				ft_printf("j: %d\n---\n", j);
			}
			shell->token = shell->token->next;
			j = 0;
		}
	}
}