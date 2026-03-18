# AR Overlay

A real-time augmented reality overlay that projects OpenStreetMap (OSM) road data onto live camera footage using GPS and IMU telemetry. Built for aircraft and UAVs.

Inspired by news helicopters with street overlays, showing road labels and headings, rendered directly onto the camera view.

## Note

This project is primarily a learning exercise in C. I'm starting from zero experience with the language,
and am using tutorials, documentation, videos, and LLM assistance throughout. All code is written and
understood by hand; this is a learning project first.

## Roadmap

- [ ] Ground station renderer with fake sensor backend
- [ ] OSM road vector projection
- [ ] Replay file support with scripted flight paths
- [ ] Onboard Microcontroller (maybe Pi Zero) stream transmitter
- [ ] Live video + telemetry integration
- [ ] Street label rendering along road curves
- [ ] Cross-compile to ARM64 via CMake toolchain file
- [ ] Custom PCB (stretch goal)

## Getting Started

<!-- ### Dependencies

- # apt install -y build-essential cmake git gcc
- [- ylib dependencies](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#Dependencies)

-->

### Linux Build Instructions

*Proper Dependencies & Build Instructions coming once the project matures.*

```sh
# Enter root directory
$ cd ar-overlay

# Create "build" directory then navigate into it
$ mkdir build && cd build

# Generate build files
$ cmake ..

# Build the program
$ make -j$(nproc)

# Run the program
$ ./ground/ground_station
```
