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

void	echo(t_data *data, t_node *node)
{
	int	i;
	int	n;

	(void)data;
	n = 0;
	i = 1;
	if (node->cmd[i] && !strncmp(node->cmd[i++], "-n", 2))
		n = 1;
	else if (i > 1)
		i -= 1;
	while (node->cmd[i])
	{
		printf("%s", node->cmd[i]);
		i += 1;
		if (node->cmd[i])
			printf(" ");
	}
	if (!n)
		printf("\n");
}
