function generateAllDataSet()
solution_number = 50;
set_number = 1000;
dimension = 2;
for problem_type = ["linear", "concave", "convex"]
    % File name data_set_d_solutionNumber_problemType_setNum_numVector
    data_set_file_name = sprintf("data_set_%d_%d_%s_%d.mat", dimension, solution_number, problem_type, set_number);
    data_set = load(data_set_file_name, "data_set");
    data_set = data_set.data_set;
    HVC_file_name = sprintf("HVC_%d_%d_%s_%d.mat", dimension, solution_number, problem_type, set_number);
    if exist(HVC_file_name) == 2
        HVC = load(HVC_file_name);
        HVC = HVC.x;
    else
        HVC = calculateHVC(data_set);
        save(HVC_file_name, "HVC");
    end
    parfor i = 2:200
        num_vector = i
        % File name result_set_d_solutionNumber_problemType_setNum_numVector
        result_set_file_name = sprintf("result_set_%d_%d_%s_%d_%d.mat", dimension, solution_number, problem_type, set_number, num_vector);
        result_set = calculateResult(data_set, num_vector);
        result_set = [HVC; result_set];
        parsave(result_set_file_name, result_set);
    end
end

end