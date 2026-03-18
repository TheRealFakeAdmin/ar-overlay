#include "geo_math.h"
#include <math.h>

#define EARTH_RADIUS_M 6371000.0

// Convert degrees to radians
double deg_to_rad(double deg) {
    return deg * M_PI / 180.0;
}

/*
    * Calculate the distance between two geographic coordinates using the Haversine formula.
    * Parameters:
    *   lat1, lon1: Latitude and longitude of the first point in degrees.
    *   lat2, lon2: Latitude and longitude of the second point in degrees.
    * Returns:
    *   Distance between the two points in meters.
*/
double geo_distance_m(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitudes and longitudes from degrees to radians
    double dlat = deg_to_rad(lat2 - lat1);
    double dlon = deg_to_rad(lon2 - lon1);

    // Calculate the components of the Haversine formula
    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(deg_to_rad(lat1)) * cos(deg_to_rad(lat2)) *
               sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Calculate the distance in meters
    return EARTH_RADIUS_M * c;
}

/*
    * Calculate the bearing from the first point to the second point.
    * Parameters:
    *   lat1, lon1: Latitude and longitude of the first point in degrees.
    *   lat2, lon2: Latitude and longitude of the second point in degrees.
    * Returns:
    *   Bearing from the first point to the second point in degrees, normalized to [0, 360).
*/
double geo_bearing(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitudes and longitudes from degrees to radians
    double dlon = deg_to_rad(lon2 - lon1);
    
    // Calculate the components of the bearing
    double y = sin(dlon) * cos(deg_to_rad(lat2));
    double x = cos(deg_to_rad(lat1)) * sin(deg_to_rad(lat2)) -
               sin(deg_to_rad(lat1)) * cos(deg_to_rad(lat2)) * cos(dlon);

    // Calculate the bearing in degrees
    double bearing = atan2(y, x) * 180.0 / M_PI;

    // Normalize the bearing to [0, 360)
    return fmod((bearing + 360.0), 360.0); // Normalize to [0, 360)
}