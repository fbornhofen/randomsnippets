#!/usr/bin/env python

import math
import struct
import wave
import sys

f = wave.open(sys.argv[1], "w")
framerate = 32768
frequency = 440

SAMPLEBITS=16
SAMPLEMOD=2**SAMPLEBITS
SAMPLEMAX=SAMPLEMOD-1
f.setnchannels(1)
f.setsampwidth(SAMPLEBITS / 8)
f.setframerate(framerate)

amplitude = SAMPLEMAX/2
iterations = 32768
a440Hz = framerate / math.pi / 2.0 / frequency
notes = []
step = math.pow(2, 1./12)
for i in range(0,13):
    notes.append(a440Hz / step ** i)

def sample_notes(frequencies, pos):
    res = 0
    for freq in frequencies:
        res += int((amplitude * math.sin(float(pos)/freq))/2)
    return res

sequence = [0, 2, 4, 5, 7, 9, 11, 12]
for i in sequence:
    for j in range(0, iterations/2):
        n1 = notes[i]
        n2 = notes[(i+3)%12]
        val = sample_notes([n1, n2], j)
        f.writeframes(struct.pack('H', val % SAMPLEMOD))
        # Optional: write 1 more value for 2nd channel

f.close()
