#include "ee.h"
#include "Arduino.h"

#define MAX_MESSAGE_L 64
#define TOT_LETTERS 26
#define NUM_MESSAGES 5
#define SYMBOL_MAX_LENGTH 4
#define MAX_LENGTH_BINARY 20
#define ON_BOARD_LED 13
#define PAUSE_AFTER_MILLIS 1800

/*set this to '1' just for debug purpose*/
#define DEBUG_ON_SERIAL 1

int i=0,j=0,k=0,p=0,timer=0,no_other_tr=0,m=0;
char traduction[MAX_LENGTH_BINARY+1];
char letter,symbol;
int length_of_messages[NUM_MESSAGES]={54,59,64,31,53};
char messages[NUM_MESSAGES][MAX_MESSAGE_L+1]=
{
	"A FEATHER IN THE HAND IS BETTER THAN A BIRD IN THE AIR",
	"A SHORT PENCIL IS USUALLY BETTER THAN A LONG MEMORY ANY DAY",
    "ACCEPT SOMETHING THAT YOU CANNOT CHANGE AND YOU WILL FEEL BETTER",
	"ADVENTURE CAN BE REAL HAPPINESS",
    "ALL THE EFFORT YOU ARE MAKING WILL ULTIMATELY PAY OFF"
};

char morse_table[TOT_LETTERS][SYMBOL_MAX_LENGTH+1]=
{
	".-",	//A
	"-...",	//B
	"-.-.",	//C
	"-..",	//D
    ".",	//E
	"..-.",	//F
	"--.",	//G
	"....",	//H
	"..",	//I
	".---",	//J
	"-.-",	//K
	".-..",	//L
	"--",	//M
	"-.",	//N
	"---",	//O
	".--.",	//P
	"--.-",	//Q
	".-.",	//R
	"...",	//S
	"-",	//T
	"..-",	//U
	"...-",	//V
	".--",	//W
	"-..-",	//X
	"-.--",	//Y
	"--.."	//Z
};

/*
 * TASK  MUST BE C SYMBOL
 */
extern "C" {
	/* TASKs */
	DeclareTask(Task1);
	/*
	#if (defined(OSEE_API_DYNAMIC))
		TaskType Task1;
	#endif */
	void StartupHook(void)
	{
		#if(DEBUG_ON_SERIAL)
			Serial.write("HELLO FROM ARDUINO\n", 20);
		#endif
	}
}

void setup(void)
{
  /* initialize the digital pin as an output. */
  pinMode(ON_BOARD_LED, OUTPUT);
  #if(DEBUG_ON_SERIAL)
  	  Serial.begin(115200);
  #endif
}

int main(void)
{
  init();
  setup();
#if defined(USBCON)
  USBDevice.attach();
#endif
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

/*
 * TASK 1
 */
TASK(Task1)
{
	/*enter here only if y need to start a traduction of a new letter*/
	/*---BLOCK#1-----*/
	if(no_other_tr==0){
		letter=messages[m][i];
		for(j=0,symbol=morse_table[letter-'A'][0];j<SYMBOL_MAX_LENGTH&&(letter!=' ');j++,symbol=morse_table[letter-'A'][j]){
			if(symbol=='.'){
				traduction[k++]='1';
				traduction[k++]='0';
			}else if(symbol=='-'){
				traduction[k++]='1';
				traduction[k++]='1';
				traduction[k++]='1';
				traduction[k++]='0';
			}else{
				/*\0 found,every symbol traduced for the current letter*/
				break;
			}
		}
		/*at the end of a letter we need "000",add only 2 zero because 1 already putted in any case*/
		if(letter!=' '){
			traduction[k++]='0';
			traduction[k++]='0';
		}
		/*is this the last letter of our message or the and of a word? than put 0000*/
		if(i==(length_of_messages[m]-1)||letter==' '){
			traduction[k++]='0';
			traduction[k++]='0';
			traduction[k++]='0';
			traduction[k++]='0';
		}
		/*traduction completed*/
		no_other_tr=1;
	}
	timer++;
	/*print traduction each clock tick*/
	/*---BLOCK#2-----*/
	if(timer<PAUSE_AFTER_MILLIS){
		if(p<k){
			if(traduction[p++]=='1'){
				#if(DEBUG_ON_SERIAL)
					Serial.write("1\n");
				#else
					digitalWrite(ON_BOARD_LED, HIGH);
				#endif
			}else
				#if(DEBUG_ON_SERIAL)
					Serial.write("0\n");
				#else
					digitalWrite(ON_BOARD_LED, LOW);
				#endif
			if(p==k){
				/*last bit has been printed!, go for the next letter*/
				no_other_tr=0;
				i=(i+1)%(length_of_messages[m]);
				k=0;p=0;
			    #if(DEBUG_ON_SERIAL)
					Serial.write("\n");
				#endif
			}
		}
	/*go for next message after 180 seconds,[stay idle for 0.5 seconds(5 cycles)]*/
	/*---BLOCK#3-----*/
	}else{
		#if(DEBUG_ON_SERIAL)
			Serial.write("I\n");
		#else
			digitalWrite(ON_BOARD_LED, LOW);
		#endif
		if(timer==PAUSE_AFTER_MILLIS+4){
			k=0;p=0;i=0,timer=0;
			m=(m+1)%NUM_MESSAGES;
			no_other_tr=0;
			timer=0;
		}
	}
	TerminateTask();
}


