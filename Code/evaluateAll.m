function evaluateAll()
% Open file
fid = fopen('evaluate_result', 'w');

% Print Header
fprintf(fid, 'D,Problem_type,number_vector,solution_number,set_number,avg_consis_R2C_1,avg_consis_newR2C_1,avg_consis_R2C_2,avg_consis_newR2C_2,avg_correct_R2C_1,avg_correct_newR2C_1,avg_correct_R2C_2,avg_correct_newR2C_2\n');

solution_number = 50;
set_number = 1000;
dimension = 2;

for problem_type = ["linear", "concave", "convex"]
    for num_vector = 2:200
        arr = evaluate(dimension, solution_number, problem_type, set_number, num_vector);
        arr = num2cell(arr);
        [r1, r2, r3, r4, r5, r6, r7, r8] = deal(arr{:});
        fprintf(fid, '%d,%s,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f\n', dimension, problem_type, num_vector, solution_number, set_number, r1, r2, r3, r4, r5, r6, r7, r8);
    end
end
fclose(fid);
end