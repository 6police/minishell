#include "ft_parsing.h"

// function to count the number of quotes
int count_quotes(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if ((line[i] == '\'' || line[i] == '\"') && !count)
            count = line[i];
        else if (count && line[i] == count)
            count = 0;
        i++;
    }
    return (count);
}

// function to handle quotes and double quotes
// split the line into tokens
// if there is a quote or double quote then the token should be everything inside the quotes
// if there is a space inside the quotes then it should be considered part of the token
// if theres quotes inside quotes then it should be considered part of the token
//

void mark_quotes(char *line)
{
    int i;
    int c;

    i = -1;
    c = 0;
    while (line[++i])
    {
        if ((line[i] == '\'' || line[i] == '\"') && !c)
            c = line[i];
        else if (c && line[i] == c)
            c = 0;
        else if (line[i] == ' ' && !c)
            line[i] = 7;
    }
}

    // split the line into tokens
// need to use split but take into consideration the quotes and double quotes
// if there is a quote or double quote then the token should be everything inside the quotes
// if there is a space inside the quotes then it should be considered part of the token
// if theres quotes inside quotes then it should be considered part of the token
char **ft_parse_split(char *line)
{
    if (!line)
        return (NULL);
    if (count_quotes(line) != 0)
        return (ft_printf_fd(2, "Error: Odd number of quotes\n"), NULL);
    return (mark_quotes(line), ft_split(line, 7)); // split the line into tokens
}