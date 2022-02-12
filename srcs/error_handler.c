/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:10:45 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:10:47 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cleanup.h"
#include "../includes/miniRT.h"

void	parsing_error(t_scene scene)
{
	free_scene(scene);
	ft_putstr_fd("Error\n incorrect scene input\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	perror("Error\n Malloc failed");
	exit(EXIT_FAILURE);
}

void	file_error(char *error_message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	mlx_error(t_scene scene)
{
	free_scene(scene);
	ft_putstr_fd("Error\nCould not start miniLibX", STDERR_FILENO);
	exit(EXIT_FAILURE);
}