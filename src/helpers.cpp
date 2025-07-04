#include <cmath>
#include <utility>
#include "tracking_system.hpp"
#include "helpers.hpp"
#include <numbers>
#include <iostream>

double pi = std::numbers::pi;

//vector class definition

    
    //methods
    //setter
    void vector::set_coords(double x_coord, double y_coord){
        x = x_coord;
        y = y_coord;
    }
    void vector::set_polar(double angle_in_radians, double magnitude) {
        polar_angle = angle_in_radians;
        magnitude = magnitude;
    }
    //cartesian to polar conversion
    std::pair<double, double> vector::cartesian_to_polar() const {
        double magnitude = sqrt(x*x + y*y);
        double polar_angle = atan2(y,x);
        return std::make_pair(magnitude, polar_angle);
    }

    //polar to cartesian conversion
    std::pair<double, double> vector::polar_to_cartesian(double magnitude, double polar_angle) const {
        double x_coord = magnitude * cos(polar_angle);
        double y_coord = magnitude * sin(polar_angle);
        return std::make_pair(x_coord, y_coord);
    }
    
    std::ostream& operator<<(std::ostream& os, const vector& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
    }

//degree to radian conversion method
double degree_to_radian(double degree){
    return degree * (pi / 180.0);
}

//radian to degree conversion method
double radian_to_degree(double radian){
    return radian * (180.0 / pi);
}


//field to robot global conversion
std::pair<double, double> field_to_robot_global(vector robot_global_vector){
    double field_global_x = robot_global_vector.x + robot_to_field_x_scaling + start_vertical;
    double field_global_y = robot_global_vector.y + robot_to_field_y_scaling + start_horizontal;
    return std::make_pair(field_global_x, field_global_y);
}