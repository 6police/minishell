#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "../minishell.h"
// parsing

// parsing the line into tokens
char	**parse_line(char *line, int letter, int sub);

// parsing to make tokens so we can later parse the tokens into commands
void	parse_tokens(t_shell *shell);

// parse the line and tokens
void	parse(t_shell *shell);

// count the number of quotes
int		count_quotes(char *line);

// mark a character in the line and switch for another
void	mark_and_replace(char *line, int letter, int sub);

// mark the pipes
void	mark_pipes(char *line);

// split the line into tokens
char	**ft_parse_split(char *line, int letter, int sub);

// function to initialize tokens
t_token	*init_token(char **tokens);

// function to add a token to the list
t_cmd	*build_cmds(t_shell *shell);

void	parse_redirs(t_cmd *cmd, t_shell *shell);

#endif
