/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:39:01 by mvpee             #+#    #+#             */
/*   Updated: 2024/04/02 12:37:52 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_struct(t_data *data, char **av)
{
	data->s_cmd = NULL;
	data->s_cmd2 = NULL;
	data->cmd = NULL;
	data->cmd2 = NULL;
	data->input = -1;
	data->output = -1;
	data->input = open(av[1], O_RDONLY);
	if (data->input == -1)
	{
		perror(av[1]);
		ft_exit(data, "", REDIRECTION_FAILURE);
	}
	data->output = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->output == -1)
	{
		perror(av[4]);
		ft_exit(data, "", REDIRECTION_FAILURE);
	}
}

void	init(t_data *data, char **av, char **env)
{
	init_struct(data, av);
	data->s_cmd = ft_split(av[2], " ");
	if (!data->s_cmd)
		ft_exit(data, RED "E-02.2\nSplit1 Fail...\n" RESET, EXIT_FAILURE);
	data->s_cmd2 = ft_split(av[3], " ");
	if (!data->s_cmd2)
		ft_exit(data, RED "E-02.2\nSplit2 Fail...\n" RESET, EXIT_FAILURE);
	data->cmd = find_path(env, data->s_cmd[0]);
	if (!data->cmd)
	{
		ft_printf("%s: command not found\n", data->s_cmd[0]);
		ft_exit(data, "", COMMAND_NOT_FOUND);
	}
	data->cmd2 = find_path(env, data->s_cmd2[0]);
	if (!data->cmd2)
	{
		ft_printf("%s: command not found\n", data->s_cmd2[0]);
		ft_exit(data, "", COMMAND_NOT_FOUND);
	}
}

void	ft_exit(t_data *data, char *message, int type)
{
	ft_free_matrix(2, &data->s_cmd, &data->s_cmd2);
	ft_free(2, &data->cmd, &data->cmd2);
	if (data->input)
		close(data->input);
	if (data->output)
		close(data->output);
	ft_printf_fd(2, "%s", message);
	exit(type);
}
