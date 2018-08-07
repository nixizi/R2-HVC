import numpy as np
import math
import scipy.io as sio
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import itertools
import pygmo

def MC_HVC(data, exclusiv_index, num_sample):
    (num_data, dimension) = np.shape(data)
    u = np.zeros(1, dimension)
    dominance_matrix = data >= data[exclusiv_index]
    for i in range(dimension):
        # temp = 
        pass