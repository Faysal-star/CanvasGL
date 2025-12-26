#ifndef POINT_H
#define POINT_H


class Point {
public:
    float x, y, z = 1.0f;
    Point(float x_, float y_, float z_ = 1.0f) : x(x_), y(y_), z(z_) {}
};

inline Point project(Point p) {
        return Point(p.x / p.z, p.y / p.z, p.z);
}

inline Point translateZ(Point p, float dz) {
    return Point(p.x, p.y, p.z + dz);
}

inline Point rot_xz(Point p, float angle) {
    double c = cos(angle);
    double s = sin(angle);

    return Point(
        p.x * c - p.z * s,
        p.y,
        p.x * s + p.z * c
    );
}

inline Point rot_yz(Point p, float angle) {
    double c = cos(angle);
    double s = sin(angle);

    return Point(
        p.x,
        p.y * c - p.z * s,
        p.y * s + p.z * c
    );
}

inline Point rot_xy(Point p, float angle) {
    double c = cos(angle);
    double s = sin(angle);

    return Point(
        p.x * c - p.y * s,
        p.x * s + p.y * c,
        p.z
    );
}

#endif // POINT_H