function avg_arr = evaluate(dimension, solution_number, problem_type, set_number, num_vector)
    % Load result
    result_set_file_name = sprintf("result_set_%d_%d_%s_%d_%d.mat", dimension, solution_number, problem_type, set_number, num_vector);
    result_set = load(result_set_file_name);
    result_set = result_set.x;
    % Initialize
    total_consis_R2C_1 = 0;
    total_consis_newR2C_1 = 0;
    total_consis_R2C_2 = 0;
    total_consis_newR2C_2 = 0;
    total_correct_R2C_1 = 0;
    total_correct_newR2C_1 = 0;
    total_correct_R2C_2 = 0;
    total_correct_newR2C_2 = 0;
    
    % Evaluate
    for i = 1:set_number
        % Slice
        HVC = result_set(1, :, i);
        R2C = result_set(2:3, :, i);
        newR2C = result_set(4:5, :, i);
        
        % Calculate consistency
        [r1, r2] = consistency(HVC, R2C, newR2C, 1);
        total_consis_R2C_1 = total_consis_R2C_1 + r1;
        total_consis_newR2C_1 = total_consis_newR2C_1 + r2;
        [r1, r2] = consistency(HVC, R2C, newR2C, 2);
        total_consis_R2C_2 = total_consis_R2C_2 + r1;
        total_consis_newR2C_2 = total_consis_newR2C_2 + r2;
        
        % Calculate worst point
        [r1, r2] = isWorstSame(HVC, R2C, newR2C, 1);
        total_correct_R2C_1 = total_correct_R2C_1 + r1;
        total_correct_newR2C_1 = total_correct_newR2C_1 + r2;
        [r1, r2] = isWorstSame(HVC, R2C, newR2C, 2);
        total_correct_R2C_2 = total_correct_R2C_2 + r1;
        total_correct_newR2C_2 = total_correct_newR2C_2 + r2;
    end
    
    avg_consis_R2C_1 = total_consis_R2C_1/set_number;
    avg_consis_newR2C_1 = total_consis_newR2C_1/set_number;
    avg_consis_R2C_2 = total_consis_R2C_2/set_number;
    avg_consis_newR2C_2 = total_consis_newR2C_2/set_number;
    avg_correct_R2C_1 = total_correct_R2C_1/set_number;
    avg_correct_newR2C_1 = total_correct_newR2C_1/set_number;
    avg_correct_R2C_2 = total_correct_R2C_2/set_number;
    avg_correct_newR2C_2 = total_correct_newR2C_2/set_number;
    avg_arr = [avg_consis_R2C_1, avg_consis_newR2C_1, avg_consis_R2C_2, avg_consis_newR2C_2, avg_correct_R2C_1, avg_correct_newR2C_1, avg_correct_R2C_2, avg_correct_newR2C_2];
    
end