"""
This program is used to checking the HVC result

Since we used two different packages to calcualte the HVC
we must make sure that two calculation result is the same

"""
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
    dimension = 15
    data_set_size = 100
    data_type = "random"
    name_1 = "HVC_{0}_{1}_{2}_{3}.mat".format(dimension, point_num, data_type, data_set_size)
    name_2 = "HVC_{0}_{1}_{2}_{3}.mat.test.mat".format(dimension, point_num, data_type, data_set_size)
    data_1 = read_data("/home/nixizi/Repository/R2-HVC/evaluate_result_dim_5_probtype_concave_triangular.mat", "evaluate_result")
    # data_2 = read_data(name_2, "HVC")
    print(data_1)
    # print(check(data_1, data_2))