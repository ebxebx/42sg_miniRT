#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_camera	t_camera;

void	build_camera_axes(t_camera *cam);
void	rotate_camera(t_camera *cam, double yaw, double pitch);
void	pan_camera(t_camera *cam, double horizontal, double vertical);
double	degrees_to_radians(double degrees);
double	radians_to_degrees(double radians);

#endif
