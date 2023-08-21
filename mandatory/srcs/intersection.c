#include "../includes/minirt.h"
#include <stdio.h> //remove

int	hit_line_sphere(t_ray3 *ray, t_sphere *sp)
{
	t_vec3	l;
	double	tca;
	double	d2;
	double	tnc;


	// p = p0 + tV
	l = sub_vector(sp->center, ray->origin); // 원점과 구 중심을 잇는 방향벡터
	tca = scalar_product(l, ray->dir); // 빛이 구를 향해가고 있는지를 판단
	if (tca < 0)
		return (0);
	d2 = scalar_product(l, l) - (tca * tca); // 원점에서 벡터 사이의 거리가 r^2보다 크면 FALSE d = d^2
	if (d2 > sp->radius * sp->radius)
		return (0);
	tnc = sqrt(sp->radius * sp->radius - d2);
	if (tca - tnc < 0.0)
		return (1);
	else
		return (1);
	return (1);
}

double	distance_a(t_vec3 a, t_vec3 b)
{
	double	dx;
	double	dy;
	double	dz;

	dx = a.x - b.x;
	dy = a.y - b.y;
	dz = a.z - b.z;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}


int	intersect_sphere_shadow(t_ray3 *ray, t_canvas canvas)
{
	t_vec3	p;
	t_vec3	g_norm;
	t_ray3	light;
	int		idx;

	idx = 0;
	p = add_vector(ray->origin, multiple_vector(ray->t, ray->dir));
	g_norm = norm_vec(sub_vector(canvas.light_orig, p));
	light.dir = g_norm;
	light.origin = p;
	while (idx < canvas.obj->sp_cnt)
	{
		if (hit_line_sphere(&light, &canvas.obj->sp[idx]))
			return (1);
		idx++;
	}
	return (0);
}

double mapToRange(double value, double minInput, double maxInput, double minOutput, double maxOutput)
{
    // 로그 함수를 사용하여 입력값을 [0, ∞) 범위로 매핑
    double logValue = log(value - minInput + 1);

    // [0, ∞) 범위의 값을 [minOutput, maxOutput] 범위로 선형 변환
    return (((logValue) / (log(maxInput - minInput + 1))) * (maxOutput - minOutput) + minOutput);
}


void	hit_plane(t_ray3 *ray, t_plane *pl, t_canvas canvas)
{
	double	tmp;
	double	scalar[3];

	scalar[0] = scalar_product(pl->on_plane, pl->norm);
	scalar[1] = scalar_product(ray->origin, pl->norm);
	scalar[2] = scalar_product(ray->dir, pl->norm);
	tmp = (scalar[0] - scalar[1]) / scalar[2];
	if ((ray->t < 0.0 && tmp > 0.0) || (tmp > 0.0 && ray->t > tmp))
	{
		ray->t = tmp;
		ray->type = PL;
		ray->color[RED] = pl->color[RED];
		ray->color[GREEN] = pl->color[GREEN];
		ray->color[BLUE] = pl->color[BLUE];
		ray->obj = (void *)pl;
		if (intersect_sphere_shadow(ray, canvas))
			ray->type = SHADOW;
	}
}

void	hit_sphere(t_ray3 *ray, t_sphere *sp, t_canvas canvas)
{
	t_vec3	l;
	double	tca;
	double	tnc;
	double	d2;
	double	tmp;

	l = sub_vector(sp->center, ray->origin); // 원점과 구 중심을 잇는 방향벡터
	tca = scalar_product(l, ray->dir); // 빛이 구를 향해가고 있는지를 판단
	if (tca < 0)
		return ;
	d2 = scalar_product(l, l) - (tca * tca); // 원점에서 벡터 사이의 거리가 r^2보다 크면 FALSE d = d^2
	if (d2 > sp->radius * sp->radius)
		return ;
	tnc = sqrt(sp->radius * sp->radius - d2);
	if (tca - tnc < 0.0)
		tmp = tca + tnc;
	else
		tmp = tca - tnc;
	if ((ray->t < 0.0 && tmp > 0.0) || (tmp > 0.0 && ray->t > tmp))
	{
		ray->t = tmp;
		ray->color[RED] = sp->color[RED];
		ray->color[GREEN] = sp->color[GREEN];
		ray->color[BLUE] = sp->color[BLUE];
		ray->type = SP;
		ray->obj = (void *)sp;
		if (intersect_sphere_shadow(ray, canvas))
			ray->type = SHADOW;
	}
}

