/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:34:43 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/26 23:34:47 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**export(t_data *data, t_node *node)
{
	int		c;
	char	**e;

	c = -1;
	while (data->env[++c])
		continue ;
	e = malloc(sizeof(char *) * (c + 1 + 1));
	if (!e)
		return (data->env);
	e[c + 1] = NULL;
	c = -1;
	while (data->env[++c])
	{
		e[c] = ft_strdup(data->env[c]);
		if (!e[c])
			return (d_free(e), data->env);
	}
	e[c] = ft_strdup(node->cmd[1]);
	if (!e[c])
		return (d_free(e), data->env);
	d_free(data->env);
	return (e);
}
