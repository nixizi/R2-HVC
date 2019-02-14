dimension = 5;
solution_number = 100;
problem_type = string('concave_invertedtriangular');
%set(gca,'position',[0.1,0.1,0.9,0.9]);
%figure1=figure('Position', [0, 0, 1500, 400]);
result = zeros(5,6);
for reference_point = 0:1:4
   file_name = sprintf('evaluate_result_dim_%d_probtype_%s_numSol_%d_%d.mat',dimension, problem_type, solution_number, reference_point);
   evaluate_result = load(file_name, 'evaluate_result');
   evaluate_result = evaluate_result.evaluate_result;
   evaluate_result = evaluate_result(5,:,:);
    data = sum(evaluate_result,3)/30;
    result(reference_point+1,:) = data;
end

if problem_type == string('linear_triangular')
    problem = string('linear triangular PF');
elseif problem_type == string('linear_invertedtriangular')
    problem = string('linear inverted triangular PF');    
elseif problem_type == string('convex_triangular')
    problem = string('convex triangular PF'); 
elseif problem_type == string('convex_invertedtriangular')
    problem = string('convex inverted triangular PF'); 
elseif problem_type == string('concave_triangular')
    problem = string('concave triangular PF'); 
elseif problem_type == string('concave_invertedtriangular')
    problem = string('concave inverted triangular PF'); 
end
    %data = max(evaluate_result,[],3);
    x = 0:-0.1:-0.4;
    %subplot(2,1,1);
    figure(1);
   
    plot(x,result(:,1),'-.','LineWidth',4,'Marker', '*','markersize',15);
    hold on;
    plot(x,result(:,2),'LineWidth',4,'Marker', 'd','markersize',15);
    hold on;
    plot(x,result(:,3),'--','LineWidth',4,'Marker', 'o','markersize',15);
    a = legend('Traditional','New','Monte Carlo','Location','northoutside');
    %rect = [0.623660708511514 0.152380952380953 0.270535714285714 0.183333333333333];
    set(a,'FontSize',20);
    %set(a,'Position', rect);
    set(gca,'Fontsize', 20);
    %set(gca,'xtick',[0:500:1000]);
    axis([-0.4 0 0 1]);
    title(problem);
    xlabel('Reference point r');
    ylabel('Consistency rate');
    set(gca,'XTick',(-0.4:0.1:0))
    %    set(gca,'ytick',(0:0.2:1));
    grid on
    set ( gca, 'xdir', 'reverse' )

    %subplot(2,1,2);
    figure(2);
    plot(x,result(:,4),'-.','LineWidth',4,'Marker', '*','markersize',15);
    hold on;
    plot(x,result(:,5),'LineWidth',4,'Marker', 'd','markersize',15);
    hold on;
    plot(x,result(:,6),'--','LineWidth',4,'Marker', 'o','markersize',15);

    %legend('old correct','new correct','mc correct');
    a = legend('Traditional','New','Monte Carlo','Location','northoutside');
    set(a,'FontSize',20);
    set(gca,'Fontsize', 20);
    %set(gca,'xtick',[0:100:1000]);
    axis([-0.4 0 0 1]);
    title(problem);
    xlabel('Reference point r');
    ylabel('Correct identification rate');
    set(gca,'XTick',(-0.4:0.1:0))
    %    set(gca,'ytick',(0:0.2:1));
    grid on
    set ( gca, 'xdir', 'reverse' )

     
 %rect = [0.169633227550996 0.597 0.076560842948146 0.12125];

%a = legend('Traditional','New','Monte Carlo','Location','northoutside');
%set(a,'FontSize',12)
%set(a,'Position', rect)