#include "render/overlay.h"
#include "sensors/gps_fake.h"
#include "logging.h"
#include <raylib.h>

int main(void) {
    LOG_INFO("Starting AR Overlay Ground Station");

    gps_fake_init(NULL);
    overlay_init(1280, 720);

    PosePacket pose = {0};

    while (!WindowShouldClose()) {
        if (gps_fake_next(&pose)) {
            overlay_draw(&pose);
        } else {
            LOG_WARN("Failed to get next GPS data");
        }
    }

    overlay_close();
    gps_fake_close();
    LOG_INFO("AR Overlay Ground Station exiting");
    return 0;
}