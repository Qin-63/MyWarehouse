%Increment PID Controller
clear, clc, close all;

ts=0.001; %采样时间=0.001s
Deadband=0.05;   %死区值
sys=tf(400,[1,50,0]); %建立被控对象传递函数
dsys=c2d(sys,ts,'z'); %把传递函数离散化
[num,den]=tfdata(dsys,'v'); % 离散化后提取分子、分母

u_1=0.0;u_2=0.0;u_3=0; %输入向量的初始状态
y_1=0.0;y_2=0.0;y_3=0; %输出的初始状态
error_1=0; %初始化上次误差
error_2=0; %初始化上上次误差

x=[0,0,0]'; %PID的3个参数Kp Ki Kd组成的数组

for k=1:1:1000
    time(k)=k*ts; %仿真时间1000ms
    Kp=10;Ki=0.1;Kd=10;
    rink(k)=1; %指令为阶跃信号
    
    du=Kp*x(1)+Ki*x(2)+Kd*x(3); % PID控制器 输出变化量
    u(k)=u_1+du;
    
    if u(k)>=10
        u(k)=10;
    end
    if u(k)<=-10
        u(k)=-10;
    end
    
    % 近似线性模型
    rout(k)=-den(2)*y_1-den(3)*y_2+num(2)*u_1+num(3)*u_2;
    error=rink(k)-rout(k);  %SV-PV
    
    if(abs(error) <= Deadband)   
        du=0;
        error=0;       
    end
    if(abs(error) > Deadband)
        error=error;
    end
    
    % 返回pid参数
    u_3=u_2;u_2=u_1;u_1=u(k); %保留上上次、上次、本次PID输出
    y_3=y_2;y_2=y_1;y_1=rout(k); %保留上上次、上次、本次系统输出
    x(1)=error-error_1; % 计算 Pout
    x(2)=error; % 计算 Iout
    x(3)=error-2*error_1+error_2; % 计算 Dout
    error_2=error_1;
    error_1=error;
end
figure(1);
plot(time,rink,'r',time,rout,'b','linewidth',2);
title('Kp=10;Ki=0.1;Kd=10 Deadband=0.05');
xlabel('time(s)');ylabel('rin,rout');
legend('SV','PV');