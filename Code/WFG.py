import scipy.io as sio
import numpy as np
import uuid
import subprocess
import os


def read_data(name, variable_name):
    mat_file = sio.loadmat(name)
    data = mat_file[variable_name]
    return data


def to_file(file_path, data):
    with open(file_path, "w") as f:
        for data_set_index in range(len(data)):
            f.write("#\n")
            for data_index in range(len(data[0][0])):
                for d in range(len(data[0])):
                    f.write(str(data[data_set_index][d][data_index]) + " ")
                f.write("\n")
        f.write("#")


def WFG_HV(data):
    tmp_path = "../Data/tmp/"
    cwd = os.getcwd()
    file_name = str(uuid.uuid4())
    file_path = tmp_path + file_name + ".dat"
    to_file(file_path, data)
    os.chdir(tmp_path)
    args = [cwd + "/WFG_1.15/wfg"]
    args.append(file_name + ".dat")
    subprocess.run(args)
    os.chdir(cwd)
    result_path = file_path + ".result.csv"
    HV_result = []
    with open(result_path, "r") as f:
        lines = f.readlines()
    for l in lines:
        hv, t = l.split(";")
        HV_result.append(float(hv))
    return HV_result


if __name__ == "__main__":
    point_num = 100
    dimension = 10
    data_set_size = 100
    data_path = "../Data/"
    for data_type in ["linear_triangular"]:
        data = read_data(data_path + "data_set_{0}_{1}_{2}_{3}_0.mat".format(
            dimension, point_num, data_type, data_set_size), "data_set")
        WFG_HV(data)
