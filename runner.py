#!/usr/bin/env python3.7
import subprocess
import sys
import csv

def run(k: float, drag: float):
    #print("Running with a k of " + str(k), file=sys.stderr)
    s = subprocess.run(['./main'], input=f"{str(k)}\n{str(drag)}".encode(), capture_output=True)
    raw = s.stdout.decode()
    info = s.stderr.decode()
    
    if s.returncode != 0:
        print("stderr log:", file=sys.stderr)
        print('\t' + info.replace('\n', "\n\t"), file=sys.stderr)
        s.check_returncode()
    
    passOnVal = [l for l in info.split('\n') if l.startswith('>')]
    for line in passOnVal:
        print(line, file=sys.stderr)


    # data parsing
    data = [line.split(':', maxsplit=1) for line in raw.split('\n') if ':' in line]
    #print(f"data line count = {len(data)}", file=sys.stderr)

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

def run2(k, drag):
    # print(f'k = {k}, drag = {drag}')
    if len(sys.argv) == 3:
        k = float(sys.argv[1])
        drag = float(sys.argv[2])

    initE, flips, inter = run(k, drag)

    # print(f"Initial Energy = {initE}", file=sys.stderr)

    outerFlipsE = [flip['energy'] for flip in flips]
    maxIntersections = [i['percent'] for i in inter]

    if len(maxIntersections) == 0:
        print('No bounce', file=sys.stderr)
        return '', ''

    # print("Flips: ")
    # print(outerFlipsE)

    coeff = 0
    for after, before in zip(outerFlipsE[1:], outerFlipsE[:-1]):
        coeff = after / before
        # print(f"Coefficient = {coeff}")

    # print('', file=sys.stderr)
    # print("Intersections:", file=sys.stderr)
    # print('Percent Overlap =', maxIntersections[0])
    percentOverlap = maxIntersections[0]

    return percentOverlap, coeff

if __name__ == '__main__':
    s = subprocess.run(['make', 'main'], capture_output=True)
    raw = s.stdout.decode()
    err = s.stderr.decode()
    print(raw)
    if s.returncode != 0:
        print(err)


    # kVals = [pow(10, i) for i in range(5,14)]
    # dragVals = [pow(10, i) for i in range(1, 6)]

    # 1e9-11
    # kVals += [3e9, 7e9, 3e10, 7e10, 3e11, 7e11]
    # drag 133-4
    # dragVals += [3e3, 5e3, 8e3, 3e4, 5e4, 8e4]

    kVals = [pow(10, i) for i in range(-5, 10)]

    dragVals = [0]

    print(kVals)

    with open('dataOverlap.csv', 'w') as f_over:
        with open('dataCoeff.csv', 'w') as f_c:
            writerO = csv.writer(f_over)
            writerC = csv.writer(f_c)
    
            writerO.writerow(['d'] + dragVals)
            writerC.writerow(['d'] + dragVals)
            for k in kVals:
                pLs = []
                coeffLs = []

                for drag in dragVals:
                    percentOverlap, coeff = run2(k, drag)
                    if (isinstance(percentOverlap, float) and percentOverlap < 5 and coeff > 0.4 and coeff < 0.6):
                        print('='*30)
                        print(f'k = {k}, drag = {drag}')
                        
                        print(f"Coefficient = {coeff}")
                        print('Percent Overlap =', percentOverlap)

                    pLs.append(percentOverlap)
                    coeffLs.append(coeff)
                
                writerO.writerow([k] + pLs)
                writerC.writerow([k] + coeffLs)

