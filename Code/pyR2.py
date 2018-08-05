import numpy as np
import scipy.io as sio

def read_data(name, variable_name):
    mat_file = sio.loadmat(name)
    data = mat_file[variable_name]
    return data

def R2(data_set, weight_vector_grid, exclusive_index):
    (length, dimenstion) = np.shape(weight_vector_grid)
    result = np.zeros((length, dimenstion))
    exclusive_point = data_set[exclusive_index, :]
    np.delete(data_set, exclusive_index, axis=0)
    for i in range(length):
        pass