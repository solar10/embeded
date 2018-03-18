#define setbit(x,y) ((x) |= bitpos[(y)])
#define readbit(x,y) ((x) & bitpos[(y)])
#define clearbit(x,y) ((x) &= ~(bitpos[(y)]))
#define wren 0x06
#define wrdata 0x02
#define redata 0x03
#define redsta 0x05
#define wrsta 0x01
enum VCC {VON = 1, VOFF = 0};
enum LED {LON = 0, LOFF = 1};
enum BIT {BB0 = 0b00000001, BB1 = 0b00000010, BB2 = 0b00000100, BB3 = 0b00001000, BB4 = 0b00010000, BB5 = 0b00100000, BB6 = 0b01000000, BB7 = 0b10000000};
enum SNUM {N0 = 0b11000000, N1 = 0b11111001, N2 = 0b10100100, N3 = 0b10110000, N4 = 0b10011001, N5 = 0b10010010, N6 = 0b10000010, N7 = 0b11011000, N8 = 0b10000000, N9 = 0b10010000};
enum PPIN { KEYr0 = 5, KEYr1 = 6, KEYr2 = A3, KEYr3 = A2,
            JOYxTEMp = A0, JOYyCDS1WIRe = A1, BUZ = 4, REMoconint = INT1, REMocon = 3, MICrosonicint = INT0, MICrosonic = 2, MICtriger = A5,
            TXD = 1, RXD = 0, SCL0 = SCL, SDA0 = SDA, SCK0 = 13, MISo = 12, MOSi = 11, EECs = 10, PAThcs = 9,  LATch0 = 7, LATch1 = 8
          };
byte inputpin[] {KEYr0, KEYr1, KEYr2, KEYr3, JOYxTEMp, JOYyCDS1WIRe, REMocon, MICrosonic, RXD, MISo};
byte outputpin[] {BUZ, LATch0, LATch1, TXD, SCL0, SDA0, SCK0, MOSi,  PAThcs, MICtriger, EECs};
byte writehigh[] {EECs};
byte writelow[] {SCK0, MOSi, PAThcs, MICtriger, MISo};
struct {
  byte company;
  byte data;
} remdata;

struct Music {
  int um;
  long tm;
};
enum um {do0, re, mi, pa, sol, la, si, do1};
enum ryt {T1 = 500, T3 = 500, T2 = 1250, T4 = 250, T5 = 350};
unsigned long hz[] {261, 293, 329, 349, 391, 440, 493, 523};
unsigned long umge[8] {0,};
unsigned long bakja[] {T1, T2, T3, T4};
Music school [100] {{sol, T1}, {sol, T1},  {la, T1},  {la, T1}, {sol, T1}, {sol, T1},  {mi, T1}, { -1, T3},
  {sol, T1},   {sol, T1},  {mi, T1},  {mi, T1}, {re, T1}, { -1, T3},
  {sol, T1},  {sol, T1}, {la, T1},  {la, T1},  {sol, T1},  {sol, T1},  {mi, T1}, { -1, T3} ,
  {sol, T1}, {mi, T1},  {re, T1}, {mi, T1}, {do0, T1}, { -1, T3}, { -2, 0}
};
byte bitpos[] {BB0, BB1, BB2, BB3, BB4, BB5, BB6, BB7};
byte segnum [] {N0, N1, N2, N3, N4, N5, N6, N7, N8, N9};
byte dotnum[][8] {
  {B00000000, B00011000, B00100100, B00100100, B00100100, B00100100, B00100100, B00011000},
  {B00000000, B00001000, B00011000, B00001000, B00001000, B00001000, B00001000, B00111100},
  {B00000000, B00011000, B00100100, B00000100, B00001000, B00010000, B00100000, B00111100},
  {B00000000, B00011000, B00100100, B00000100, B00001000, B00000100, B00100100, B00011000},
  {B00000000, B00000100, B00000100, B00100100, B00100100, B00111110, B00000100, B00000100},
  {B00000000, B00111100, B00100000, B00111000, B00000100, B00000100, B00100100, B00011000},
  {B00000000, B00011000, B00100100, B00100000, B00111000, B00100100, B00100100, B00011000},
  {B00000000, B00111100, B00100100, B00000100, B00000100, B00001000, B00001000, B00001000},
  {B00000000, B00011000, B00100100, B00100100, B00011000, B00100100, B00100100, B00011000},
  {B00000000, B00011000, B00100100, B00100100, B00011100, B00000100, B00100100, B00011000},

  {B00011000, B00111100, B01111110, B11011011, B10011001, B00011000, B00011000, B00011000},
  {B00011000, B00011000, B00011000, B10011001, B11011011, B01111110, B00111100, B00011000},
  {B00011000, B00110000, B01100000, B11111111, B11111111, B01100000, B00110000, B00011000},
  {B00011000, B00001100, B00000110, B11111111, B11111111, B00000110, B00001100, B00011000},
  {B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000},

  {B00000000, B00011000, B00100100, B00100100, B00111100, B00100100, B00100100, B01100110},
  {B00000000, B01111100, B00100010, B00100010, B00111100, B00100010, B00100010, B01111100},
  {B00000000, B00011000, B00100100, B00100000, B00100000, B00100000, B00100100, B00011000},
  {B00000000, B01111000, B00100100, B00100010, B00100010, B00100010, B00100100, B01111000},
  {B00000000, B01111100, B00100000, B00100000, B00111100, B00100000, B00100000, B01111100},
  {B00000000, B01111100, B00100000, B00100000, B00111100, B00100000, B00100000, B01100000}
};

