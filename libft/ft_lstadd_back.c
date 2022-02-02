/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 17:36:53 by lwray         #+#    #+#                 */
/*   Updated: 2021/01/17 21:37:34 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*last;

	if (list && *list)
	{
		last = ft_lstlast(*list);
		if (last)
			last->next = new;
	}
	else if (list)
		*list = new;
}
