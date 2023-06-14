/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:52:03 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/14 15:52:04 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_nfound(t_data *data, char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	prerror(" : command not found\n");
	free_data(data);
	exit(127);
}

void	access_error(t_data *data, char *path, char *cmd, int ex)
{
	perror(cmd);
	free_data(data);
	free(path);
	exit(ex);
}

void	path_isdir(t_data *data, char *path, DIR *dir)
{
	write(2, path, ft_strlen(path));
	prerror(" : Is a directory\n");
	free_data(data);
	closedir(dir);
	free(path);
	exit(126);
}
