#include "figure.h"
#include <stdio.h>

int main() {
    double radius, width, height;
    double x, y;
    while(true) {
        printf("Coordinates of central point of circle: \n");
        if(scanf("%lf %lf", &x, &y) < 2)
            break;
        Point centre = Point(x, y);

        printf("Radius of circle: \n");
        if(scanf("%lf",  &radius) < 1)
            break;

        Figure *circle = new Circle(centre, radius);
        printf("Square of ");
        circle->showDescription();
        printf(" is %lf \n",circle->getSquare());


        printf("Coordinates of left bottom point of rectangle: \n");
        if(scanf("%lf %lf", &x, &y) < 2)
            break;
        Point leftBot = Point(x, y);

        printf("Enter width of rectangle: \n");
        if(scanf("%lf",  &width) < 1)
            break;

        printf("Enter height of rectangle: \n");
        if(scanf("%lf",  &height) < 1)
            break;
        Figure *rect = new Rectangle(leftBot, width, height);
        printf("Square of ");
        rect->showDescription();
        printf(" is %lf \n ",rect->getSquare());


        printf("Coordinates of a point of triangle: \n");
        if(scanf("%lf %lf", &x, &y) < 2)
            break;
        Point a = Point(x, y);
        printf("Coordinates of b point of triangle: \n");
        if(scanf("%lf %lf", &x, &y) < 2)
            break;
        Point b = Point(x, y);
        printf("Coordinates of c point of triangle: \n");
        if(scanf("%lf %lf", &x, &y) < 2)
            break;
        Point c = Point(x, y);
        Figure *tr = new Triangle(a, b, c);
        printf("Square of ");
        tr->showDescription();
        printf(" is %lf \n ",tr->getSquare());


        printf("Coordinates of some point: \n");
        if(scanf("%lf %lf", &x, &y) < 2)
            break;
        Point point = Point(x,y);
        printf("The point %s in the circle\n", circle->contains(point) ? "is" : "is not");
        printf("The point %s in the rectangle \n", rect->contains(point) ? "is" : "is not");
        printf("The point %s in the triangle \n \n \n", tr->contains(point) ? "is" : "is not");
    }
    return 0;
}
