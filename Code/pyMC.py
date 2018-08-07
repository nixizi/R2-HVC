import numpy as np
import math
import scipy.io as sio
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import itertools
import pygmo

def MC_HVC(data_set, exclusive_index, num_sample, reference_point, is_maximum):
    (num_data, dimension) = np.shape(data_set)
    u = np.zeros(dimension)
    if is_maximum is True:
        dominance_matrix = data_set >= data_set[exclusive_index]
    else:
        dominance_matrix = data_set <= data_set[exclusive_index]
    exclusive_point = data_set[exclusive_index]
    for i in range(dimension):
        temp = (dominance_matrix[:, i] == 0) & (np.sum(dominance_matrix[:, [j for j in range(i)] + [j for j in range(i + 1, dimension)]], axis=1) == dimension - 1)
        candidates = data_set[temp==1, :]
        if len(candidates) == 0:
            u[i] = reference_point[i]
        else:
            if is_maximum is True:
                u[i] = max(candidates[:, i])
            else:
                u[i] = min(candidates[:, i])
    points = np.random.rand(num_sample, dimension)
    if is_maximum is True:
        points = points * abs(exclusive_point - u) + u
    else:
        points = points * abs(exclusive_point - u) + exclusive_point
    data_set = np.delete(data_set, exclusive_index, axis=0)
    miss = 0
    for i in range(num_sample):
        if is_maximum is True:
            dominance_check = (data_set >= points[i, :])
        else:
            dominance_check = (data_set <= points[i, :])
        if max(np.sum(dominance_check, axis=1)) == dimension:
            miss+=1
    return ((num_sample - miss) / num_sample) * np.prod(abs(exclusive_point - u))