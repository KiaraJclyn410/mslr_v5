#include <iostream>
#include <cmath>
#include "tracking_system.hpp"
#include "pros/rotation.hpp"
#include <numbers>
#include <list>

double pi = std::numbers::pi;


void tracking_loop (){
    while (true){
        //get the starting value for this cycle
        double start_horizontal = horizontal_rotation.get_position();
        double start_vertical = vertical_rotation.get_position();
        double start_angle = imu_sensor.get_rotation();

        //get the current values for this cycle
        double horizontal_wheel = horizontal_rotation.get_position();
        double vertical_wheel = vertical_rotation.get_position();
        double angle = imu_sensor.get_rotation();

        //get the differences to use in this timeframe's calculations
        double distance_vertical = vertical_wheel - start_vertical;
        double distance_horizontal = horizontal_wheel - start_horizontal;
        double difference_angle = angle - start_angle;

        //update the starting values for the next cycle
        start_horizontal = start_horizontal + distance_horizontal;
        start_vertical = start_vertical + distance_vertical;

        //normalize "angle" here
        double normalized_angle = fmod(angle, 360.0);

        //turn to radians
        double angle_in_radians = normalized_angle * (pi / 180.0);

        //find the arc radius
        double arc_radius = distance_vertical/angle_in_radians + vertical_wheel_to_center_distance;

        //find the chord length
        double y_axis = 2 * arc_radius * sin(angle_in_radians/2);

        //calculate the shift, aka x-axis
        double x_axis = horizontal_wheel/angle_in_radians + horizontal_wheel_to_center_distance;

        //calculate the distance vector in the local coordinate system
        double local_vector_y = 2 * sin(angle_in_radians/2) * y_axis;
        double local_vector_x = 2 * sin(angle_in_radians/2) * x_axis;
        std::local_vector<double> = {local_vector_x, local_vector_y};
    }
}