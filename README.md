# R2-HVC

Code and data for R2-based Hypervolume Contribution Approximation.

[arXiv link](https://arxiv.org/abs/1805.06773)

## Data

The data sets are in the **Data/** folder.

For example, `data_set_10_100_concave_invertedtriangular_100_0.mat` is the solution set in 10 dimensional space, each solution set has 100 solutions, the PF type is concave inverted triangular, there are totally 100 solution sets, the reference point is 0.

Each data set is stored as a 3-dimension matrix, where each row represents the objective values of a solution, each column represents the corresponding objective, each page represents a solution set.

## Result

The results are in the **Result/** folder.

The result `HVC_10_100_concave_invertedtriangular_100_0.mat` is the hypervolume contributions of all solutions in solution set `data_set_10_100_concave_invertedtriangular_100_0.mat`.

The result `evaluate_result_dim_10_probtype_concave_invertedtriangular_numSol_100_0.mat` is the final evaluation result of the solution set `data_set_10_100_concave_invertedtriangular_100_0.mat`, where each column (from left to right) represent:  Consistency rate of the traditional method, Consistency rate of the new method, Consistency rate of the Monte Carlo method, Correct identification rate of the traditional method, Correct identification rate of the new method, Correct identification rate of the Monte Carlo method.

## Code

The source codes are in the **Code/** folder.

To run the experiments, there are three steps:

Step 1: run `pyHVC.py` or `pyHVC_parallel.py` to calculate the hypervolume contributions of the solution sets.

Step 2: run `generateAllResults.m` to calculate the hypervolume contribution approximations with different methods (i.e., the new method, the traditional method and the Monte Carlo method), and store the results as intermediate results.

Step 3: run `evaluateAllResults.m` to evaluate all the intermediate results and output the final results (i.e., Consistency rate and Correct identification rate).

## Requirements

1. Matlab R2018a
2. Python3
    * Numpy
    * Matplotlib
    * [Pygmo](http://esa.github.io/pygmo/)
    * Scipy
    * Pandas
