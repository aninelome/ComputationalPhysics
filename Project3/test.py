import pyarma as pa
import numpy as np


r = pa.cube()
v = pa.cube()

r.load("position.bin")
v.load("velocity.bin")

r = np.array(r)
v = np.array(v)
print(r)
print(r.shape)
