/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:58:35 by irlozano          #+#    #+#             */
/*   Updated: 2023/10/13 15:15:06 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	a;

	ptr = NULL;
	total_size = count * size;
	a = 0;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(0));
	if (count != 0 && total_size / count != size)
		return (NULL);
	ptr = malloc (total_size);
	if (!ptr)
		return (NULL);
	if (ptr != NULL)
	{
		ft_bzero(ptr, size * count);
		return (ptr);
	}
	return (NULL);
}
