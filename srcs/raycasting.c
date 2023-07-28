/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 02:07:30 by seodong-gyu       #+#    #+#             */
/*   Updated: 2023/07/28 18:49:25 by jinhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_camera	camera(t_canvas canvas)
{
	t_camera	cam; 
	t_vec3		up;
	double		fov_radians;
	double		viewport[2];

	// 카메라 좌표
	cam.origin = canvas.cam_orig;

	// fov각도에 따른 viewport와 카메라의 거리	
	fov_radians = canvas.fov * M_PI / 180;
	cam.focal_len = 1.0 / tan(0.5 * fov_radians);
	
	// 정규화 되어있는 viewport 가로 세로 길이
	viewport[HEIGHT] = 2.0;
	viewport[WIDTH] = viewport[HEIGHT] * canvas.ratio;

	// viewport를 향하는 direction vector
	cam.dir = canvas.cam_dir;

	up = vec3(0.0, 1.0, 0.0);
	cam.r_norm = cross_product(cam.dir, up); // right = dir x up
	cam.v_norm = cross_product(cam.r_norm, cam.dir); // up = right x dir
	cam.left_lower = sub_vector(sub_vector(\ //left_lower만들어서 리턴해주는 함수 따로 구현해야됨
				sub_vector(add_vector(cam.origin, \
				multiple_vector(0.5 * viewport[WIDTH], cam.r_norm)), \
				multiple_vector(0.5 * viewport[HEIGHT], cam.v_norm)), \
				multiple_vector(cam.focal_len, cam.dir)), cam.origin);
	return (cam);
}

t_ray3	create_ray(t_camera cam, double u, int v)
{
	t_ray3	ray;

	ray.origin = cam.origin;
	ray.dir = norm_vec(add_vector(\
		add_vector(cam.left_lower, multiple_vector(u, cam.r_norm)), \
		multiple_vector(v, cam.v_norm)));
	return (ray);
}


/* void render(
    const Options &options,
    const std::vector<std::unique_ptr<Object>> &objects,
    const std::vector<std::unique_ptr<Light>> &lights)
{
    Matrix44f cameraToWorld;
    Vec3f *framebuffer = new Vec3f[options.width * options.height];
    Vec3f *pix = framebuffer;
    float scale = tan(deg2rad(options.fov * 0.5));
    float imageAspectRatio = options.width / (float)options.height;
    Vec3f orig;
    cameraToWorld.multVecMatrix(Vec3f(0), orig);

    for (uint32_t j = 0; j < options.height; ++j) {
        for (uint32_t i = 0; i < options.width; ++i) {
            // Calculate pixel position on the image plane
            float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;

            // Calculate the direction of the ray in world coordinates
            float Px = (2 * ((x + 0.5) / options.width) - 1) * tan(deg2rad(options.fov * 0.5));
            float Py = (1 - 2 * ((y + 0.5) / options.height)) * tan(deg2rad(options.fov * 0.5));

            Vec3f rayOrigin = Point3(0, 0, 0);
            Vec3f rayPWorld(Px, Py, -1);
            cameraToWorld.multVecMatrix(rayOrigin, orig);
            cameraToWorld.multVecMatrix(rayPWorld, rayPWorld);
            Vec3f rayDirection = rayPWorld - orig;
            rayDirection.normalize();

            // Cast the ray and get the pixel color
            *(pix++) = castRay(orig, rayDirection, objects, lights, options, 0);
        }
    }

    // Save result to a PPM image (keep these flags if you compile under Wi
    std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << options.width << " " << options.height << "\n255\n";
    for (uint32_t i = 0; i < options.height * options.width; ++i) {
        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }
    ofs.close();
    delete[] framebuffer;
}
 */