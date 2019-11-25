//*************************************************************************
//** created 2014                                                        **
//** by dataino www.dataino.it                                           **
//** modified 18 Aug 2014                                                **
//** by G. Carmelo                                                       **
//*************************************************************************
//** Dataino Serial version 001                                          **
//** Copyright (c) 2015 Carmelo G.                                       **
//** If you require a license, see                                       **
//** http://www.opensource.org/licenses/bsd-license.php                  **
//*************************************************************************
//**                    PROGRAMM VARIABLE AND CONST                      **
//*************************************************************************
boolean VAR_IN = false;             // switch fon incoming variable
boolean VAL_IN = false;             // switch fon incoming value
int valId = 0;                      // Variable ID
boolean stringComplete = false;     // 
unsigned long Timer = 100;          // Time basis to do something
const int MAX_STRING_LEN = 256;     // the largest string you will process
char stringBuffer[MAX_STRING_LEN];  // static buffer for computation 
char inData[MAX_STRING_LEN];        // Allocate some space for the string
char inChar = -1;                   // Where to store the character read
byte index  = 0;                    // Index into array for store the char
char IOT[6] = "j1qe1";              //
char Live[5] = "Live";              //
char GetConfig[5] = "GetC";         //
char GetValues[5] = "GetV";         //
char SetVar[5]    = "SetV";         //
char EndSend[3]   = "*E";           //
//=========================================================================
// PROJECT ID: 
//=========================================================================
// INCOMING OUTGOING GAUGE VARIABLE SETTING 
//=========================================================================
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW05 = false;
#define SW05iD 1832
//*************************************************************************
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW03 = false;
#define SW03iD 2966
//*************************************************************************
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW07 = false;
#define SW07iD 2970
//*************************************************************************
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW04 = false;
#define SW04iD 1076
//*************************************************************************
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW06 = false;
#define SW06iD 3937
//*************************************************************************
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW01 = false;
#define SW01iD 4734
//*************************************************************************
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW02 = false;
#define SW02iD 4919
//*************************************************************************
// Switch Boolean 0 to 1
//*************************************************************************
boolean SW00 = false;
#define SW00iD 4998
//*************************************************************************

