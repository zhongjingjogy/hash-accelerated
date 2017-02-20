import numpy as np
from readbin import readbin
import matplotlib.pyplot as plt

data = readbin("temp.dat")

for each in data:
    plt.plot(each)

plt.savefig("result.png")
