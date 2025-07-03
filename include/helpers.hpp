
class vector {
public:
    double x;
    double y;
    double polar_angle;
    double magnitude;

    void set_coords(double x_coord, double y_coord);
    void set_polar(double angle_in_radians, double magnitude);

    std::pair<double, double> cartesian_to_polar() const;
    std::pair<double, double> polar_to_cartesian(double magnitude, double polar_angle) const;
    std::pair<double, double> field_to_robot_global() const;
};

double degree_to_radian(double degree){}

double radian_to_degree(double radian){}

std::pair<double, double> field_to_robot_global(){}