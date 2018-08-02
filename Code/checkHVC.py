import numpy as np
import scipy.io as sio
import pygmo

def read_data(name, variable_name):
    mat_file = sio.loadmat(name)
    data = mat_file[variable_name]
    return data

def check(data_1, data_2):
    (d_1, point_num_1, data_set_size_1) = np.shape(data_1)
    (d_2, point_num_1, data_set_size_2) = np.shape(data_2)
    if data_set_size_1 != data_set_size_2:
        return False
    for i in range(data_set_size_1):
        if np.equal(data_1[:, :, i], data_2[:, :, i]) is False:
            print(data_1[:, :, i])
            print(data_2[:, :, i])
            return False
    return True

if __name__=="__main__":
    point_num = 100
    dimension = 5
    data_set_size = 100
    data_type = "concave"
    name_1 = "HVC_{0}_{1}_{2}_{3}.mat".format(dimension, point_num, data_type, data_set_size)
    name_2 = "HVC_{0}_{1}_{2}_{3}.mat.test.mat".format(dimension, point_num, data_type, data_set_size)
    data_1 = read_data(name_1, "HVC")
    data_2 = read_data(name_2, "HVC")
    print(check(data_1, data_2))