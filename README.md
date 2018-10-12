# R2-HVC
Code and data for R2-based hypervolume contribution approximation. 

The paper has been submitted to TEVC. 

## Data
The data sets are named as "data_set_a_b_c_d_e.mat", where

a - dimension
b - solution number
c - PF type
d - set number
e - reference point index

For example, "data_set_10_100_concave_invertedtriangular_100_0.mat" is the solution set in 10 dimensional space, each solution set has 100 solutions, the PF type is concave inverted triangular, there are totally 100 solution sets, the reference point is 0.

## Result
The result "HVC_10_100_concave_invertedtriangular_100_0.mat" is the hypervolume contributions of all solutions in solution set "data_set_10_100_concave_invertedtriangular_100_0.mat". 

The result "evaluate_result_dim_10_probtype_concave_invertedtriangular_numSol_100_0.mat" is the final evaluation result of the solution set "data_set_10_100_concave_invertedtriangular_100_0.mat", where each column (from left to right) represent: 

Consistency rate of the traditional method, Consistency rate of the new method, Consistency rate of the Monte Carlo method, Correct identification rate of the traditional method, Correct identification rate of the new method, Correct identification rate of the Monte Carlo method.