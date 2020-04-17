#include <TimeLib.h>
#include <Streaming.h>
#include "CronClass.h"


void setup()
{
	Serial.begin(9600);

}


void loop()
{
	//printDateTime(18670594);
	String st = "*/15 18 10 4";
	MyCronTime* cron = new MyCronTime(st);
	bool argv;
	time_t prnt = 1587098520;
	argv = cron->checkCronString();
	if (argv)
		Serial.println("Truelz");
	else
		prnt = cron->calcCron(prnt);

	Serial.println(prnt);
		
	
	delay(5000);
}

void printDateTime(time_t t)
{
	Serial << ((day(t) < 10) ? "0" : "") << _DEC(day(t));
	Serial << monthShortStr(month(t)) << _DEC(year(t)) << ' ';
	Serial << ((hour(t) < 10) ? "0" : "") << _DEC(hour(t)) << ':';
	Serial << ((minute(t) < 10) ? "0" : "") << _DEC(minute(t)) << ':';
	Serial << ((second(t) < 10) ? "0" : "") << _DEC(second(t));
}