int	discriminant(double a, double b, double c)
{
	if ((b * b) - (4 * a * c) >= 0.0)
		return (1);
	else
		return (0);
}

double	quad_formula(double a, double b, double c)
{
	double	sol1;
	double	sol2;

	sol1 = ((-1) * b - sqrt(b * b - (4 * a * c))) / (2.0 * a);
	sol2 = ((-1) * b + sqrt(b * b - (4 * a * c))) / (2.0 * a);
	if (sol1 > 0.0 && sol2 > 0.0)
		return (sol1);
	else if (sol1 < 0.0 && sol2 > 0.0)
		return (sol2);
	else
		return (-1.0);
}

int	cy_in_range(t_ray3 *ray, double t, t_cylinder *cy)
{
	t_vec3	hit;
	double	height[2];

	hit = add_vector(ray->origin, multiple_vector(t, ray->dir));
	height[0] = scalar_product(sub_vector(hit, cy->center), cy->dir);
	height[1] = scalar_product(sub_vector(hit, cy->center), multiple_vector(-1.0, cy->dir));
	if (height[0] > 0 && height[0] > cy->height / 2)
		return (0);
	if (height[1] > 0 && height[1] > cy->height / 2)
		return (0);
	return (1);
}

void	hit_cylinder_cap(t_ray3 *ray, t_cylinder *cy, t_canvas canvas)
{
	(void)ray;
	(void)cy;
	(void)canvas;
}

void	hit_cylinder(t_ray3 *ray, t_cylinder *cy, t_canvas canvas)
{
	t_vec3	oc;
	t_vec3	v[2];
	double	coef[3];
	double	tmp;

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
	{
		ray->t = tmp;
		ray->color[RED] = cy->color[RED];
		ray->color[GREEN] = cy->color[GREEN];
		ray->color[BLUE] = cy->color[BLUE];
		ray->type = CY;
		ray->obj = (void *)cy;
		if (intersect_sphere_shadow(ray, canvas))
			ray->type = SHADOW;
	}
}
/*
void hit_cylinder(t_ray3 *ray, t_cylinder *cy)
{
    t_vec3 oc = sub_vector(ray->origin, cyl->center);
    double a = scalar_product(ray->dir, ray->dir) - pow(scalar_product(ray->dir, cyl->center), 2);
    double b = 2.0 * (scalar_product(ray->dir, oc) - scalar_product(ray->dir, cyl->center) * scalar_product(oc, cyl->center));
    double c = scalar_product(oc, oc) - pow(scalar_product(oc, cyl->center), 2) - cyl->radius * cyl->radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant > 0) {
        double t0 = (-b - sqrt(discriminant)) / (2.0*a);
        double t1 = (-b + sqrt(discriminant)) / (2.0*a);
        double y0 = ray->origin.y + t0 * ray->dir.y;
        double y1 = ray->origin.y + t1 * ray->dir.y;
        if (y0 > cyl->center.y && y0 < cyl->center.y + cyl->height) {
            update_ray(ray, t0, cyl->color, CYLINDER, cyl);
            return;
        }
        if (y1 > cyl->center.y && y1 < cyl->center.y + cyl->height) {
            update_ray(ray, t1, cyl->color, CYLINDER, cyl);
            return;
        }
    }
    // 원기둥의 상단 및 하단 원과의 교차를 처리하는 코드는 여기에 추가될 수 있습니다.
}
*/