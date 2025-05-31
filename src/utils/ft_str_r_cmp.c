/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_r_cmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:51 by joao              #+#    #+#             */
/*   Updated: 2025/05/31 18:17:53 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int	ft_str_r_cmp(const char *s1, const char *s2)
{
	int	len_s1;
	int	len_s2;

	if (!s1 || !s2)
		return (-1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (len_s1 > 0 && len_s2 > 0 && s1[len_s1 - 1] == s2[len_s2 - 1])
	{
		len_s1--;
		len_s2--;
	}
	return (s1[len_s1 - 1] - s2[len_s2 - 1]);
}
