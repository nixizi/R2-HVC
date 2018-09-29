function R2val = R2ind(data,W,dim)
%% R2 for hv approximation        
                [row, ~] = size(W);
                y = 0;
                for j=1:row
                        temp = data./W(j,:);
                        [x,~] = max(min(temp,[],2));
                        y = y+x^dim;
                end
                R2val = y/row;
            end