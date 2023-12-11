/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:38 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/11 21:01:35 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void parent_process(t_data data, int *fd, char **env)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(data.output, STDOUT_FILENO);
	if (execve(data.cmd2, (char *[]){data.cmd2, NULL}, env) == -1)
	{
		close(data.output);
		ft_free(2, &data.cmd, &data.cmd2);
		perror("execve parent");
		exit(EXIT_FAILURE);
	}
	close(data.output);
	ft_free(1, &data.cmd2);
}

static void child_process(t_data data, int *fd, char **env)
{
	close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
	dup2(data.input, STDIN_FILENO);
    close(fd[1]);
    if (execve(data.cmd, (char *[]){data.cmd, NULL}, env) == -1)
	{
		close(data.input);
		ft_free(2, &data.cmd, &data.cmd2);
		perror("execve child");
		exit(EXIT_FAILURE);
	}
	close(data.input);
	ft_free(1, &data.cmd);
}

int	main(int ac, char **av, char **env)
{
    t_data data;
	int fd[2];
	pid_t pid;

	// Arg check
	if (ac != 5)
		return (ft_printf_fd(2, RED "E-01:\nNumber(s) of args is invalid...\n" RESET), 1);
	data.input = open(av[1], O_RDONLY);
    data.output = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data.input == -1)
		return (ft_printf_fd(2, RED "E-02:\nInput doesn't exist...\n" RESET), 1);
	data.cmd = find_path(env, av[2]);
	if (!data.cmd)
		return (ft_printf_fd(2, RED "E-03:\nCMD fail...\n" RESET), 1);
    data.cmd2 = find_path(env, av[3]);
	if (!data.cmd2)
		return (ft_free(1, &data.cmd), ft_printf_fd(2, RED "E-03.1:\nCMD2 fail...\n" RESET), 1);

	// Unit Test
    ft_printf(GREEN "\nCMD: %s\nPIPE: %s\n\n" RESET, data.cmd, data.cmd2);
	
	// Process
    if (pipe(fd) == -1)
		return (ft_free(2, &data.cmd, &data.cmd2), ft_printf_fd(2, RED "E-03.1:\nPIPE fail...\n" RESET), 1);
    pid = fork();
	if (pid == -1)
		return (ft_free(2, &data.cmd, &data.cmd2), ft_printf_fd(2, RED "E-04:\nFork fail...\n" RESET), 1);
	if (pid == 0)
		child_process(data, fd, env);
	else
	{
		parent_process(data, fd, env);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
