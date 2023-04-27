/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:34:24 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/05 19:21:23 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_data *data, t_node *node)
{
	int	i;

	(void)node;
	if (!data->env)
		return ;
	i = -1;
	while (data->env[++i])
		printf("%s \n", data->env[i]);
}
