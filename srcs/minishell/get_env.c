/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 01:52:30 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/01 06:30:30 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmp_env(char *env, char *key)
{
	int	i;

	i = -1;
	while (env[++i] != '=' || key[i])
		if (env[i] != key[i])
			return (env[i] - key[i]);
	return (0);
}

char	*get_env(char **env, char *s)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (cmp_env(env[i], s) == 0)
			return (ft_strchr(env[i], '=') + 1);
	}
	return (NULL);
}

char	**env(char **env)
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

