//============================================================
// STUDENT NAME: <your name>
// MATRIC NO.  : <matric no.>
// NUS EMAIL   : <your NUS email address>
// COMMENTS TO GRADER:
// <comments to grader, if any>
//
// ============================================================
//
// FILE: Sphere.cpp



#include <cmath>
#include "Sphere.h"

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
	//***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    Vector3d rO = r.origin() - center;
	double dRd = dot( r.direction(), r.direction() );
    double dRo = dot( r.direction(), rO);
    double oRo = dot( rO, rO );
    double a = dRd;
    double b = 2 * dRo;
    double c = oRo - radius * radius; 
    double discriminant = b * b - 4 * a * c;
    double t = 0;
    if ( discriminant < 0 ) return false; 
    if ( discriminant == 0 ) {
        t =  (-1 * b ) / (2 * a);
        if ( t < 0 ) return false;
    } else {
        double t1 = (-1 * b + sqrt(discriminant)) / (2 * a);
        double t2 = (-1 * b - sqrt(discriminant)) / (2 * a);
        if ( t1 > t2 && t2 > 0 ) {
            t = t2; 
        } else if ( t1 > 0 ) {
            t = t1; 
        } else {
            return false;
        }
    }

	if ( t < tmin || t > tmax ) return false;
	// We have a hit -- populat hit record. 
	rec.t = t;
	rec.p = r.pointAtParam(t);
	Vector3d normal = rec.p - center;
	rec.normal = normal / normal.length(); 
	rec.mat_ptr = matp;
	return true;

}




bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
	//***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************

	Vector3d rO = r.origin() - center;
	double dRd = dot( r.direction(), r.direction() );
    double dRo = dot( r.direction(), rO);
    double oRo = dot( rO, rO );
    double a = dRd;
    double b = 2 * dRo;
    double c = oRo - radius * radius; 
    double discriminant = b * b - 4 * a * c;
    double t = 0;
    if ( discriminant < 0 ) return false; 
    if ( discriminant == 0 ) {
        t =  (-1 * b ) / (2 * a);
        if ( t < 0 ) return false;
    } else {
        double t1 = (-1 * b + sqrt(discriminant)) / (2 * a);
        double t2 = (-1 * b - sqrt(discriminant)) / (2 * a);
        if ( t1 > t2 && t2 > 0 ) {
            t = t2; 
        } else if ( t1 > 0 ) {
            t = t1; 
        } else {
            return false;
        }
    }

	return ( t >= tmin && t <= tmax );
}

