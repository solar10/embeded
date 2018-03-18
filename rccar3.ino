//#include "C:\Users\Administrator\Documents\Arduino\libraries/mega.h"
//아두이노 메가 헤더파일
//#define ReadB(x,y,z) (z)=(1&((x)>>(y)))  
//#define SetB(x,y,z) (x)^((z)<<(y)))
enum MOTOR {M1=1,M2=2};
enum CWCCW {CW=HIGH,CCW=LOW};
enum VCC {VON = HIGH, VOFF = LOW};  //전압
enum ONOFF {ON = HIGH, OFF = LOW};  //스위치
enum LEDONOFF {LON = LOW, LOFF = HIGH}; //LED
enum DIRECTION {UP = 232, DOWN = 176, LEFT = 48, RIGHT = 160, CENTER = 64}; //리모콘 방향키
enum PIN {
  REMOCON =2,
  VOM = A2,         //가변저항
  SW0 = 50, SW1 = 51, //스위치  50풀업,51풀다운
  LED0 = 32, LED1 = 33,     //LED
  VOITRI = 52, VOIECHO = 21, //초음파
  JOYSW = 53, JOYX = A0, JOYY = A1,   //조이스틱
  M1CW=4,M1CCW=5,M2CW=6,M2CCW=7,M1EN=8,M2EN=9,  //dc모터
  C0 = 34, C1 = 36, C2 = 38, C3 = 40, C4 = 42, C5 = 44, C6 = 46, C7 = 48,  //도트메트릭스 LED
  R0 = 35, R1 = 37, R2 = 39, R3 = 41, R4 = 43, R5 = 45, R6 = 47, R7 = 49, //도트메트릭스 전압
  V1 = 30, V2 = 31, S1 = 22, S2 = 23, S3 = 24, S4 = 25, S5 = 26, S6 = 27, S7 = 28, S8 = 29  //FND(7 세그먼트)
};
byte dotnum[][8] {
  {  0b0000000,  0b0011000,  0b0100100,  0b0100100,  0b0100100,  0b0100100,  0b0100100,  0b0011000  },
  {0x00, 0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x3c},
  {0x00, 0x18, 0x24, 0x04, 0x08, 0x10, 0x20, 0x3c},
  { 0b0000000, 0b0011000, 0b0100100, 0b0000100, 0b0011100, 0b0000100, 0b0100100, 0b0011000},
  { 0b0000000,  0b0001000,  0b0011000,  0b0101000,  0b0101000,  0b0101000,  0b0111100,  0b0001000  },
  {  0b0000000,  0b0111100,  0b0100000,  0b0100000,  0b0111000,  0b0000100,  0b0100100,  0b0011000  },
  { 0b0000000,  0b0011100,  0b0100000,  0b0100000,  0b0111000,  0b0100100,  0b0100100,  0b0011000  },
  {  0b0000000,  0b0011000,  0b0100100,  0b0100100,  0b0000100,  0b0000100,  0b0000100,  0b0000100  },
  { 0b0000000,  0b0011000,  0b0100100,  0b0100100,  0b0011000,  0b0100100,  0b0100100,  0b0011000  },
  {  0b0000000,  0b0011000,  0b0100100,  0b0100100,  0b0011100,  0b0000100,  0b0100100,  0b0011000  },
  {  0b0000000,  0b0000000,  0b0000000,  0b0011000,  0b0011000,  0b0000000,  0b0000000,  0b0000000  }
};
byte segnum [] {0b00111111, 0b00000011, 0b01101101, 0b01100111, 0b01010011, 0b01110110, 0b01111110, 0b00110011, 0b01111111, 0b01110111};
byte remnum [] {106, 66, 194, 240, 120, 184, 56, 24, 162, 50};//, UP, DOWN, LEFT, RIGHT, CENTER
byte dotarray[8][8] {0,};
byte row[] = {R0, R1, R2, R3, R4, R5, R6, R7};
byte col[] = {C0, C1, C2, C3, C4, C5, C6, C7};
void pinsetup();
void interruptsetup();
void test(int);

