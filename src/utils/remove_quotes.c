#include "ft_utils.h"

char	*remove_quotes(char *arg)
{
	char	*new_str;

	if (!arg)
		return (NULL);
	if (arg[0] == '\"')
	{
		new_str = ft_strtrim(arg, "\"");
		free(arg); // Free the old arg
		return (new_str);
	}
	else if (arg[0] == '\'')
	{
		new_str = ft_strtrim(arg, "\'");
		free(arg); // Free the old arg
		return (new_str);
	} // Duplicate the string if no quotes
	 // Return the new string
	return (arg);
}

char *remove_all_quotes(char *arg)
{
	char *new_str;
	char *temp;

	if (!arg)
		return (NULL);
	new_str = ft_strdup(arg);
	if (!new_str)
		return (NULL);

	temp = new_str;
	while (*temp)
	{
		if (*temp == '\'' || *temp == '\"')
		{
			ft_memmove(temp, temp + 1, ft_strlen(temp)); // includes null byte
			continue; // don't decrement, just recheck current temp
		}
		temp++;
	}
	free(arg);
	return (new_str);
}
