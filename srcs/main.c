/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:38 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/12 13:40:59 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
	Second Child Process that take the data from the pipe,
	change the output for the fileout and also close with the exec function.
*/
static void	child2_process(t_data *data, int *fd, char **env)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(data->output, STDOUT_FILENO) \
		== -1)
		ft_exit(data, RED "Dup2 child failure...\n" RESET, EXIT_FAILURE);
	close(fd[0]);
	if (execve(data->cmd2, data->s_cmd2, env) == -1)
		ft_exit(data, RED "Execve child2 failure...\n" RESET, EXIT_FAILURE);
}

/*
	First Child Process that run inside a fork, take the filein,
	put the output inside a pipe and then close with the exec function.
*/
static void	child_process(t_data *data, int *fd, char **env)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1 || dup2(data->input, STDIN_FILENO) \
		== -1)
		ft_exit(data, RED "Dup2 child failure...\n" RESET, EXIT_FAILURE);
	close(fd[1]);
	if (execve(data->cmd, data->s_cmd, env) == -1)
		ft_exit(data, RED "Execve child failure...\n" RESET, EXIT_FAILURE);
}

/*
	Init structure data, create a pipe with
		- fd[0] Write
		- fd[1] Read
	Double fork for the pipe.
	EXIT_SUCCES with parent process.
*/
int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd[2];
	pid_t	pid[2];

	if (ac != 5 || !env)
		return (ft_printf_fd(2, \
				RED "E-01:\nNumber(s) of args is invalid...\n" RESET), 1);
	if (!env)
		return (ft_printf_fd(2, RED "E-02:\nNo environment\n" RESET), 1);
	init(&data, av, env);
	if (pipe(fd) == -1)
		ft_exit(&data, RED "E-03:\nPipe fail...\n" RESET, EXIT_FAILURE);
	pid[0] = fork();
	pid[1] = fork();
	if (pid[0] == -1 || pid[1] == -1)
		ft_exit(&data, RED "E-04:\nFork fail...\n" RESET, EXIT_FAILURE);
	if (pid[0] == 0)
		child_process(&data, fd, env);
	else if (pid[1] == 0)
		child2_process(&data, fd, env);
	else
		ft_exit(&data, "", EXIT_SUCCESS);
	return (0);
}
