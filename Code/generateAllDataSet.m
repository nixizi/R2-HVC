function generateAllDataSet(dimension)
solution_number = 100;
set_number = 100;
%dimension = 5;

for problem_type = [string('convex_invertedtriangular'), string('concave_triangular'), string('concave_invertedtriangular')]
% for problem_type = [string('convex_triangular'), string('linear_invertedtriangular'), , string('linear_triangular')]
%for problem_type = [string('random')]
    % File name data_set_d_solutionNumber_problemType_setNum_numVector
    data_set_file_name = sprintf('data_set_%d_%d_%s_%d.mat', dimension, solution_number, problem_type, set_number);
    data_set = load(data_set_file_name, 'data_set');
    data_set = data_set.data_set;
    HVC_file_name = sprintf('HVC_%d_%d_%s_%d.mat', dimension, solution_number, problem_type, set_number);
    if exist(HVC_file_name) == 2
        HVC = load(HVC_file_name);
        HVC = HVC.HVC;
    else
        HVC = calculateHVC(data_set);
        save(HVC_file_name, 'HVC');
    end
    parfor i = 1:100
        num_vector = i*10;
        for seed = 1:30
            % File name result_set_d_solutionNumber_problemType_setNum_numVector
             result_set_file_name = sprintf('result_set_%d_%s_numVec_%d_seed_%d.mat', dimension, problem_type, num_vector, seed);
             if exist(result_set_file_name, 'file') ~= 2
                result_set = calculateResult(data_set, num_vector, seed);
                result_set = [HVC; result_set];
                parsave(result_set_file_name, result_set);
        end   
    end
end

end
