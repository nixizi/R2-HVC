function evaluateAll_H()
% Open file
fid = fopen('evaluate_result', 'w');

% Print Header
fprintf(fid, 'D,Problem_type,number_vector,solution_number,set_number,avg_consis_R2C_1,avg_consis_newR2C_1,avg_consis_R2C_2,avg_consis_newR2C_2,avg_correct_R2C_1,avg_correct_newR2C_1,avg_correct_R2C_2,avg_correct_newR2C_2\n');

solution_number = 100;
set_number = 1000;
dimension = 3;

for problem_type = ["linear", "concave", "convex"]
    for h = 1:50
        [W, num_vector] = UniformPoint_H(h, dimension);
        arr = evaluate(dimension, solution_number, problem_type, set_number, num_vector);
        arr = num2cell(arr);
        [r1, r2, r3, r4, r5, r6, r7, r8] = deal(arr{:});
        fprintf(fid, '%d,%s,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f\n', dimension, problem_type, num_vector, solution_number, set_number, r1, r2, r3, r4, r5, r6, r7, r8);
    end
end
fclose(fid);
end