byte keyread[] {KEYr0, KEYr1, KEYr2, KEYr3};
byte keymatrix[4][4] {{1, 2, 3, 10}, {4, 5, 6, 11}, {7, 8, 9, 12}, {14, 0, 15, 13}};
byte dotmatrixarray[8] {0,};
byte cc = 0, dotrowcount = 0, pflag = 0, flag = 0, countflag = 0xff, countstep[8] {1, 6, 3, 10, 15, 1, 1, 1};
unsigned long bsync = 50, pbsync = 0, bcount = 0, ledsync = 2000, mppdelay = 0, ppmicro[] {0,}, ppsync = 10, ppsyncmax[8] { 100,}, ppcount[8] { 0,};
volatile int remflag = 0,  input[5] {0,} , inputc = 0, inputr = 0, dotcounter = 0, pcounter = 7 , displaynum = -1, displaycounter = 0, shiftcounter = 0, shiftflag = 0;
volatile unsigned long delaymicro[40], leadtime = 13500, ontime = 2250, offtime = 1125, scope = 300;
unsigned long psyncmillis = 0, platchmillis = 0, pnummillis = 0, pfndmillis = 0, pmatmillis = 0;
int num = 0, ikey = 0, ikey0 = 0, prkey = -1, count = 0;
unsigned long portdata = 0;
byte dataflag = 0, LATch = 0, col = 0, mode = 33;
struct {
  byte flag = 0;
  byte scope = 10;
  byte count = 0;
  unsigned long pdelay = 0;
  byte number [5];
} temp;
int pkey = -1, ckey = -2;
byte outnum[3], devaddr = 0xa0,  memaddr = 0x00, memaddr1 = 0x00, data = 0xaa;
volatile unsigned long psondelay, csondelay;
volatile int sonflag = 3;
unsigned long premdelay, cremdelay, delaymicros;
byte rnum [][15] {{106, 66, 194, 240, 120, 184, 56, 24, 162, 50, 232, 176, 48, 160, 64}, {104, 48, 24, 122, 16, 56, 90, 66, 74, 82, 168, 224, 34, 2, 194}}; //, UP, DOWN, LEFT, RIGHT, CENTER
String remostr[] {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "UP", "DOWN", "LEFT", "RIGHT", "CENTER"};
union {
  struct {
    byte dummy = 0;
    byte keyc;         //0000 keyc3-c0
    byte servo;       //servo7-0
    byte led;         //led7-0
  };
  unsigned long full;
} b3;

