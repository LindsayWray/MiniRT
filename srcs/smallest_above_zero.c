/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   smallest_above_zero.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:13:43 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:13:47 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

float	smallest_above_zero(float x1, float x2)
{
	if (x1 > 0 && (x1 < x2 || x2 < 0))
		return (x1);
	if (x2 > 0 && (x2 < x1 || x1 < 0))
		return (x2);
	return (-1);
}
