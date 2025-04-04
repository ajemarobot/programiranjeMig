#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

double degrees_to_radians(double angle) {
    return angle * PI / 180.0;
}

double radians_to_degrees(double angle) {
    return angle * 180.0 / PI;
}

struct Vector2D {
    double x, y;
    
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    double dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    
    double cross(const Vector2D& other) const {
        return x * other.y - y * other.x;
    }
    
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag < EPS) return *this;
        return Vector2D(x / mag, y / mag);
    }
    
    double angle_with(const Vector2D& other) const {
        return acos(dot(other) / (magnitude() * other.magnitude()));
    }
    
    Vector2D rotate(double angle) const {
        double cos_theta = cos(angle);
        double sin_theta = sin(angle);
        return Vector2D(
            x * cos_theta - y * sin_theta,
            x * sin_theta + y * cos_theta
        );
    }
};

struct Vector3D {
    double x, y, z;
    
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
    
    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }
    
    Vector3D normalize() const {
        double mag = magnitude();
        if (mag < EPS) return *this;
        return Vector3D(x / mag, y / mag, z / mag);
    }
    
    double angle_with(const Vector3D& other) const {
        return acos(dot(other) / (magnitude() * other.magnitude()));
    }
};

struct Line2D {
    double a, b, c;
    
    Line2D(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}
    
    static Line2D from_points(const Vector2D& p1, const Vector2D& p2) {
        double a = p2.y - p1.y;
        double b = p1.x - p2.x;
        double c = p2.x * p1.y - p1.x * p2.y;
        return Line2D(a, b, c);
    }
    
    double distance_to(const Vector2D& p) const {
        return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }
};

struct Circle2D {
    Vector2D center;
    double radius;
    
    Circle2D(const Vector2D& center = Vector2D(), double radius = 0) 
        : center(center), radius(radius) {}
    
    bool contains(const Vector2D& p) const {
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        return dx * dx + dy * dy <= radius * radius + EPS;
    }
    
    static Circle2D from_three_points(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3) {
        Vector2D mid1 = (p1 + p2) * 0.5;
        Vector2D mid2 = (p2 + p3) * 0.5;
        
        Vector2D dir1 = (p2 - p1).rotate(PI/2);
        Vector2D dir2 = (p3 - p2).rotate(PI/2);
        
        Line2D line1 = Line2D::from_points(mid1, mid1 + dir1);
        Line2D line2 = Line2D::from_points(mid2, mid2 + dir2);
        
        double det = line1.a * line2.b - line2.a * line1.b;
        if (abs(det) < EPS) {
            return Circle2D();
        }
        
        double x = (line1.b * line2.c - line2.b * line1.c) / det;
        double y = (line2.a * line1.c - line1.a * line2.c) / det;
        Vector2D center(x, y);
        
        return Circle2D(center, (center - p1).magnitude());
    }
};

struct Parabola2D {
    double a, b, c;
    
    Parabola2D(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}
    
    static Parabola2D from_three_points(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3) {
        double det = p1.x*p1.x*(p2.x - p3.x) - p1.x*(p2.x*p2.x - p3.x*p3.x) + (p2.x*p2.x*p3.x - p2.x*p3.x*p3.x);
        if (abs(det) < EPS) {
            return Parabola2D();
        }
        
        double a = (p1.y*(p2.x - p3.x) - p2.y*(p1.x - p3.x) + p3.y*(p1.x - p2.x)) / det;
        double b = (p1.x*p1.x*(p2.y - p3.y) - p2.x*p2.x*(p1.y - p3.y) + p3.x*p3.x*(p1.y - p2.y)) / det;
        double c = (p1.x*p1.x*(p2.x*p3.y - p2.y*p3.x) - p1.x*(p2.x*p2.x*p3.y - p2.y*p3.x*p3.x) + 
                  p1.y*(p2.x*p2.x*p3.x - p2.x*p3.x*p3.x)) / det;
        
        return Parabola2D(a, b, c);
    }
    
    double evaluate(double x) const {
        return a * x * x + b * x + c;
    }
};

struct Point2D {
    int x, y;
    Point2D(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}
    
    bool operator<(const Point2D& other) const {
        if (x != other.x) 
            return x < other.x;
        return y < other.y;
    }
};

bool is_right_turn(Point2D p, Point2D q, Point2D r) {
    int det = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    return det <= 0; 
}

void compute_convex_hull_edges() {
    int n;
    cin >> n;
    vector<Point2D> points;
    set<pair<Point2D, Point2D>> edges; 
    
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            
            Point2D p = points[i];
            Point2D q = points[j];
            bool valid = true;
            
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                
                Point2D r = points[k];
                if (!is_right_turn(p, q, r)) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                edges.insert({p, q});
            }
        }
    }
    
    for (const auto& edge : edges) {
        Point2D a = edge.first;
        Point2D b = edge.second;
        cout << "(" << a.x << ", " << a.y << ") -> (" << b.x << ", " << b.y << ")" << endl;
    }
}

struct Point {
    double e[3];

    Point(double x = 0.0, double y = 0.0, double w = 0.0) {
        e[0] = x;
        e[1] = y;
        e[2] = w;
    }
};

struct Matrix {
    double m[3][3] = {0};
    
    Matrix() {
        for (int i = 0; i < 3; i++) {
            m[i][i] = 1;
        }
    }
    
    Matrix(int v) {
        for (int i = 0; i < 3; i++) {
            m[i][i] = v;
        }
    }
    
    double &at(int x, int y) {
        return m[x][y];
    }
    