union {
  struct {
    byte clcd;        //clcd 7-4,e,rs,fndvcc1,0
    byte fnd;         //fnddot-a
    byte dot_r;       //dot r7-r0
    byte dot_c;       //dot c7-c0
  };
  unsigned long full;
} b4;
byte addr = 0;

void setup() {
  Serial.begin(250000);
  attachInterrupt(MICrosonicint, echomic, CHANGE);
  //  attachInterrupt(REMoconint, echorem, FALLING);
  b4.dot_r = 0x0; b3.led = 0xff;
  dotfontchange();
  umgecalcu();
  initialize();
  reset();
}

void loop() {
  switch (mode) {
    case 0:   //기본모드
      showdisp();
      if (!dataflag) {
        readmatrix();
      }
      break;
    case 1:// 리셋 모드
      reset();
      //      dataflag = 1;
      mode = 0;
      break;
    case 11:// 부저모드
      playmusic();
      mode = 1;
      break;
    case 22:// pwm led 모드
      ledpwm();
      mode = 1;
      break;
    case 33:// i2ceeprom 모드
      i2ceprom();
      mode = 1;
      break;
    case 31:// spieeprom 모드
      spieprom();
      mode = 1;
      break;
    case 44:// 리모콘 모드
      remocon() ;
      mode = 1;
      break;
    case 55:// 조이스틱모드
      joystick() ;
      mode = 1;
      break;
    case 66:// microsonic 모드
      microsonic();
      mode = 1;
      break;
    case 77:// 조도 센서 모드
      phosensor();
      mode = 1;
      break;
    case 88:// 온도 습도센서 모드
      temphum();
      mode = 1;
      break;
    case 99:// clcd 모드
      charlcd();
      mode = 1;
      break;
    case 91:// clcd 모드
      custom_lcd();
      mode = 1;
      break;
  }
}

void tempinter() {
  if (temp.flag == 0) {
    temp.pdelay = micros();
    temp.flag = 1; return;
  }
  if (temp.flag == 1)  {     //160us  low
    if ((micros() - temp.pdelay) < (160 + temp.scope)) {
      temp.pdelay = micros();
      temp.flag = 2; return;
    } else {
      temp.flag = 0; return;
    }
  }
  if (temp.flag == 2)  {
    if ((micros() - temp.pdelay) < (110)) {
      temp.pdelay = micros();
      temp.number[temp.count / 8] <<= 1;
      temp.count++;
    } else {
      temp.pdelay = micros();
      temp.number[temp.count / 8] += 1;
      temp.number[temp.count / 8] <<= 1;
      temp.count++;
    }
  }
  //  Serial.println(temp.count);
  if (temp.count == 40) {
    if (temp.number[4] == temp.number[0] + temp.number[1] + temp.number[2] + temp.number[3]) {
      Serial.println("OKKK");
    } else {
      Serial.println("ERROR");
    }
    Serial.print(temp.number[0], DEC);
    Serial.println("\%");
    Serial.print(temp.number[2], DEC);
    Serial.println("C");
    for (int i = 0; i < 5; i++) {
      Serial.println(temp.number[i], BIN);
    }
    temp.flag = 0; temp.count = 0;
  }
}

void temphum() {
  detachInterrupt(REMoconint);
  delay(2000);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW); delay(20); digitalWrite(3, HIGH);
  pinMode(3, INPUT);
  attachInterrupt(REMoconint, tempinter, FALLING);
  while (1) {
    if (!digitalRead(5)) {
      detachInterrupt(REMoconint);
      return;
    }
  }
}


