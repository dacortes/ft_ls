/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:53:19 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/27 10:14:00 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	sort_entries(struct dirent **entries, int count, t_flags flags)
{
	if (!entries || count <= 1)
		return ;
	quicksort_entries(entries, 0, count - 1, flags);
}
