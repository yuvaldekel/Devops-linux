from math import sqrt
from random import uniform
import numpy as np
import matplotlib.pyplot as plt


def main():
    x_points = np.empty((0, 0))
    y_points = np.empty((0, 0))

    n = 1000
    inside = 0

    for _ in range(n):
        x = uniform(-1, 1)
        y = uniform(-1, 1)

        x_points = np.append(x_points, x)
        y_points = np.append(y_points, y)
        
        distance = sqrt(x ** 2 + y ** 2)

        if distance <= 1:
            inside += 1

    print(4 * inside / n)

    axes = plt.subplots()[1]
    uncolored_circle = plt.Circle((0, 0),
                                  1,
                                  fill = False)
    
    axes.set_aspect(1)
    axes.add_artist(uncolored_circle)

    plt.plot(x_points, y_points, 'o')
    plt.show()


if __name__ == "__main__":
    main()