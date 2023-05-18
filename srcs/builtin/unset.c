/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:50:50 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/28 15:51:12 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	size_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		continue ;
	return (i);
}

static char	*find_env(char **env, char *key)
{
	int		i;

	i = -1;
	while (env[++i])
		if (cmp_env(env[i], key) == 0)
			return (env[i]);
	return (NULL);
}

char	**unset(t_data *data, t_node *node)
{
	int		i;
	int		j;
	int		size;
	char	**e;

	if (!node->cmd[1])
		return (data->env);
	if (find_env(data->env, node->cmd[1]) == NULL)
		return (data->env);
	size = size_env(data->env) - 1;
	e = malloc(sizeof(char *) * (size + 1));
	if (!e)
		return (data->env);
	e[size] = NULL;
	i = -1;
	j = -1;
	while (data->env[++i])
	{
		if (cmp_env(data->env[i], node->cmd[1]) == 0)
			continue ;
		e[++j] = ft_strdup(data->env[i]);
	}
	dfree(data->env);
	g_exit = 0;
	return (e);
}
