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