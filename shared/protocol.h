#pragma once
#include <stdint.h>

typedef struct {
    double lat;
    double lon;
    float heading;
    float pitch;
    float roll;
    float speed_ms;
} PosePacket;
