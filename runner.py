#!/usr/bin/env python3.7
import subprocess
import sys

def run(k: int):
    print("Running with a k of " + str(k))
    s = subprocess.run(['./main'], input=str(k).encode(), capture_output=True)
    raw = s.stdout.decode()
    info = s.stderr.decode()
    print("stderr log:")
    print('\t' + info.replace('\n', "\n\t"))
    s.check_returncode()

    # data parsing
    data = [line.split(':', maxsplit=1) for line in raw.split('\n') if ':' in line]
    print(f"data line count = {len(data)}")

    initE = None
    flips = []
    intersections = []

    for tag, content in data:
        if tag == "initE":
            assert initE == None # don't set twice
            initE = float(content.strip())
        elif tag == "flipped":
            time, energy, deltaX = [c.strip() for c in content.split(",")]
            time = float(time)
            energy = float(energy)
            deltaX = float(deltaX)

            flips.append({'time': time, "energy": energy, "deltaX": deltaX})
        elif tag == "intersection":
            time, percent = [c.strip() for c in content.split(",")]
            assert percent.endswith('%')
            percent = float(percent[:-1])
            time = float(time)
            intersections.append({'time': time, "percent": percent})
        else:
            raise Exception(f"Unknown tag: {tag}  with body: {content}")
    
    return initE, flips, intersections

if __name__ == '__main__':
    k = 1e+11
    if len(sys.argv) == 2:
        k = float(sys.argv[1])

    initE, flips, inter = run(k)

    print(f"Initial Energy = {initE}")

    outerFlipsE = [flip['energy'] for flip in flips if flip['deltaX'] > 0]
    maxIntersections = [i['percent'] for i in inter]

    #print("Flips: ")
    #print(outerFlipsE)

    for after, before in zip(outerFlipsE[1:], outerFlipsE[:-1]):
        coeff = after / before
        print(f"Coefficient = {coeff}")

    print()
    print("Intersections:")
    print(maxIntersections)

        
