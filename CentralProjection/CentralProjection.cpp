#include <stdio.h>
#include "R3Graph/R3Graph.h"
#include "math.h"

using namespace R3Graph;

const double R_EARTH = 6371000;

R3Vector radiusVector(double lat, double lon);

R3Point intersect(
        const R3Point& p0,
        const R3Vector& norm, //normal vector of plane
        const R3Point& p1,
        const R3Vector& dir //directional vector of line
        );

int main()
{
    while(true) {
        double lat0, lat1, lon0, lon1;
        printf("Enter coordinate of central point: \n");
        if(scanf("%lf %lf", &lat0, &lon0) < 2)
            break;

        printf("Enter coordinate of projective point: \n");
        if(scanf("%lf %lf",  &lat1, &lon1) < 2)
            break;

        R3Vector OP = radiusVector(lat0, lon0); // Centre of new system
        R3Vector OM = radiusVector(lat1, lon1); // Projective point

        R3Vector ez = R3Vector(0., 0., 1.);
        R3Vector ex = ez.vectorProduct(OP);
        ex.normalize();
        R3Vector ey = OP.vectorProduct(ex);
        ey.normalize();

        R3Point X = R3Point(ex.x, ex.y, ex.z) + OP;
        R3Point Q = intersect(X, OP, R3Point(0., 0., 0.), OM);
        R3Vector PQ = R3Vector(Q.x - OP.x, Q.y - OP.y, Q.z - OP.z);

        double x = PQ.scalarProduct(ex);
        double y = PQ.scalarProduct(ey);
        printf("Coordinates of projective point are %.0f %.0f \n", x, y);
    }
    return 0;
}

R3Vector radiusVector(double lat, double lon)
{
    double phi = lat*M_PI/180;
    double lambda = lon*M_PI/180;
    return R_EARTH * R3Vector(cos(phi)*cos(lambda),cos(phi)*sin(lambda),sin(phi));
}

R3Point intersect(
        const R3Point& p0,
        const R3Vector& norm, //normal vector of plane
        const R3Point& p1,
        const R3Vector& dir //directional vector of line
        )
{
    double s = norm.scalarProduct(dir);
    double t = (p0 - p1).scalarProduct(norm) / s;
    return p1 + dir*t;
}

