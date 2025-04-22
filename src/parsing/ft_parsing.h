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
int		check_for_redirs(char *token);

// function to treat tokens and corresponding redirections
char	**split_into_redirs(char *token);

// function to add a redirection to the list
void	add_last_redir(t_fd **head, t_fd *new_redir);

// function to check and assign the redirection type
int assign_redir_type(char *str);

// function to assign the redirection file
void assign_redir_file(t_fd *redir, char *str);

// function to create a new redirection
t_fd *create_redir(char *str);

// function to assemble all the redirections
t_fd *assemble_redirs(char **redirs);







#endif
