data = sum(evaluate_result,3)/30;
x = 100:100:1000;

figure(1);

plot(x,data(:,1),'LineWidth',3);
hold on;
plot(x,data(:,2),'LineWidth',3);
hold on;
plot(x,data(:,3),'LineWidth',3);
legend('old consist','new consist','mc consist');
set(gca,'Fontsize', 30);

figure(2);
plot(x,data(:,4),'LineWidth',3);
hold on;
plot(x,data(:,5),'LineWidth',3);
hold on;
plot(x,data(:,6),'LineWidth',3);

legend('old correct','new correct','mc correct');

set(gca,'Fontsize', 30);
