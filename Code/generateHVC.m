function generateHVC()
solution_number = 50;
set_number = 1000;
dimension = 2;
problem = ["linear", "concave", "convex"];

parfor i = 1:3
    problem_type = problem(i);
    data_set_file_name = sprintf("data_set_%d_%d_%s_%d.mat", dimension, solution_number, problem_type, set_number);
    data_set = load(data_set_file_name, "data_set");
    data_set = data_set.data_set;
    HVC_file_name = sprintf("HVC_%d_%d_%s_%d.mat", dimension, solution_number, problem_type, set_number);
    HVC = calculateHVC(data_set);
    parsave(HVC_file_name, HVC);
end