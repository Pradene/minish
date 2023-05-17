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
	int		newline;
	int		options;
	char	**cmd;

	i = 0;
	newline = 0;
	options = 0;
	cmd = node->cmd;
	if (cmd[1])
		newline = check_options(cmd[1]);
	while (cmd[++i])
	{
		if (!options && check_options(cmd[i]))
			continue;
		options = 1;
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (!newline)
		printf("\n");
	g_exit = 0;
}
