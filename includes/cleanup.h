/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:14:48 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:14:50 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "miniRT.h"

int		free_array(char **words);
int		close_window(t_minirt *minirt);
void	free_scene(t_scene scene);

#endif
