#include "../../includes/minishell.h"

char	*addchar(char *s, char c)
{
	int		size;
	char	*new;

	size = ft_strlen(s);
	new = malloc(sizeof(char) * (size + 1 + 1));
	if (!new)
		return (s);
	memcpy(new, s, size);
	new[size] = c;
	new[size + 1] = '\0';
	if (s)
		free(s);
	return (new);
}