    Matrix operator*(const Matrix &second) {
        Matrix result(0);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    result.m[i][j] += m[i][k] * second.m[k][j];
                }
            }
        }
        return result;
    }
    
    Point operator*(const Point &second) {
        Point result;
        for (int i = 0; i < 3; i++) {
            result.e[i] = 0;
            for (int j = 0; j < 3; j++) {
                result.e[i] += m[i][j] * second.e[j];
            }
        }
        return result;
    }
};

class Point3D {
private:
    double x, y, z;
public:
    Point3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}

    Point3D rotateX(double angle) const {
        double rad = angle * M_PI / 180.0;
        double newY = y * cos(rad) - z * sin(rad);
        double newZ = y * sin(rad) + z * cos(rad);
        return Point3D(x, newY, newZ);
    }

    Point3D rotateY(double angle) const {
        double rad = angle * M_PI / 180.0;
        double newX = x * cos(rad) + z * sin(rad);
        double newZ = -x * sin(rad) + z * cos(rad);
        return Point3D(newX, y, newZ);
    }

    Point3D rotateZ(double angle) const {
        double rad = angle * M_PI / 180.0;
        double newX = x * cos(rad) - y * sin(rad);
        double newY = x * sin(rad) + y * cos(rad);
        return Point3D(newX, newY, z);
    }

    Point3D translate(double dx, double dy, double dz) const {
        return Point3D(x + dx, y + dy, z + dz);
    }

    Point3D scale(double sx, double sy, double sz, double cx = 0, double cy = 0, double cz = 0) const {
        double newX = cx + (x - cx) * sx;
        double newY = cy + (y - cy) * sy;
        double newZ = cz + (z - cz) * sz;
        return Point3D(newX, newY, newZ);
    }

    friend ostream &operator<<(ostream &os, const Point3D &p) {
        os << fixed << setprecision(4) << "(" << p.x << ", " << p.y << ", " << p.z << ")\n";
        return os;
    }
};

ostream &operator<<(ostream &os, const Matrix &matrix) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            os << matrix.m[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const Point &p) {
    os << "[ ";
    for (int i = 0; i < 3; i++) {
        os << p.e[i] << " ";
    }
    os << "]" << endl;
    return os;
}

int main() {
    cout << "2D Convex Hull Edges:" << endl;
    compute_convex_hull_edges();
    
    cout << "\n2D Vector Operations:" << endl;
    Vector2D v1(1, 2), v2(3, 4);
    cout << "v1 + v2 = (" << (v1 + v2).x << ", " << (v1 + v2).y << ")\n";
    cout << "v1 - v2 = (" << (v1 - v2).x << ", " << (v1 - v2).y << ")\n";
    cout << "v1 * 3 = (" << (v1 * 3).x << ", " << (v1 * 3).y << ")\n";
    cout << "Dot product: " << v1.dot(v2) << "\n";
    cout << "Cross product: " << v1.cross(v2) << "\n";
    cout << "Angle between: " << radians_to_degrees(v1.angle_with(v2)) << " degrees\n\n";
    
    Vector2D p1(1, 1), p2(4, 5);
    Line2D line = Line2D::from_points(p1, p2);
    Vector2D p_test(2, 3);
    cout << "Line equation: " << line.a << "x + " << line.b << "y + " << line.c << " = 0\n";
    cout << "Distance from point to line: " << line.distance_to(p_test) << "\n\n";
    
    Vector2D p3(6, 2);
    Circle2D circle = Circle2D::from_three_points(p1, p2, p3);
    cout << "Circle center: (" << circle.center.x << ", " << circle.center.y << ")\n";
    cout << "Circle radius: " << circle.radius << "\n";
    cout << "Point in circle: " << (circle.contains(p_test) ? "Yes" : "No") << "\n\n";
    
    Parabola2D parabola = Parabola2D::from_three_points(p1, p2, p3);
    cout << "Parabola equation: y = " << parabola.a << "x² + " << parabola.b << "x + " << parabola.c << "\n";
    cout << "Parabola at x=2: y=" << parabola.evaluate(2) << "\n\n";
    
    cout << "2D Transformations:" << endl;
    Matrix first;
    Matrix second;

    first.m[0][2] = 3;
    second.m[0][0] = 0.5;
    Matrix rot;
    rot.m[0][0] = cos(M_PI / 2);
    rot.m[1][1] = cos(M_PI / 2);
    rot.m[0][1] = -sin(M_PI / 2);
    rot.m[1][0] = sin(M_PI / 2);
    Point p1(3, 1, 1);
    Matrix result = first * second;
    Point p2 = rot * p1;
    cout << p2;
    cout << result;
    cout << "3D Transformations:" << endl;
    Point3D p3D1(-1, 5, 0), p3D2(2, 2, 2);
    cout << p3D1.rotateX(-45);
    cout << p3D1.translate(1, 10, -25);
    cout << p3D2.scale(2, 2, 2);
    cout << p3D2.scale(2, 2, 2, 1, 1, 1);
    cout << p3D1.rotateY(180);
    Vector3D v3d1(1, 2, 3), v3d2(4, 5, 6);
    cout << "3D Vector Operations:\n";
    cout << "Cross product: (" << v3d1.cross(v3d2).x << ", " 
         << v3d1.cross(v3d2).y << ", " << v3d1.cross(v3d2).z << ")\n";
    cout << "Angle between: " << radians_to_degrees(v3d1.angle_with(v3d2)) << " degrees\n";

    return 0;
}
