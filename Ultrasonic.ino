

const int TrigPin = 2;  //超音波發射腳位定義
const int EchoPin = 3;  //超音波接收腳位定義
int buzzer = 7; //設置控制蜂鳴器的數位IO腳

int GledPin = 10; //定義數位10 介面
int YledPin = 9; //定義數位10 介面
int RledPin = 8; //定義數位10 介面
 unsigned char i, j,x,z; //定義變數
 
float cm;
float xcm;






void setup() {

  Serial.begin(9600);          //設定序列PORT川輸速率 9600 作為程式 DEBUG 時  可自 ARDUINO IDE 序列埠監控視窗 取得目前執行結果
  pinMode(buzzer, OUTPUT); //設置數位IO腳模式，OUTPUT為輸出__蜂鳴器
  pinMode(GledPin, OUTPUT);//定義小燈介面為輸出介面
  pinMode(YledPin, OUTPUT);//定義小燈介面為輸出介面
  pinMode(RledPin, OUTPUT);//定義小燈介面為輸出介面
 
  pinMode(TrigPin, OUTPUT);   // 將 PIN 2 定義為輸出
  pinMode(EchoPin, INPUT);    // 將 PIN 3 定義為輸入
}

void loop() {
  Ultrasonic();
 if (xcm < 100) {buzzer1();} //距離小於 100CM 才啟動聲音
  WLight();

}


//----------------------------------蜂鳴器--------------------------------------------------------------

void buzzer1()

{
if  (xcm < 100) {z=1000;}
if  (xcm < 50)  {z=500;}
if  (xcm < 10)  {z=100;}

digitalWrite(buzzer,HIGH);//發聲音
delay(z);
digitalWrite(buzzer,LOW);//發聲音
delay(z);
 
}



//--------------------------------LED 閃爍------------------------------------------------------------

void WLight()
{
  digitalWrite(GledPin, LOW); //熄滅G小燈   //每次程式循環前先把所有燈號熄滅
  digitalWrite(YledPin, LOW); //熄滅Y小燈   //之後在由下方 IF 判斷燈號顯示
  digitalWrite(RledPin, LOW); //熄滅R小燈
  
  if (xcm < 100)digitalWrite(GledPin, HIGH); //點亮G小燈
  if (xcm < 50)digitalWrite(YledPin, HIGH); //點亮Y小燈
  if (xcm < 10)digitalWrite(RledPin, HIGH); //點亮R小燈
  //--------------------------------------------------------------
   
}




//---------------------------------超音波測距-------------------------------------------------------------
void Ultrasonic()
{
  digitalWrite(TrigPin, LOW); //低高低電平發一個短時間脈衝去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  cm = pulseIn(EchoPin, HIGH) / 58.0; //將回波時間換算成cm
  xcm= cm; // 將距離儲存起來 供給燈號與聲音判斷　
  cm = (int(cm * 100.0)) / 100.0; //保留兩位小數
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(1);
}

