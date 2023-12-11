/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:38 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/12 00:33:35 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void parent_process(t_data *data, int *fd, char **env)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(data->output, STDOUT_FILENO);
	if (execve(data->cmd2, data->s_cmd2, env) == -1)
		ft_exit(data, "execve parent", EXIT_FAILURE);
}

static void child_process(t_data *data, int *fd, char **env)
{
	close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
	dup2(data->input, STDIN_FILENO);
    close(fd[1]);
    if (execve(data->cmd, data->s_cmd, env) == -1)
		ft_exit(data, "execve child", EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
    t_data data;
	int fd[2];
	pid_t pid;

	// Arg check
	if (ac != 5)
		return (ft_printf_fd(2, RED "E-01:\nNumber(s) of args is invalid...\n" RESET), 1);
	if (arg_check(&data, av, env))
		return (2);

	// Unit Test
    ft_printf(GREEN "\nCMD: %s\nPIPE: %s\n\n" RESET, data.cmd, data.cmd2);
	
	// Process
    if (pipe(fd) == -1)
		return (ft_free(2, &data.cmd, &data.cmd2), ft_printf_fd(2, RED "E-03.1:\nPIPE fail...\n" RESET), 3);
    pid = fork();
	if (pid == -1)
		return (ft_free(2, &data.cmd, &data.cmd2), ft_printf_fd(2, RED "E-04:\nFork fail...\n" RESET), 4);
	if (pid == 0)
		child_process(&data, fd, env);
	parent_process(&data, fd, env);
	ft_exit(&data, GREEN "SUCCESS" RESET, EXIT_SUCCESS);
	return (0);
}
