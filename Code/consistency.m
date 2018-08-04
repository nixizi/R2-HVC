function [result_1, result_2, result_3] = consistency(HVC, R2C, newR2C,mcsim, k)
    count1 = 0;
    count2 = 0;
    count3 = 0;
    % Total points pair number
    num = 0;

    for i = 1:length(HVC)-1
       for j = (i+1):length(HVC)
           if ((HVC(i)-HVC(j))>0 && (R2C(k,i)-R2C(k,j))>0) || ((HVC(i)-HVC(j))<0 && (R2C(k,i)-R2C(k,j))<0) || ((HVC(i)-HVC(j))==0 && (R2C(k,i)-R2C(k,j))==0)
               count1 = count1 + 1;
           end
           if ((HVC(i)-HVC(j))>0 && (newR2C(k,i)-newR2C(k,j))>0) || ((HVC(i)-HVC(j))<0 && (newR2C(k,i)-newR2C(k,j))<0) || ((HVC(i)-HVC(j))==0 && (newR2C(k,i)-newR2C(k,j))==0)
               count2 = count2 + 1;
           end
           if ((HVC(i)-HVC(j))>0 && (mcsim(k,i)-mcsim(k,j))>0) || ((HVC(i)-HVC(j))<0 && (mcsim(k,i)-mcsim(k,j))<0) || ((HVC(i)-HVC(j))==0 && (mcsim(k,i)-mcsim(k,j))==0)
               count3 = count3 + 1;
           end
           num = num + 1;
       end
    end

    result_1 = count1/num;
    result_2 = count2/num;
    result_3 = count3/num;
end