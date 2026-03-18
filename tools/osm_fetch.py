#!/usr/bin/env python3
"""
Fetch road data from Overpass API and write it to a .roads file.

Usage:
    python3 osm_fetch.py --lat <latitude> --lon <longitude> --radius <radius_in_meters> --out <output_file.roads>

Example:
    python3 osm_fetch.py --lat 37.7749 --lon -122.4194 --radius 1000 --out ../data/maps/san_francisco.roads
"""

import argparse
import json
import urllib.request
import urllib.parse
import sys

OVERPASS_API_URL = "https://overpass-api.de/api/interpreter"

def fetch_osm_roads(lat, lon, radius_m):
    # Construct query to fetch roads within specified radius
    query = f"""
    [out:json][timeout:25];
    (
      way["highway"](around:{radius_m},{lat},{lon});
    );
    out body;
    >;
    out skel qt;
    """
    
    data = urllib.parse.urlencode({'data': query}).encode()
    req = urllib.request.Request(OVERPASS_API_URL, data=data)
    print(f"Overpass API: Fetching roads within {radius_m}m of ({lat}, {lon})...")

    with urllib.request.urlopen(req, timeout=30) as resp:
        return json.loads(resp.read().decode())

def parse_osm_roads(osm_data):
    nodes = {}
    for element in osm_data.get('elements', []):
        if element['type'] == 'node':
            nodes[element['id']] = (element['lat'], element['lon'])

    roads = []
    for element in osm_data.get('elements', []):
        if element['type'] == 'way' and 'highway' in element['tags']:
            points = [nodes[node_id] for node_id in element['nodes'] if node_id in nodes]
            if len(points) < 2:
                continue  # Skip roads that don't have at least 2 nodes

            road = {
                'id': element['id'], # OSM road ID
                'name': element['tags'].get('name', ''), # Road name (if available)
                'type': element['tags']['highway'], # Road type
                'points': points # List of (lat, lon) representing the road nodes
            }
            roads.append(road)

    return roads

def write_roads_to_file(roads, output_file_path):
    with open(output_file_path, "x") as f: # Open file in write mode
        f.write(f"# ar-overlay roads file\n")
        f.write(f"# roads: {len(roads)}\n")
        for road in roads:
            # Sanitize road name
            name = road['name'].replace('|', ' ').replace('\n', ' ') if road['name'] else 'unnamed'
            f.write(f"ROAD {name}\n")
            for lat, lon in road['points']:
                f.write(f"{lat:.8f} {lon:.8f}\n")
            f.write("END\n")
    print(f"Wrote {len(roads)} roads to {output_file_path}")

def main():
    p = argparse.ArgumentParser(description="Fetch road data from Overpass API and write to .roads file")
    p.add_argument('--lat', type=float, required=True, help='Latitude of the center point')
    p.add_argument('--lon', type=float, required=True, help='Longitude of the center point')
    p.add_argument('--radius', type=int, required=True, help='Radius in meters to fetch roads')
    p.add_argument('--out', type=str, required=True, help='Output .roads file path')
    args = p.parse_args()

    osm = fetch_osm_roads(args.lat, args.lon, args.radius)
    roads = parse_osm_roads(osm)

    if not roads:
        print("No roads found in the specified area.")
        sys.exit(1)

    write_roads_to_file(roads, args.out)

if __name__ == "__main__":
    main()
