/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_float.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:44:19 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:44:20 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_float(char *str)
{
	int	i;

	if (!str || !ft_strlen(str))
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	if (str[i] == '.')
	{
		i++;
		return (ft_is_uint(str + i));
	}
	return (0);
}