void custom_lcd() {
  inilcd(); custom_lcd_input(); sendlcdins4(0x80); sendlcdins4(0x1);
  sendlcddata4(0x00);
  sendlcddata4(0x02);
  sendlcddata4(0x03);
  sendlcddata4(0x04);
  ; sendlcdins4(0xc0);
  sendlcddata4(0x01); sendlcdins4(0xc3);
  sendlcddata4(0x05);

  while (1) {
    if (!digitalRead(5)) {
      return;
    }
  }
}

void custom_lcd_input() {
  byte custom_char[][8] {
    {0, 0, 1, 29, 5, 5, 9, 17},     //기
    {15, 9, 15, 0, 0, 0, 0, 0},    //ㅁ
    {0, 0, 0, 7, 4, 7, 4, 7},  //ㅌ
    {0, 0, 20, 20, 20, 28, 20, 20},  //ㅐ
    {0, 9, 21, 9, 1, 29, 11, 9}, //워
    {8, 8, 15, 0, 0, 0, 0, 0}  //ㄴ
  };
  sendlcdins4(0x40);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      sendlcddata4(custom_char[i][j]);
    }
  }
}

void print_font(int num) {
  unsigned long p_fnd_delay, p_latch_delay;
  byte outnum[3], latch_flag = 1;
  outnum[2] = num / 100; outnum[1] = (num % 100) / 10; outnum[0] = num % 10;

  if (micros() - p_fnd_delay >= 15000) {
    readbit(b4.clcd, 0) ?  (clearbit(b4.clcd, 0), setbit(b4.clcd, 1), b4.fnd = segnum[outnum[1]]) : (clearbit(b4.clcd, 1), setbit(b4.clcd, 0), b4.fnd = segnum[outnum[0]]);
    p_fnd_delay = micros();
  }
  if (micros() - p_latch_delay >= 1500) {
    latch_flag ?
    (latch_flag = 0, portdata = b3.full, LATch = LATch1) :
    (latch_flag = 1, portdata = b4.full, LATch = LATch0, (b4.dot_r = (b4.dot_r > 0x1 ?  b4.dot_r >> 1 :  0x80)), (b4.dot_c = ~(dotnum[outnum[2]][col = ((col == 0) ? 7 : --col)])));
    p_latch_delay = micros();  send4byte(); sendlatch();
  }

  if (micros() -  pmatmillis >= 3000) {
    ikey0 = (ikey0 == 3  ? 0 : ++ikey0);
    clearbit(b3.keyc = 0x0f, ikey0);
    pmatmillis = micros();
  }

  if (millis() - pnummillis >= 100) {
    b3.led = ((b3.led == 1) ? 0xff : (b3.led >> 1));
    pnummillis = millis();
  }
}

void outport () {
  portdata = b4.full;
  send4byte();
  sendlatch(); delay(1);
}

void sendlcdins4(byte data) {   //상위 하위비트 나누어서 보낼것..
  LATch = LATch0;
  b4.clcd = data & 0xf0;
  outport();
  b4.clcd = b4.clcd | 0x08;
  outport();
  b4.clcd = b4.clcd & 0xf0;
  outport();

  b4.clcd = (data & 0x0f) << 4;
  outport();
  b4.clcd = b4.clcd | 0x08;
  outport();
  b4.clcd = b4.clcd & 0xf0;
  outport();
}

void sendlcddata4(byte data) {   //상위 하위비트 나누어서 보낼것..
  LATch = LATch0;
  b4.clcd = (data & 0xf0) | 0x04;
  outport();
  b4.clcd = b4.clcd | 0x08;
  outport();
  b4.clcd = b4.clcd & 0xf0;
  outport();

  b4.clcd = ((data & 0x0f) << 4) | 0x04;
  outport();
  b4.clcd = b4.clcd | 0x08;
  outport();
  b4.clcd = b4.clcd & 0xf0;
  outport();
}

