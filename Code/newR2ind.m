function R2val = newR2ind(data,W,dim,s)
%% R2 for hvc approximation
    y = 0;
    [row, ~] = size(W);
    temp1 = min(s./W,[],2);
    for j=1:row
        temp = (s-data)./W(j,:);
        [x,~] = min(max(temp,[],2));
        y = y+min(x,temp1(j))^dim;
    end
    R2val = y/row;
end