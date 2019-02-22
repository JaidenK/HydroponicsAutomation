clear all
 
% simulation horizon                                                    
T = 2000000;                                                                 
J = 2000000;

% Target pH
global pH_inputs control_density T_pH_star K_p K_d K_i K_i_sat pump_limiter c_damping
c_damping = 2;
pump_limiter = 1; % How fast the pump changes the pH
K_p = 0.3;
K_d = 0*0.00002;
K_i = 0 * 0.00001;
K_i_sat = 1;
T_pH_star = 2;
control_density = 30;
pH_inputs = [
   % volume, density, pH, time
   20, 10, 3, 0;
   1, control_density, 14, 5;
   3, control_density, 14, 7;
   2, control_density, 14, 30;
   6, control_density, 0, 50;
   4, control_density, 14, 55;
   3, control_density, 0, 70;
   1, control_density, 0, 90
   1, control_density, 0, 1000000
];


x0 = [
   0;              % 1 continuous time 
   0;              % 2 discrete time
   pH_inputs(1,3); % 3 time when the previous drop of pH up/down was added
   pH_inputs(1,3); % 4 Steady-state pH
   pH_inputs(1,3); % 5 Previous steady-state pH
   pH_inputs(1,3); % 6 Current pH
   2;              % 7 Next pH input 
   1;              % 8 Mixing coefficient
   pH_inputs(1,1); % 9 Solution volume
   pH_inputs(1,2); % 10 Solution density
   0;              % 11 pH velocity
   0;              % 12 Steady-state velocity
   0;              % 13 pump timer
   0;              % 14 pump state
   pH_inputs(1,3); % 15 measured pH
   T_pH_star       % 16 pH Sensor Timer
   0;              % 17 Integrated error
   -1;             % 18 pH Sensor Timer State
];
                                                                        
% rule for jumps                                                        
% rule = 1 -> priority for jumps                                        
% rule = 2 -> priority for flows                                        
% rule = 3 -> no priority, random selection when simultaneous conditions
rule = 1;                                                               

% These don't seem to be applied, so set them manually!
%solver tolerances
RelTol = 1e-6;
MaxStep = 1e-3; 