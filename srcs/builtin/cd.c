/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 01:55:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/28 01:55:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_env(char **env, char *key, char *nvalue)
{
	int		i;
	char	*s;

	i = -1;
	while (env[++i])
	{
		if (cmp_env(env[i], key) == 0)
		{
			s = ft_stradd(ft_strcat(key, "="), nvalue);
			if (!s)
				return ;
			free(env[i]);
			env[i] = s;
		}
	}
}

void	cd(char **env, char *path)
{
	char	old_pwd[BUFFER_SIZE];
	char	pwd[BUFFER_SIZE];

	if (getcwd(old_pwd, BUFFER_SIZE) == NULL)
		return ;
	if (chdir(path) == -1)
		perror(path);
	if (getcwd(pwd, BUFFER_SIZE) == NULL)
		return ;
	change_env(env, "OLDPWD", old_pwd);
	change_env(env, "PWD", pwd);
}
