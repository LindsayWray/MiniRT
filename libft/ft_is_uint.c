/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_uint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:44:19 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:44:20 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_uint(char *str)
{
	int	i;

	if (!str || !ft_strlen(str))
		return (0);
	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
