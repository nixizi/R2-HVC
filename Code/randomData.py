"""
Random data generator
"""

import scipy.io as sio
import numpy as np
import random
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pygmo

def random_data(lower_bound, upper_bound, dimension):
    return [lower_bound + random.random() * (upper_bound - lower_bound) for i in range(dimension)]
    # return [random.randint(lower_bound, upper_bound -1) for i in range(dimension)]


def is_dominate(x, y):
    """
    Check whether x dominate y(x > y)

    Parameters
    ----------
    x: list or ndarray
    y: list or ndarray

    Returns
    -------
    True for x dominate y
    False for x non-dominate y

    """
    flag = False
    for i in range(len(x)):
        if(x[i] < y[i]):
            return False
        elif x[i] > y[i]:
            flag = True
        else:
            pass
    return flag

def is_same(x, y):
    return np.array_equal(x, y)
    # return np.allclose(x, y)

def remove_dominated(result):
    n = len(result)
    dominated = [0 for x in range(n)]
    dominated_list = []
    for a in range(n):
        for b in range(n):
            p1 = result[a, :]
            p2 = result[b, :]
            if is_dominate(p1, p2) is True:
                dominated[b] = 1
    for i in range(n):
        if dominated[i] == 0:
            dominated_list.append(result[i, :])
    return np.array(dominated_list)

def remove_same(result):
    n = len(result)
    dominated = [0 for x in range(n)]
    dominated_list = []
    for a in range(n):
        for b in range(a + 1, n):
            p1 = result[a, :]
            p2 = result[b, :]
            if is_same(p1, p2) is True:
                dominated[b] = 1
    for i in range(n):
        if dominated[i] == 0:
            dominated_list.append(result[i, :])
    return np.array(dominated_list)

def generate_data_set(lower_bound, upper_bound, dimension, size):
    data_set = [random_data(lower_bound, upper_bound, dimension) for i in range(10 * size)]
    data_set = remove_same(np.array(data_set))
    data_set = remove_dominated(data_set)
    while(len(data_set) < size):
        new_set = [random_data(lower_bound, upper_bound, dimension) for i in range(10 * (size - len(data_set)))]
        new_set = remove_same(np.array(new_set))
        data_set = remove_dominated(np.concatenate((data_set, new_set), axis=0))
        data_set = remove_dominated(data_set)
    # random.shuffle(data_set)
    return np.transpose(data_set[:size])

def generate(lower_bound, upper_bound, dimension, size, num_of_data_size):
    return np.array([generate_data_set(lower_bound, upper_bound, dimension, size) for i in range(num_of_data_size)])

def plot_3D(EP):
    # Print 3D graph of EP
    fig = plt.figure(figsize=(9, 9), dpi=200)
    ax = fig.add_subplot(111, projection='3d')
    ax.w_xaxis.set_pane_color((1.0, 1.0, 1.0, 0))
    ax.w_yaxis.set_pane_color((1.0, 1.0, 1.0, 0))
    ax.w_zaxis.set_pane_color((1.0, 1.0, 1.0, 0))
    ax.tick_params(axis='x', labelsize=20)
    ax.tick_params(axis='y', labelsize=20)
    ax.tick_params(axis='z', labelsize=20)
    # plt.xlim(0, 1.2)
    # plt.ylim(0, 1.2)
    # ax.set_zlim(0, 1.2)
    plt.xlabel("Minimize $f_1(x)$", fontsize=25, labelpad=15)
    plt.ylabel("Minimize $f_2(x)$", fontsize=25, labelpad=15)
    ax.set_zlabel("Minimize $f_3(x)$", fontsize=25, labelpad=15)
    temp = np.array(EP)
    ax.scatter(temp[:, 0], temp[:, 1], temp[:, 2], c='b')
    ax.view_init(20, 45)
    plt.show()

def read_data(name, variable_name):
    mat_file = sio.loadmat(name)
    data = mat_file[variable_name]
    return data

if __name__=="__main__":
    dimension = 15
    point_num = 100
    set_num = 100
    data = generate(0, 1, dimension, point_num, set_num)
    data = np.transpose(data)
    a_dict = {"data_set": data}
    sio.savemat("data_set_{0}_{1}_random_{2}.mat".format(dimension, point_num, set_num), a_dict)
    print(data)
    print(np.shape(data))