//=========================================================================
// SETUP
//=========================================================================
void setup()
{
  Serial.begin( 57600 );
  Serial.println( F("Dataino|") );

  //----------------------------------------------------------------------------
// Codigo agregado manualmente
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,OUTPUT);
// Codigo agregado manualmente
//----------------------------------------------------------------------------

}
//=========================================================================
// LOOP
//=========================================================================
void loop()
{
  if (stringComplete) 
  {
    // reset Value
    stringComplete = false;
    split_value(inData);
    // Clear inData Array
    for(int i=0 ; i < MAX_STRING_LEN ; i++ ) {
      inData[i] = 0;
    }// End For
  }
 //================================================
 // it's time to do something
 //================================================
 if ( millis() > Timer ) {
   Timer = millis();
 }
//----------------------------------------------------------------------------
// Codigo agregado manualmente 
  digitalWrite(2,SW00);
  digitalWrite(3,SW01);
  digitalWrite(5,SW02);
  digitalWrite(6,SW03);
  digitalWrite(7,SW04);
  digitalWrite(8,SW05);
  digitalWrite(10,SW06);
  digitalWrite(12,SW07);
// Codigo agregado manualmente
//---------------------------------------------------------------------------- 

}
//=========================================================================
/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
//=========================================================================
//
//=========================================================================
void serialEvent() {
  while ( Serial.available() ) {
    //---------------------------------------------------------------------
    inChar = Serial.read();       // Read a character
    int charx = char(inChar);
    //---------------------------------------------------------------------
    if ( (index == 0) && ( charx < 32 ) )
    {
      Serial.println(F(">"));
    }
    else
    {
      //-------------------------------------------------------------------
      inData[index] = inChar;         // Store it
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      //-------------------------------------------------------------------
      if (inChar == '\n'){
        inData[index] = '\0';         // Null terminate the string
        stringComplete = true;
        //-----------------------------------------------------------------
      }
      else
      {
        //-----------------------------------------------------------------
        index++;                      // Increment where to write next
        //-----------------------------------------------------------------
      }
    }
  }
}
//=========================================================================
//  SPLIT FUNCTION
//=========================================================================
void split_value(char* string)
{
  //-----------------------------------------------------------------------
  char *str;
  char *p;
  //-----------------------------------------------------------------------
  strncpy(stringBuffer, string, MAX_STRING_LEN);      // copy source string
  //-----------------------------------------------------------------------
  // split using comma loop while str is not null get subsequent tokens
  //-----------------------------------------------------------------------
  for( str = strtok_r(stringBuffer,";",&p);str;str=strtok_r(NULL,";",&p))
  {
    //---------------------------------------------------------------------
    // Arduino is OK ?
    //---------------------------------------------------------------------
    if( Comp(str, Live) == 0 ){
      Serial.println(F("Dataino|"));
    }
    //---------------------------------------------------------------------
    // GET MONITOR CONFIG
    //---------------------------------------------------------------------
    if( Comp(str, GetConfig) == 0 ){
      Serial.print( F( "IOT;j1qe1|" ) );
      Serial.print( F( "PJT;5325-6957-8446|" ) );
      Serial.print( F( "VER;001|" ) );
      //==========================================================
      Serial.print( F( "GA;1;1832;05;bin;Switch;0;;On;Off|" ) );
      Serial.print( F( "GA;1;2966;03;bin;Switch;0;;On;Off|" ) );
      Serial.print( F( "GA;1;2970;07;bin;Switch;0;;On;Off|" ) );
      Serial.print( F( "GA;1;1076;04;bin;Switch;0;;On;Off|" ) );
      Serial.print( F( "GA;1;3937;06;bin;Switch;0;;On;Off|" ) );
      Serial.print( F( "GA;1;4734;01;bin;Switch;0;;On;Off|" ) );
      Serial.print( F( "GA;1;4919;02;bin;Switch;0;;On;Off|" ) );
      Serial.print( F( "GA;1;4998;00;bin;Switch;0;;On;Off|" ) );
      //==========================================================
      Serial.println( F( "END|" ) );
    } // END if
    //---------------------------------------------------------------------
    // Get Values  
    //---------------------------------------------------------------------
    if( Comp(str, GetValues) == 0 ){
      //==========================================================
      SendValue( SW05iD );
      SendValue( SW03iD );
      SendValue( SW07iD );
      SendValue( SW04iD );
      SendValue( SW06iD );
      SendValue( SW01iD );
      SendValue( SW02iD );
      SendValue( SW00iD );
    } //END if
    //
    //---------------------------------------------------------------------
    // Set Value  
    //---------------------------------------------------------------------
    // Single Value format SetV;[GaugeId];[value];*E
    // SetV;3578;1;*E
    // Multi Values format SetV;[GaugeId];[value];[value];[value];*E
    //---------------------------------------------------------------------
    // End Value
    //---------------------------------------------------------------------
    if( Comp(str, EndSend) == 0 )
    {
      VAL_IN = false;
      VAR_IN = false;
    }
    //---------------------------------------------------------------------
    // Value on Recive
    //---------------------------------------------------------------------
    if ( VAR_IN == false && VAL_IN == true )
    {
      switch ( valId ) {
      //Switch Variable
      case SW05iD:
         SW05 = atoi(str);
        break;
      //Switch Variable
      case SW03iD:
         SW03 = atoi(str);
        break;
      //Switch Variable
      case SW07iD:
         SW07 = atoi(str);
        break;
      //Switch Variable
      case SW04iD:
         SW04 = atoi(str);
        break;
      //Switch Variable
      case SW06iD:
         SW06 = atoi(str);
        break;
      //Switch Variable
      case SW01iD:
         SW01 = atoi(str);
        break;
      //Switch Variable
      case SW02iD:
         SW02 = atoi(str);
        break;
      //Switch Variable
      case SW00iD:
         SW00 = atoi(str);
        break;

      default:
        Serial.println(F("Variable UNKNOW"));
      }
    }
  //---------------------------------------------------------------------
  // RECIVE ID VAR
  //---------------------------------------------------------------------
  if ( VAR_IN == true && VAL_IN == false )
  {
    valId  = atoi(str);
    VAR_IN = false;
    VAL_IN = true;
  }

    //---------------------------------------------------------------------
    // Variable Name do not exist
    //---------------------------------------------------------------------
    if( VAR_IN == true && VAL_IN == false )
    {
      valId =  0;
      VAR_IN = false;
      VAL_IN = true;
    }
    //---------------------------------------------------------------------
    // Variable On Recive
    //---------------------------------------------------------------------
    if( Comp(str, SetVar) == 0 && VAR_IN == false && VAL_IN == false ){
      VAR_IN = true;
      VAL_IN = false;
    } //END if
    //---------------------------------------------------------------------
  } // END for
} // END void
//=========================================================================
// Compare Value
//=========================================================================
char Comp(char* inData, char* This){
  index = 0;
  if(strcmp(inData,This)  == 0) {
    return(0);
  } else {
    return(1);
  }
}
//=========================================================================
// SEND VALUE To MONITOR
//=========================================================================
void SendValue(int SendVar)
{
  //***********************************************************************
  //* SEND VALUE TO MONITOR:
  //***********************************************************************
 char OutBuffer[MAX_STRING_LEN];  // static buffer for computation
  sprintf( OutBuffer, "V;%s;%i;", IOT, SendVar );
  Serial.print( OutBuffer );
  switch ( SendVar )
  {
  case SW05iD:
    // SEND VALUE "Switch >> SW05"  TO MONITOR
    Serial.print( SW05 );
    break;
  case SW03iD:
    // SEND VALUE "Switch >> SW03"  TO MONITOR
    Serial.print( SW03 );
    break;
  case SW07iD:
    // SEND VALUE "Switch >> SW07"  TO MONITOR
    Serial.print( SW07 );
    break;
  case SW04iD:
    // SEND VALUE "Switch >> SW04"  TO MONITOR
    Serial.print( SW04 );
    break;
  case SW06iD:
    // SEND VALUE "Switch >> SW06"  TO MONITOR
    Serial.print( SW06 );
    break;
  case SW01iD:
    // SEND VALUE "Switch >> SW01"  TO MONITOR
    Serial.print( SW01 );
    break;
  case SW02iD:
    // SEND VALUE "Switch >> SW02"  TO MONITOR
    Serial.print( SW02 );
    break;
  case SW00iD:
    // SEND VALUE "Switch >> SW00"  TO MONITOR
    Serial.print( SW00 );
    break;

  }
  Serial.println( F( "|" ) );
}

//***********************************************************************

