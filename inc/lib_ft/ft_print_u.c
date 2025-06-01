/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 03:03:04 by joamiran          #+#    #+#             */
/*   Updated: 2025/06/01 18:15:34 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen_u(unsigned int n)
{
	int	len;

	len = 1;
	while (n)
	{
		n /= 10;
		if (n)
			len++;
	}
	return (len);
}

static int	calculate_padding_u(t_data *data, unsigned int n)
{
	int	len;
	int	padding;

	len = ft_nbrlen_u(n);
	padding = data->format.width - len;
	if (data->format.plus_sign)
		padding--;
	return (padding);
}

static int	ft_write_nbr_u(unsigned int n)
{
	unsigned int	nb;
	int				chars_printed;

	chars_printed = 0;
	nb = n;
	if (nb >= 10)
	{
		chars_printed += ft_write_nbr_u(nb / 10);
	}
	chars_printed += ft_write(nb % 10 + '0');
	return (chars_printed);
}

static int	handle_padding_u(t_data *data, unsigned int n, int padding,
		int prec_padding)
{
	if (data->format.minus_sign)
	{
		print_padding(data, prec_padding, '0');
		if (!(n == 0 && data->format.precision == 0))
			data->chars_printed += ft_write_nbr_u(n);
		if (padding > prec_padding)
			print_padding(data, padding - prec_padding, ' ');
		return (1);
	}
	else if (padding < 0)
	{
		print_padding(data, prec_padding, '0');
		if (!(n == 0 && data->format.precision == 0))
			data->chars_printed += ft_write_nbr_u(n);
		return (1);
	}
	else if (data->format.zero_padding && data->format.precision == -1)
		print_padding(data, padding, '0');
	else
	{
		print_padding(data, padding - prec_padding, ' ');
		print_padding(data, prec_padding, '0');
	}
	return (0);
}

void	ft_print_u(t_data *data, unsigned int n)
{
	int	padding;
	int	prec_padding;
	int	is_printed;

	padding = calculate_padding_u(data, n);
	prec_padding = data->format.precision - ft_nbrlen_u(n);
	if (prec_padding < 0)
		prec_padding = 0;
	if (n == 0 && data->format.precision == 0)
	{
		print_padding(data, padding + 1, ' ');
		return ;
	}
	is_printed = handle_padding_u(data, n, padding, prec_padding);
	if (!is_printed)
		data->chars_printed += ft_write_nbr_u(n);
}
