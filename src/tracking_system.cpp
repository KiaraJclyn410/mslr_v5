#include <iostream>
#include <cmath>
#include "tracking_system.hpp"
#include <numbers>
#include <list>
#include "helpers.hpp"

void tracking_loop (){
    //get the starting values for this cycle
    horizontal_wheel_to_center_distance = 5.0; // modify for the robot's value
    vertical_wheel_to_center_distance = 7.0; // modify for the robot's value
    robot_to_field_x_scaling = 1000.0; //adjust later
    robot_to_field_y_scaling = 200.0; //adjust later
    //testing 
    //plug values here to test
    start_horizontal = 1000.0;
    start_vertical = 2000.0;
    double start_angle = 45.0;

    while (true){

        //get the current values for this cycle
        //plug values here to test
        double horizontal_wheel = 1100.0;
        double vertical_wheel = 2100.0;
        double angle = 60.0;

        //get the differences to use in this timeframe's calculations
        double delta_vertical = vertical_wheel - start_vertical;
        double delta_horizontal = horizontal_wheel - start_horizontal;
        double delta_angle = angle - start_angle;
        std::cout << "delta_vert is: " << delta_vertical << std::endl;
        std::cout << "delta_horz is: " << delta_horizontal << std::endl;
        std::cout << "delta_angle is: " << delta_angle << std::endl;

        //update the starting values for the next cycle
        start_horizontal = start_horizontal + delta_horizontal;
        start_vertical = start_vertical + delta_vertical;
        std::cout << "updated_start_horz is : " << delta_vertical << std::endl;
        std::cout << "updated_start_vert is: " << delta_vertical << std::endl;

        //normalize "angle" here
        double normalized_angle = fmod(angle, 360.0);
        std::cout << "delta_normalized_angle is: " << normalized_angle << std::endl;

        //turn to radians
        double angle_in_radians = degree_to_radian(normalized_angle);
        std::cout << "angle_in_radians is: " << angle_in_radians << std::endl;

        //find the arc radius
        double vertical_arc_radius = delta_vertical/angle_in_radians + vertical_wheel_to_center_distance;//+ or -
        double horizontal_arc_radius = delta_horizontal/angle_in_radians + horizontal_wheel_to_center_distance;//+ or -
        std::cout << "vertical_arc_radius is: " << vertical_arc_radius << std::endl;
        std::cout << "horizontal_arc_radius is: " << horizontal_arc_radius << std::endl;

        //find the chord length
        double chord_length = delta_vertical/delta_angle + vertical_wheel_to_center_distance;
        std::cout << "chords length is: " << chord_length << std::endl;

        //find vector in robot_local
        int robot_local_x = chord_length;
        int robot_local_y = delta_horizontal/delta_angle + horizontal_wheel_to_center_distance;
        std::cout << "robot_local_x is: " << robot_local_x << std::endl;
        std::cout << "robot_local_y is: " << robot_local_y << std::endl;

        //create a vector in robot local with our vector class
        //this vector is in cartesian
        vector robot_local_vector;
        robot_local_vector.set_coords(robot_local_x, robot_local_y);
        std::cout << "robot_local_vector is: " << robot_local_vector << std::endl;

        //convert to polar coordinates
        std::pair<double, double> robot_local_vector_polar = robot_local_vector.cartesian_to_polar();
        //vars
        double magnitude = robot_local_vector_polar.first;
        double polar_angle = robot_local_vector_polar.second;
        std::cout << "robot_local_vector_polar is: " << robot_local_vector_polar.first << ", " << robot_local_vector_polar.second << std::endl;

        //rotate the angle to the robot_global
        double offset_angle = (start_angle + angle)/2;
        std::cout << "offset_angle is: " << offset_angle << std::endl;

        //convert to radians
        double offset_angle_in_radians = degree_to_radian(offset_angle);
        std::cout << "offset_angle_in_radians is: " << offset_angle_in_radians << std::endl;

        //add the offset angle to the polar angle
        double robot_global_angle = polar_angle + offset_angle;//+or-
        std::cout << "robot_global_angle is: " << robot_global_angle << std::endl;

        //get the robot global vector in polar
        vector robot_global_vector_polar;
        robot_global_vector_polar.set_polar(robot_global_angle, magnitude);
        std::cout << "robot_global_vector_polar is: " << robot_global_vector_polar << std::endl;
        

        //convert to cartesian
        std::pair<double, double> robot_global_vector_cartesian_coords = robot_global_vector_polar.polar_to_cartesian(magnitude, robot_global_angle);
        double robot_global_x = robot_global_vector_cartesian_coords.first;
        double robot_global_y = robot_global_vector_cartesian_coords.second;

        //now we have the robot global vector in cartesian
        vector robot_global_vector_cartesian;
        robot_global_vector_cartesian.set_coords(robot_global_x, robot_global_y);
        std::cout << "robot_global_vector_cartesian is: " << robot_global_vector_cartesian << std::endl;

        //shift to the field_global plane
        std::pair<double, double> field_global_vector_= field_to_robot_global(robot_global_vector_cartesian);
        double field_global_x = field_global_vector_.first;
        double field_global_y = field_global_vector_.second;
        std::cout << "field_global_vector is: " << field_global_x << ", " << field_global_y << std::endl;
    }
};