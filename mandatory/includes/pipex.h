/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:01 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/11 20:06:02 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/includes/libft.h"
# include <stdio.h>
# include <sys/wait.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHITW "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct s_pipex_data
{
	char	*cmd;
	char	*pipe;
	int		input;
	int		output;
}			t_data;

char		*find_path(char **env, char *cmd);

#endif