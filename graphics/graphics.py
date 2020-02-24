#!/usr/bin/env python3

import json
import time
import sys
from typing import List, Union

import tkinter as tk

canvas_width = 500
canvas_height = 500


def drawCircle(canvas, x: int, y: int, r: int):
    return canvas.create_oval(x - r, y - r, x + r, y + r)


def main(pipe):
    master = tk.Tk()

    w = tk.Canvas(master,
                  width=canvas_width,
                  height=canvas_height)
    w.pack()

    y = int(canvas_height / 2)

    objects = {}

    scaleFactor: float = 1

    #
    # Types of lines to send
    #
    # new:[id,x,y,r]
    #   new object
    # mv:[id,x,y,r]
    #   move existing object
    # set-scale-factor:factor
    #   set scaling factor
    #

    while(True):
        master.update()

        line: str = pipe.readline().strip()

        if line == '':
            time.sleep(0.5)
            continue

        isNew: bool = line.startswith('new')
        isMv: bool = line.startswith('mv')

        try:
            if isNew or isMv:
                parts: List[str] = [l.strip() for l in line.split(':')]
                if len(parts) != 2:
                    raise SyntaxError

                data: List[Union[int, float]] = json.loads(parts[1])

                if len(data) != 4:
                    raise ValueError('Not right number of data points given')
                if all(map(lambda t: type(t) != float and type(t) != int, data)):
                    raise TypeError(f'Got non-number (float, int) data: {data}')

                idNum, x, y, r = data

                if type(idNum) != int:
                    raise TypeError(f'idNum should be of type int, got type {type(idNum)}')

                if isNew:
                    if idNum in objects:
                        raise KeyError(f"New key {idNum} already exists")
                    d = drawCircle(w,
                                   canvas_width/2 + int(x * scaleFactor),
                                   canvas_height/2 + int(y * scaleFactor),
                                   int(r))

                    objects[idNum] = d
                    print(f"New object with id={idNum}, x={x}, y={y}, r={r}")
                elif isMv:
                    if idNum not in objects:
                        raise KeyError(f"key {idNum} not found")

                    w.coords(objects[idNum],
                             canvas_width/2 + int(x * scaleFactor - r),
                             canvas_height/2 + int(y * scaleFactor - r),
                             canvas_width/2 + int(x * scaleFactor + r),
                             canvas_height/2 + int(y * scaleFactor + r))

            elif line.startswith('set-scale-factor'):
                parts: List[str] = [l.strip() for l in line.split(':')]
                if len(parts) != 2:
                    raise SyntaxError

                scaleFactor = float(parts[1])
                print(f"Scale Factor was set to {scaleFactor}")

            elif line.strip() == "done":
                break
            else:
                raise SyntaxError(f"Unrecognized format: {line}")
        except BaseException as e:
            print(e, file=sys.stderr)

    # tk.mainloop()


if __name__ == "__main__":
    p = open("graphics.socket", "r")
    try:
        main(p)
    finally:
        p.close()
