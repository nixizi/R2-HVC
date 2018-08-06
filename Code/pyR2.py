import numpy as np
import math
import scipy.io as sio
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import itertools


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


def generate_WV_grid(num_of_vectors, dimension):
    mu = np.zeros((dimension))
    sigma = np.eye(dimension)
    R = np.random.multivariate_normal(mu, sigma, num_of_vectors)
    V = abs(R/np.sqrt(np.sum(np.square(R), axis=1))[:, None])
    return V

def get_weighted_vectors(M, H):
    """Set docstring here.

    Parameters
    ----------
    M: The number of objects
    H: A parameter that influence the number of weight vector

    Returns
    -------
    numpy matrix, every row is a weight vector

    """
    comb = [i for i in range(1, M + H)]
    weight_matrix = []
    comb = list(itertools.combinations(comb, M - 1))
    for space in comb:
        weight = []
        last_s = 0
        for s in space:
            w = (((s - last_s) - 1) / H)
            last_s = s
            weight.append(w)
        weight.append(((M + H - last_s) - 1) / H)
        weight_matrix.append(weight)
    V = np.array(weight_matrix)
    V = abs(V/np.sqrt(np.sum(np.square(V), axis=1))[:, None])
    return V


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

if __name__ == "__main__":
    total_number = 100
    V2 = get_weighted_vectors(3, 11)
    V = generate_WV_grid(total_number - len(V2), 3)
    print(np.shape(V2))
    V = np.concatenate((V, V2))
    plot_3D(V)
