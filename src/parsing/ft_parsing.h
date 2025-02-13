#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "../minishell.h"

// parsing

// parsing the line into tokens
void parse_line(t_shell *shell);

// parsing to make tokens so we can later parse the tokens into commands
void parse_tokens(t_shell *shell);

// parse the line and tokens
void parse(t_shell *shell, int debug);

// look for quotes
int look_for_quotes(char *line);

// count the number of quotes
int count_quotes(char *line);

// split the line with quotes
char **split_with_quotes(char *line);

// split the line into tokens
char **ft_parse_split(char *line);

#endif