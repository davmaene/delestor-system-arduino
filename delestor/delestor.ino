// -----------------------------------------------
// -----------------------------------------------
// ---------  TP KUBUYA DAVID Darone -------------
// --------  TECH 1 G.I ULPLG | FSTA--------------
// -----------------------------------------------
// -----------------------------------------------
#include <Keypad.h>
//------------------------------------------------
const int numberOfLines = 3;
const int ROW_NUM = 4; 
const int COLUMN_NUM = 3; 
//------------------------------------------------
int Readline_1 = A0; // readValue of line 1
int Readline_2 = A1; // readValue of line 2
int Readline_3 = A2; // readValue of line 3
// ------------------ out for lines ---------------
int out_line_1 = 13;
int out_line_2 = 12;
int out_line_3 = 11;
// ------------------ end output ------------------
// --------- max level of load for line -----------
const int mVperAmp_line_1 = 66; // for 10 A
const int mVperAmp_line_2 = 66; // for 15 A
const int mVperAmp_line_3 = 66; // for 20 A
// ------------------ end -------------------------
int ACSoffset = 2500;
float Voltage_line_1 = 0;
float Voltage_line_2 = 0;
float Voltage_line_3 = 0;
// ------------------------------------------------
double Amps_line_1 = 0;
double Amps_line_2 = 0;
double Amps_line_3 = 0;
// ------------------------------------------------
float RawValue_1 = 0;
float RawValue_2 = 0;
float RawValue_3 = 0;
// ------------------------------------------------
int btn_1 = 2;
int btn_2 = 3;
int btn_3 = 0;
volatile int buttonState = 0; 
// -----------------------------------------------
volatile bool blck = false;
volatile bool isLocked_line_1 = false;
volatile bool isLocked_line_2 = false;
bool isLocked_line_3 = false;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte pin_rows[ROW_NUM] = {8, 7, 6, 5}; 
byte pin_column[COLUMN_NUM] = {4, 9, 10}; 
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
const String password = "1945";
String input_password_user;
// ------------------------------------------------
void setup()
{
// ------------- configuring pots -----------------
  Serial.begin(9600);
  pinMode(out_line_1,OUTPUT);
  pinMode(out_line_2,OUTPUT);
  pinMode(out_line_3,OUTPUT);
  pinMode(Readline_1,INPUT);
  pinMode(Readline_2,INPUT);
  pinMode(Readline_3,INPUT);
  pinMode(btn_1,INPUT_PULLUP);
  pinMode(btn_2,INPUT_PULLUP);
  pinMode(btn_3,INPUT_PULLUP);
  input_password_user.reserve(32);
  attachInterrupt(digitalPinToInterrupt(btn_1),pin_In_1, RISING);
  attachInterrupt(digitalPinToInterrupt(btn_2),pin_In_2, RISING);
  attachInterrupt(digitalPinToInterrupt(btn_3),pin_In_3, RISING);
// ------------------- end config -----------------
  Serial.println("-----------------------------------------------------");
  Serial.println("----        TP KUBUYA DAVID Darone         -----");
  Serial.println("----           TECH1 ULPGL FSTA            -----");
  Serial.println("-----------------------------------------------------");
  delay(1000);
}
// -------------------------------------------------
void pin_In_1()
{
  if(isLocked_line_1){blck = true;}else{Serial.println("LINE IS STILL WORKING");}
}
void pin_In_2()
{
  if(isLocked_line_2){blck = true;}else{Serial.println("LINE IS STILL WORKING");}
}
void pin_In_3()
{
  if(isLocked_line_3){blck = true;}else{Serial.println("LINE IS STILL WORKING");}
}
//  ---------------------------------
bool _onTyppingPassword()
{
  
  char key = keypad.getKey();
  if (key){
    if(key == '*') {
      input_password_user = "";
    } else if(key == '#') {
      if(password == input_password_user) {
        Serial.println("password is correct");
        input_password_user = "";
        Serial.println(":::: LINE IS UP :::::");
        blck = false;
      } else {
        Serial.println(); 
        Serial.println("password is incorrect, try again or contact David Maene");
        input_password_user = "";
        return false;
      }
      input_password_user = "";
    } else {
      input_password_user += key;
      Serial.println(); 
      Serial.print(input_password_user);
    }
  }
}
// -------------------------------------------------
void _line_estb_1()
{
  float maxpoint=0;
  int i=0;
  for(i=0;i<500;i++){
    RawValue_1=analogRead(Readline_1);
    if(RawValue_1>maxpoint)maxpoint=RawValue_1;
  }
  Voltage_line_1 = (maxpoint/1024.0)*5000;// my output vol in mV
  Amps_line_1 = ((Voltage_line_1-ACSoffset)/mVperAmp_line_1);
//  Amps_line_1=Amps_line_1/sqrt(2);
  Serial.print("LINE 1 ::::: Value = ");
  Serial.print(Voltage_line_1);
  Serial.print("mV = ");
  Serial.print("\t Amps = ");
  Serial.println(Amps_line_1); 
  if(Amps_line_1<=9.0){digitalWrite(out_line_1,LOW); isLocked_line_1 = false;}
  else{digitalWrite(out_line_1, HIGH); isLocked_line_1 = true;} // my relay is acti e to 0
  delay(1000);     
}
// ----------------------------------------------
void _line_estb_2()
{
  float maxpoint=0;
  int i=0;
  for(i=0;i<500;i++){
    RawValue_2=analogRead(Readline_2);
    if(RawValue_2>maxpoint)maxpoint=RawValue_2;
  }
  Voltage_line_2 = (maxpoint/1024.0)*5000;// my output vol in mV
  Amps_line_2 = ((Voltage_line_2-ACSoffset)/mVperAmp_line_2);
//  Amps_line_1=Amps_line_1/sqrt(2);
  Serial.print("LINE 2 :::::  Value = ");
  Serial.print(Voltage_line_2);
  Serial.print("mV = ");
  Serial.print("\t Amps = ");
  Serial.println(Amps_line_2); 
  if(Amps_line_2<=30.0){digitalWrite(out_line_2,LOW); isLocked_line_2 = false;}
  else{digitalWrite(out_line_2, HIGH); isLocked_line_2 = true;} // my relay is acti e to 0
  delay(1000); 
}
// ----------------------------------------------
void _line_estb_3()
{
  float maxpoint=0;
  int i=0;
  for(i=0;i<500;i++){
    RawValue_3=analogRead(Readline_3);
    if(RawValue_3>maxpoint)maxpoint=RawValue_3;
  }
  Voltage_line_3 = (maxpoint/1024.0)*5000;// my output vol in mV
  Amps_line_3 = ((Voltage_line_3-ACSoffset)/mVperAmp_line_3);
//  Amps_line_1=Amps_line_1/sqrt(2);
  Serial.print("LINE 3 ::::: Value = ");
  Serial.print(Voltage_line_3);
  Serial.print("mV = ");
  Serial.print("\t Amps = ");
  Serial.println(Amps_line_3); 
  Serial.println("--------------------------------------------------");
  if(Amps_line_3<=30.0){digitalWrite(out_line_3,LOW); isLocked_line_3 = false;}
  else{digitalWrite(out_line_3, HIGH); isLocked_line_3 = true;} // my relay is acti e to 0
  delay(1000); 
}
// -----------------------------------------------
void onNotif(int line)
{
  Serial.print("LINE ");
  Serial.print(line);
  Serial.println(" IS DOWN PUSH THE BUTTON TO SET IT UP");
  Serial.println("--------------------------------------------------");
  delay(2000);
}
// ------------------------------------------------
// ----------------- establis line ----------------
void _establishLine(int line)
{
  switch(line){
    case 1:
      (!isLocked_line_1)?_line_estb_1(): onNotif(line);
    break;
    case 2:
      (!isLocked_line_2)?_line_estb_2(): onNotif(line);
    break;
    case 3:
      (!isLocked_line_3)?_line_estb_3(): onNotif(line);
    break;
    default:
    break;
    }
}
// ---------------- end --------------------------
// ------------------------------------------------
void loop()
{
  if(!blck){
    for(int i=0;i<numberOfLines;i++)
      {
          _establishLine(i+1);
      }
  }else{
     _onTyppingPassword();
   }
}
