/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:10:11 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:10:13 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	free_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free (strs[i]);
		i++;
	}
	free (strs);
	return (-1);
}

void	free_scene(t_scene scene)
{
	free(scene.spheres);
	free(scene.planes);
	free(scene.cylinders);
}

int	close_window(t_minirt *minirt)
{
	free_scene(minirt->scene);
	mlx_destroy_image(minirt->mlx, minirt->img.img);
	mlx_destroy_window(minirt->mlx, minirt->mlx_win);
	exit(EXIT_SUCCESS);
}
