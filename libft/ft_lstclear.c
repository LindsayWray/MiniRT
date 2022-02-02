/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/10 17:13:05 by lwray         #+#    #+#                 */
/*   Updated: 2020/12/13 14:08:15 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next));
	ft_lstdelone(*lst);
	*lst = NULL;
}
