/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:55:58 by tmalless          #+#    #+#             */
/*   Updated: 2023/05/02 14:01:37 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"
#include "../../includes/minishell.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int	ft_strlen(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_strncmp(const char *s1, const char *s2, int n);

int	looking_for_a_star(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '*')
			count++;
		i++;
	}
	printf("d\n");
	return (count);
}

char	**add_dir(char *s, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	tab[i] = s;
	return (tab);
}

char	**fill_motif(char *cmd, char **motif, int m_count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i] == '*')
		i++;
	while (k < m_count)
	{
		j = i;
		while (cmd[i] != '*')
			i++;
		motif[k] = ft_substr(cmd, j, i - j);
		printf("mot: %s\n", motif[k]);
		k++;
		while (cmd[i] == '*')
			i++;
	}
	return (motif);
}

char	**create_motif(char *cmd, char **motif)
{
	int	i;
	int	m_count;

	i = 0;
	m_count = 0;
	while (cmd[i])
	{
		while (cmd[i] == '*')
			i++;
		if (cmd[i])
			m_count++;
		else
			break ;
		while (cmd[i] && cmd[i] != '*')
			i++;
	}
	motif = ft_calloc(sizeof(char *), m_count + 1);
	return (fill_motif(cmd, motif, m_count));
}

int	motif_size(char **motif)
{
	int i;

	i = 0;
	if (!motif)
		return (0);
	while (motif[i])
		i++;
	return (i);
}

int	corresponding_dir(char *dir, char **motif, int stars)
{
	int		i;
	int		j;
	char	*k;

	i = 0;
	j = 0;
	if (!motif)
		return (1);
	if ((stars == 0 || stars == 2) && motif[0])
	{
		if (ft_strncmp(motif[0], dir, ft_strlen(motif[0])) != 0)
			return (0);
		else
		{
			i = ft_strlen(motif[0]) - 1;
			j = 1;
		}
	}
	while (j < motif_size(motif))
	{
		if (j == motif_size(motif) - 1 && (stars == 0 || stars == 1))
		{
			if (ft_strncmp(motif[motif_size(motif) - 1], &dir[ft_strlen(dir) - ft_strlen(motif[motif_size(motif) - 1])], ft_strlen(motif[motif_size(motif) - 1])) != 0)
				return (0);
			else
				return (1);
		}
		else
		{
			k = ft_strnstr(&dir[i], motif[j], ft_strlen(dir) - i);
			if (!k)
				return (0);
			else
			{
				dir = k + ft_strlen(motif[j]);
				j++;
				i = 0;
			}
		}
	}
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**wild_carder(char *cmd)
{
	struct dirent	*lecture;
	DIR				*rep;
	char			**ans;
	char			**motif;
	int				stars;
	static int				d_number = 0;

	motif = NULL;
	rep = NULL;
	motif = create_motif(cmd, motif);
	rep = opendir(".");
	if (!rep)
		printf("ca marche pas zbi \n");
	ans = ft_calloc(sizeof(char *), 4096);
	if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] != '*')
		stars = 0;
	else if (cmd[0] == '*' && cmd[ft_strlen(cmd) - 1] != '*')
		stars = 1;
	else if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] == '*')
		stars = 2;
	else
		stars = 3;
	lecture = readdir(rep);
	while (lecture)
	{
		long pos = telldir(rep);
		printf("ici meme : %ld\n", pos);
		if (d_number > 4095)
			break ;
		if (corresponding_dir(lecture->d_name, motif, stars))
		{
			add_dir(lecture->d_name, ans);
			d_number++;
		}
		//free(lecture);
		lecture = readdir(rep);
	}
	//int v = closedir(rep);
	//printf("Klose %d\n", v);
	free_tab(motif);
	return (ans);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**wild_card(char **cmds)
{
	int	i;
	int	j;
	int	k;
	int n;
	char **new_cmd;
	char **old_cmd;
	char **dirs;

	i = -1;
	old_cmd = cmds;
	while (old_cmd[++i])
	{
		j = 0;
		k = 0;
		if (old_cmd[i] && ft_strchr(old_cmd[i], '*'))
		{
			dirs = wild_carder(old_cmd[i]);
			new_cmd = ft_calloc(tab_size(dirs) + tab_size(old_cmd), sizeof(char *));
			printf("dirdir : %s\n", dirs[0]);
			while (j < i)
			{
				new_cmd[j] = old_cmd[j];
				j++;
			}
			printf("le d n'a pas fini de faire parler de lui ! %d\n", k);
			while (dirs[k])
			{
				new_cmd[j] = dirs[k];
				printf("Deontay : %s\n", new_cmd[j]);
				k++;
				j++;
			}
			n = i + 1;
			while (old_cmd[n])
			{
				new_cmd[j] = old_cmd[n];
				printf("new_c : %s\n", new_cmd[j]);
				j++;
				n++;
			}
			free(old_cmd);
			old_cmd = new_cmd;
			//free(dirs);
			//free(new_cmd);
		}
	}
	int t = -1;
	while (old_cmd[++t])
		printf("c la nouvelle commande ca : %s\n", old_cmd[t]);
	return (old_cmd);
}

/* int main(int ac, char **av)
{
	char	**s;
	
	printf("%s\n", av[1]);
	s = wild_carder(av[1], 0, 0, 0);
	int i = 0;
	while (s[i])
	{
		printf("%d : %s\n", i, s[i]);
		i++;
	}
	free(s);
	return (0);
} */