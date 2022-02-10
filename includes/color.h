/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:14:56 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:14:58 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "miniRT.h"

t_color	new_color(int r, int g, int b);
t_color	mix_color(t_color color, t_color light);
t_color	add_colors(t_color c1, t_color c2);
t_color	color_factor(t_color color, float light_factor);

#endif
