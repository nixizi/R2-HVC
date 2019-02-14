function H = getH(dim,PopNum)
    for H=1:100
       N = nchoosek(H+dim-1,dim-1); 
       if N>PopNum
           break;
       end
    end
    H = H-1;
end