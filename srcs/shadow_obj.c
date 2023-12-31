/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 08:18:49 by jinhyeop          #+#    #+#             */
/*   Updated: 2023/09/13 08:25:23 by jinhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	shadow_sphere(t_ray3 *ray, t_sphere *sp)
{
	t_vec3	l;
	float	tca;
	float	tnc;
	float	d2;
	float	tmp;

	l = sub_vector(sp->center, ray->origin);
	tca = scalar_product(l, ray->dir);
	if (tca < 0)
		return ;
	d2 = scalar_product(l, l) - (tca * tca);
	if (d2 > sp->radius * sp->radius)
		return ;
	tnc = sqrt(sp->radius * sp->radius - d2);
	if (tca - tnc < 0.0)
		tmp = tca + tnc;
	else
		tmp = tca - tnc;
	if ((ray->t < 0.0 && tmp > 0.0) || (tmp > 0.0 && ray->t > tmp))
		ray->t = tmp;
}

void	shadow_triangle(t_ray3 *ray, t_plane *pl)
{
	float	tmp;
	float	scalar[3];
	t_vec3	hit;

	scalar[0] = scalar_product(pl->on_plane, pl->norm);
	scalar[1] = scalar_product(ray->origin, pl->norm);
	scalar[2] = scalar_product(ray->dir, pl->norm);
	tmp = (scalar[0] - scalar[1]) / scalar[2];
	if ((ray->t < 0.0 && tmp > 0.0) || (tmp > 0.0 && ray->t > tmp))
	{
		hit = add_vector(ray->origin, multiple_vector(tmp, ray->dir));
		if (in_triangle(hit, pl) == 0)
			return ;
		ray->t = tmp;
	}
}

void	shadow_plane(t_ray3 *ray, t_plane *pl)
{
	float	tmp;
	float	scalar[3];

	if (pl->type == TRI)
	{
		shadow_triangle(ray, pl);
		return ;
	}
	scalar[0] = scalar_product(pl->on_plane, pl->norm);
	scalar[1] = scalar_product(ray->origin, pl->norm);
	scalar[2] = scalar_product(ray->dir, pl->norm);
	tmp = (scalar[0] - scalar[1]) / scalar[2];
	if ((ray->t < 0.0 && tmp > 0.0) || (tmp > 0.0 && ray->t > tmp))
		ray->t = tmp;
}

void	shadow_cap(t_ray3 *ray, t_cylinder *cy, t_plane *cap)
{
	float	tmp;
	float	scalar[3];
	t_vec3	hit;

	scalar[0] = scalar_product(cap->on_plane, cap->norm);
	scalar[1] = scalar_product(ray->origin, cap->norm);
	scalar[2] = scalar_product(ray->dir, cap->norm);
	tmp = (scalar[0] - scalar[1]) / scalar[2];
	hit = add_vector(ray->origin, multiple_vector(tmp, ray->dir));
	if (size_of_vec(sub_vector(hit, cap->on_plane)) > cy->radius)
		return ;
	if ((ray->t < 0.0 && tmp > 0.0) || (tmp > 0.0 && ray->t > tmp))
		ray->t = tmp;
}

void	shadow_cylinder(t_ray3 *ray, t_cylinder *cy)
{
	t_vec3	oc;
	t_vec3	v[2];
	float	coef[3];
	float	tmp;

	shadow_cap(ray, cy, cy->ucap);
	shadow_cap(ray, cy, cy->lcap);
	oc = sub_vector(ray->origin, cy->center);
	v[0] = vector_product(ray->dir, cy->dir);
	v[1] = vector_product(oc, cy->dir);
	coef[0] = scalar_product(v[0], v[0]);
	coef[1] = 2 * scalar_product(v[0], v[1]);
	coef[2] = scalar_product(v[1], v[1]) - cy->radius * cy->radius;
	if (discriminant(coef[0], coef[1], coef[2]))
		tmp = quad_formula(coef[0], coef[1], coef[2]);
	else
		tmp = -1.0;
	if (tmp >= 0.0 && cy_in_range(ray, tmp, cy) == 0)
		return ;
	if ((ray->t < 0.0 && tmp > 0.0) || (tmp > 0.0 && ray->t > tmp))
		ray->t = tmp;
}
