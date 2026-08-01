/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:53:30 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 15:15:40 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t	color;

	color = (uint32_t)r << 24;
	color |= (uint32_t)g << 16;
	color |= (uint32_t)b << 8;
	color |= (uint32_t)a;
	return (color);
}
