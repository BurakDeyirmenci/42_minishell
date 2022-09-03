/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acalayir <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:44:45 by acalayir          #+#    #+#             */
/*   Updated: 2022/01/13 15:44:49 by acalayir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*tmp_s;
	unsigned char		tmp_c;

	tmp_s = (unsigned const char *)s;
	tmp_c = (unsigned char)c;
	while (n--)
		if (*tmp_s++ == tmp_c)
			return ((void *)(tmp_s - 1));
	return (NULL);
}
