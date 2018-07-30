function result_set = calculateResult(data_set, num_vec)
% Calculate R2C and newR2C
[data_size, dimension, data_set_size] = size(data_set);
% Initialize a matrix with dimentio
result_set = zeros(4, data_size, data_set_size);

% Iterate all data_set
for k = 1:data_set_size
    result_set(:, :, k) = result_single(data_set(:, :, k), num_vec);
end

    function result_one = result_single(data, num_vec)
        % Calculate single R2C and newR2C result
        
        % dim: dimension
        % Num: Number of point
        [Num,dim] = size(data);

        %generate vectors W
        NumVec = num_vec;
        [W,N] = UniformPoint(NumVec,dim);
        W = W./sqrt(sum(W.^2,2));

        %Store results
        R2C = zeros(2,Num);
        newR2C = zeros(2,Num);
        %Some constant values 
        R2HV = R2ind(data,W,dim);
        R2 = R2ind(data,W,1);

        % Iterate all points in a single data_set
        for i=1:Num
            data1 = data;
            s = data1(i,:);
            data1(i,:) = [];
            
            len = sqrt(sum(s.^2,2));
            lambda = s./len;

            %R2 contribution by old method
            R2C(1,i) = len - R2ind(data1,lambda,1);
            R2C(2,i) = R2HV - R2ind(data1,W,dim);

            %R2 contribution by new method
            newR2C(1,i) = newR2ind(data1,W,1,s);
            newR2C(2,i) = newR2ind(data1,W,dim,s);
        
        end
        result_one = [R2C; newR2C];
        
            function R2val = newR2ind(data,W,dim,s)
                % data: A data set
                % W: Weight vector grid
                % s: a data in the data set(data)
                % Calculate R2 by new method
                result = zeros(size(W));
                for j=1:length(W)
                    temp = (s-data)./W(j,:);
                    [~,index] = min(max(temp,[],2));
                    result(j,:) = (s-data(index,:));
                end
                temp1 = min(s./W,[],2);
                temp = result./W;
                l = min(max(temp,[],2),temp1);
                R2val = sum(l.^dim)/length(W);
            end

            function R2val = R2ind(data,W,dim)
                % Calculate R2
                result = zeros(size(W));
                [row, line] = size(W);
                for j=1:row
                        temp = data./W(j,:);
                        [~,index] = max(min(temp,[],2));
                        result(j,:) = data(index,:);
                end
                temp = result./W;
                l = min(temp,[],2);
                R2val = sum(l.^dim)/length(W);
            end
        
    end

end

