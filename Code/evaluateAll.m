function evaluateAll(dimension)
% Open file
%fid = fopen('evaluate_result', 'w');

% Print Header
%fprintf(fid, 'D,Problem_type,number_vector,solution_number,set_number,avg_consis_R2C_1,avg_consis_newR2C_1,avg_correct_R2C_1,avg_correct_newR2C_1\n');
solution_number = 100;
set_number = 100;
seed_number = 30;
max_vec = 100;
%dimension = 5;

for problem_type = ["linear_triangular", "linear_invertedtriangular", "concave_triangular", "concave_invertedtriangular", "convex_triangular", "convex_invertedtriangular"]
%for problem_type = ["random"]
    evaluate_result = zeros(set_number, 6, seed_number);
    for i = 1:max_vec
        num_vector = i*10;
        for seed = 1:seed_number
            arr = evaluate(dimension, solution_number, problem_type, set_number, num_vector, seed);
            if arr == 0
                continue;
            end
            %arr = num2cell(arr);
            %[r1, r2, r3, r4, r5, r6] = deal(arr{:});
            evaluate_result(i,:,seed) = arr;
        end
        
        %fprintf(fid, '%d,%f,%f,%f,%f,%f,%f\n', num_vector, r1, r2, r3, r4, r5, r6);
    end
    file_name = sprintf("evaluate_result_dim_%d_probtype_%s.mat", dimension, problem_type);
    save(file_name, "evaluate_result");  
end

%fclose(fid);
end