void inilcd() {
  delay(50);
  sendlcdins4(0x03); delay(1);
  sendlcdins4(0x03); delay(1);
  sendlcdins4(0x03); delay(1);
  sendlcdins4(0x02); delay(1);
  sendlcdins4(0x28);  //0x28functionset  8바이트 모두 보낼것..쪼개지 말기. 데이터와 명령어를 표시해서 보낼것.
  sendlcdins4(0x06);  //0x06entryset
  sendlcdins4(0x0f); delay(1); //0x0fdisplayon
  sendlcdins4(0x01); delay(2);
  sendlcdins4(0xc0); delay(1);

}

void charlcd() {
  inilcd();
  byte data = 0x00;
  while (1) {
    sendlcddata4(data++);
    //    remocon();
    if (!digitalRead(5)) {
      return;
    }
  }
}

void phosensor() {
  int x;
  while (1) {
    x = analogRead(JOYyCDS1WIRe);
    Serial.println("cds value: " + String(x));
    if (!digitalRead(5)) {
      return;
    }
  }
}

void joystick() {
  int x, y, cx = 0, cy = 0, analogscope = 30;
  unsigned long cmillis, pmillis, joypmillis, joysync = 100, dotsync = 1;
  LATch = LATch0;
  byte dot_r = 0x18;
  byte dot_c = 0x18;
  while (1) {
    x = analogRead(JOYxTEMp);
    y = analogRead(JOYyCDS1WIRe);
    //    cx = 0; cy = 0;
    if ((cmillis = millis()) - joypmillis > joysync) {
      joypmillis = cmillis;
      x < (512 - analogscope)&& cx < 3 ?  dot_r <<= 1, cx++ : 1;
      x > (512 + analogscope)&& cx > -3 ?  dot_r >>= 1, cx-- : 1;
      y < (512 - analogscope)&& cy > -3 ?  dot_c >>= 1, cy-- : 1;
      y > (512 + analogscope)&& cy < 3 ?  dot_c <<= 1, cy++ : 1;
    }
    b4.dot_r = dot_r;
    b4.dot_c = ~dot_c;
    while ((cmillis = millis()) - pmillis < dotsync) {}
    pmillis = cmillis;
    dotdisplay();
    if (!digitalRead(5)) {
      return;
    }
  }
}

void dotdisplay() {
  portdata = b4.full;
  send4byte();
  sendlatch();
}

void spieprom() {
  byte rdata = 0x0, data = 0x0f;
  while (1) {
    delay(1);
    digitalWrite(EECs, LOW);
    sendspi(wren);
    digitalWrite(EECs, HIGH);
    digitalWrite(EECs, LOW);
    sendspi(wrdata);
    sendspi(addr);
    sendspi(data++);
    digitalWrite(EECs, HIGH);
    delay(1);
    digitalWrite(EECs, LOW);
    sendspi(redata);
    sendspi(addr);
    rdata = readspi();
    digitalWrite(EECs, HIGH);
    Serial.println("  addr" + String(addr++) + ": " + String(rdata));
    if (!digitalRead(5)) {
      return;
    }
    //    while (1) {}
  }
}

byte readspi() {
  byte data = 5;
  int i = 0;

  digitalWrite(SCK0, LOW);
  for (i = 7; i >= 0; i--) {
    digitalWrite(SCK0, HIGH);
    digitalRead(MISo) ? (data |= 1 << i ) : (data &= ~(1 << i)) ;
    digitalWrite(SCK0, LOW);
  }
  return data;
}
void sendspi(byte data) {
  int i = 0;
  for (i = 7; i >= 0; i--) {
    (data & (1 << i)) ? WriteHIGH() : WriteLOW();
  }
}

void WriteHIGH() {
  digitalWrite(MOSi, HIGH);
  digitalWrite(SCK0, HIGH);
  digitalWrite(SCK0, LOW);
  digitalWrite(MOSi, LOW);
}

