#include "includes/minirt.h"

t_bool	hit_sphere(t_ray3 *ray, t_sphere *sp)
{
	t_vec3	l;
	double	tca;
	double	tnc;
	double	d;


	// p = p0 + tV
	l = sub_vector(sp->sphere, ray->origin); // 원점과 구 중심을 잇는 방향벡터
	tca = scalar_product(l, ray->dir); // 빛이 구를 향해가고 있는지를 판단
	if (tca < 0)
		return (FALSE);
	d = sqrt(scalar_product(l, l) - (t * t)); // 원점에서 벡터 사이의 거리가 r^2보다 크면 FALSE
	if (d * d > sp->r * sp->r)
		return (FALSE);
	tnc = sqrt(sp->r * sp->r - d * d);
	ray->t = tca - tnc;
	return (TRUE);
}