"""
This is how we plot the figure in the paper
"""

import pandas as pd
import matplotlib.pyplot as plt


def plot_consistancy(plot_data, name):
    markers = ['--', '-', ':']
    i = 0
    plt.figure(figsize=(12, 9))
    ax = plt.subplot(111)
    for col in ["Simple method", "Traditional method", "New method"]:
        m = markers[i]
        plt.plot(plot_data["number_vector"], plot_data[col], linestyle=m, linewidth=4)
        i += 1
    plt.tick_params(labelsize=25)
    plt.xlim(0, 24000)
    plt.ylim(0, 1)
    plt.xlabel("Number of Vectors", fontsize=30)
    plt.ylabel("Consistency Rate", fontsize=30)
    plt.title("{0}".format(name), fontsize=30)
    # plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=2, ncol=3, mode="expand", borderaxespad=0., prop={'size': 25})
    plt.legend(prop={'size': 25})
    plt.savefig("{0}.pdf".format(name), bbox_inches='tight')


def plot_correct(plot_data, name):
    markers = ['--', '-', ':']
    i = 0
    plt.figure(figsize=(12, 9))
    ax = plt.subplot(111)
    for col in ["Simple method", "Traditional method", "New method"]:
        m = markers[i]
        plt.plot(plot_data["number_vector"], plot_data[col], linestyle=m, linewidth=4)
        i += 1
    plt.tick_params(labelsize=25)
    plt.xlim(0, 24000)
    plt.ylim(0, 1)
    plt.xlabel("Number of Vectors", fontsize=30)
    plt.ylabel("Correct Identification Rate", fontsize=30)
    plt.title("{0}".format(name), fontsize=30)
    plt.legend(prop={'size': 25})
    # plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=2, ncol=3, mode="expand", borderaxespad=0., prop={'size': 25})
    plt.savefig("{0}.pdf".format(name), bbox_inches='tight')


if __name__ == "__main__":
    data = pd.read_csv(
        "/home/nixizi/Repository/R2-HVC/Code/evaluate_result", sep=',')
    names = data.columns.tolist()
    names.append("number_vector")
    names.pop(2)
    data_set_size = 50
    data_consistency = data[["avg_consis_R2C_1", "avg_consis_newR2C_1",
                             "avg_consis_R2C_2", "avg_consis_newR2C_2", "number_vector"]].copy()
    data_correct = data[["avg_correct_R2C_1", "avg_correct_newR2C_1",
                         "avg_correct_R2C_2", "avg_correct_newR2C_2", "number_vector"]].copy()
    data_consistency.rename(columns={'avg_consis_R2C_1': 'Simple method', 'avg_consis_R2C_2': 'Traditional method',
                                     "avg_consis_newR2C_1": "New method with R2", "avg_consis_newR2C_2": "New method"}, inplace=True)
    data_correct.rename(columns={'avg_correct_R2C_1': 'Simple method', 'avg_correct_R2C_2': 'Traditional method',
                                 "avg_correct_newR2C_1": "New method with R2", "avg_correct_newR2C_2": "New method"}, inplace=True)

    data_linear_consistency = data_consistency[:data_set_size]
    data_concave_consistency = data_consistency[data_set_size:2*data_set_size]
    data_convex_consistency = data_consistency[2*data_set_size:3*data_set_size]

    data_linear_correct = data_correct[:data_set_size]
    data_concave_correct = data_correct[data_set_size:2*data_set_size]
    data_convex_correct = data_correct[2*data_set_size:3*data_set_size]

    plot_consistancy(data_linear_consistency, "4D-Linear-Consistency")
    plot_consistancy(data_concave_consistency, "4D-Concave-Consistency")
    plot_consistancy(data_convex_consistency, "4D-Convex-Consistency")
    plot_correct(data_linear_correct, "4D-Linear-Correctness")
    plot_correct(data_concave_correct, "4D-Concave-Correctness")
    plot_correct(data_convex_correct, "4D-Convex-Correctness")
