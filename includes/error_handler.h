/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:15:05 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:15:07 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include "miniRT.h"

void	file_error(char *error_message);
void	malloc_error(void);
void	parsing_error(t_scene scene);
void	mlx_error(t_scene scene);

#endif
