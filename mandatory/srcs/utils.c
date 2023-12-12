/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:39:01 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/12 09:46:35 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**get_paths_from_env(char **env)
{
	int		i;
	char	**paths;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH", 4))
			break ;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ":");
	return (paths);
}

static char	*find_executable_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_split(1, &paths), NULL);
		path = ft_strjoin(temp, cmd);
		if (!path)
			return (ft_free_split(1, &paths), ft_free(1, &temp), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_split(1, &paths), ft_free(1, &temp), path);
		ft_free(2, &path, &temp);
	}
	ft_free_split(1, &paths);
	return (NULL);
}

static char	*find_path(char **env, char *cmd)
{
	char	**paths;
	char	*executable_path;

	paths = get_paths_from_env(env);
	executable_path = find_executable_path(paths, cmd);
	return (executable_path);
}

int	init(t_data *data, char **av, char **env)
{
	data->s_cmd = NULL;
	data->s_cmd2 = NULL;
	data->cmd = NULL;
	data->cmd2 = NULL;
	data->input = 0;
	data->output = 0;
	data->input = open(av[1], O_RDONLY);
	if (data->input == -1)
		return (ft_printf_fd(2, RED "E-02.0:\nInvalid input...\n" RESET), 1);
	data->output = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	data->s_cmd = ft_split(av[2], " ");
	if (!data->s_cmd)
		return (ft_printf_fd(2, RED "E-02.1:\nSplit Fail...\n" RESET), 1);
	data->s_cmd2 = ft_split(av[3], " ");
	if (!data->s_cmd2)
		return (ft_printf_fd(2, RED "E-02.2\nSplit2 Fail...\n" RESET), 1);
	data->cmd = find_path(env, data->s_cmd[0]);
	if (!data->cmd)
		return (ft_printf_fd(2, RED "E-02.3:\nCMD fail...\n" RESET), 1);
	data->cmd2 = find_path(env, data->s_cmd2[0]);
	if (!data->cmd2)
		return (ft_printf_fd(2, RED "E-02.4:\nCMD2 fail...\n" RESET), 1);
	return (0);
}

void	ft_exit(t_data *data, char *message, int type)
{
	ft_free_split(2, &data->s_cmd, &data->s_cmd2);
	ft_free(2, &data->cmd, &data->cmd2);
	if (data->input)
		close(data->input);
	if (data->output)
		close(data->output);
	ft_printf_fd(2, "%s\n", message);
	exit(type);
}
