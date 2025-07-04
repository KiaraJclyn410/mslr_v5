#include <iostream>
#include <cmath>
#include "tracking_system.hpp"
#include "pros/rotation.hpp"
#include <numbers>
#include <list>
#include "helpers.hpp"

void tracking_loop (){
    //get the starting values for this cycle
    pros::Rotation horizontal_rotation(1); // replace with actual port
    pros::Rotation vertical_rotation(2); // replace with actual port
    pros::IMU imu_sensor(3); // replace with actual port
    horizontal_wheel_to_center_distance = 1; // modify for the robot's value
    vertical_wheel_to_center_distance = 1; // modify for the robot's value
    robot_to_field_x_scaling = 0; //adjust later
    robot_to_field_y_scaling = 0; //adjust later
    start_horizontal = horizontal_rotation.get_position();
    start_vertical = vertical_rotation.get_position();
    double start_angle = imu_sensor.get_rotation();
    while (true){

        //replace later with stuff
        //get the current values for this cycle
        double horizontal_wheel = horizontal_rotation.get_position();
        double vertical_wheel = vertical_rotation.get_position();
        double angle = imu_sensor.get_rotation();

        //get the differences to use in this timeframe's calculations
        double delta_vertical = vertical_wheel - start_vertical;
        double delta_horizontal = horizontal_wheel - start_horizontal;
        double delta_angle = angle - start_angle;

        //update the starting values for the next cycle
        start_horizontal = start_horizontal + delta_horizontal;
        start_vertical = start_vertical + delta_vertical;

        //normalize "angle" here
        double normalized_angle = fmod(angle, 360.0);

        //turn to radians
        double angle_in_radians = degree_to_radian(normalized_angle);

        //find the arc radius
        double vertical_arc_radius = delta_vertical/angle_in_radians + vertical_wheel_to_center_distance;//+ or -
        double horizontal_arc_radius = delta_horizontal/angle_in_radians + horizontal_wheel_to_center_distance;//+ or -

        //find the chord length
        double chord_length = delta_vertical/delta_angle + vertical_wheel_to_center_distance;

        //find vector in robot_local
        int robot_local_x = chord_length;
        int robot_local_y = delta_horizontal/delta_angle + horizontal_wheel_to_center_distance;

        //create a vector in robot local with our vector class
        //this vector is in cartesian
        vector robot_local_vector;
        robot_local_vector.set_coords(robot_local_x, robot_local_y);

        //convert to polar coordinates
        std::pair<double, double> robot_local_vector_polar = robot_local_vector.cartesian_to_polar();
        //vars
        double magnitude = robot_local_vector_polar.first;
        double polar_angle = robot_local_vector_polar.second;

        //rotate the anlge to the robot_global
        double offset_angle = (start_angle + angle)/2;

        //convert to radians
        double offset_angle_in_radians = degree_to_radian(offset_angle);

        //add the offset angle to the polar angle
        double robot_global_angle = polar_angle + offset_angle;//+or-

        //let's convert it to cartesian
        vector robot_global_vector_polar;
        robot_global_vector_polar.set_polar(robot_global_angle, magnitude);
        //now we have the robot global vector in polar

        //convert to cartesian
        std::pair<double, double> robot_global_vector_cartesian_coords = robot_global_vector_polar.polar_to_cartesian(magnitude, robot_global_angle);
        double robot_global_x = robot_global_vector_cartesian_coords.first;
        double robot_global_y = robot_global_vector_cartesian_coords.second;

        //now we have the robot global vector in cartesian
        vector robot_global_vector_cartesian;
        robot_global_vector_cartesian.set_coords(robot_global_x, robot_global_y);

        //shift to the field_global plane
        std::pair<double, double> field_global_vector_= field_to_robot_global(robot_global_vector_cartesian);
        double field_global_x = field_global_vector_.first;
        double field_global_y = field_global_vector_.second;
    }
};