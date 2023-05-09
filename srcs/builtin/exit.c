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

void	ex(t_node *node)
{
	printf("exit\n");
	if (get_size(node->cmd) > 2)
	{
		prerror("exit: too many arguments\n");
		g_exit = 1;
		return ;
	}
	if (node->cmd[1])
		exit(atoi(node->cmd[1]));
	exit(0);
}
