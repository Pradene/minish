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

static void	go_home(t_data *data)
{
	char	*tmp;

	tmp = get_env(data->env, "HOME");
	if (!tmp)
	{
		write(2, "HOME not set\n", 13);
		return ;
	}
	if (chdir(tmp) == -1)
	{
		perror(tmp);
		g_exit = 1;
	}
}

void	cd(t_data *data, t_node *node)
{
	char	old_pwd[BUFFER_SIZE];
	char	pwd[BUFFER_SIZE];

	if (dsize(node->cmd) > 2)
	{
		prerror("cd: too many arguments\n");
		g_exit = 1;
		return ;
	}
	if (!node->cmd[1])
		return (go_home(data));
	if (!getcwd(old_pwd, BUFFER_SIZE))
		return ;
	if (chdir(node->cmd[1]) == -1)
	{
		perror(node->cmd[1]);
		g_exit = 1;
		return ;
	}
	if (!getcwd(pwd, BUFFER_SIZE))
		return ;
	change_env(data->env, "OLDPWD", old_pwd);
	change_env(data->env, "PWD", pwd);
	g_exit = 0;
}