void WriteLOW() {
  digitalWrite(MOSi, LOW);
  digitalWrite(SCK0, HIGH);
  digitalWrite(SCK0, LOW);
}


void i2ceprom() {
  epwrite();
  delay(5);
  epread();
  while (1) {
    //    epwrite();
    //    epread();
    if (!digitalRead(5)) {
      return;
    }
  }
}

void epwrite () {
  i2cstart();
  sendbyte(devaddr); //  device address send
  sendbyte(memaddr);//  memory address send
  //  sendbyte(memaddr1);//  memory address send
  sendbyte(data);//  data send
  i2cstop();

}

void epread () {
  byte dss;
  i2cstart();
  sendbyte(devaddr); //  device address send
  sendbyte(memaddr);//  memory address send
  //  sendbyte(memaddr1);//  memory address send
  i2cstart();
  sendbyte(devaddr + 1); //  device address send
  dss = readbyte();
  i2cstop();
  Serial.println(dss, BIN); //  data read
}

byte sendbyte(char sdata) {
  int ii = 0;
  do {
    if (ii == 10) return -1;
    for (int i = 7; i >= 0; i--) {
      digitalWrite(SCL0, LOW);
      digitalWrite(SDA0, readbit(sdata, i));
      digitalWrite(SCL0, HIGH); digitalWrite(SCL0, LOW); digitalWrite(SDA0, LOW);
    }
    ii++;
  } while (readack());
  return 1;
}

byte readbyte() {
  byte rdata;
  pinMode(SDA0, INPUT);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(SCL0, LOW);
    digitalWrite(SCL0, HIGH);
    digitalRead(SDA0) ? setbit(rdata, i) : clearbit(rdata, i) ;
    digitalWrite(SCL0, LOW);
  }
  pinMode(SDA0, OUTPUT);
  writeack();
  return rdata;
}
byte readack() {
  byte a;
  pinMode(SDA0, INPUT);
  digitalWrite(SCL0, LOW);
  digitalWrite(SCL0, HIGH);   a = digitalRead(SDA0);  digitalWrite(SCL0, LOW);
  pinMode(SDA0, OUTPUT);
  return a;
}
void writeack() {
  digitalWrite(SDA0, HIGH);
  digitalWrite(SCL0, HIGH); digitalWrite(SCL0, LOW); digitalWrite(SDA0, LOW);
}
void i2cstart() {
  byte count = 0;
  do {
    TWCR = 0xa4;
    while (!(TWCR & 0x80));
    count++;
    if (count == 10) {
      Serial.println("스타트 에러");
      break;
    }
  } while ((TWSR & 0xf8) != 0x08);
}
void i2cstop() {
  TWCR = 0x94;
  //  while (!(TWCR & 0x80));
}

void remocon() {
  detachInterrupt(REMoconint);
  attachInterrupt(REMoconint, echorem, FALLING);
  while (1) {
    if (remflag == 2) {
      remdata.company = remdata.data = 0;
      for (int i = 9 ; i <= 16 ; i++) {
        remdata.company |= (((delaymicro[i] > ontime - scope && delaymicro[i] < ontime + scope) ? 1 : 0) << (16 - i));
      }
      for (int i = 17 ; i <= 24 ; i++) {
        remdata.data |= (((delaymicro[i] > ontime - scope && delaymicro[i] < ontime + scope) ? 1 : 0) << (24 - i));
      }
      //      Serial.print(String(remdata.company) + ":"); Serial.println(String(remdata.data));
      int i = remdata.company == 251 ? 0 : 1;
      for (int j = 0 ; j < sizeof(rnum[0]) / sizeof(rnum[0][0]); j++) {
        if (remdata.data == rnum[i][j]) {
          Serial.println(remostr[j]);
          break;
        }
      }
      remflag = 0;
    }
    if (!digitalRead(5)) {
      return;
    }
  }
}

