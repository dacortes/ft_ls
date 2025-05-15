/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:24 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/14 15:20:41 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"

/**
 * bool_to_text - Converts a boolean value to a color-coded string
 * representation.
 * 
 * @bool: An unsigned integer representing the boolean value.
 *        Expected values are 0 (false) or 1 (true).
 * 
 * Return: A pointer to a string containing the text "false" in red color
 *         if the input is 0, or "true" in blue color if the input is 1.
 *         The string includes ANSI escape codes for color formatting.
 * 
 * Note: The function assumes the terminal supports ANSI escape codes.
 */
char	*bool_to_text(unsigned int bool)
{
	if (bool == false)
		return ("\033[1;31mfalse\033[m");
	return ("\033[1;34mtrue\033[m");
}

/**
 * @file print_flags.c
 * @brief Contains the implementation of a function to print the values
 * of flags.
 *
 * This file is part of the ft_ls project and provides functionality to display
 * the current state of various flags used in the program.
 */

/**
 * @brief Prints the values of the flags in a formatted manner.
 *
 * This function outputs the current state of the flags stored in the 
 * `t_flags` structure. Each flag is displayed with its corresponding 
 * boolean value converted to a textual representation using the 
 * `bool_to_text` function.
 *
 * @param flag A pointer to a `t_flags` structure containing the flags to print.
 *
 * The flags printed are:
 * - `l`: Long format
 * - `R`: Recursive
 * - `a`: All
 * - `r`: Reverse
 * - `t`: Time
 *
 * The output is color-coded with the flag header in orange and
 * the rest in default color.
 */
void	printf_value_flag(t_flags *flag)
{
	ft_printf("%sFLAGS\n%s", ORANGE, END);
	ft_printf("\tl = %s\n", bool_to_text(flag->long_format));
	ft_printf("\tR = %s\n", bool_to_text(flag->recursive));
	ft_printf("\ta = %s\n", bool_to_text(flag->all));
	ft_printf("\tr = %s\n", bool_to_text(flag->reverse));
	ft_printf("\tt = %s\n", bool_to_text(flag->time));
}
