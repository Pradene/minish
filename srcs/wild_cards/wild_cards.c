/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:55:58 by tmalless          #+#    #+#             */
/*   Updated: 2023/04/04 16:58:40 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int	ft_strlen(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);

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

char	**wild_carder(char *cmd, int i, int j, int k)
{
	struct dirent	*lecture;
	DIR				*rep;
	char			**ans;
	char			*motif;
	int				stars_count;

	rep = opendir(".");
	stars_count = looking_for_a_star(cmd);
	ans = malloc(sizeof(char *) * 4096);
	while (k < stars_count)
	{
		j = i;
		while (cmd[i] != '*')
			i++;
		motif = ft_substr(cmd, j, i - j);
		lecture = readdir(rep);
		while (lecture)
		{
			if (ft_strnstr(lecture->d_name, motif, ft_strlen(lecture->d_name)))
			{
				add_dir(lecture->d_name, ans);
			}
			lecture = readdir(rep);
		}
		k++;
	}
	return (ans);
}

int main(int ac, char **av)
{
	char **s;
	printf("%s\n", av[1]);
	s = wild_carder(av[1], 0, 0, 0);
	int i = 0;
	while (s[i])
	{
		printf("%d : %s\n", i, s[i]);
		i++;
	}
	return (0);
}