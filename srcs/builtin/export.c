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
		{
			printf("\n");
			continue ;
		}
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

int	sscpy(char **dst, char **src)
{
	int	i;

	i = -1;
	while (src[++i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (1);
	}
	dst[i] = NULL;
	return (0);
}

int	addtoenv(char **dst, char **src)
{
	int	i;
	int	size;
	int	exit;

	size = dsize(dst);
	i = 0;
	exit = 0;
	while (src[++i])
	{
		if (!check_arg(src[i]))
		{
			dst[size + i - exit - 1] = ft_strdup(src[i]);
			if (!dst[size + i - exit - 1])
				return (1);
		}
		else
		{
			write(2, src[i], ft_strlen(src[i]));
			prerror(": not a valid identifier\n");
			g_exit = 1;
			exit += 1;
		}
	}
	dst[size + i - exit - 1] = NULL;
	return (0);
}

char	**export(t_data *data, t_node *node)
{
	int		c1;
	int		c2;
	char	**e;

	e = NULL;
	if (!node->cmd[1])
		return (handle_export(data->env), data->env);
	c1 = dsize(data->env);
	c2 = dsize(node->cmd) - 1;
	e = malloc(sizeof(char *) * (c1 + c2 + 1));
	if (!e)
		return (data->env);
	if (sscpy(e, data->env))
		return (dfree(e), data->env);
	g_exit = 0;
	if (addtoenv(e, node->cmd))
		return (dfree(e), data->env);
	dfree(data->env);
	return (e);
}
