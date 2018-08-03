function HVC_Appro = MonteCarlo(data,s,solutionIndex,dim,numSample, points)
%MonteCarlo - This is the implementation of the Monte Carlo simulation
%method for the hypervolume contribution in paper "Faster Hypervolume-Based
%Search Using Monte Carlo Sampling" by Johannes Bader, Kalyanmoy Deb, and 
%Eckart Zitzler.
%
%This method first try to find the tightest sampling space of a solution,
%then use Monte Carlo hit-or-miss method to approximation the hypervolume
%contribution of the corresponding solution.
%
%Parameters:
%   data:          solution set
%   s:             solution
%   solutionIndex: index of s in data
%   dim:           dimension
%   numSample:     number of samples

    dominanceMatrix = (data >= s);
    u = zeros(1,dim);
    for i = 1:dim
        temp = dominanceMatrix(:,i)==0 & sum(dominanceMatrix(:,[1:i-1 i+1:end]),2)==dim-1;
        candidates = data(temp==1,:);
        if isempty(candidates)
            u(i) = 0;
        else
            u(i) = max(candidates(:,i));
        end
    end
    % sampling space: u->s
    % monte carlo sampling
    
    %rng(seed);
    %points = rand(numSample,dim);
    points = points.*(s-u) + u;
    
    data1 = data;
    data1(solutionIndex,:) = [];
    
    miss = 0;
    for i = 1:numSample
       dominanceCheck = (data1 >= points(i,:));
       if max(sum(dominanceCheck,2)) == dim
           miss = miss+1;
       end
    end
    
    HVC_Appro = (numSample-miss)/numSample*prod(s-u);
end