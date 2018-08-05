import numpy as np
import math
import scipy.io as sio


def read_data(name, variable_name):
    mat_file = sio.loadmat(name)
    data = mat_file[variable_name]
    return data


def R2(data_set, weight_vector_grid, exclusive_index):
    (num_weight_vector, dimenstion) = np.shape(weight_vector_grid)
    exclusive_point = data_set[exclusive_index, :]
    data_set_exclusive = np.delete(data_set, exclusive_index, axis=0)
    temp1 = np.min(exclusive_point/weight_vector_grid, axis=1)
    y = 0
    for i in range(num_weight_vector):
        temp = (exclusive_point - data_set_exclusive)/weight_vector_grid[i, :]
        x = np.min(np.max(temp, axis=1))
        y = y + math.pow(min(x, temp1[i]), dimenstion)
    return y/num_weight_vector
