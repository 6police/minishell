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

// funciton to count the number of > redirects in the token
int		forward_redir_count(char *token);

// function to count the number of >> redirects in the token
int		dbl_forward_redir_count(char *token);

// function to count the number of < redirects in the token
int		back_redir_count(char *token);

// function that counts the number of here_docs in the token
int		here_doc_count(char *token);

// function to check for redirections
void	check_for_redirs(char *token);

#endif
