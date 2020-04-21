#include <TimeLib.h>
#include <Streaming.h>
#include "CronClass.h"
//#include "Header.h"
//MyCronTime* cron = new MyCronTime();
extern int __bss_end;
extern void *__brkval;

void setup()
{
	Serial.begin(9600);

}


void loop()
{
    //Serial.println(memoryFree());
	String st = "12-15 18-20 18-24 1-7";
	time_t prnt = 1587368160;
 	MyCronTime::calculateTimer(&prnt, &st);
	Serial.print("result = ");
	Serial.println(prnt);
	Serial.println(memoryFree());


}

void printDateTime(time_t t)
{
	Serial << ((day(t) < 10) ? "0" : "") << _DEC(day(t));
	Serial << monthShortStr(month(t)) << _DEC(year(t)) << ' ';
	Serial << ((hour(t) < 10) ? "0" : "") << _DEC(hour(t)) << ':';
	Serial << ((minute(t) < 10) ? "0" : "") << _DEC(minute(t)) << ':';
	Serial << ((second(t) < 10) ? "0" : "") << _DEC(second(t));
}

int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}
