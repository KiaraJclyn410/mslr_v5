#include <iostream>
#include <numbers>

class vector{
    public:
    //attributes
    double x;
    double y;
    double polar_angle; //in radians
    double magnitude;
    //methods
    void set_coords(double x_coord, double y_coord);
    void set_polar(double angle_in_radians, double magnitude);

    std::pair<double, double> cartesian_to_polar() const;
    std::pair<double, double> polar_to_cartesian(double magnitude, double polar_angle) const;

    friend std::ostream& operator<<(std::ostream& os, const vector& v);
};

double degree_to_radian(double degree);

double radian_to_degree(double radian);

std::pair<double, double> field_to_robot_global(vector robot_global_vector);