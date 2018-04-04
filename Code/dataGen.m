%dimension
dim = 2;

%number of solutions in a solution set
solutionNum = 50;

%raw data
data = rand(solutionNum,dim);

%linear f1+f2=1
data = data./sum(data,2);

%concave f1^2+f2^2=1
data = data./sqrt(sum(data.^2,2));

%convex 
data = data./sqrt(sum(data.^2,2));
data = data*(-1);
data = data + 1;