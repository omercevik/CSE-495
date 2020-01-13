#include "Game.h"
#include "Buzzer.h"
#include "Ultrasonic.h"
#include "i2c-lcd.h"
#include "KeyPad.h"
#include "Motors.h"

int melodyChanger = 100;
int timeout = 0;
extern RTC_HandleTypeDef hrtc;
extern bool alarmRing;
int counter = 0;
int usrIndex = 6;
char gameUser[30] = "USR :          ";
char key = ' ';
int winner = 0;
bool gameContinue = true;
int game[6] = {7, 5, 3, 9, 8};

void playGame(void)
{
	char gamePC[30];
	lcd_send_cmd(0x80);
	sprintf(gamePC,"PC  : %d %d %d %d %d", game[0], game[1], game[2], game[3], game[4]);
	lcd_send_string(gamePC);
	lcd_send_cmd(0xc0);
	lcd_send_string(gameUser);
	
	while(gameContinue)
	{	
		while(counter < 5)
		{
			ultraSonicModule();
			buzzerModule();
			HAL_Delay(melodyChanger);
			ultraSonicModule();
			key = KeyPad_WaitForKeyGetChar(timeout);
			if(key != ' ' && key != 0)
			{
				if(game[counter] + key - '0' == 9)
				{
					gameUser[usrIndex++] = key;
					gameUser[usrIndex++] = ' ';
					lcd_send_cmd(0xc0);
					lcd_send_string(gameUser);
					++winner;
					++counter;
				}
			}
			
			HAL_Delay(melodyChanger);
			ultraSonicModule();
			HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // backup register 
		}
		if(winner == 5)
		{
			stopMotors();
			alarmRing = false;
			gameContinue = false;
			HAL_GPIO_DeInit(Button_GPIO_Port,Button_Pin);
		}
		else{
			for (int i = 6; i < 16; ++i)
					gameUser[i] = ' ';
			counter = 0;
			
			
			winner = 0;
			usrIndex = 6;
		}
	}
}

