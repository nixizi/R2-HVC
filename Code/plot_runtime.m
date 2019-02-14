dimension = 15;
solution_number = 100;
problem_type = string('linear_triangular');
%set(gca,'position',[0.1,0.1,0.9,0.9]);
%figure1=figure('Position', [0, 0, 1500, 400]);

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

for reference_point = 2
   file_name = sprintf('runtime_%d_%s_numSol_%d_%d.mat', dimension, problem_type, solution_number, reference_point);
   evaluate_result = load(file_name);
   evaluate_result = evaluate_result.x;
   data = sum(evaluate_result,3)/10;
    %data = sum(evaluate_result,3)/30;
    %data = max(evaluate_result,[],3);
    x = 100:100:1000;
    %subplot(2,5,reference_point+1);
    figure(1);
   
    plot(x,data(:,3),'-.','LineWidth',4,'Marker', '*','markersize',15);
    hold on;
    plot(x,data(:,1),'LineWidth',4,'Marker', 'd','markersize',15);
    hold on;
    plot(x,data(:,2),'--','LineWidth',4,'Marker', 'o','markersize',15);
    %legend('old consist','new consist','mc consist', 'Location', 'NorthEastOutside');
    set(gca,'Fontsize', 20);
    %set(gca,'xtick',[0:100:1000]);
    %set(gca,'ytick',[0:0.2:1]);
    axis([0 1000 0 50]);
    title('15-Dimension');
    xlabel('#Vectors/Points');
    ylabel('Runtime (s)');
    a = legend('Traditional','New','Monte Carlo','Location','northoutside');
    %rect = [0.623660708511514 0.152380952380953 0.270535714285714 0.183333333333333];
    set(a,'FontSize',20);
    %set(a,'Position', rect);
    grid on
    %subplot(2,5,reference_point+1*6);
end
%rect = [0.169633227550996 0.597 0.076560842948146 0.12125];

%a = legend('Traditional','New','Monte Carlo','Location','northoutside');
%set(a,'FontSize',12)
%set(a,'Position', rect)