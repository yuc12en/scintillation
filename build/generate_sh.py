import re
import numpy as np

file_path = 'temp.sh'
Temperature = list(np.arange(25,400,25))
LY = list(np.arange(10,25,1))


Temperature = list(map(str,Temperature))
LY = list(map(str,LY))


with open(file_path, 'w') as f:
    for i in range(len(LY)):
        for j in range(len(Temperature)):
                file_name = 'Y'+LY[i]+'T'+Temperature[j]+'.root'
                f.write('./Simulation -f '+file_name +' -T ' + Temperature[j] + ' -Y ' + LY[i] + ' >output.log')
                f.write('\n')
                f.write('echo '+ "'Program on " +str(i*len(Temperature)+j+1)+'/'+str(len(LY)*len(Temperature))+ " Finished !'")
                f.write('\n')

    f.write('rm -rf Geant4Data\n')
    f.write('mkdir Geant4Data\n')
    f.write('mv *.root Geant4Data\n')
    # f.write('ln -s -r Geant4Data /home/yuchen/Documents/graduation_design/Experiment_Data/\n')

    
    
    

       
