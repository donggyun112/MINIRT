/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:48:10 by jinhyeop          #+#    #+#             */
/*   Updated: 2023/09/13 09:25:03 by jinhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	intersection(t_ray3 *ray, t_volume *obj, t_canvas canvas)
{
	int	idx;

	idx = 0;
	while (idx < obj->sp_cnt)
	{
		hit_sphere(ray, &obj->sp[idx], canvas);
		idx++;
	}
	idx = 0;
	while (idx < obj->pl_cnt)
	{
		hit_plane(ray, &obj->pl[idx], canvas);
		idx++;
	}
	idx = 0;
	while (idx < obj->cy_cnt)
	{
		hit_cylinder(ray, &obj->cy[idx], canvas);
		idx++;
	}
}

void	color_cal(t_view *view, t_canvas canvas, t_ray3 *ray, int pix[])
{
	if (ray->t > 0.0)
	{
		ray_color(canvas, ray);
		my_mlx_pixel_put(view, pix[0], pix[1], rgb_to_int(ray->color));
	}
	else
		my_mlx_pixel_put(view, pix[0], pix[1], 0x00FFFFFF);
}

void	make_image(t_view *view, t_canvas canvas, t_camera cam)
{
	int		pix[2];
	double	vp_idx[2];
	t_ray3	ray;

	pix[1] = 0;
	while (pix[1] < canvas.height)
	{
		pix[0] = 0;
		vp_idx[1] = 2.0 * (double)pix[1] / (double)canvas.height;
		while (pix[0] < canvas.width)
		{
			vp_idx[0] = canvas.ratio * 2.0 * (double)pix[0] \
				/ (double)canvas.width;
			ray = create_ray(cam, vp_idx[0], vp_idx[1]);
			intersection(&ray, canvas.obj, canvas);
			color_cal(view, canvas, &ray, pix);
			pix[0]++;
		}
		pix[1]++;
	}
}

int	is_valid_file_type(char *file_path)
{
	char	**path;
	int		answer;
	int		i;

	answer = 0;
	i = 0;
	path = ft_split(file_path, ".");
	if (!path)
		return (0);
	while (path[i] != 0)
		i++;
	if (ft_strncmp(path[i - 1], "rt", 2) == 0)
		answer = 1;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (answer);
}

int	main(int argc, char *argv[])
{
	t_view		view;
	t_canvas	canvas;
	t_camera	cam;

	if (argc != 2 || !is_valid_file_type(argv[1]))
	{
		ft_putstr_fd("Error\nInput mapfile(*.rt) as argument\n", 2);
		return (1);
	}
	canvas = parse(argv);
	make_obj_cap(canvas.obj);
	cam = camera(canvas);
	view.mlx = mlx_init();
	view.win = mlx_new_window(view.mlx, canvas.width, canvas.height, "miniRT");
	view.img = mlx_new_image(view.mlx, canvas.width, canvas.height);
	view.addr = mlx_get_data_addr(view.img, &view.bits_per_pixel, \
		&view.line_length, &view.endian);
	view.can = canvas;
	make_image(&view, canvas, cam);
	mlx_put_image_to_window(view.mlx, view.win, view.img, 0, 0);
	mlx_hook(view.win, 17, 1L << 5, win_destroy, &view);
	mlx_hook(view.win, 2, 1L << 0, key_hook, &view);
	mlx_loop(view.mlx);
	return (0);
}
