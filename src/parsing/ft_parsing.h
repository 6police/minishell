#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "../minishell.h"

// parsing

// parsing the line into tokens
void parse_line(t_shell *shell, int *char_set, int sub);

// parsing to make tokens so we can later parse the tokens into commands
void parse_tokens(t_shell *shell);

// parse the line and tokens
void parse(t_shell *shell, int debug);


// count the number of quotes
int count_quotes(char *line);

// mark a character in the line and switch for another
void mark_and_replace(char *line, int *char_set, int sub);

// split the line into tokens
char **ft_parse_split(char *line, int *char_set, int sub);

#endif