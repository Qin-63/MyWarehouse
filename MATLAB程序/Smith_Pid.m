clear all;close all;
Ts = 20;  %20ms����ʱ��
TIME = 600    ; %����ʱ��2000s
kp = 1;Tp = 60;tol = 80;  
sys = tf([kp],[Tp,1],'inputdelay',tol);
dsys = c2d(sys,Ts,'zoh');
[num,den] = tfdata(dsys,'v');

M=3;
if M==1  %ģ�Ͳ���ȷ
    kp1 = kp * 1.10;
    Tp1 = Tp * 1.10;
    tol1 = tol* 1.10;
elseif M==2||M==3  %ģ�;�ȷ
    kp1 = kp;
    Tp1 = Tp;
    tol1 = tol;
end

sys1 = tf([kp1],[Tp1,1],'inputdelay',tol1);
dsys1 = c2d(sys1,Ts,'zoh');
[num1,den1] = tfdata(dsys1,'v');

u_1=0.0; u_2=0.0; u_3=0.0; u_4=0.0; u_5=0.0;
e1_1=0; e2=0.0; e2_1=0.0; ei=0.0;
xm_1=0.0; ym_1=0.0; y_1=0.0;

for k=1:1:TIME  %����ʱ��
    time(k) = k*Ts;
    
    S=1;
    if S==1  %��Ծ�ź�
        rin(k)=100.0;
        KP=3;KI=0.0177;
    elseif S==2  %�����ź�
        rin(k)=sign(square(0.0004*pi*k*Ts));
        KP=0.5;KI=0.01;
    end
    
    %��ʱ�͵�ģ��ϵͳ���
    xm(k)=-den1(2)*xm_1+num1(2)*u_1;
    %��ʱ�͵�ģ��ϵͳ���
    ym(k)=-den1(2)*ym_1+num1(2)*u_5;
    %��ʱ�͵�ʵ��ϵͳ���
    yout(k)=-den(2)*y_1+num(2)*u_5;
    
    if M==1  %ģ�Ͳ���ȷ��PI+Smith
        e1(k)=rin(k)-yout(k);  %ƫ�����
        e2(k)=e1(k)-xm(k)+ym(k);
        ei=ei+Ts*e2(k);
        u(k)=KP*e2(k)+KI*ei;
        e1_1=e1(k);
    elseif M==2  %ģ�;�ȷ��PI+Smith
        e2(k)=rin(k)-xm(k);
        ei=ei+Ts*e2(k);
        u(k)=KP*e2(k)+KI*ei;
        e2_1=e2(k);
    elseif M==3  %PI����
        e1(k)=rin(k)-yout(k);
        ei=ei+Ts*e1(k);
        u(k)=KP*e1(k)+KI*ei;
        e1_1=e1(k);
    end   
    
    if u(k)>110
        u(k)=110;
    end       
    if u(k)<-110
        u(k)=-110;
    end
    
    xm_1=xm(k);
    ym_1=ym(k);
    u_5=u_4; u_4=u_3; u_3=u_2; u_2=u_1; u_1=u(k);
    y_1=yout(k);    
end

plot(time,rin,'r--',time,yout,'b','linewidth',2);
xlabel('time(s)');
ylabel('rin,yout');
legend('SV','PV');
