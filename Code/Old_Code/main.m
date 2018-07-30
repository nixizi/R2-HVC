%solution set
data = D(:,:,1);

%dimension
[Num,dim] = size(data);

%generate vectors W
NumVec = 10;
[W,N] = UniformPoint(NumVec,dim);
W = W./sqrt(sum(W.^2,2));

%Store results
HVC = zeros(1,Num);
R2C = zeros(2,Num);
newR2C = zeros(2,Num);

%Some constant values 
HVvalue = HyperVolume(data*(-1));
R2HV = R2ind(data,W,dim);
R2 = R2ind(data,W,1);

for i=1:Num
    data1 = data;
    s = data1(i,:);
    data1(i,:) = [];
    
    length = sqrt(sum(s.^2,2));
    lambda = s./length;
    
    %Hypervolume contribution of solution s
    HVC(i) = HVvalue - HyperVolume(data1*(-1));
    
    %R2 contribution by method 1
    %R2C(1,i) = R2 - R2ind(data1,W,1);
    R2C(1,i) = length - R2ind(data1,lambda,1);
    R2C(2,i) = R2HV - R2ind(data1,W,dim);

    %R2 contribution by method 2
    newR2C(1,i) = newR2ind(data1,W,1,s);
    newR2C(2,i) = newR2ind(data1,W,dim,s);
    
end

function R2val = newR2ind(data,W,dim,s)
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
result = zeros(size(W));
[line,~] = size(W);
    for j=1:line
            temp = data./W(j,:);
            [~,index] = max(min(temp,[],2));
            result(j,:) = data(index,:);
    end
    temp = result./W;
    l = min(temp,[],2);
    R2val = sum(l.^dim)/line;
end

function [W,N] = UniformPoint(N,M)
%UniformPoint - Generate a set of uniformly distributed points on the unit
%hyperplane
%
%   [W,N] = UniformPoint(N,M) returns approximate N uniformly distributed
%   points with M objectives.
%
%   Example:
%       [W,N] = UniformPoint(275,10)

%--------------------------------------------------------------------------
% Copyright (c) 2016-2017 BIMK Group
% You are free to use the PlatEMO for research purposes. All publications
% which use this platform or any code in the platform should acknowledge
% the use of "PlatEMO" and reference "Ye Tian, Ran Cheng, Xingyi Zhang, and
% Yaochu Jin, PlatEMO: A MATLAB Platform for Evolutionary Multi-Objective
% Optimization, IEEE Computational Intelligence Magazine, 2017, in press".
%--------------------------------------------------------------------------

    H1 = 1;
    while nchoosek(H1+M,M-1) <= N
        H1 = H1 + 1;
    end
    W = nchoosek(1:H1+M-1,M-1) - repmat(0:M-2,nchoosek(H1+M-1,M-1),1) - 1;
    W = ([W,zeros(size(W,1),1)+H1]-[zeros(size(W,1),1),W])/H1;
    if H1 < M
        H2 = 0;
        while nchoosek(H1+M-1,M-1)+nchoosek(H2+M,M-1) <= N
            H2 = H2 + 1;
        end
        if H2 > 0
            W2 = nchoosek(1:H2+M-1,M-1) - repmat(0:M-2,nchoosek(H2+M-1,M-1),1) - 1;
            W2 = ([W2,zeros(size(W2,1),1)+H2]-[zeros(size(W2,1),1),W2])/H2;
            W  = [W;W2/2+1/(2*M)];
        end
    end
    W = max(W,1e-6);
    N = size(W,1);
end