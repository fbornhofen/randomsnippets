#!/usr/bin/env python

import wave
import sys
import math

f = wave.open(sys.argv[1], "w")
framerate = 32768
frequency = 440

f.setnchannels(1)
f.setsampwidth(1)
f.setframerate(framerate)

amplitude = 170
iterations = 32768
a440Hz = framerate / math.pi / 2.0 / frequency
notes = []
step = math.pow(2, 1./12)
for i in range(0,13):
    notes.append(a440Hz / step ** i)

sequence = [0, 2, 4, 5, 7, 9, 11, 12]
for i in sequence:
    for j in range(0, iterations/2):
        pitch = notes[i]
        val = int((amplitude * math.sin(j/pitch) + 255)/2)
        f.writeframes(chr(val))
        # write 1 more byte for 2nd channel

f.close()
