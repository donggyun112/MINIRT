/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:59:30 by jinhyeop          #+#    #+#             */
/*   Updated: 2023/09/14 10:57:50 by jinhyeop         ###   ########.fr       */
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
# include "../../mlx/mlx.h"
# include "../../libft/libft.h"

# define RED 0
# define GREEN 1
# define BLUE 2
# define HEIGHT 0
# define WIDTH 1
# define PL 0
# define SP 1
# define CY 2
# define SHADOW 100

//parse
t_canvas	parse(char *av[]);
void		find_problem(char **tmp, int count);
void		error_print(char *tmp, int expected, int input_count);

//parse utils
int			argument_count(char **tmp);
void		init_view2(t_canvas *canvas, char **tmp);
int			ft_strcmp(char *s1, char *s2);
void		free_split(char **tmp);

//parse obj
int			init_view(char **tmp, t_canvas *canvas, int count);
int			init_plane(char **tmp, t_canvas *canvas, int count);
int			init_sphere(char **tmp, t_canvas *canvas, int count);
int			init_cylinder(char **tmp, t_canvas *canvas, int count);
int			init_light(char **tmp, t_canvas *canvas, int count);

//shadow
int			hit_shadow(t_ray3 *ray, t_canvas canvas);
void		shadow_cap(t_ray3 *ray, t_cylinder *cy, t_plane *cap);
void		shadow_check(t_ray3 *ray, t_canvas canvas);
void		shadow_plane(t_ray3 *ray, t_plane *pl);
void		shadow_sphere(t_ray3 *ray, t_sphere *sp);
void		shadow_cylinder(t_ray3 *ray, t_cylinder *cy);

//angle_utils
double		get_hit_height(t_cylinder *cy, t_vec3 hit);
t_vec3		reflection(t_vec3 normal, t_vec3 light);

//cylinder
void		make_cylinder_cap(t_cylinder *cy);
int			cy_in_range(t_ray3 *ray, double t, t_cylinder *cy);
void		hit_cylinder(t_ray3 *ray, t_cylinder *cy, t_canvas canvas);

//sphere
void		hit_sphere(t_ray3 *ray, t_sphere *sp, t_canvas canvas);

//mlx_utils
int			win_destroy(t_view *view);
int			key_hook(int keycode, t_view *view);
void		my_mlx_pixel_put(t_view *mlx, int x, int y, unsigned int color);
int			rgb_to_int(int color[]);
void		make_obj_cap(t_volume *obj);

//intersection
int			discriminant(double a, double b, double c);
double		quad_formula(double a, double b, double c);
void		hit_sphere(t_ray3 *ray, t_sphere *sp, t_canvas canvas);
void		hit_plane(t_ray3 *ray, t_plane *pl, t_canvas canvas);
void		hit_cylinder(t_ray3 *ray, t_cylinder *cy, t_canvas canvas);
void		make_cylinder_cap(t_cylinder *cy);
t_vec3		check_plane_direction(t_plane *pl, t_ray3 *ray);
int			cy_in_range(t_ray3 *ray, double t, t_cylinder *cy);

//raycasting
t_ray3		create_ray(t_camera cam, double u, double v);
t_camera	camera(t_canvas canvas);

//angle
double		cos_sp(t_sphere *sp, t_ray3 *ray, t_canvas canvas);
double		cos_pl(t_plane *pl, t_ray3 *ray, t_canvas canvas);
double		cos_cy(t_cylinder *cy, t_ray3 *ray, t_canvas canvas);
double		ref_sp(t_sphere *sp, t_ray3 *ray, t_canvas canvas);
double		ref_pl(t_plane *pl, t_ray3 *ray, t_canvas canvas);
double		ref_cy(t_cylinder *cy, t_ray3 *ray, t_canvas canvas);

//color
void		ray_color(t_canvas canvas, t_ray3 *ray);

//shadow
int			hit_shadow(t_ray3 *ray, t_canvas canvas);

#endif
