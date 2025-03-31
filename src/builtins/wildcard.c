#include "ft_builtins.h"

static int	check_wildcard_type(char *str);
static bool	is_there_quotes(char *str);


bool	check_wildcard(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '*')
			return (true);
	}
	return (false);
}

void	do_wildcard(char *arg)
{
	int	a;
	
	a = 0;
	if (is_there_quotes(arg) == true)
		return ;
	a = check_wildcard_type(arg);
	do_echo(arg, a);
}

static bool	is_there_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
			return (true);
	}
	return (false);
}

static int	check_wildcard_type(char *str)
{
	int	wild_card_type;

	wild_card_type = 0;
	// * .* *. *.* '\"'
	if (str[0] == '*' && !str[1]) // *
		wild_card_type = 1;
	else if (str[0] == '*' && str[1] != '\0') // *.
		wild_card_type = 2;
	else if (str[0] != '\0' && str[ft_strlen(str) - 1] == '*') // .*
		wild_card_type = 3;
	else if (str[0] == '*' && str[ft_strlen(str) - 1] == '*') // *.*
		wild_card_type = 4;
	return (wild_card_type);
}