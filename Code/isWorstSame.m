function [correct_1, correct_2, correct_3] = isWorstSame(HVC, R2C, newR2C,mcsim, k)
    mHVC = min(HVC);
    iHVC = find(HVC == mHVC);
    mR2C = min(R2C(k, :));
    iR2C = find(R2C(k, :) == mR2C);
    mNew = min(newR2C(k, :));
    iNew = find(newR2C(k, :) == mNew);
    mMC = min(mcsim(k, :));
    iMC = find(mcsim(k, :) == mMC);
    if iHVC == iR2C
        correct_1 = 1;
    else
        correct_1 = 0;
    end
    
    if iHVC == iNew
        correct_2 = 1;
    else
        correct_2 = 0;
    end
    
    if iHVC == iMC
        correct_3 = 1;
    else
        correct_3 = 0;
    end
    
end