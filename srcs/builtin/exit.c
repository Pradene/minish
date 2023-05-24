/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:56:23 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/17 20:56:24 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	count(long long n)
{
	int	c;
	int	d;

	d = 1;
	c = 0;
	if (n < 0)
		c++;
	while (n || d == 1)
	{
		d = 0;
		n /= 10;
		c++;
	}
	return (c);
}

char	*itoll(long long n)
{
	int		c;
	char	*str;
	int		d;

	d = 1;
	c = count(n);
	str = malloc(sizeof(char) * (c + 1));
	if (!str)
		return (0);
	str[c] = '\0';
	if (n < 0)
		*str = '-';
	while (n || d == 1)
	{
		d = 0;
		c--;
		str[c] = absolute(n % 10) + 48;
		n /= 10;
	}
	return (str);
}

int	intcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1[i] == '+')
		i += 1;
	if (s2[j] == '+')
		j += 1;
	while (s1[i] || s2[j])
	{
		if (s1[i] != s2[j])
			return (1);
		i += 1;
		j += 1;
	}
	return (0);
}

void	ex(t_data *data, t_node *node)
{
	long long	n;
	char		*s;

	if (node->fd_in != -1 || node->fd_out != -1)
		return ;
	if (dsize(node->cmd) > 2)
		return (g_exit = 1, prerror("exit: too many arguments\n"));
	printf("exit\n");
	if (node->cmd[1])
	{
		n = atoll(node->cmd[1]);
		s = itoll(n);
		if (intcmp(s, node->cmd[1]))
		{
			write(2, node->cmd[1], ft_strlen(node->cmd[1]));
			prerror(": numeric argument required\n");
			(free_data(data), free(s));
			exit(2);
		}
		(free_data(data), free(s));
		exit(n % 256);
	}
	free_data(data);
	exit(0);
}
