/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:10:21 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:10:23 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color	new_color(int r, int g, int b)
{
	t_color	color;

	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	color.r = r;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	color.g = g;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	color.b = b;
	return (color);
}

t_color	mix_color(t_color color, t_color light)
{
	t_color	mix;

	mix.r = roundf((float)color.r * light.r / 255);
	mix.g = roundf((float)color.g * light.g / 255);
	mix.b = roundf((float)color.b * light.b / 255);
	return (mix);
}

t_color	color_factor(t_color c, float light_factor)
{
	t_color	color;

	color = new_color(
			c.r * light_factor,
			c.g * light_factor,
			c.b * light_factor
			);
	return (color);
}

t_color	add_colors(t_color c1, t_color c2)
{
	t_color	color;

	if (c1.r > c2.r)
		color.r = c1.r;
	else
		color.r = c2.r;
	if (c1.g > c2.g)
		color.g = c1.g;
	else
		color.g = c2.g;
	if (c1.b > c2.b)
		color.b = c1.b;
	else
		color.b = c2.b;
	return (color);
}
