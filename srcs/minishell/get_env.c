/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 01:52:30 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/05 17:56:23 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmp_env(char *env, char *key)
{
	int	i;

	i = -1;
	while (env[++i] || key[i])
	{
		if (env[i] == '=' && !key[i])
			break ;
		else if (env[i] != key[i])
			return (env[i] - key[i]);
	}
	return (0);
}

int	cmp_envs(char **src, char *key)
{
	int	i;

	i = -1;
	while (src[++i])
	{
		if (!cmp_env(src[i], key))
			return (1);
	}
	return (0);
}

char	*get_env(char **env, char *s)
{
	int	i;

	if (!env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (cmp_env(env[i], s) == 0 && strchr(env[i], '='))
			return (ft_strchr(env[i], '=') + 1);
	}
	return (NULL);
}

char	**envcp(char **env)
{
	int		c;
	char	**envp;

	c = 0;
	while (env[c])
		++c;
	envp = malloc(sizeof(char *) * (c + 1));
	if (!envp)
		return (NULL);
	envp[c] = NULL;
	c = -1;
	while (env[++c])
	{
		envp[c] = ft_strdup(env[c]);
		if (!envp[c])
		{
			while (--c)
				free(envp[c]);
			free(envp);
		}
	}
	return (envp);
}
