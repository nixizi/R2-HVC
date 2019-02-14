 dimension = 15;
 %solution_number=100; 
 set_number=100;
 reference_point=2;  

 %for problem_type = [string('linear_triangular'),string('linear_invertedtriangular'),string('convex_triangular'),string('convex_invertedtriangular'),string('concave_triangular'),string('concave_invertedtriangular')]
 for problem_type = [string('linear_triangular')]
   for solution_number=100:100:100
    data_set_file_name = sprintf('data_set_%d_%d_%s_%d_%d.mat', dimension, solution_number, problem_type, set_number, reference_point);
    data_set = load(data_set_file_name, 'data_set');
    data_set = data_set.data_set;

    fid=fopen(strcat(data_set_file_name,'.txt'),'w');

    for i = 1:set_number
      data = data_set(:,:,i);
      %data = data*1000;
      fprintf(fid,'#\n');
      fprintf(fid,[repmat('%.10f ', 1, size(data, 2)-1) '%.10f\n'], data');
    end
    fprintf(fid,'#\n');
    fclose(fid);
   end
 end
