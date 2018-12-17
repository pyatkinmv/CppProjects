#include <stdio.h>
#include "R3Graph/R3Graph.h"
#include "math.h"
using namespace R3Graph;

R3Vector radiusVector(double lat, double lon);

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

    R3Vector OP = radiusVector(lat0, lon0); // Центр новой системы
    R3Vector OM = radiusVector(lat1, lon1); // Проективная точка
    R3Vector ez = R3Vector(0., 0., 1.);

    R3Vector ex = ez.vectorProduct(OP);
    ex.normalize();
    R3Vector ey = OP.vectorProduct(ex);
    ey.normalize();

    double t =
    (OP.x*(ex.y + ey.z - ex.z - ey.y) + OP.y*(ex.z+ey.x-ex.x-ey.z) + OP.z*(ex.x+ey.y-ex.y-ey.x))/
    (OM.x*(ex.y + ey.z - ex.z - ey.y) + OM.y*(ex.z+ey.x-ex.x-ey.z) + OM.z*(ex.x+ey.y-ex.y-ey.x));

    R3Point Q = R3Point(OM.x*t, OM.y*t, OM.z*t);

    R3Vector OQ = R3Vector(Q.x - OP.x, Q.y - OP.y, Q.z - OP.z);

    double x = OQ.scalarProduct(ex);
    double y = OQ.scalarProduct(ey);

    printf("Coordinates of projective point are %f %f \n", x, y);
  }
   return 0;
}

R3Vector radiusVector(double lat, double lon){
  double phi = lat*M_PI/180.;
  double lambda = lon*M_PI/180.;
  return R3Vector(cos(phi) * cos(lambda), cos(phi)*sin(lambda),sin(phi));
}
