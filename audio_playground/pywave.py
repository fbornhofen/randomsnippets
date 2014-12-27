#!/usr/bin/env python

import math
import struct
import wave
import sys

f = wave.open(sys.argv[1], "w")
framerate = 32768

SAMPLEBITS=16
SAMPLEMOD=2**SAMPLEBITS
SAMPLEMAX=SAMPLEMOD-1
f.setnchannels(1)
f.setsampwidth(SAMPLEBITS / 8)
f.setframerate(framerate)

amplitude = SAMPLEMAX/8
iterations = 32768 / 7
a440Hz = framerate / math.pi / 2.0 / 440
notes = [99999] # pause
step = math.pow(2, 1./12)
for i in range(0, 37):
    notes.append(a440Hz / step ** i)

def sample_notes(frequencies, pos):
    res = 0
    for freq in frequencies:
        res += int((amplitude * math.sin(float(pos)/freq))/2)
    return res

def write_pause(wavefile, length):
    for i in range(length):
        f.writeframes(struct.pack('H', 0))

sequence = [16, 14, 16, 11, 7, 11, 4, 0,
            16, 14, 16, 11, 7, 11, 4]
for i in sequence:
    n1 = notes[i]
    for j in range(0, iterations):
        val = sample_notes([n1], j)
        f.writeframes(struct.pack('H', val % SAMPLEMOD))
        # Optional: write 1 more value for 2nd channel
    write_pause(f, iterations/3)

f.close()
