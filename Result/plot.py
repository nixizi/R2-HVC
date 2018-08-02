import pandas as pd
import matplotlib.pyplot as plt


def plot_consistancy(plot_data, name):
    markers = ['--', ':', '-']
    i = 0
    plt.figure(figsize=(12, 9))
    ax = plt.subplot(111)
    for col in ["Simple method", "Traditional method", "New method"]:
        m = markers[i]
        plt.plot(plot_data["number_vector"], plot_data[col], linestyle=m, linewidth=4)
        i += 1
    plt.tick_params(labelsize=30)
    plt.xlim(0, 135752)
    plt.ylim(0, 1)
    plt.xlabel("Number of Vectors", fontsize=40)
    plt.ylabel("Consistency Rate", fontsize=40)
    plt.title("{0}".format(name), fontsize=40)
    # plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=2, ncol=3, mode="expand", borderaxespad=0., prop={'size': 30})
    plt.legend(prop={'size': 30})
    plt.savefig("{0}.pdf".format(name), bbox_inches='tight')


def plot_correct(plot_data, name):
    markers = ['--', ':', '-']
    i = 0
    plt.figure(figsize=(12, 9))
    ax = plt.subplot(111)
    for col in ["Simple method", "Traditional method", "New method"]:
        m = markers[i]
        plt.plot(plot_data["number_vector"], plot_data[col], linestyle=m, linewidth=4)
        i += 1
    plt.tick_params(labelsize=30)
    plt.xlim(0, 135752)
    plt.ylim(0, 1)
    plt.xlabel("Number of Vectors", fontsize=40)
    plt.ylabel("Correct Identification Rate", fontsize=40)
    plt.title("{0}".format(name), fontsize=40)
    plt.legend(prop={'size': 30})
    # plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=2, ncol=3, mode="expand", borderaxespad=0., prop={'size': 30})
    plt.savefig("{0}.pdf".format(name), bbox_inches='tight')


if __name__ == "__main__":
    data = pd.read_csv(
        "5D_100_100_10:135751", sep=',')
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

    plot_consistancy(data_linear_consistency, "5D-Linear-Consistency")
    plot_consistancy(data_concave_consistency, "5D-Concave-Consistency")
    plot_consistancy(data_convex_consistency, "5D-Convex-Consistency")
    plot_correct(data_linear_correct, "5D-Linear-Correctness")
    plot_correct(data_concave_correct, "5D-Concave-Correctness")
    plot_correct(data_convex_correct, "5D-Convex-Correctness")
