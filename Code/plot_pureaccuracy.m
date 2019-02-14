setNum = 3;
result = data(:,:,setNum);
result = result';
result = result./max(result);   
    plot(result(:,1),result(:,2),'.','LineWidth',1,'Marker', '*','markersize',8);
    hold on;
    plot(result(:,1),result(:,3),'.','LineWidth',1,'Marker', 'd','markersize',8);
    hold on;
    plot(result(:,1),result(:,4),'.','LineWidth',1,'Marker', 'o','markersize',8);
    hold on;
    plot([0,1],[0,1]);
    %legend('old consist','new consist','mc consist', 'Location', 'NorthEastOutside');
    set(gca,'Fontsize', 20);
    %set(gca,'xtick',[0:500:1000]);
    %set(gca,'ytick',[0:0.2:1]);
    %axis([0 1 0 1]);
    title('Solution set 3');
    xlabel('True Hypervolume');
    ylabel('Approximated Hypervolume');
    a = legend('Traditional','New','Monte Carlo','Location','northoutside');
    %rect = [0.623660708511514 0.152380952380953 0.270535714285714 0.183333333333333];
    set(a,'FontSize',20);
    %set(a,'Position', rect);
    grid on
        %set ( gca, 'xdir', 'reverse' )