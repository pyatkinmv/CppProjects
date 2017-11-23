//#include "stdafx.h"
 #include <iostream>
 #include <math.h>

 using namespace std;
 //базовый класс figure
 const double  PI =  3.14159;
 const double R2GRAPH_EPSILON = 0.0000001;
class Point {
public:
    double x;
    double y;

    Point():                         // Default constructor
        x(0.),
        y(0.)
    {}

    Point(const Point& p):        // Copy-constructor
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
        return sqrt(pow(x - b.x, 2) + pow(y - b.y, 2));
    }

    // Comparings
    bool operator==(const Point& p) const {
        //... return (x == p.x && y == p.y);
        return (
            fabs(x - p.x) <= R2GRAPH_EPSILON &&
            fabs(y - p.y) <= R2GRAPH_EPSILON
        );
    }
    bool operator!=(const Point& p) const { return !operator==(p); }
    bool operator>=(const Point& p) const {
        //... return (x > p.x || (x == p.x && y >= p.y));
        return (x > p.x || (x >= p.x && y >= p.y));
    }
    bool operator>(const Point& p) const {
        //... return (x > p.x || (x == p.x && y > p.y));
        return (x > p.x || (x >= p.x && y > p.y));
    }
    bool operator<(const Point& p) const { return !operator>=(p); }
    bool operator<=(const Point& p) const { return !operator>(p); }

};

class Figure {
public:
    //конструктор класса фигуры
    Figure() {
        cout<<" Это абстрактный конструктор "<<endl;
    }

    virtual double getSquare()
    {
       cout<<" Квадратная фигура не абстрактна "<<endl;
       return 0;
    }
    virtual void showDescription()
    {
       cout<<" Абстрактная фигура ";
    }
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
        centre(centre),
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

    Point getCentre() const { return centre; }
    double getRadius() const { return radius; }

    void setCentre(Point _centre) { centre = _centre; }
    void setRadius(double _radius) { radius = _radius; }

    bool contains(const Point& p2) const {
        return centre.distance(p2) <= radius;
    }

    double getSquare() {
       return PI * pow(radius, 2);
    }

     bool empty() const {
         return (radius < 0.);
     }
};


class Rectangle: public Figure {
    Point p;
    double width;   // width
    double height;   // height
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

    Point getLeftBottom() const { return p; }
    double getWidth() const { width; }
    double getHeight() const { return height; }

    void setLeftBottom(Point p2) { p = p2; }
    void setWidth(double _width) { width = _width; }
    void setHeight(double _height) { height = _height; }


    double getSquare() {
       return width * height;
    }

    bool contains(const Point& p2) const {
        return (
            p.x <= p2.x && p2.x < p.x + width &&
            p.y <= p2.y && p2.y < p.y + height
        );
    }

     bool empty() const {
         return (width < 0. || height < 0.);
     }
 };

 //главная функция
int main() {
    setlocale(LC_ALL,"Rus");
    Point p(0.,0.);
    Point p2(-1.,1.);
    Rectangle rect(p,5.,7.);
    Circle circle(p, 4.);
    cout<<rect.contains(p2)<< " square: "<< rect.getSquare()<< endl;
    cout<<circle.contains(p2)<<" square: "<<circle.getSquare()<< endl;
    //system("pause");
    return 0;
}
