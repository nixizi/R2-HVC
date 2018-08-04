function evaluateAll(dimension)
% Open file
%fid = fopen('evaluate_result', 'w');

% Print Header
%fprintf(fid, 'D,Problem_type,number_vector,solution_number,set_number,avg_consis_R2C_1,avg_consis_newR2C_1,avg_correct_R2C_1,avg_correct_newR2C_1\n');
evaluate_result = zeros(100, 6, 30);
solution_number = 100;
set_number = 100;
%dimension = 5;

for problem_type = [string('linear'),string('convex'),string('concave')]
    for i = 1:100
        num_vector = i*10;
        for seed = 1:30
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
end

file_name = sprintf('evaluate_result_dim_%d.mat',dimension);
save(file_name, 'evaluate_result');

%fclose(fid);
end