/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeop <jinhyeop@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:49:07 by jinhyeop          #+#    #+#             */
/*   Updated: 2023/09/13 08:22:56 by jinhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include "struct.h"

//vector
t_vec3	vec3(float x, float y, float z);
t_vec3	norm_vec(t_vec3 vec);
float	scalar_product(t_vec3 v1, t_vec3 v2);
t_vec3	vector_product(t_vec3 v1, t_vec3 v2);

//simple_vec_cal
float	size_of_vec(t_vec3 vec);
t_vec3	multiple_vector(float t, t_vec3 vec);
t_vec3	add_vector(t_vec3 v1, t_vec3 v2);
t_vec3	sub_vector(t_vec3 v1, t_vec3 v2);
t_vec3	add_three_vector(t_vec3 v1, t_vec3 v2, t_vec3 v3);

#endif
