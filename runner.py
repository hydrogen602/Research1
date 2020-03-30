#!/usr/bin/env python3.7
import subprocess
import sys

def run(k: float, drag: float):
    print("Running with a k of " + str(k), file=sys.stderr)
    s = subprocess.run(['./main'], input=f"{str(k)}\n{str(drag)}".encode(), capture_output=True)
    raw = s.stdout.decode()
    info = s.stderr.decode()
    print("stderr log:", file=sys.stderr)
    print('\t' + info.replace('\n', "\n\t"), file=sys.stderr)
    s.check_returncode()

    # data parsing
    data = [line.split(':', maxsplit=1) for line in raw.split('\n') if ':' in line]
    print(f"data line count = {len(data)}", file=sys.stderr)

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
    k = 1e11
    drag = 1e3
    if len(sys.argv) == 3:
        k = float(sys.argv[1])
        drag = float(sys.argv[2])

    initE, flips, inter = run(k, drag)

    print(f"Initial Energy = {initE}", file=sys.stderr)

    outerFlipsE = [flip['energy'] for flip in flips]
    maxIntersections = [i['percent'] for i in inter]

    #print("Flips: ")
    #print(outerFlipsE)

    for after, before in zip(outerFlipsE[1:], outerFlipsE[:-1]):
        coeff = after / before
        print(f"Coefficient = {coeff}")

    print('', file=sys.stderr)
    print("Intersections:", file=sys.stderr)
    print('Percent Overlap =', maxIntersections[0])

        
