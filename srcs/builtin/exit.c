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

void	ex(t_data *data, t_node *node)
{
	(void)data;
	printf("exit\n");
	if (get_size(node->cmd) > 2)
		exit(1);
	if (node->cmd[1])
		exit(atoi(node->cmd[1]));
	exit(0);
}
