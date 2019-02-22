close all


%{
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
   4;              % 13 pump timer
   1;              % 14 pump state
   0;              % 15 measured pH
   T_pH_star       % 16 pH Sensor Timer
];
%}

figure(1)
%subplot(2,1,1)
plot(t,x(:,6))
hold on
plot(t,x(:,4))
hold on
plot(t,x(:,15))
axis([-inf inf 0 14])
legend('actual pH','pH_{\infty}','measured pH')
text(0.5,13,sprintf('T_{pH}^*: %3.2f',T_pH_star))
text(0.5,12,sprintf('K_p: %3.2f',K_p))
text(0.5,11,sprintf('Pump Strength: %3.2f',pump_limiter))
xlabel('time')
ylabel('pH')

%{
figure(2)
plot(t,x(:,16))
hold on
plot(t,x(:,13))
legend('\tau_{pH}','\tau_{pump}')

%}
