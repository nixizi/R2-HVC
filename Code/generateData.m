for d = 10:10
    solution_num = 100;
    set_num = 100;
    for problem_type = [string('linear_triangular'),string('linear_invertedtriangular'), ...
            string('concave_triangular'),string('concave_invertedtriangular'), ...
            string('convex_triangular'),string('convex_invertedtriangular')]
        generateData_f(d, solution_num, problem_type, set_num);
    end
end

function data_set = generateData_f(dimension, solution_number, problem_type, set_number)
% Generate data_set
% problem_type = linear, concave, convex

data_set = zeros(solution_number, dimension, set_number);
for i = 1:set_number
    data_set(:, :, i) = generate_data(dimension, solution_number, problem_type);
end
data_set_file_name = sprintf('data_set_%d_%d_%s_%d.mat', dimension, solution_number, problem_type, set_number);
save(data_set_file_name, 'data_set');

function data = generate_data(dimension, solution_number, problem_type)
% Generate data
% problem_type = linear, concave, convex

%dimension
dim = dimension;

%number of solutions in a solution set
solutionNum = solution_number;

%raw data
mu = zeros(1,dim);
sigma = eye(dim,dim);
%rng(seed);
data = abs(mvnrnd(mu,sigma,solutionNum));
%V = abs(R./sqrt(sum(R.^2,2)));
%data = rand(solutionNum,dim);

switch(problem_type)
    case string('linear_triangular')
        data = data./sum(data,2);
    case string('linear_invertedtriangular')
        data = data./sum(data,2);
        data = data*(-1);
        data = data+1;
    case string('concave_triangular')
        data = data./sqrt(sum(data.^2,2));
    case string('convex_invertedtriangular')
        data = data./sqrt(sum(data.^2,2));   
        data = data*(-1);
        data = data+1;
    case string('convex_triangular')
        data = data./sum(sqrt(data),2).^2;
    case string('concave_invertedtriangular')
        data = data./sum(sqrt(data),2).^2; 
        data = data*(-1);
        data = data+1;
    otherwise
        fprintf('Invalid problem_type');
        data = [];
end

end

end
