#include "gps_fake.h"
#include "logging.h"
#include <math.h>

static double t = 0.0; // Simulated time in seconds

bool gps_fake_init(const char *replay_file) {
    LOG_INFO("GPS fake initialized with replay file: %s", replay_file);
    return true;
}

bool gps_fake_next(PosePacket *out) {
    t += 0.017; // Simulate ~60Hz update rate [1/60 seconds]
    out->lat    = 33.7490; // Fixed latitude (Atlanta, GA)
    out->lon    = -84.3880; // Fixed longitude (Atlanta, GA)
    out->heading = fmod(t * 20.0, 360.0); // Simulate heading changing over time
    out->pitch   = 0.0f; // No pitch
    out->roll    = 0.0f; // No roll
    out->speed_ms = 0.0f; // No speed
    return true;
}

void gps_fake_close(void) {
    LOG_INFO("GPS fake closed");
}
