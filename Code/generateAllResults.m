function generateAllResults(dimension,solution_number)
set_number = 100;

for problem_type = [string('convex_invertedtriangular')]
    for reference_point = 0:1:4
        % File name data_set_d_solutionNumber_problemType_setNum_numVector
        data_set_file_name = sprintf('data_set_%d_%d_%s_%d_%d.mat', dimension, solution_number, problem_type, set_number, reference_point);
        data_set = load(data_set_file_name, 'data_set');
        data_set = data_set.data_set;
        HVC_file_name = sprintf('HVC_%d_%d_%s_%d_%d.mat', dimension, solution_number, problem_type, set_number, reference_point);
        if exist(HVC_file_name) == 2
            HVC = load(HVC_file_name);
            HVC = HVC.HVC;
        end
        parfor i = 1:10
            num_vector = i*100;
            for seed = 1:30
                % File name result_set_d_solutionNumber_problemType_setNum_numVector
                 result_set_file_name = sprintf('result_set_%d_%s_numVec_%d_seed_%d_numSol_%d_%d.mat', dimension, problem_type, num_vector, seed, solution_number, reference_point);
                 if exist(result_set_file_name, 'file') ~= 2
                    result_set = calculateResult(data_set, num_vector, seed);
                    result_set = [HVC; result_set];
                    parsave(result_set_file_name, result_set);
                 end   
            end
        end
    end
end
