/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:38 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/11 17:59:32 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
    t_data data;

	// Verifier les arguments (+Verifier si input existe)
	if (ac != 5)
		return (ft_printf_fd(2, "E-01:\nNumber(s) of args is invalid...\n"), 1);
	data.input = open(av[1], O_RDONLY);
    data.output = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data.input == -1)
		return (ft_printf_fd(2, "E-02:\nInput doesn't exist...\n"), 1);

	// Trouver le path
	data.path = find_path(env, av[2]);
	if (!data.path)
		return (ft_printf_fd(2, "E-03:\nPATH fail...\n"), 1);
	ft_printf("%s\n", data.path);
    
    // Faire le premier cmd
    
	// Faire le pipe

	// Ecrire dans l'output le result

	return (0);
}

//  Free : data.path at end