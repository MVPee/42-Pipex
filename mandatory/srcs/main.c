/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:38 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/12 09:46:54 by mvpee            ###   ########.fr       */
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
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(data->output, STDOUT_FILENO);
	if (execve(data->cmd2, data->s_cmd2, env) == -1)
		ft_exit(data, RED "Execve parent failure...\n" RESET, EXIT_FAILURE);
}

/*
	First Child Process that run inside a fork, take the filein,
	put the output inside a pipe and then close with the exec function.
*/
static void	child_process(t_data *data, int *fd, char **env)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(data->input, STDIN_FILENO);
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
		return (ft_printf_fd(2,
				RED "E-01:\nNumber(s) of args is invalid...\n" RESET), 1);
	if (init(&data, av, env))
		ft_exit(&data, "", EXIT_FAILURE);
	ft_printf(GREEN "\nCMD: %s\nCMD2: %s\n\n" RESET, data.cmd, data.cmd2);
	ft_printf(GREEN "\n%s | %s\n\n" RESET, av[2], av[3]);
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
		ft_exit(&data, GREEN "SUCCESS" RESET, EXIT_SUCCESS);
	return (0);
}
