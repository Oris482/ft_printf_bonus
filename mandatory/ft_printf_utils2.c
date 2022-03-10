/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:43:53 by jaesjeon          #+#    #+#             */
/*   Updated: 2022/03/10 22:15:28 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nstrchr_cnt(const char *s, int c, int *cnt)
{
	int	idx;
	int	free_space;

	idx = 0;
	if (cnt)
		free_space = INT_MAX - *cnt;
	while (s[idx])
	{
		if (s[idx] == (char)c)
		{
			if (cnt)
				*cnt += idx;
			return (idx);
		}
		idx++;
		if (idx < 0)
			return (ERROR);
	}
	if (!cnt)
		return (ERROR);
	if (free_space <= idx)
		return (ERROR);
	*cnt += idx;
	return (idx);
}

t_pctlst	*ft_lstnew_before_str(char *before)
{
	t_pctlst	*new;

	new = malloc(sizeof(t_pctlst));
	if (!new)
		return (NULL);
	new->before_pct = before;
	new->after_pct = NULL;
	new->full_len = 0;
	return (new);
}

void	print_lst(t_pctlst *lst)
{
	if (lst)
	{
		if (lst->before_pct)
		{
			ft_putstr_fd(lst->before_pct, 1);
			free(lst->before_pct);
		}
		if (lst->after_pct)
		{
			if (lst->full_len != 0)
				write(1, lst->after_pct, lst->full_len);
			else
				ft_putstr_fd(lst->after_pct, 1);
			free(lst->after_pct);
		}
	}
	free(lst);
}
