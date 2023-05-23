/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:09:53 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/23 15:23:57 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit = 0;

void	sig_handler2(int sig)
{
	t_data	*data;
	char	**tab;

	tab = ft_calloc(2, sizeof(char *));
	tab[0] = "minishell5";
	tab[1] = 0;
	data = singleton(NULL);
	(void)sig;
	if (!data)
		return ;
	if (data->exec)
	{
		printf("Quit (core dumped)\n");
		execve("/mnt/nfs/homes/tmalless/Documents/minishell5", tab, data->env);
		exit(131);
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		exit(EXIT_FAILURE);
	data.env = envcp(envp);
	data.root = NULL;
	data.exec = 0;
	set_attribute();
	signal(SIGQUIT, sig_handler2);
	signal(SIGINT, sig_handler);
	singleton(&data);
	while (1)
		get_cmd(&data);
	return (0);
}
