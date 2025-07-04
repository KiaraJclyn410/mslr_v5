#include "pros/rotation.hpp"
#include "pros/imu.hpp"
extern pros::Rotation horizontal_rotation;
extern pros::Rotation vertical_rotation;
extern pros::IMU imu_sensor;
extern double vertical_wheel_to_center_distance; 
extern double horizontal_wheel_to_center_distance; 

//global pos to robot_global_position
extern double robot_to_field_x_scaling; 
extern double robot_to_field_y_scaling;

extern double start_horizontal;
extern double start_vertical;

