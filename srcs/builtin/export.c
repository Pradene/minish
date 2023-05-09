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

	i = -1;
	while (env[++i])
	{
		j = -1;
		printf("declare -x ");
		while (env[i][++j] != '=')
			printf("%c", env[i][j]);
		printf("=\"");
		while (env[i][++j])
			printf("%c", env[i][j]);
		printf("\"\n");
	}
}

int	check_arg(char *arg)
{
	int	i;

	i = -1;
	if (isdigit(arg[0]))
		return (1);
	while (arg[++i] && arg[i] != '=')
		continue ;
	if (!arg[i])
		return (1);
	i += 1;
	if (!arg[i])
		return (1);
	return (0);
}

char	**export(t_data *data, t_node *node)
{
	int		c;
	char	**e;

	if (!node->cmd[1])
		return (handle_export(data->env), data->env);
	c = -1;
	while (data->env[++c])
		continue ;
	e = malloc(sizeof(char *) * (c + get_size(node->cmd)));
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
