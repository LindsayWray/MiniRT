/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ends_with.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:12:45 by lwray         #+#    #+#                 */
/*   Updated: 2021/01/17 19:34:35 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ends_with(char *str, char *end)
{
	int	index;

	index = ft_strlen(str) - ft_strlen(end);
	if (ft_strequal(str + index, end))
		return (1);
	return (0);
}
