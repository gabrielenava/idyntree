function [basePose,jointPos,baseVel,jointVel] = getRobotState(KinDynModel)

    % GETROBOTSTATE gets the floating base system state from the reduced model.
    %
    % This matlab function wraps a functionality of the iDyntree library.                     
    % For further info see also: https://github.com/robotology/idyntree
    %
    % FORMAT:  [basePose,jointPos,baseVel,jointVel] = getRobotState(KinDynModel)
    %
    % INPUTS:  - KinDynModel: a structure containing the loaded model and additional info.
    %
    % OUTPUTS: - basePose: [4 x 4] from base frame to world frame transform;
    %          - jointPos: [ndof x 1] vector of joint positions;
    %          - baseVel: [6 x 1] vector of base velocity;
    %          - jointVel: [ndof x 1] vector of joint velocities.
    %
    % Author : Gabriele Nava (gabriele.nava@iit.it)
    %
    % Copyright (C) 2019 Istituto Italiano di Tecnologia (IIT). All rights reserved.
    % This software may be modified and distributed under the terms of the
    % GNU Lesser General Public License v2.1 or any later version.

    %% ------------Initialization----------------
    
    % get the floating base state
    KinDynModel.kinDynComp.getRobotState(KinDynModel.kinematics.basePose_iDyntree,KinDynModel.kinematics.jointPos_iDyntree, ...
                                         KinDynModel.kinematics.baseVel_iDyntree,KinDynModel.kinematics.jointVel_iDyntree, ...
                                         KinDynModel.kinematics.gravityVec_iDyntree);
   
    % get the base position and orientation
    baseRotation_iDyntree = KinDynModel.kinematics.basePose_iDyntree.getRotation;
    baseOrigin_iDyntree   = KinDynModel.kinematics.basePose_iDyntree.getPosition;
    
    % covert to Matlab format
    baseRotation = baseRotation_iDyntree.toMatlab;
    baseOrigin   = baseOrigin_iDyntree.toMatlab;
    basePose     = [baseRotation, baseOrigin;
                       0,  0,  0,  1]; 
    jointPos     = KinDynModel.kinematics.jointPos_iDyntree.toMatlab;
    baseVel      = KinDynModel.kinematics.baseVel_iDyntree.toMatlab;
    jointVel     = KinDynModel.kinematics.jointVel_iDyntree.toMatlab;   
    
    % Debug output
    if KinDynModel.DEBUG
        
        disp('[getRobotState]: debugging outputs...')
        
        % baseRotation = basePose(1:3,1:3) must be a valid rotation matrix
        if det(basePose(1:3,1:3)) < 0.9 || det(basePose(1:3,1:3)) > 1.1
            
            error('[getRobotState]: baseRotation is not a valid rotation matrix.')
        end
        
        IdentityMatr = basePose(1:3,1:3)*basePose(1:3,1:3)';
        
        for kk = 1:size(IdentityMatr, 1)
            
            for jj = 1:size(IdentityMatr, 1)
                
                if jj == kk
                    
                    if abs(IdentityMatr(kk,jj)) < 0.9 || abs(IdentityMatr(kk,jj)) > 1.1
                        
                        error('[getRobotState]: baseRotation is not a valid rotation matrix.')
                    end
                else
                    if abs(IdentityMatr(kk,jj)) > 0.01
                        
                        error('[getRobotState]: baseRotation is not a valid rotation matrix.')
                    end
                end
            end   
        end    
        disp('[getRobotState]: done.')     
    end
end
