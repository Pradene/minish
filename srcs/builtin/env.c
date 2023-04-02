/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:34:24 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/26 23:34:25 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s \n", env[i]);
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
