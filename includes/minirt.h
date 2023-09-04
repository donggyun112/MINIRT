/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:59:30 by jinhyeop          #+#    #+#             */
/*   Updated: 2023/09/05 00:02:44 by jinhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "struct.h"
# include "vector.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define DIFF 0
# define REF 1
# define RED 0
# define GREEN 1
# define BLUE 2
# define HEIGHT 0
# define WIDTH 1
# define PL 0
# define SP 1
# define CY 2
# define TSP 3
# define CSP 4
# define CPL 5
# define TPL 6
# define SHADOW 100

//parse
t_canvas	parse(char *av[]);

//utils

//mlx_utils
int			win_destroy(t_view *view);
int			key_hook(int keycode, t_view *view);
void		my_mlx_pixel_put(t_view *mlx, int x, int y, unsigned int color);
int			rgb_to_int(int color[]);
t_vec3		rotate_around_axis(t_vec3 vec, t_vec3 axis, float angle);
void	rotate_vertical(int keycode, t_view *view);
void	rotate_horizontal(int keycode, t_view *view);
void	up_down(int keycode, t_view *view);
void	left_right(int keycode, t_view *view);
void	foward_back(int keycode, t_view *view);
void	quality(int keycode, t_view *view);
void	move_focus(int scalra, t_view *view, float sensitivity);

//intersection
int			discriminant(float a, float b, float c);
float		quad_formula(float a, float b, float c);
void		hit_sphere(t_ray3 *ray, t_sphere *sp);
void		hit_plane(t_ray3 *ray, t_plane *pl);
void		hit_cylinder(t_ray3 *ray, t_cylinder *cy);
void		make_cylinder_cap(t_cylinder *cy);
t_vec3		check_plane_direction(t_plane *pl, t_ray3 *ray);
int			cy_in_range(t_ray3 *ray, float t, t_cylinder *cy);

//raycasting
t_ray3		create_ray(t_camera cam, float u, float v);
t_camera	camera(t_canvas canvas);
void		make_image(t_view *view, t_canvas canvas);

//angle
float		cos_sp(t_sphere *sp, t_ray3 *ray, t_canvas canvas, int light);
float		cos_pl(t_plane *pl, t_ray3 *ray, t_canvas canvas, int light);
float		cos_cy(t_cylinder *cy, t_ray3 *ray, t_canvas canvas, int light);
float		ref_sp(t_sphere *sp, t_ray3 *ray, t_canvas canvas, int light);
float		ref_pl(t_plane *pl, t_ray3 *ray, t_canvas canvas, int light);
float		ref_cy(t_cylinder *cy, t_ray3 *ray, t_canvas canvas, int light);

//color
int			amb_light(t_canvas canvas, t_ray3 *ray, int idx);
void		ray_color(t_canvas canvas, t_ray3 *ray, int light);

//pattern
void	init_texture(t_texture *texture, t_view *view, char *path);
t_color get_texture_color(t_texture texture, float u, float v);
void	spherical_map(t_vec3 p, float *u, float *v, t_vec3 center, float ag);

//shadow
int			hit_shadow(t_ray3 *ray, t_canvas canvas, int light);


//
void	newwin(t_view *view);
void	multi_rend(t_view *view);
#endif
