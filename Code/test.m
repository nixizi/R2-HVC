dimension = 5;
solution_number = 100;
problem_type = [string('concave_triangular')];
%set(gca,'position',[0.1,0.1,0.9,0.9]);
figure1=figure('Position', [0, 0, 1500, 400]);
for reference_point = 0:1:4
   file_name = sprintf('evaluate_result_dim_%d_probtype_%s_numSol_%d_%d.mat',dimension, problem_type, solution_number, reference_point);
   evaluate_result = load(file_name, 'evaluate_result');
   evaluate_result = evaluate_result.evaluate_result;
   
    data = sum(evaluate_result,3)/30;
    %data = max(evaluate_result,[],3);
    x = 100:100:1000;
    subplot(2,5,reference_point+1);
    %figure(1);
   
    plot(x,data(:,1),'-.','LineWidth',1,'Marker', '*');
    hold on;
    plot(x,data(:,2),'LineWidth',1,'Marker', 'd');
    hold on;
    plot(x,data(:,3),'--','LineWidth',1,'Marker', 'o');
    %legend('old consist','new consist','mc consist', 'Location', 'NorthEastOutside');
    set(gca,'Fontsize', 12);
    %set(gca,'xtick',[0:500:1000]);
    %set(gca,'ytick',[0:0.2:1]);
    axis([0 1000 0 1]);
    title(['r=', num2str(reference_point/10*(-1))]);
    xlabel('#Vectors/Points');
    ylabel('Consistency rate');
    subplot(2,5,reference_point+1*6);
    %figure(2);
    plot(x,data(:,4),'-.','LineWidth',1,'Marker', '*');
    hold on;
    plot(x,data(:,5),'LineWidth',1,'Marker', 'd');
    hold on;
    plot(x,data(:,6),'--','LineWidth',1,'Marker', 'o');

    %legend('old correct','new correct','mc correct');

    set(gca,'Fontsize', 12);
    %set(gca,'xtick',[0:100:1000]);
    %set(gca,'ytick',[0:0.2:1]);
    axis([0 1000 0 1]);
    title(['r=', num2str(reference_point/10*(-1))]);
    xlabel('#Vectors/Points');
    ylabel('Correct identification rate');
    
end
rect = [0.169633227550996 0.597 0.076560842948146 0.12125];

a = legend('Traditional','New','Monte Carlo','Location','northoutside');
set(a,'FontSize',12)
set(a,'Position', rect)