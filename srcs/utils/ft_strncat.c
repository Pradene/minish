#include "../../includes/minishell.h"

char	*ft_strncat(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		++i;
	j = -1;
	while (++j < n)
		s1[i + j] = s2[j];
	return (s1);
}
