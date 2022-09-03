/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:52:07 by rdeyirme          #+#    #+#             */
/*   Updated: 2022/09/01 10:52:07 by rdeyirme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_quit(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
}

int	line_check(char *line)
{
	if (!line)
		exit(0);
	if (!line[0])
	{
		free(line);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_command	*command;

	(void)argc;
	(void)argv;
	g_data = (t_data *)malloc(sizeof(t_data));
	init(env);
	while (1)
	{
		line = readline("\033[1;32m Minishell>\033[0m");
		if (!line_check(line))
			continue ;
		add_history(line);
		signal(SIGQUIT, main_quit);
		command = tokenize_input(line);
		g_data->keep = 0;
		execute_command(command, g_data->env_p);
		g_data->keep = 1;
		signal(SIGQUIT, SIG_IGN);
		del_elem(command);
	}
	return (0);
}
