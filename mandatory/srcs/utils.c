/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:39:01 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/11 17:45:25 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*temp;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH", 4))
			break ;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ":");
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
	return (NULL);
}
