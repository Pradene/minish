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

static int	get_index(char *src)
{
	int		index;
	char	*tmp;

	tmp = ft_strchr(src, '=');
	if (!tmp)
		index = ft_strlen(src);
	else
		index = tmp - src;
	return (index);
}

static int	sscpy(char **dst, char **src, char **cmd)
{
	int		i;
	int		j;
	int		index;
	char	*key;

	i = -1;
	j = -1;
	while (src[++i])
	{
		index = get_index(src[i]);
		key = ft_strndup(src[i], index);
		if (cmp_envs(cmd, key))
		{
			free(key);
			continue ;
		}
		free(key);
		dst[++j] = ft_strdup(src[i]);
		if (!dst[j])
			return (1);
	}
	dst[++j] = NULL;
	return (0);
}

static int	addtoenv(char **dst, char **src)
{
	int	i;
	int	size;
	int	exit;

	size = dsize(dst);
	i = 0;
	exit = 0;
	while (src[++i])
	{
		if (!export_arg(src[i]))
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

static int	env_count(t_data *data, char **cmd)
{
	int		i;
	int		count;
	int		index;
	char	*key;
	char	*tmp;

	i = -1;
	count = 0;
	while (cmd[++i])
	{
		tmp = ft_strchr(cmd[i], '=');
		if (!tmp)
			index = ft_strlen(cmd[i]);
		else
			index = tmp - cmd[i];
		key = ft_strndup(cmd[i], index);
		count += cmp_envs(data->env, key);
		free(key);
	}
	return (count);
}

char	**export(t_data *data, t_node *node)
{
	int		c1;
	int		c2;
	int		count;
	char	**e;

	e = NULL;
	if (!node->cmd[1])
		return (print_export(data->env), data->env);
	c1 = dsize(data->env);
	c2 = dsize(&node->cmd[1]);
	count = env_count(data, &node->cmd[1]);
	e = malloc(sizeof(char *) * (c1 + c2 - count + 1));
	if (!e)
		return (data->env);
	e[c1 + c2 - count] = NULL;
	if (sscpy(e, data->env, &node->cmd[1]))
		return (dfree(e), data->env);
	g_exit = 0;
	if (addtoenv(e, node->cmd))
		return (dfree(e), data->env);
	dfree(data->env);
	return (e);
}
