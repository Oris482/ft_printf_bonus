/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_diu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojinjang <hojinjang@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:54:38 by minsuki2          #+#    #+#             */
/*   Updated: 2022/03/09 19:28:10 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	input_dec_base(char *dst, unsigned int nbr, int len, int origin_len)
{
	if (origin_len)
	{
		input_dec_base(dst, nbr / DEC, len - 1, origin_len - 1);
		if (!nbr)
			dst[len - 1] = '0';
		else
			dst[len - 1] = DEC_BASE[nbr % DEC];
	}
}

static void	ft_inputnbr(char *str, t_gather *fwp, int n, int len)
{
	if ((fwp->bits & CV_U) || n >= 0)
		input_dec_base(str, n, len, fwp->origin_len);
	else
		input_dec_base(str, -n, len, fwp->origin_len);
}

static void	ft_handle_sign(int n, int bits, char *dst)
{
	int		i;
	char	sign;

	if (n < 0)
		sign = '-';
	else
	{
		sign = ' ';
		if (bits & FG_PLUS)
			sign = '+';
	}
	i = 1;
	if (bits & FG_MINUS)
		dst[0] = sign;
	else
	{
		while (dst[i] && !ft_strchr(DEC_BASE, dst[i]))
			i++;
		dst[i - 1] = sign;
	}
}

static char	*make_str(int n, t_gather *fwp, int len, int full_len)
{
	char	*dst;

	if ((fwp->bits & FG_ZERO)
		&& (salloc_int(&dst, full_len, '0') == ERROR))
		return (NULL);
	else if (!(fwp->bits & FG_ZERO)
		&& (salloc_int(&dst, full_len, ' ') == ERROR))
		return (NULL);
	if (fwp->bits & FG_MINUS)
	{
		if (fwp->bits & PC_EXIST)
			ft_memset(dst + isfg_inc(fwp), '0', len);
		ft_inputnbr(dst + isfg_inc(fwp), fwp, n, len);
	}
	else
	{
		if (fwp->bits & PC_EXIST)
			ft_memset(dst + full_len - len, '0', len);
		ft_inputnbr(dst + full_len - len, fwp, n, len);
	}
	if (fwp->bits & CV_D && (n < 0 || fwp->bits & (FG_PLUS | FG_SPACE)))
		ft_handle_sign(n, fwp->bits, dst);
	return (dst);
}

char	*make_diu(t_gather *fwp, int n, int *cnt, int len)
{
	int		full_len;

	fwp->origin_len = len;
	if (!(fwp->bits & CV_U) && n < 0)
		fwp->bits |= FG_PLUS;
	full_len = measure_len_diuxp(fwp, &len);
	if (full_len == ERROR)
		return (NULL);
	if (check_max(cnt, full_len) == ERROR)
		return (NULL);
	return (make_str(n, fwp, len, full_len));
}
