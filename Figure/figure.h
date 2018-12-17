#include <stdio.h>
#include <math.h>

using namespace std;
const double  PI =  3.141596;
const double EPSILON = 0.0000001;

class Point {
public:
    double x;
    double y;

    Point(): 
        x(0.),
        y(0.)
    {}

    Point(const Point& p):        
        x(p.x),
        y(p.y)
    {}

    Point(double xx, double yy):
        x(xx),
        y(yy)
    {}

    Point& operator=(const Point& p) {    // Copy-operator
        x = p.x; y = p.y;
        return *this;
    }

    ~Point() {}                              // Destructor

    Point operator+(const Point& p) const {
        return Point(x+p.x, y+p.y);
    }

    Point operator-(const Point& p) const {
        return Point(x-p.x, y-p.y);
    }

    Point& operator+=(const Point& p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator-=(const Point& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point operator*(double c) const {
        return Point(x*c, y*c);
    }

    Point& operator*=(double c) {
        x *= c;
        y *= c;
        return *this;
    }

    double distance (const Point& b) const {
        return sqrt((x - b.x)*(x - b.x) + (y - b.y)*(y - b.y));
    }

    bool operator==(const Point& p) const {
        return (
        fabs(x - p.x) <= EPSILON &&
        fabs(y - p.y) <= EPSILON
        );
    }
    bool operator!=(const Point& p) const { return !operator==(p); }
    bool operator>=(const Point& p) const {
        return (x > p.x || (x >= p.x && y >= p.y));
    }
    bool operator>(const Point& p) const {
        return (x > p.x || (x >= p.x && y > p.y));
    }
    bool operator<(const Point& p) const { return !operator>=(p); }
    bool operator<=(const Point& p) const { return !operator>(p); }
    void showDescription() {
        printf("Point");
    }
};

class Figure {
public:
    Figure()
    {}

    virtual ~Figure(){}

    virtual double getSquare() {
        return 0;
    }
    virtual void showDescription() {
        printf("Abstract Figure");
    }
    virtual bool contains(const Point& p2) const = 0;
};

class Circle: public Figure {
    Point centre;
    double radius;
public:
    Circle():
        centre(Point(0., 0.)),
        radius(0.)
    {}

    Circle(const Point& _centre, double _radius):
        centre(_centre),
        radius(_radius)
    {}


    Circle(const Circle& c):
        centre(c.centre),
        radius(c.radius)
    {}

    ~Circle() {}

    Circle& operator=(const Circle& c) {
        centre = c.centre;
        radius = c.radius;
        return *this;
    }

    bool operator==(const Circle& c) const {
        return (
        fabs(centre.distance(c.centre)) <= EPSILON &&
        fabs(radius - c.radius) <= EPSILON );
    }
    bool operator!=(const Circle& c) const { return !operator==(c); }

    Point getCentre() const { return centre; }
    double getRadius() const { return radius; }

    void setCentre(Point _centre) { centre = _centre; }
    void setRadius(double _radius) { radius = _radius; }

    bool contains(const Point& p2) const;

    double getSquare() {
        return PI * pow(radius, 2);
    }

    void showDescription() {
        printf("Circle");
    }
};

class Rectangle: public Figure {
    Point p;
    double width;
    double height;
public:
    Rectangle():
        p(Point(0.,0.)),
        width(0.),
        height(0.)
    {}

    Rectangle(const Point& p2, double _width, double _height):
        p(p2),
        width(_width),
        height(_height)
    {}

    Rectangle(const Rectangle& r):
        p(r.p),
        width(r.width),
        height(r.height)
    {}

    ~Rectangle() {}

    Rectangle& operator=(const Rectangle& r) {
        p = r.p;
        width = r.width;
        height = r.height;
        return *this;
    }

    bool operator==(const Rectangle& rect) const {
        return (
        fabs(p.distance(rect.getLeftBottom())) <= EPSILON &&
        fabs(width - rect.getWidth()) <= EPSILON &&
        fabs(height - rect.getHeight()) <= EPSILON
        );
    }
    bool operator!=(const Rectangle& rect) const { return !operator==(rect); }


    Point getLeftBottom() const { return p; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }

    void setLeftBottom(Point p2) { p = p2; }
    void setWidth(double _width) { width = _width; }
    void setHeight(double _height) { height = _height; }


    double getSquare() {
        return width * height;
    }

    bool contains(const Point& p2) const;

    void showDescription() {
        printf("Rectangle");
    }
};

class Triangle: public Figure {
    Point a;
    Point b;
    Point c;
public:
    Triangle():
        a(Point(0.,0.)),
        b(Point(0.,0.)),
        c(Point(0.,0.))
    {}

    Triangle(const Point& _a, const Point& _b, const Point& _c):
        a(_a),
        b(_b),
        c(_c)
    {}

    Triangle(const Triangle& t):
        a(t.a),
        b(t.b),
        c(t.c)
    {}

    ~Triangle() {}

    Triangle& operator=(const Triangle& t) {
        a = t.a;
        b = t.b;
        c = t.c;
        return *this;
    }

    bool operator==(const Triangle& t) const {
        return (
        fabs(a.distance(t.getA())) <= EPSILON &&
        fabs(b.distance(t.getB())) <= EPSILON &&
        fabs(c.distance(t.getC())) <= EPSILON
    );
    }
    bool operator!=(const Triangle& t) const { return !operator==(t); }


    Point getA() const { return a; }
    Point getB() const { return b; }
    Point getC() const { return c; }

    void setA(Point _a) { a = _a; }
    void setB(Point _b) { b = _b; }
    void setC(Point _c) { c = _c; }

    double getSquare() {
        double p = (a.distance(b) + b.distance(c) + a.distance(c))/2;
        return sqrt(p*(p - a.distance(b))*(p - b.distance(c))*(p - a.distance(c)));
    }

    bool contains(const Point& p) const;

    void showDescription() {
        printf("Triangle");
    }
};
