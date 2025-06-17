/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:56:35 by dacortes          #+#    #+#             */
/*   Updated: 2025/06/01 18:33:01 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"

void	print_no_format(struct dirent	**entries, int size)
{
	int	iter;

	if (!size || !entries || !*entries)
	{
		ft_printf(WARNING_POINTER, YELLOW, END, \
			"print_entries", "files");
		return ;
	}
	iter = 0;
	while (iter < size)
	{
		ft_printf("%s", entries[iter]->d_name);
		iter++;
		if (iter != size)
			ft_printf("  ");
	}
	ft_printf("\n");
}
