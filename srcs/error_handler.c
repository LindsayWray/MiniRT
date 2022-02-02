/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/15 16:59:26 by lwray         #+#    #+#                 */
/*   Updated: 2021/08/15 16:59:28 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parsing_error()
{
	ft_putstr_fd("Error: incorrect scene input\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	malloc_error()
{
	perror("Malloc failed");
	exit(EXIT_FAILURE);
}

void	file_error(char *error_message)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

// void	mlx_error(void **fields, int len)
// {
// 	perror("Error: mlx error");
// 	free_fields(fields, len);
// 	exit(EXIT_FAILURE);
// }
