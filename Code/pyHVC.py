"""
A program to calculate HVC
"""

import numpy as np
import scipy.io as sio
import pygmo


def read_data(name, variable_name):
    mat_file = sio.loadmat(name)
    data = mat_file[variable_name]
    return data


def calculateHVC(data, target_name):
    """
    Calculate the HVC
        :param data: Input data point, the data format is [point_index, point_dimension, data_set_index]
        :param target_name: The filename which the final result will be stored
    """
    (point_num, dimension, data_set_size) = np.shape(data)
    HVC = np.zeros((1, point_num, data_set_size))
    data = data * -1
    reference_point = [0 for i in range(dimension)]
    for s in range(data_set_size):
        hv = pygmo.hypervolume(data[:, :, s])
        # HV = hv.compute(reference_point)
        for p in range(point_num):
            HVC[0, p, s] = hv.exclusive(p, reference_point)
        print("Finished ", s, "th HVC")
    a_dict = {'HVC': HVC}
    # print(HVC)
    sio.savemat(target_name, a_dict)


if __name__ == "__main__":
    point_num = 10
    dimension = 3
    data_set_size = 10
    #data_type = "random"
    #data = read_data("data_set_{0}_{1}_{2}_{3}.mat".format(dimension, point_num, data_type, data_set_size), "data_set")
    #calculateHVC(data, "HVC_{0}_{1}_{2}_{3}.mat".format(dimension, point_num, data_type, data_set_size))
    for data_type in ["linear_triangular", "linear_invertedtriangular", "concave_triangular", "concave_invertedtriangular", "convex_triangular", "convex_invertedtriangular"]:
        data = read_data("data_set_{0}_{1}_{2}_{3}.mat".format(
            dimension, point_num, data_type, data_set_size), "data_set")
        calculateHVC(data, "HVC_{0}_{1}_{2}_{3}.mat".format(
            dimension, point_num, data_type, data_set_size))
