/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seodong-gyun <seodong-gyun@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:38:12 by jinhyeop          #+#    #+#             */
/*   Updated: 2023/09/06 00:45:30 by seodong-gyu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"
#include "../includes/struct.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	norm_vec(t_vec3 vec)
{
	t_vec3	norm;
	double	size;

	size = size_of_vec2(vec);
	norm.x = vec.x / size;
	norm.y = vec.y / size;
	norm.z = vec.z / size;
	return (norm);
}

double	scalar_product(t_vec3 v1, t_vec3 v2)
{
	double	res;

	res = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (res);
}

t_vec3	vector_product(t_vec3 v1, t_vec3 v2)
{
	t_vec3	cr;

	cr.x = (v1.y * v2.z) - (v1.z * v2.y);
	cr.y = (v1.z * v2.x) - (v1.x * v2.z);
	cr.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (cr);
}
