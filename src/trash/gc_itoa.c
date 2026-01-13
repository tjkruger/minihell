/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r2d2 <r2d2@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:25:12 by hkaraogl          #+#    #+#             */
/*   Updated: 2026/01/13 00:03:14 by r2d2             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len(int n)
{
    int	length;

    length = 0;
    if (n <= 0)
        length = 1;
    while (n != 0)
    {
        length++;
        n /= 10;
    }
    return (length);
}

char	*gc_itoa(t_trash *trash, int n)
{
    int		lengh;
    char	*result;
    int		is_neg;

    if (n == -2147483648)
        return (gc_strdup(trash, "-2147483648"));
    lengh = get_len(n);
    result = (char *)gc_malloc(trash, (lengh + 1), sizeof(char));
    if (!result)
        return (NULL);
    is_neg = (n < 0);
    if (is_neg)
        n = -n;
    result[lengh] = '\0';
    while (lengh > 0)
    {
        lengh--;
        result[lengh] = (n % 10) + '0';
        n /= 10;
    }
    if (is_neg)
        result[0] = '-';
    return (result);
}