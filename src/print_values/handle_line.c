/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:19:39 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 12:17:27 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"
#include "errors.h"
#include "print_values.h"

/**
 * handle_line_long_format - Processes and formats an array of 
 * t_line structures based on flags.
 * @flags:     Structure containing formatting flags, including
 * long_format.
 * @line:      Double pointer to an array of t_line structures 
 * to be processed.
 * @limit:     Number of elements in the line array.
 *
 * If the long_format flag is set in @flags, this function calculates 
 * the maximum field widths for formatting, formats each line accordingly,
 * and clears each line.
 * If memory allocation fails during clearing, the program exits with an 
 * error message.
 * After processing, the function frees the memory allocated
 * for the line array and sets the pointer to NULL.
 */
short	handle_line_long_format(t_flags flags, t_line **line, int limit)
{
	t_size	size;
	int		iter;

	if (flags.long_format == false)
		return (EXIT_SUCCESS);
	iter = 0;
	ft_bzero(&size, sizeof(size));
	while (iter < limit)
	{
		update_max_lengths(&(*line)[iter], &size);
		iter++;
	}
	iter = 0;
	while (iter < limit)
	{
		create_line(&(*line)[iter], size);
		clear_line(&(*line)[iter]);
		iter++;
	}
	return (EXIT_SUCCESS);
}

void	ignore_hidden_files(t_flags flags, t_line **line, int *iter)
{
	while (!flags.all && (*line)[*iter].name && (*line)[*iter].name[0] == '.')
	{
		free((*line)[*iter].name);
		(*iter)++;
	}
}

int	ignore_null_files(t_flags flags, t_line **line, int *iter, int limit)
{
	while (*iter < limit && !(*line)[*iter].name)
		(*iter)++;
	if (!(*line)[*iter].name)
		return (true);
	ignore_hidden_files(flags, line, iter);
	return (false);
}

short	handle_line_basic(t_flags flags, t_line **line, int limit)
{
	char	*tmp;
	char	*str;
	int		iter;

	if (flags.long_format == true)
		return (EXIT_SUCCESS);
	iter = 0;
	if (ignore_null_files(flags, line, &iter, limit))
		return (EXIT_SUCCESS);
	str = protected_memory(ft_strdup((*line)[iter].name), "handle_line_basic");
	while (iter < limit)
	{
		if ((*line)[iter + 1].name)
		{
			ignore_hidden_files(flags, line, &iter);
			tmp = protected_memory(ft_strjoin(str, "  "), "handle_line_basic");
			free(str);
			ignore_hidden_files(flags, line, &iter);
			str = protected_memory(ft_strjoin(tmp, (*line)[iter + 1].name), "");
			free(tmp);
		}
		free((*line)[iter].name);
		++iter;
	}
	return (print_line(str, "", ft_strlen(str)), free(str), EXIT_SUCCESS);
}

short	handle_line(t_flags flags, t_line **line, int limit)
{
	handle_line_long_format(flags, line, limit);
	handle_line_basic(flags, line, limit);
	if (line && *line)
		free(*line);
	*line = NULL;
	return (EXIT_SUCCESS);
}
