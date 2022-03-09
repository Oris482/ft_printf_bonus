/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:14:26 by jaesjeon          #+#    #+#             */
/*   Updated: 2021/11/23 21:12:00 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	cnt;

	cnt = 0;
	while (*s++ != '\0')
		cnt++;
	s--;
	if ((char)c == '\0')
		return ((char *)s);
	while (cnt-- > 0)
		if (*--s == (char)c)
			return ((char *)s);
	return (0);
}
