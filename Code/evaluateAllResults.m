function evaluateAllResults(dimension)

    solution_number = 100;
    set_number = 100;
    seed_number = 30;
    max_vec = 10;

    for problem_type = ["convex_invertedtriangular"]
       for reference_point = 0:1:4
            evaluate_result = zeros(max_vec, 6, seed_number);
            for i = 1:max_vec
                num_vector = i*100;
                for seed = 1:seed_number
                    arr = evaluate(dimension, solution_number, problem_type, set_number, num_vector, seed, reference_point);
                    if arr == 0
                        continue;
                    end
                    evaluate_result(i,:,seed) = arr;
                end      
            end
            file_name = sprintf("evaluate_result_dim_%d_probtype_%s_numSol_%d_%d.mat", dimension, problem_type, solution_number,reference_point);
            save(file_name, "evaluate_result");  
       end
    end
end
