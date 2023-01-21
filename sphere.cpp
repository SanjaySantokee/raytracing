#include <iostream>
#include <cmath>

// A simple structure to represent a 3D vector
struct Vec3 {
    double x, y, z;

    Vec3 operator+(const Vec3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(const Vec3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() const {
        return *this * (1 / length());
    }
};

// A function to calculate dot product of two 3D vectors
double dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// A simple structure to represent a sphere
struct Sphere {
    Vec3 center;
    double radius;
};

// A function to check if a ray intersects with a sphere
bool intersect(const Vec3 &origin, const Vec3 &direction, const Sphere &sphere, double &t) {
    Vec3 oc = origin - sphere.center;
    double a = direction.length();
    double b = 2 * dot(oc, direction);
    double c = oc.length() - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }
    t = (-b - sqrt(discriminant)) / (2 * a);
    return true;
}

int main() {
    const int width = 800;
    const int height = 600;

    // Create a simple scene with a single sphere
    Sphere sphere = {{0, 0, -1}, 0.5};

    // Iterate over each pixel
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double u = (2 * (i + 0.5) / (double)width - 1) * tan(M_PI / 4);
            double v = (1 - 2 * (j + 0.5) / (double)height) * tan(M_PI / 4);
            Vec3 direction = (Vec3{u, v, -1}).normalize();
            double t;
            if (intersect({0, 0, 0}, direction, sphere, t)) {
                // The ray intersected with the sphere, so we color the pixel
                std::cout << "o";
            } else {
                // The ray missed the sphere, so we leave the pixel black
                std::cout << ".";
            }
        }
    }

    return 0;
}