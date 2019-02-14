function R2val = newR2ind(data,W,s,ref)
%R2 for hvc approximation
    %data = min(s,data);   
    %data = data*(-1);
    %data = unique (data(stk_paretofind (data), :), 'rows');
    %data = data*(-1);
    
    y = 0;
    [row, dim] = size(W);
    temp1 = min(abs(s-ref)./W,[],2);
    for j=1:row
        temp = (s-data)./W(j,:);
        [x,~] = min(max(temp,[],2));
        y = y+min(x,temp1(j))^dim;
    end
    R2val = y/row;
end