#include "../../includes/minishell.h"

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	value;

	i = 0;
	value = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		value = value * 10 + str[i] - 48;
		i++;
	}
	return (value * (long long)sign);
}
