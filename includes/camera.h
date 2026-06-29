#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_camera	t_camera;

void	build_camera_axes(t_camera *cam);
void	rotate_camera(t_camera *cam, double yaw, double pitch);

#endif
