/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:17:38 by jinhyeop          #+#    #+#             */
/*   Updated: 2023/09/06 05:42:12 by jinhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minirt.h"

int	win_destroy(t_view *view)
{
	mlx_destroy_window(view->mlx, view->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_view *view)
{
	if (keycode == 53)
		win_destroy(view);
	return (0);
}

void	my_mlx_pixel_put(t_view *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(int color[])
{
	return ((color[RED] << 16) | (color[GREEN] << 8) \
	| color[BLUE]);
}

void	make_obj_cap(t_volume *obj)
{
	int	idx;

	idx = 0;
	while (idx < obj->cy_cnt)
		make_cylinder_cap(&obj->cy[idx++]);
}
