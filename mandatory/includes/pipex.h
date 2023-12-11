/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:01 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/11 17:54:40 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/includes/libft.h"
# include <unistd.h>

typedef struct s_pipex_data
{
	char	*path;
	int		input;
	int		output;
}			t_data;

char		*find_path(char **env, char *cmd);

#endif