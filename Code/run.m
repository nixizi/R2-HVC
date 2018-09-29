indexSolutionSet = 49;
data = data_set(:,:,indexSolutionSet);

hvc = HVC(:,:,indexSolutionSet);
[~,index] = min(hvc);


figure(1);
parallelcoords(data,'LineWidth',1);
hold on
parallelcoords(data(index,:),'LineWidth',5, 'Color', 'r');

set(gca,'Fontsize', 20);
xlabel('Objective index');
ylabel('Objective value');
title('r=0.0');

grid on;

%text(3,0.9,num2str(data(index,:)),'Color','red','FontSize',20);

figure(2);
mc = x(4,:,indexSolutionSet);
[~,index1] = min(mc);
index
index1
scatter(mc,hvc,100,'+','LineWidth',1);
hold on
scatter(mc(index),hvc(index),150,'o','red','LineWidth',2);
set(gca,'Fontsize', 20);
xlabel('Sampling space size');
ylabel('Hypervolume contribution');
title('r=0.0');

grid on;