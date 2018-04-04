function HVC = calculateHVC(data_set_sub)
    [data_size, dimension_sub, data_set_size] = size(data_set_sub);
    HVC = zeros(1, data_size, data_set_size);
    for k = 1:data_set_size
        HVC(:, :, k) = calculateSingleHVC(data_set_sub(:, :, k));
        fprintf("Finish %dth HVC\n", k)
    end

    function HVC_sub = calculateSingleHVC(data_sub)
        [Num,dim] = size(data_sub);
        HVC_sub = zeros(1,Num);
        HVvalue = HyperVolume(data_sub*(-1));
        for i=1:Num
            data1 = data_sub;
            s = data1(i,:);
            data1(i,:) = [];
            HVC_sub(i) = HVvalue - HyperVolume(data1*(-1));
        end
    end

end