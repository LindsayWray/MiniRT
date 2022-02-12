/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:12:10 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:12:13 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/parsing.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_scene	scene;

	if (argc != 2 || !ends_with(argv[1], ".rt"))
		file_error("Please provide a correct filename\n");	
	if (WINDOW_SIZE < 0 || WINDOW_SIZE > 1200)
		file_error("Incorrect window size\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nCould not open scene file");
		exit(EXIT_FAILURE);
	}
	scene = parse_file(fd);
	close(fd);
	draw_window(scene, WINDOW_SIZE);
}
