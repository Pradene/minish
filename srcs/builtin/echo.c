/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:57:11 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/17 20:57:12 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_options(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 0;
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

void	echo(t_node *node)
{
	int		i;
	int		fd;
	int		newline;
	int		options;

	i = 0;
	fd = STDOUT_FILENO;
	if (node->fd_out != -1)
		fd = node->fd_out;
	newline = 0;
	options = 0;
	if (node->cmd[1])
		newline = check_options(node->cmd[1]);
	while (node->cmd[++i])
	{
		if (!options && check_options(node->cmd[i]))
			continue ;
		options = 1;
		write(fd, node->cmd[i], ft_strlen(node->cmd[i]));
		if (node->cmd[i + 1])
			write(fd, " ", 1);
	}
	if (!newline)
		write(fd, "\n", 1);
	g_exit = 0;
}
