from math import sin, cos
from random import seed


class PerlinNoise:


    def init_random_gradient(self) -> None:
        self.corners_gradient = {}

        for corner_x in range(self.x_size + 1):

            for corner_y in range(self.y_size + 1):
                angle = seed(0, 359)
                vector_x = corner_x + cos(angle)
                vector_y = corner_y + sin(angle)

                self.corners_gradient[(corner_x, corner_y)] = (vector_x, vector_y)


    def __init__(self, x_size, y_size) -> None:
        self.x_size = x_size 
        self.y_size = y_size
        self.init_gradient_corner()


    @staticmethod
    def dot(vector1, vector2):
        return vector1[0] * vector2[0] + vector1[1] * vector2[1]


    @staticmethod
    def smothstep(w):
        return 3 * (w ** 2) -  2 *(w ** 3)


    def perlin(self, x, y):
        vectors = []
        corner_vector = []

        int_x = int(x)
        int_y = int(y)

        corner_vector[0] = self.corners_gradient[(int_x, int_y)]
        corner_vector[1] = self.corners_gradient[(int_x, int_y + 1)]
        corner_vector[2] = self.corners_gradient[(int_x + 1, int_y)]
        corner_vector[3] = self.corners_gradient[(int_x + 1, int_y + 1)]

        vectors[0] = (x - int_x, y - int_y)
        vectors[1] = (x - int_x, int_y + 1 - y)
        vectors[2] = (int_x + 1 - x, y - int_y)
        vectors[3] = (int_x + 1 - x, int_y + 1 -y)

        dot_lu = self.dot(corner_vector[0], vectors[0])
        dot_lb = self.dot(corner_vector[1], vectors[1])
        dot_ru = self.dot(corner_vector[2], vectors[2])
        dot_rb = self.dot(corner_vector[3], vectors[3])

        w = (y - int_y) 
        dot_l = dot_lu + self.smothstep(w) * (dot_lb - dot_lu)
        dot_r = dot_ru + self.smothstep(w) * (dot_rb - dot_ru)

        w = (x - int_x) 
        return dot_l + self.smothstep(w) * (dot_r - dot_l)
    
    def create_array(self, frequency):
        array = []
        
        for y in range(0, self.y_size, frequency):
        
            for x in range(0, self.x_size, frequency):
                row = []
                row.append(self.perlin(x, y))
            
            array.append(row)

        return array


def main():
    pass