void setup() {
  pinsetup();
  interruptsetup();
  test(500);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void test(int delaymillis) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(row[i], VON);
    for (int j = 0; j < 8; j++) {
      digitalWrite(col[j], LON);
      delay(delaymillis);
      digitalWrite(col[j], LOFF);
    }
    digitalWrite(row[i], VOFF);
  }

  digitalWrite(LED0, VON);
  delay(delaymillis);
  digitalWrite(LED0, VOFF);
  digitalWrite(LED1, VON);
  delay(delaymillis);
  digitalWrite(LED1, VOFF);

  if ((sctime=millis())-dsptime>=500){
    dsptime=sctime;
    if (++scount==100) scount=0;
    }
  sctime=millis();
  if (sctime-sptime>=sttime){
      sptime=sctime;
      digitalRead(V1) ? (digitalWrite(V1,VOFF),digitalWrite(V2,VON),upf.pb=num[(i%10)]):(digitalWrite(V1,VON),digitalWrite(V2,VOFF),upf.pb=num[(i/10)]) ;
      digitalWrite(S1,upf.pf.b0==1 ? LON :LOFF);
      digitalWrite(S2,upf.pf.b1==1 ? LON :LOFF);
      digitalWrite(S3,upf.pf.b2==1 ? LON :LOFF);
      digitalWrite(S4,upf.pf.b3==1 ? LON :LOFF);
      digitalWrite(S5,upf.pf.b4==1 ? LON :LOFF);
      digitalWrite(S6,upf.pf.b5==1 ? LON :LOFF);
      digitalWrite(S7,upf.pf.b6==1 ? LON :LOFF);
    }
  }
}

void interruptsetup() {     //2,3,18,19,20,21
  attachInterrupt(INT0, intfall, FALLING);
  attachInterrupt(INT2, echo, CHANGE);
  //  attachInterrupt(INT0,intrise,RISING);
}

void pinsetup() {
  Serial.begin(250000);
  pinMode(M1CW, OUTPUT); pinMode(M1CCW, OUTPUT); pinMode(M2CW, OUTPUT); pinMode(M2CCW, OUTPUT); pinMode(M1EN, OUTPUT); pinMode(M2EN, OUTPUT);
  pinMode(JOYX, INPUT);  pinMode(JOYY, INPUT);  pinMode(A2, INPUT);  //아날로그핀은 디폴트가 인풋이다.
  pinMode(REMOCON,INPUT); // interrupt 0 리모콘수신부
  pinMode(VOIECHO,INPUT); //interrupt 2 초음파 에코부
  pinMode(SW0,INPUT);
  pinMode(SW1,INPUT);
  pinMode(VOITRI,OUTPUT);//초음파 트리거
  pinMode(JOYSW,INPUT);//조이스틱스위치
  for (int i = 22; i < 50; i++) {  //segment,dotmatrix
    pinMode(i, OUTPUT);
  }
}

void echo() {
  if (digitalRead(EP)) {
    pmicros = micros();
    return;
  }
  cmicros = micros(); echoflag = 1;
}

void intfall() {
  unsigned long bbmicro;
  if (!RPflag) {
    pmicros = micros();
    RPflag = HIGH;
    return;
  } else {
    bbmicro = (cmicros = micros()) - pmicros;
    if (((bbmicro) > (leadrpulse - rscope) && (bbmicro) < (leadrpulse + rscope))) {
      count = 0;
      rpulse[0] = 0;
      RPflag = HIGH;
      rpulse[count++] = bbmicro;
      pmicros = cmicros;
      return;
    }
    if (!(((bbmicro) > (onrpulse - rscope) && (bbmicro) < (onrpulse + rscope)) || ((bbmicro) > (offrpulse - rscope) && (bbmicro) < (offrpulse + rscope)))) {
      count = 0;
      rpulse[0] = 0;
      RPflag = LOW;
      return;
    }
    rpulse[count++] = bbmicro;
    pmicros = cmicros;
  }
  if (!(rpulse[0] > leadrpulse - rscope && rpulse[0] < leadrpulse + rscope)) {
    count = 0;
    rpulse[0] = 0;
    RPflag = LOW;
    return;
  }
  if (count >= 33) {
    for (i = 0; i <= 33; i++) {
      switch (i) {
        case 0 :
          break;
        default :
          switch (i % 8) {
            case 1:
              btoi.bytebit.b8 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
            case 2:
              btoi.bytebit.b7 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
            case 3:
              btoi.bytebit.b6 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
            case 4:
              btoi.bytebit.b5 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
            case 5:
              btoi.bytebit.b4 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
            case 6:
              btoi.bytebit.b3 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
            case 7:
              btoi.bytebit.b2 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
            case 0:
              btoi.bytebit.b1 = (rpulse[i] > onrpulse - rscope ) && (rpulse[i] < onrpulse + rscope) ? 1 : 0 ;
              break;
          }
          if (!((i) % 8)) {
            if (i / 8 == 3) rnum = btoi.byteint;
          }
          break;
      }
    }
    count = 0;
    for (i = 0; i < 40; i++) {
      rpulse[i] = 0;
    }
    RPflag = LOW;
  }
}

