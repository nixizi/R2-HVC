d = 4;
solution_num = 100;
set_num = 100;
for problem_type = ["linear", "concave", "convex"]
    generateData_f(d, solution_num, problem_type, set_num);
end

function data_set = generateData_f(dimension, solution_number, problem_type, set_number)
% Generate data_set
% problem_type = linear, concave, convex

data_set = zeros(solution_number, dimension, set_number);
for i = 1:set_number
    data_set(:, :, i) = generate_data(dimension, solution_number, problem_type);
end
data_set_file_name = sprintf("data_set_%d_%d_%s_%d.mat", dimension, solution_number, problem_type, set_number);
save(data_set_file_name, "data_set");

function data = generate_data(dimension, solution_number, problem_type)
% Generate data
% problem_type = linear, concave, convex

%dimension
dim = dimension;

%number of solutions in a solution set
solutionNum = solution_number;

%raw data
data = rand(solutionNum,dim);

switch(problem_type)
    case "linear"
        data = data./sum(data,2);
    case "concave"
        data = data./sqrt(sum(data.^2,2));
    case "convex"
        data = data./sqrt(sum(data.^2,2));
        data = data*(-1);
        data = data + 1;
    otherwise
        fprintf("Invalid problem_type");
        data = [];
end

end

end