/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:52:54 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 13:06:56 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.h"

#include <dirent.h>
#include <stdlib.h>

#include "print_values.h"

short	clear_array(char **ptr);
short	clear_entries(struct dirent **entries, int size, short is_loop);
short	clear_line(t_line *line);