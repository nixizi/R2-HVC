    dimension = 5;
    solution_number = 100;
    set_number = 100;
    seed_number = 30;
    max_vec = 1;
    
    result = 0;
    for problem_type = [string('linear_triangular')]
       for reference_point = 2
            evaluate_result = zeros(max_vec, 6, seed_number);
            for i = 1:max_vec
                num_vector = i*500;
                for seed = 1:seed_number
                    result_set_file_name = sprintf('result_set_%d_%s_numVec_%d_seed_%d_numSol_%d_%d.mat', dimension, problem_type, num_vector, seed, solution_number, reference_point);
                    if exist(result_set_file_name) == 0
                        avg_arr = 0;
                        return;
                    end
                    result_set = load(result_set_file_name);
                    result_set = result_set.x;
                    result = result + result_set;
                end      
            end
       end
    end