void microsonic() {
  while (1) {
    if (sonflag == 1) {
      Serial.println("distance=" + (String((double)(csondelay - psondelay) * 34 / 1000 / 2)));
      sonflag = 3;
    } else if (sonflag == 3) {
      digitalWrite(MICtriger, HIGH);
      delayMicroseconds(10);
      digitalWrite(MICtriger, LOW);
      sonflag = 0;
    }
    if (!digitalRead(5)) {
      return;
    }
  }
}

void echomic() {
  if (!sonflag) {
    if (digitalRead(2)) {
      psondelay = micros();
      return;
    }
    csondelay = micros(); sonflag = 1;
  }
}

void echorem() {
  if ( !remflag) {
    remflag = 1;
    premdelay = micros();
  }
  else if (remflag == 1) {
    cremdelay = micros();
    if (((delaymicros = cremdelay - premdelay) >= leadtime - scope) && (delaymicros <= leadtime + scope) ) {
      premdelay = cremdelay;
      if (count != 0) count = 0;
      delaymicro[count++] = delaymicros;
      return;
    } else if ((delaymicros >= ontime - scope && delaymicro <= ontime + scope) || (delaymicros >= offtime - scope && delaymicro <= offtime + scope)) {
      premdelay = cremdelay;
      delaymicro[count++] = delaymicros;
      if ( count >= 33 ) {
        count = 0;
        remflag = 2;
      }
      return;
    }
    remflag = 0;
    count = 0;
  }
}

void playmusic() {
  unsigned long um = micros(), ryt = millis();
  unsigned int count = 0;
  while (1) {
    if (millis() - ryt > school[count].tm) {
      ryt = millis(), count++;
      if (school[count].um == -2) count = 0;
    }
    if ((school[count].um != -1) && ((millis() - ryt) < (school[count].tm - 50))) {
      if (micros() - um > umge[school[count].um]) {
        um = micros(); buzz();
      }
    }
    if (!digitalRead(5)) {
      return;
    }
  }
}

void buzz() {
  digitalWrite(BUZ, !digitalRead(BUZ));
}

void ledpwm() {
  unsigned long pcountdelay = micros(), pdelay = micros(), pledsync = millis();
  unsigned int countmax = 2000, countdelay = 400;
  int count = 0;
  byte countflag = 0;
  LATch = LATch1;
  while (1) {
    if (millis() - pledsync > 100) {
      pledsync = millis();
      b3.led = ((b3.led == 1) ? 0xff : (b3.led >> 1));
    }
    if ((micros() - pdelay < count)) {
      setbit(b3.led, 0);
    }
    if ((micros() - pdelay >= count)) {
      clearbit(b3.led, 0);
    }
    if (micros() - pdelay >= countmax) {
      pdelay = micros();
    }
    if (micros() - pcountdelay >= countdelay) {
      pcountdelay = micros();
      count = countflag ? (count >= countmax ? (countflag = 0, --count)  : ++count) : (count <= 0 ? (countflag = 1, ++count)  : --count) ;
    }
    portdata = b3.full;
    send4byte();
    sendlatch();
    if (!digitalRead(5)) {
      return;
    }
  }
}

void reset() {
  portdata = 0x0;
  send4byte();
  LATch = LATch1;
  sendlatch();

  portdata = 0x0;
  send4byte();
  LATch = LATch0;
  sendlatch();
}

