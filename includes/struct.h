/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 01:23:19 by seodong-gyu       #+#    #+#             */
/*   Updated: 2023/09/13 06:40:14 by jinhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_checkerpattern
{
	t_color	color_a;
	t_color	color_b;
	int		width;
	int		height;
}	t_checker;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ray3
{
	t_vec3			origin;
	t_vec3			dir;
	float			t;
	int				type;
	void			*obj;
	int				pix[2];
	int				color[3];
	int				real[3];
	float			angle[2];
}	t_ray3;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	left_upper;
	t_vec3	dir;
	t_vec3	r_norm;
	t_vec3	v_norm;
	float	fov;
	float	focal_len;
}	t_camera;

typedef struct s_plane
{
	t_vec3			on_plane;
	t_vec3			norm;
	t_vec3			tr_v1;
	t_vec3			tr_v2;
	int				type;
	t_texture		texture;
	char			*filepath;
	int				color[3];
}	t_plane;

typedef struct s_sphere
{
	int				type;
	int				idx;
	int				rsp_type;
	float			angle;
	t_texture		texture;
	t_texture		bumtexture;
	char			*filepath;
	char			*bumppath;
	t_vec3			center;
	float			radius;
	int				color[3];
}	t_sphere;

typedef struct s_rsphere
{
	int			type;
	int			sp_idx;
	t_sphere	*sp;
	t_vec3		r_center;
	t_vec3		r_axis;
	float		r_radius;
}	t_rsphere;

typedef struct s_cylinder
{
	int			type;
	float		angle;
	t_texture	texture;
	t_texture	bumtexture;
	char		*filepath;
	char		*bumppath;
	t_vec3		center;
	t_vec3		dir;
	float		radius;
	float		height;
	int			color[3];
	t_plane		*ucap;
	t_plane		*lcap;
}	t_cylinder;

typedef struct s_light
{
	int		rotate_idx;
	t_vec3	light_orig;
	float	light_bright;
	int		light_col[3];
}	t_light;

typedef struct s_rlight
{
	int		light_idx;
	t_vec3	r_center;
	t_vec3	r_axis;
	t_light	*light;
}	t_rlight;

typedef struct s_volume
{
	int			pl_cnt;
	int			sp_cnt;
	int			cy_cnt;
	int			l_cnt;
	int			rl_cnt;
	int			rsp_cnt;
	int			error_flag[3];
	float		ag;
	t_plane		*pl;
	t_sphere	*sp;
	t_cylinder	*cy;
	t_light		*l;
	t_rsphere	*rsp;
	t_rlight	*rl;
}	t_volume;

typedef struct s_canvas
{
	int			width;
	int			height;
	float		ratio;
	float		amb_bright;
	int			amb_col[3];
	t_vec3		cam_orig;
	t_vec3		cam_dir;
	int			fov;
	t_vec3		light_orig;
	float		light_bright;
	int			light_col[3];
	char		*bgt_filepath;
	t_volume	*obj;
	t_camera	cam;
}	t_canvas;

typedef struct s_grep
{
	void		*obj;
	int			grep;
	int			type;
}	t_grep;

typedef struct s_backup
{
	int				type;
	void			*obj;
	struct s_backup	*next;
}	t_backup;

typedef struct s_view
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			anti_scalar;
	int			low_scalar;
	int			quality_scalar;
	int			flag;
	int			focus;
	int			stop;
	int			click_status;
	int			show_mouse;
	int			change_dir;
	int			mini_size;
	int			real_size;
	int			lnum;
	t_camera	cam;
	t_canvas	can;
	t_grep		grep;
	t_texture	back;
	t_backup	*backup;
}	t_view;

typedef struct s_thread
{
	int			id;
	t_ray3		ray;
	t_view		*view;
	t_canvas	canvas;
	pthread_t	thread;
}	t_thread;

#endif
