/* ------------------------------------------------
* SERIAL COM - HANDELING MULTIPLE BYTES inside ARDUINO - 03_function development
* by beltran berrocal
*
* this prog establishes a connection with the pc and waits for it to send him
* a long string of characters like "hello Arduino!". 
* Then Arduino informs the pc that it heard the whole sentence
*
* the same as examlpe 02 but it deploys 2 reusable functions.
* for doing the same job. 
* readSerialString() and  printSerialString()
* the only problem is that they use global variables instead of getting them passed 
* as parameters. this means that in order to reuse this code you should also copy
* the 4 variables instantiated at the beginning of the code.
* Another problem is that if you expect more than one string at a time 
* you will have to duplicate and change names to all variables as well as the functions.
* Next version should have the possibility to pass the array as a parameter to the function.
*
* created 15 Decembre 2005;
* copyleft 2005 Progetto25zero1  <http://www.progetto25zero1.com>
*
* --------------------------------------------------- */

#include <SoftwareSerial.h>
String c;


int  serIn;             // var that will hold the bytes-in read from the serialBuffer
char serInString[100];  // array that will hold the different bytes  100=100characters;
                        // -> you must state how long the array will be else it won't work.
int  serInIndx  = 0;    // index of serInString[] in which to insert the next incoming byte
int  serOutIndx = 0;    // index of the outgoing serInString[] array;

void readSerialString () {
    int sb;   
    if(Serial.available()) { 
       //Serial.print("reading Serial String: ");     //optional confirmation
       while (Serial.available()){ 
          sb = Serial.read();             
          serInString[serInIndx] = sb;
          serInIndx++;
          //serialWrite(sb);                        //optional confirmation
       }
       //Serial.println();
    }  
}

void printSerialString() {
   if( serInIndx > 0) {
      for(serOutIndx=0; serOutIndx < serInIndx; serOutIndx++) {
          Serial.print( serInString[serOutIndx] );    //print out the byte at the specified index
          //serInString[serOutIndx] = "";            //optional: flush out the content
      }        
      //reset all the functions to be able to fill the string back with content
      serOutIndx = 0;
      serInIndx  = 0;
   }

}

void setup() {
  Serial.begin(115200);
}

void loop () {
  readSerialString();
  printSerialString();
}