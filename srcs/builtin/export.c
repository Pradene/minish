/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:34:43 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/05 18:00:46 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		printf("declare -x ");
		while (env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		printf("=\"");
		while (env[i][++j])
			printf("%c", env[i][j]);
		printf("\"\n");
		i++;
	}
}

char	**export(t_data *data, t_node *node)
{
	int		c;
	char	**e;

	c = -1;
	if (!node->cmd[1])
	{
		handle_export(data->env);
		return (data->env);
	}
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
