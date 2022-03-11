import numpy as np
import matplotlib.pyplot as plt

plt.axis([0, 10000, 0, 100])

for i in range(10):
    y = np.random.random()
    plt.scatter(i, y)
    plt.pause(0.05)

plt.show()