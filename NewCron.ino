#include <TimeLib.h>
#include <Streaming.h>
#include "CronClass.h"
MyCronTime* cron = new MyCronTime();
//extern int __bss_end;
//extern void *__brkval;

void setup()
{
	Serial.begin(9600);

}


void loop()
{
    //Serial.println(memoryFree());
	//printDateTime(18670594);
	String st = "* 18 * *";
	//MyCronTime* cron = new MyCronTime(st);
	//bool argv;
	time_t prnt = 1587098520;
	//argv = cron->checkCronString();
	//if (argv)
		//Serial.println("Truelz");
	//else
		//prnt = cron->calcCron(prnt);
	//prnt = cron->calcCron(prnt, st);
	time_t timer = cron->calculateTimer(prnt, st);
	Serial.println(timer);
	//Serial.println(memoryFree());
	st = "15 20 * *";
	timer = cron->calculateTimer(prnt, st);
	Serial.println(timer);
  
		
	
	//delay(5000);
}

void printDateTime(time_t t)
{
	Serial << ((day(t) < 10) ? "0" : "") << _DEC(day(t));
	Serial << monthShortStr(month(t)) << _DEC(year(t)) << ' ';
	Serial << ((hour(t) < 10) ? "0" : "") << _DEC(hour(t)) << ':';
	Serial << ((minute(t) < 10) ? "0" : "") << _DEC(minute(t)) << ':';
	Serial << ((second(t) < 10) ? "0" : "") << _DEC(second(t));
}

/*int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}
*/