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

// function to mark and switch a set of characters in the line for another
void mark_and_replace(char *line, int *char_set, int sub)
{
    int i;
    int j;

    i = -1;
    j = -1;
    while (char_set[++i])
    {
        while (line[++j])
        {
            if (line[j] == char_set[i])
                line[j] = sub;
        }
        j = -1;
    }
    // {
    //     if ((line[i] == '\'' || line[i] == '\"') && !c)
    //         c = line[i];
    //     else if (c && line[i] == c)
    //         c = 0;
    //     else if (line[i] == ' ' && !c)
    //         line[i] = sub;
    // }
}

// ok so now we must split tokens in order of priority
// first is the ; -> takes precedence over all
// then the | -> takes precedence over the rest


// function to split the line into tokens
//char **ft_parse_split(char *line)
//{
//    if (!line)
//        return (NULL);
//    if (count_quotes(line) != 0)
//        return (ft_printf_fd(2, "Error: Odd number of quotes\n"), NULL);
//    return (mark_quotes(line), ft_split(line, 7)); // split the line into tokens
//}

char **ft_parse_split (char *line, int *char_set, int sub)
{
    if (!line)
        return (NULL);
    if (count_quotes(line) != 0)
        return (ft_printf_fd(2, "Error: Odd number of quotes\n"), NULL);
    mark_and_replace(line, char_set, sub);
    printf("line: %s\n", line);
    return (ft_split(line, sub));
}