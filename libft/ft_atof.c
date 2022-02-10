/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 13:12:45 by lwray         #+#    #+#                 */
/*   Updated: 2021/01/17 19:34:35 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	too_large_number(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

static int	get_sign(const char *str, int *i)
{
	int			sign;

	sign = 1;
	while (ft_is_whitespace(str[*i]))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = sign * (-1);
		(*i)++;
	}
	return (sign);
}

float	ft_atof(const char *str)
{
	float		res;
	float		decimals;
	int			i;
	int			sign;
	int			dec_len;

	i = 0;
	res = 0;
	sign = get_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > __LONG_MAX__)
			return (too_large_number(sign));
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		decimals = ft_atoi(str + i + 1);
		dec_len = ft_strlen((char *)str + i + 1);
		while (dec_len--)
			decimals /= 10;
		res += decimals;
	}
	return (res * sign);
}
