/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:12:24 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/14 22:12:36 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_cdir(void)
{
	int		index;
	char	*dir;
	char	buf[BUFFER_SIZE];

	if (getcwd(buf, BUFFER_SIZE) == 0)
		return (NULL);
	index = last_index(buf, '/');
	dir = malloc(sizeof(char) * (ft_strlen(buf) - index + 1));
	if (!dir)
		return (NULL);
	ft_strcpy(dir, buf + index + 1, ft_strlen(buf) - index + 1);
	return (dir);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*dir;

	dir = get_cdir();
	if (!dir)
		return (NULL);
	prompt = ft_stradd(ft_strcat("→  ", dir), " ");
	free(dir);
	return (prompt);
}
