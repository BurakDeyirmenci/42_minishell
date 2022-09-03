/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acalayir <acalayir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:52:50 by rdeyirme          #+#    #+#             */
/*   Updated: 2022/09/03 14:27:05 by acalayir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(char **env)
{
	int	i;
	int	env_length;

	g_data->infd = dup(STDIN);
	g_data->outfd = dup(STDOUT);
	g_data->keep = 1;
	i = -1;
	while (env[++i] != NULL)
	env_length = i;
	g_data->env_p = (char **)malloc(sizeof(char *) * env_length);
	i = -1;
	while (++i < env_length)
		g_data->env_p[i] = ft_strdup(env[i]);
	siginit();
}

char	*get_env(char *env_key)
{
	int	i;

	if (ft_strcmp(env_key, "?") == 0)
	{
		free(env_key);
		return (join(ft_strdup("?="), ft_itoa(g_data->last_pid)));
	}
	i = -1;
	while (g_data->env_p[++i])
	{
		if (!ft_strncmp(g_data->env_p[i], env_key, ft_strlen(env_key)))
		{
			free(env_key);
			return (g_data->env_p[i]);
		}
	}
	free(env_key);
	return (0);
}

int	set_env(char *env_key, char *env_value)
{
	int	i;

	i = -1;
	if (!env_value || !env_value[0])
		env_value = "";
	while (g_data->env_p[++i])
	{
		if (!ft_strncmp(g_data->env_p[i], env_key, ft_strlen(env_key)))
		{
			env_key = join(env_key, ft_strdup("="));
			env_key = join(env_key, ft_strdup(env_value));
			free(g_data->env_p[i]);
			g_data->env_p[i] = ft_strdup(env_key);
			free(env_key);
			return (0);
		}
	}
	i--;
	env_key = join(env_key, ft_strdup("="));
	env_key = join(env_key, ft_strdup(env_value));
	free(g_data->env_p[i]);
	g_data->env_p[i] = ft_strdup(env_key);
	free(env_key);
	return (0);
}

int	unset_env(char *tmp)
{
	int		i;
	char	*env_key;

	if (ft_strchr(tmp, '='))
	{	
		printf("invalid parameter name\n");
		return (1);
	}
	env_key = ft_strjoin(tmp, "=");
	i = -1;
	while (g_data->env_p[++i])
	{
		if (!ft_strncmp(g_data->env_p[i], env_key, ft_strlen(env_key)))
		{
			free(g_data->env_p[i]);
			g_data->env_p[i] = g_data->env_p[i + 1];
			while (g_data->env_p[i])
			{
				g_data->env_p[i] = g_data->env_p[i + 1];
				i++;
			}
		}
	}
	free(env_key);
	return (0);
}

void	kill_processes(void)
{
	while (g_data->cmd)
	{
		kill(SIGINT, g_data->cmd->pid);
		g_data->cmd = g_data->cmd->next;
	}
}
