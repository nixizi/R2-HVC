function result_set = calculateResult(data_set, num_vec, seed)
% Calculate R2C newR2C & MonteCarlo
[data_size, dimension, data_set_size] = size(data_set);
%
result_set = zeros(3, data_size, data_set_size);
[W,N] = UniformVector(num_vec, dimension, seed);

%rng(seed);
%points = rand(num_vec,dimension);

for k = 1:data_set_size
    result_set(:, :, k) = result_single(data_set(:, :, k), num_vec , W);
end

    function result_one = result_single(data, num_vec, W)
        % Calculate single R2C newR2C result
        
        %dimension
        [Num,dim] = size(data);
        
        %Store results
        R2C = zeros(1,Num);
        newR2C = zeros(1,Num);
        MCsim = zeros(1,Num);
        %Some constant values         
        R2HV = R2ind(data,W,dim);
        ref = zeros(dim,1);
        for i=1:Num
            data1 = data;
            s = data1(i,:);
            data1(i,:) = [];
            
            %HVC by Monte Carlo simulation
            MCsim(1,i) = MonteCarlo(data,s,i,dim,num_vec);

            %R2 contribution by old method
            R2C(1,i) = R2HV - R2ind(data1,W,ref);

            %R2 contribution by new method
            newR2C(1,i) = newR2ind(data1,W,s,ref);
        
        end
        result_one = [R2C; newR2C; MCsim];
    end

end
