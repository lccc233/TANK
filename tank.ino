#include <Servo.h>
int ENA = 5;                        //L298使能A
int ENB = 6;                        //L298使能B
int INPUT2 = 7;                     //电机接口1
int INPUT1 = 8;                     //电机接口2
int INPUT3 = 12;                    //电机接口3
int INPUT4 = 13;                    //电机接口4
int Left_Speed_Hold = 255;          //定义左侧速度变量
int Right_Speed_Hold = 255;         //定义右侧速度变量

#define MOTOR_GO_FORWARD  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}    //车体前进                          
#define MOTOR_GO_BACK      {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}   //车体后退
#define MOTOR_GO_RIGHT    {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}    //车体右转
#define MOTOR_GO_LEFT     {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}    //车体左转
#define MOTOR_GO_STOP     {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,LOW);}      //车体停止

int finger[8]={0,0,0,0,0,0,0,0};
int num_flag=1;
int num=0;
int flag=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ENA,OUTPUT); 
  pinMode(ENB,OUTPUT); 
  pinMode(INPUT1,OUTPUT); 
  pinMode(INPUT2,OUTPUT); 
  pinMode(INPUT3,OUTPUT); 
  pinMode(INPUT4,OUTPUT);
  analogWrite(ENB,Left_Speed_Hold);//给L298使能端B赋值
  analogWrite(ENA,Right_Speed_Hold);//给L298使能端A赋值
  MOTOR_GO_STOP;
}

void loop() {
  // put your main code here, to run repeatedly:
  while( Serial.available() > 0 ) {
    char ch = Serial.read();
    if(flag==0) {  if(ch=='\n') { flag=1; } }
    else if(flag==1){
      if(ch=='\r'){
        finger[num]*=num_flag;
        how_to_run();
        flag=0;
        num=0;
        num_flag=1;
        for(int i=0;i<=7;++i)finger[i]=0;
      }
      else if(ch == ',') {
          finger[num]*=num_flag;
          for(int i=0;i<=7;++i)
          num_flag=1;
          num++;
      }
      else if(ch == '-') {num_flag=-1;}
      else {
        finger[num]*=10;finger[num]+=(ch-'0');
      }
    }
  }
}

void how_to_run(){
  if(finger[0]<50){MOTOR_GO_STOP;}
  else {MOTOR_GO_FORWARD;}
}
