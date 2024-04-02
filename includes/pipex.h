/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:01 by mvpee             #+#    #+#             */
/*   Updated: 2024/04/02 12:37:41 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../srcs/libft/includes/libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHITW "\x1B[37m"
# define RESET "\x1B[0m"

# define COMMAND_NOT_FOUND 127
# define REDIRECTION_FAILURE 1

typedef struct s_pipex_data
{
	char	*cmd;
	char	*cmd2;
	char	**s_cmd;
	char	**s_cmd2;
	int		input;
	int		output;
}			t_data;

/* Init functions */
void		init(t_data *data, char **av, char **env);

/* Exit functions */
void		ft_exit(t_data *data, char *message, int type);

/* Find the path of the command */
char		*find_path(char **env, char *cmd);

#endif