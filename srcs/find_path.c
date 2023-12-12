/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:53:22 by mvan-pee          #+#    #+#             */
/*   Updated: 2023/12/12 13:00:34 by mvan-pee         ###   ########.fr       */
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

char	*find_path(char **env, char *cmd)
{
	char	**paths;
	char	*executable_path;

	paths = get_paths_from_env(env);
	executable_path = find_executable_path(paths, cmd);
	return (executable_path);
}
