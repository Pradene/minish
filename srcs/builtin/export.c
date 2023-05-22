/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:34:43 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/10 15:56:32 by tmalless         ###   ########.fr       */
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
		while (env[i][++j] && env[i][j] != '=')
			printf("%c", env[i][j]);
		if (!env[i][j])
			continue ;
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
	while (arg[++i] && arg[i] != '=')
		if (!isalpha(arg[i]))
			return (1);
	if (!arg[i])
		return (0);
	i += 1;
	if (!arg[i])
		return (1);
	return (0);
}

int	sscpy(char **dest, char **src)
{
	int	i;

	i = -1;
	while (src[++i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (1);
	}
	return (0);
}

char	**export(t_data *data, t_node *node)
{
	int		c1;
	int		c2;
	int		i;
	char	**e;

	if (!node->cmd[1])
		return (handle_export(data->env), data->env);
	c1 = dsize(data->env);
	c2 = dsize(node->cmd) - 1;
	e = malloc(sizeof(char *) * (c1 + c2 + 1));
	if (!e)
		return (data->env);
	e[c1 + c2] = NULL;
	if (sscpy(e, data->env))
		return (free(e), data->env);
	i = 0;
	while (node->cmd[++i])
	{
		if (!check_arg(node->cmd[i]))
		{
			e[c1 + i - 1] = ft_strdup(node->cmd[i]);
			if (!e[c1 + i - 1])
				return (dfree(e), data->env);
		}
		else
		{
			write(2, node->cmd[i], ft_strlen(node->cmd[i]));
			prerror(": not a valid identifier\n");
			g_exit = 1;
			return (free(e), data->env);
		}
	}
	dfree(data->env);
	g_exit = 0;
	return (e);
}