void showdisp() {
  if (micros() - pfndmillis >= 15000) {
    readbit(b4.clcd, 0) ?  (clearbit(b4.clcd, 0), setbit(b4.clcd, 1), b4.fnd = segnum[outnum[1]]) : (clearbit(b4.clcd, 1), setbit(b4.clcd, 0), b4.fnd = segnum[outnum[0]]);
    //    b4.clcd ^= 0x03;
    //    b4.fnd = segnum[outnum[]];
    pfndmillis = micros();
  }
  if (micros() - psyncmillis >= 3000) {
    cc = (cc > 0x1 ?  cc >> 1 :  0x80);
    b4.dot_c = ~cc;
    b4.dot_r = (dotnum[outnum[2]][col = ((col == 0) ? 7 : --col)]);
    psyncmillis = micros();
  }
  if (micros() - platchmillis >= 1500) {
    dataflag ?  (dataflag = 0, portdata = b3.full, LATch = LATch1) : (dataflag = 1, portdata = b4.full, LATch = LATch0);
    if ( LATch != LATch1) {
      ikey0 = (ikey0 == 3  ? 0 : ++ikey0);
      clearbit(b3.keyc = 0x0f, ikey0);
    }
    platchmillis = micros();  send4byte(); sendlatch();
  }
  if (millis() - pnummillis >= 120) {
    pnummillis = millis();
    num + 1 == 1000 ? num = 0 : num++;
    outnum[2] = num / 100; outnum[1] = (num % 100) / 10; outnum[0] = num % 10;
    b3.led = ((b3.led == 1) ? 0xff : (b3.led >> 1));
  }
}

void readmatrix() {
  for (ikey = 0; ikey < 4; ikey++) {
    if (!digitalRead(keyread[ikey])) {
      ckey = keymatrix[ikey][ikey0];
      if (pkey == ckey) return;
      pkey == -1 ? (Serial.print(String(ckey) + ":on ")) : (Serial.println(String(pkey) + ":off "), Serial.print(String(ckey) + ":on ")); //pkey off ckey on
      pkey = ckey, prkey = ikey0; return;
    }
  }
  if (prkey == ikey0) {
    //Serial.print(String(count++) + ": ");
    Serial.println(String(pkey) + ":off ");//pkey off
    pkey = -1, prkey = -1; return;
  }
}
void lowsend4byte() {
  for (int j = 0; j <= 3; j++) {
    for (int i = 0; i <= 7; i++) {
      digitalWrite(MOSi, readbit(portdata, i));
      sendshift();
    }
    portdata >>= 8;
  }
}
void send4byte() {
  for (int j = 0; j <= 3; j++) {
    for (int i = 7; i >= 0; i--) {
      digitalWrite(MOSi, readbit(portdata, i));
      sendshift();
    }
    portdata >>= 8;
  }
}

void sendlatch() {
  digitalWrite(LATch, HIGH);  digitalWrite(LATch, LOW);
}

void sendshift() {
  digitalWrite(SCK0, HIGH); digitalWrite(SCK0, LOW);
}
void initialize() {
  for (int i = 0, k = sizeof(inputpin) / sizeof(byte); i < k; i++) {
    pinMode(inputpin[i] , INPUT);
  }
  for (int i = 0, k = sizeof(outputpin) / sizeof(byte); i < k; i++) {
    pinMode(outputpin[i] , OUTPUT);
  }
  for (int i = 0, k = sizeof(writehigh) / sizeof(byte); i < k; i++) {
    digitalWrite(writehigh[i] , HIGH);
  }
  for (int i = 0, k = sizeof(writelow) / sizeof(byte); i < k; i++) {
    digitalWrite(writelow[i] , LOW);
  }
}

void umgecalcu() {
  for (int i = 0; i < 8; i++) {
    umge[i] = 0.5 / hz[i] * 1000000;
  }
}

void dotfontchange() {
  byte temp[8] = {0,};
  for (int i = 0, k = sizeof(dotnum) / sizeof(dotnum[0]); i < k; i++) {
    for (int j = 0; j < 8; j++) {
      temp[j] = 0;
      for (int y = 0; y < 8; y++) {
        readbit(dotnum[i][y], 7 - j) ? setbit(temp[j], y) : clearbit(temp[j], y);
        //        temp[j] = temp[j] + (((dotnum[i][y] >> j) & 1) == 1);
        //        temp[j] <<= 1;
      }
    }
    for (int kk = 0; kk < 8; kk++) {
      dotnum[i][kk] = temp[kk];
    }
  }
}
