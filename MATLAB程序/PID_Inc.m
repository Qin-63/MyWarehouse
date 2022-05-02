%Increment PID Controller
clear, clc, close all;

ts=0.001; %����ʱ��=0.001s
Deadband=0.05;   %����ֵ
sys=tf(400,[1,50,0]); %�������ض��󴫵ݺ���
dsys=c2d(sys,ts,'z'); %�Ѵ��ݺ�����ɢ��
[num,den]=tfdata(dsys,'v'); % ��ɢ������ȡ���ӡ���ĸ

u_1=0.0;u_2=0.0;u_3=0; %���������ĳ�ʼ״̬
y_1=0.0;y_2=0.0;y_3=0; %����ĳ�ʼ״̬
error_1=0; %��ʼ���ϴ����
error_2=0; %��ʼ�����ϴ����

x=[0,0,0]'; %PID��3������Kp Ki Kd��ɵ�����

for k=1:1:1000
    time(k)=k*ts; %����ʱ��1000ms
    Kp=10;Ki=0.1;Kd=10;
    rink(k)=1; %ָ��Ϊ��Ծ�ź�
    
    du=Kp*x(1)+Ki*x(2)+Kd*x(3); % PID������ ����仯��
    u(k)=u_1+du;
    
    if u(k)>=10
        u(k)=10;
    end
    if u(k)<=-10
        u(k)=-10;
    end
    
    % ��������ģ��
    rout(k)=-den(2)*y_1-den(3)*y_2+num(2)*u_1+num(3)*u_2;
    error=rink(k)-rout(k);  %SV-PV
    
    if(abs(error) <= Deadband)   
        du=0;
        error=0;       
    end
    if(abs(error) > Deadband)
        error=error;
    end
    
    % ����pid����
    u_3=u_2;u_2=u_1;u_1=u(k); %�������ϴΡ��ϴΡ�����PID���
    y_3=y_2;y_2=y_1;y_1=rout(k); %�������ϴΡ��ϴΡ�����ϵͳ���
    x(1)=error-error_1; % ���� Pout
    x(2)=error; % ���� Iout
    x(3)=error-2*error_1+error_2; % ���� Dout
    error_2=error_1;
    error_1=error;
end
figure(1);
plot(time,rink,'r',time,rout,'b','linewidth',2);
title('Kp=10;Ki=0.1;Kd=10 Deadband=0.05');
xlabel('time(s)');ylabel('rin,rout');
legend('SV','PV');