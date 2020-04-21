#pragma once
static class MyCronTime {
	public:
		/*MyCronTime::MyCronTime()
		{
			//minuteC = "*";//getValue(str, ' ', 0);
			//hourC = "*";//getValue(str, ' ', 1);
			//dayC = "*";//getValue(str, ' ', 2);
			//weekDayC = "*";//getValue(str, ' ', 3);
			/*Serial.println(minuteC);
			Serial.println(hourC);
			Serial.println(weekDayC);
			Serial.println(dayC);*/
			//Serial << minuteC << " " << hourC << " " << dayC << " " << weekDayC<< '\n';	
	
		//}

		static bool checkCronString()
		{
			bool errFlag = false;
			Serial.println("start check");

			//return checkErr(errFlag, 0, 59, minuteC) || 
			for (int i = 0; i < 4; i++)
			{
				if (!errFlag)
					switch (i)
					{
					case 0:
						errFlag = checkErr(errFlag, 0, 59, minuteC);
						break;
					case 1:
						errFlag = checkErr(errFlag, 0, 23, hourC);
						break;
					case 2:
						errFlag = checkErr(errFlag, 1, 31, dayC);
						break;
					case 3:
						errFlag = checkErr(errFlag, 1, 7, weekDayC);
						break;
					}
			}
			if (errFlag)
			{
				//Serial.println("True Flag");
				return true;
			}
			else
			{
				//Serial.println("False Flag");
				return false;
			}
			Serial.println("exit check");
			//delay(5000);
		}

		
		static void calculateTimer(time_t *nowTime, String *str)
		{
			Serial.println("1");
			int cronFakeStr[4] = { -1,-1,-1,-1 };
			bool m;
			Serial.println("2");
			splitCronString(*str);
			Serial.println("3");
			m = checkCronString();
			Serial.println("4");

			if (m)
			{
				Serial.println("Truelz");
				//return 0;
			}
			else
			{
				Serial.println("1");
				calcMinute(nowTime, cronFakeStr);
				calcHour(nowTime, cronFakeStr);
				calcDay(nowTime, cronFakeStr);
				calcWeekday(nowTime, cronFakeStr);

				//return nowTime;
			}
		}


	private:

		static String minuteC;
		static String hourC;
		static String dayC;
		static String weekDayC;
		static constexpr int dayOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		static String getValue(String *data, char separator, int index)
		{
			int found = 0;
			int strIndex[] = { 0, -1 };
			int maxIndex = (*data).length() - 1;

			for (int i = 0; i <= maxIndex && found <= index; i++) {
				if ((*data).charAt(i) == separator || i == maxIndex) {
					found++;
					strIndex[0] = strIndex[1] + 1;
					strIndex[1] = (i == maxIndex) ? i + 1 : i;
				}
			}
			return found > index ? (*data).substring(strIndex[0], strIndex[1]) : "";
		}


		static bool isNumber(String str)
		{
			bool a = true;
			for (int i = 0; i < str.length(); i++)
			{
				if (!isDigit(str[i]))
				{
					a = false;
					break;

				}
			}
			if (a == true)
				return true;
			else
				return false;
		}

		static bool isBetween(String value, int a, int b)
		{
			int v = value.toInt();
				if (a <= v && v <= b)
					return true;
				else
					return false;
		}


		static bool checkInterval(String str, int a, int b)
		{
			String vlst0 = getValue(&str, '-', 0);
			String vlst1 = getValue(&str, '-', 1);
			if (isNumber(vlst0) && isNumber(vlst1) && getValue(&str, '-', 2) == NULL)
			{
				if (isBetween(vlst0, a, b) && isBetween(vlst1, a, b)) //&& vlst0.toInt() <= vlst1.toInt())
					return false;
				else
					return true;
			}

			vlst0 = getValue(&str, '/', 0);
			vlst1 = getValue(&str, '/', 1);
			if (vlst0 == "*" && isNumber(vlst1) && getValue(&str, '/', 2) == NULL)
			{
				if (isBetween(vlst1, a, b))
					return false;
				else
					return true;
			}
			else
				return true;
			
	
		}

		static String checkValue(String value)
		{
			if (value == "*" || isNumber(value))
				if (isNumber(value))
					return "True";
				else
					return "False";
			else
				return "err";
		}

		static bool checkErr(bool errFlag, int a, int b, String value)
		{
			if (checkValue(value) == "True")
			{
				if (!(a <= value.toInt() && b >= value.toInt()))
					errFlag = true;
			}	
			else
				if (checkValue(value) == "err")
					errFlag = checkInterval(value, a, b);

			return errFlag;
		}

		static void zeroMinuteInterval(time_t *timerTime, int cronFakeStr[4])
		{
			if (!isNumber(minuteC) && minuteC != "*")
				*timerTime = *timerTime - minute(*timerTime) * 60 + cronFakeStr[0] * 60;

			//return timerTime;
		}
		
		static void zeroHourInterval(time_t *timerTime, int cronFakeStr[4])
		{
			if (!isNumber(hourC) && hourC != "*")
				*timerTime = *timerTime - hour(*timerTime) * 3600 + cronFakeStr[1] * 3600;

			//return timerTime;
		}

		static void zeroMinute(time_t *timerTime)
		{
			if (minuteC == "*")
				*timerTime = *timerTime - minute(*timerTime) * 60;

			//return timerTime;
		}

		static void zeroHour(time_t *timerTime)
		{
			if (hourC == "*")
				*timerTime = *timerTime - hour(*timerTime) * 3600;

			//return timerTime;
		}

		static void calcDayForMonth(time_t *timerTime, String today)
		{
			if (dayOfMonth[month(*timerTime) - 1] > today.toInt())
			{
				*timerTime = *timerTime;
			}
			else
			{
				*timerTime = *timerTime + (dayOfMonth[month(*timerTime) - 1] - day(*timerTime) + 1) * 86400;
				while (dayOfMonth[month(*timerTime) - 1] < today.toInt())
				{
					*timerTime = *timerTime + dayOfMonth[month(*timerTime) - 1] * 86400;
				}
			}

			//return timerTime;
		}

		static int weekDayNormal(time_t *timerTime)
		{
			int wd;
			if (weekday(*timerTime) == 1)
				wd = 7;
			else
				wd = weekday(*timerTime) - 1;
			//wd = weekday(timerTime);
			Serial.print("wd = ");
			Serial.println(wd);
			return wd;
		}

		static void calcDayForWeekday(time_t *timerTime, String dayTimer)
		{
			while (day(*timerTime) != dayTimer.toInt())
			{
				*timerTime = *timerTime + 7 * 86400;
			}

			//return timerTime;
		}

		static void calcDayForWeekdayInterval(time_t *timerTime, int dayTimer,String a, String b)
		{
			while (day(*timerTime) != dayTimer)
			{
				while (a.toInt() <= b.toInt() && day(*timerTime) != dayTimer)
				{
					*timerTime = *timerTime + 86400;
				}
				if (day(*timerTime) != dayTimer)
					*timerTime = *timerTime + (7 - weekDayNormal(timerTime) + a.toInt()) * 86400;
			}
			//return timerTime;
		}

		static void calcIntervalDayForWeekdayInterval(time_t *timerTimer, int a, int b, int da, int db)
		{
			bool check = true;
			while (check)
			{
				if (da <= day(*timerTimer) && day(*timerTimer) <= db && a <= weekDayNormal(timerTimer) && weekDayNormal(timerTimer) <= b)
					check = false;
				else
					*timerTimer = *timerTimer + 86400;
			}

			//return timerTimer;
		}

		static void calcDayForWeekdaySteps(time_t *timerTime, int cronFakeLst[4], int value)
		{
			String lst0;
			String lst1;
			String temp = dayC;
			lst0 = getValue(&temp, '-', 0);
			lst1 = getValue(&temp, '-', 1);
			if (isNumber(lst0))
			{
				while (!(lst0.toInt() <= day(*timerTime) && day(*timerTime) <= lst1.toInt() && (weekDayNormal(timerTime) % value) == 0))
				{
					*timerTime = *timerTime + 86400;
				}
			}

			temp = dayC;
			lst0 = getValue(&temp, '/', 0);
			lst1 = getValue(&temp, '/', 1);
			if (isNumber(lst0))
			{
				while (!((weekDayNormal(timerTime)) % value == 0 && (day(*timerTime) % value) == 0))
				{
					*timerTime = *timerTime + 86400;
				}
			}

			if (isNumber(dayC))
			{
				while (!(day(*timerTime) == dayC.toInt() && weekDayNormal(timerTime) % value == 0))
				{
					*timerTime = *timerTime + 86400;
				}
			}

			if (dayC == "*")
			{
				while (!(weekDayNormal(timerTime) % value == 0))
				{
					*timerTime = *timerTime + 86400;
				}
			}

			if (cronFakeLst[1] == -1)
				*timerTime = *timerTime - hour(*timerTime) * 3600;

			if (cronFakeLst[0] == -1)
				*timerTime = *timerTime - minute(*timerTime) * 60;

			//return timerTime;
		}

		static void splitCronString(String str)
		{
			minuteC = getValue(&str, ' ', 0);
			hourC = getValue(&str, ' ', 1);
			dayC = getValue(&str, ' ', 2);
			weekDayC = getValue(&str, ' ', 3);
			Serial << minuteC << " " << hourC << " " << dayC << " " << weekDayC << '\n';
		}

		static void calcMinute(time_t *timerTime, int *cronFakeStr)
		{
			if (isNumber(minuteC) || minuteC == "*")
			{
				if (minuteC == "*")
				{
					if (hourC == "*")
						*timerTime = *timerTime + 60;
					if (isNumber(hourC))
					{
						if (int(hour(*timerTime)) == hourC.toInt())
							*timerTime = *timerTime + 60;
						else
							*timerTime = *timerTime - (minute(*timerTime) * 60);
					}
				}
				else
				{
					int minNow = minute(*timerTime);
					if (minNow < minuteC.toInt())
						*timerTime = *timerTime + (minuteC.toInt() - (minNow)) * 60;

					if (minNow > minuteC.toInt())
						*timerTime = *timerTime + (60 - minNow + minuteC.toInt()) * 60;
					else
						*timerTime = *timerTime + 3600;
				}
			}
			else
			{
				String lst0;
				String lst1;
				String temp = minuteC;
				temp.replace("/", "-");
				lst0 = getValue(&temp, '-', 0);
				lst1 = getValue(&temp, '-', 1);
				if (isNumber(lst0))
				{
					cronFakeStr[0] = lst0.toInt();
					if (lst0.toInt() <= minute(*timerTime) && minute(*timerTime) < lst1.toInt())
						*timerTime = *timerTime + 60;
					if (lst0.toInt() > minute(*timerTime))
						*timerTime = *timerTime + (lst0.toInt() - minute(*timerTime)) * 60;
					else
						*timerTime = *timerTime + (60 - minute(*timerTime) + lst0.toInt());
				}
				else
				{
					cronFakeStr[0] = 0;
					lst0;
					lst1;
					temp = minuteC;
					lst0 = getValue(&temp, '/', 0);
					lst1 = getValue(&temp, '/', 1);
					int nowMin = minute(*timerTime);

					if (nowMin == 0)
						*timerTime = *timerTime + int(lst1.toInt()) * 60;
					if ((nowMin - (nowMin % lst1.toInt()) + lst1.toInt()) < 59)
						*timerTime = *timerTime + lst1.toInt() * 60 - (nowMin % lst1.toInt()) * 60;
					else
						*timerTime = *timerTime + (60 - nowMin) * 60;
				}
			}

			//return timerTime;
		}

		static void calcHour(time_t *timerTime, int *cronFakeStr)
		{
			if (isNumber(hourC) && hourC == "*")
			{
				if (hourC == "*")
					*timerTime = *timerTime;
				else
				{
					int nowHour = hour(*timerTime);
					if (nowHour < hourC.toInt())
						*timerTime = *timerTime + (hourC.toInt() - nowHour) * 3600;

					if (nowHour > hourC.toInt())
						*timerTime = *timerTime + (24 - nowHour + hourC.toInt()) * 3600;
				}

			}
			else
			{
				String lst0;
				String lst1;
				String temp = hourC;
				temp.replace("/", "-");
				lst0 = getValue(&temp, '-', 0);
				lst1 = getValue(&temp, '-', 1);
				if (isNumber(lst0))
				{
					cronFakeStr[1] = lst0.toInt();
					if (lst0.toInt() <= hour(*timerTime) && hour(*timerTime) < lst1.toInt())
						*timerTime = *timerTime;
					else
						if (lst0.toInt() > hour(*timerTime))
						{
							*timerTime = *timerTime + (lst0.toInt() - hour(*timerTime)) * 3600;
							if (minuteC == "*")
								*timerTime = *timerTime - (minute(*timerTime)) * 60;
							if (!isNumber(minuteC) && minuteC != "*")
								*timerTime = *timerTime - minute(*timerTime) * 60 + cronFakeStr[0] * 60;
						}
						else
							*timerTime = *timerTime + (24 - hour(*timerTime) + lst0.toInt()) * 3600;
				}
				else
				{
					cronFakeStr[1] = 0;
					String lst0;
					String lst1;
					String temp = hourC;
					lst0 = getValue(&temp, '/', 0);
					lst1 = getValue(&temp, '/', 1);
					int nowHour = hour(*timerTime);
					if (nowHour == 0)
						*timerTime = *timerTime + lst1.toInt() * 3600;
					else
						if (nowHour % lst1.toInt() == 0)
							*timerTime = *timerTime;
						else
							if ((nowHour - (nowHour % lst1.toInt()) + lst1.toInt()) < 24 && nowHour % lst1.toInt() != 0)
							{
								*timerTime = *timerTime - nowHour * 3600 + (nowHour - (nowHour % lst1.toInt()) + lst1.toInt()) * 3600;
								if ((cronFakeStr[0] != -1))
									*timerTime = *timerTime - (minute(*timerTime)) * 60;
							}
							else
							{
								*timerTime = *timerTime + (24 - nowHour) * 3600;
								if (cronFakeStr[0] != -1)
									*timerTime = *timerTime - minute(*timerTime) * 60;
							}
				}

			}

			//return timerTime;
		}

		static void calcDay(time_t *timerTime, int *cronFakeStr)
		{

			if (isNumber(dayC) || dayC == "*")
			{
				if (dayC == "*")
					*timerTime;
				else
				{
					int nowDay = day(*timerTime);
					if (nowDay < dayC.toInt())
					{
						calcDayForMonth(timerTime, dayC);
						*timerTime = *timerTime + (dayC.toInt() - nowDay) * 86400;
						zeroHour(timerTime);
						zeroMinute(timerTime);
						zeroHourInterval(timerTime, cronFakeStr);
						zeroMinuteInterval(timerTime, cronFakeStr);
					}
					else
						if (nowDay > dayC.toInt())
						{
							calcDayForMonth(timerTime, dayC);
							int numberOfDays = dayOfMonth[month(*timerTime) - 1];
							zeroHour(timerTime);
							zeroMinute(timerTime);
							zeroHourInterval(timerTime, cronFakeStr);
							zeroMinuteInterval(timerTime, cronFakeStr);
							if (month(*timerTime) == 2)
								if (year(*timerTime) % 4 == 0)
									numberOfDays = numberOfDays + 1;

							*timerTime = (*timerTime) + (numberOfDays - nowDay + dayC.toInt()) * 86400;
						}
				}
			}
			else
			{
				int nowDay = day(*timerTime);
				String lst0;
				String lst1;
				String temp = dayC;
				temp.replace("/", "-");
				lst0 = getValue(&temp, '-', 0);
				lst1 = getValue(&temp, '-', 1);
				if (isNumber(lst0))
				{
					cronFakeStr[2] = lst0.toInt();
					if (lst0.toInt() <= day(*timerTime) && day(*timerTime) < lst1.toInt())
					{
						*timerTime = *timerTime;
					}
					else
					{
						if (lst0.toInt() > day(*timerTime))
						{
							*timerTime = *timerTime + (lst0.toInt() - day(*timerTime)) * 86400;
							zeroMinute(timerTime);
							zeroHour(timerTime);
							zeroHourInterval(timerTime, cronFakeStr);
							zeroMinuteInterval(timerTime, cronFakeStr);
						}
						else
						{
							*timerTime = *timerTime + (dayOfMonth[month(*timerTime) - 1] - day(*timerTime) + lst0.toInt()) * 86400;
						}
					}
				}
				else
				{
					cronFakeStr[2] = 1;
					String lst0;
					String lst1;
					String temp = dayC;
					lst0 = getValue(&temp, '/', 0);
					lst1 = getValue(&temp, '/', 1);
					nowDay = day(*timerTime);
					int numberOfDays = dayOfMonth[month(*timerTime) - 1];
					if (nowDay - (nowDay % lst1.toInt()) + lst1.toInt() < numberOfDays)
					{
						timerTime = timerTime - nowDay % lst1.toInt() * 86400 + lst1.toInt() * 86400;
						if (cronFakeStr[1] == -1)
							*timerTime = *timerTime - hour(*timerTime) * 3600;

						if (cronFakeStr[0] == -1)
							*timerTime = *timerTime - minute(*timerTime) * 60;
					}

				}

			}
			//return timerTime;
		}


		static void calcWeekday(time_t *timerTime, int *cronFakeStr)
		{
			if (isNumber(weekDayC) || weekDayC == "*")
			{
				if (weekDayC == "*")
					*timerTime = *timerTime;
				else
				{
					if (dayC == "*")
					{
						int numberOfWeekday = weekDayNormal(timerTime);
						if (numberOfWeekday < weekDayC.toInt())
							*timerTime = *timerTime + (weekDayC.toInt() - numberOfWeekday) * 86400;
						else
						{
							if (numberOfWeekday > weekDayC.toInt())
								*timerTime = *timerTime + (7 - numberOfWeekday + weekDayC.toInt()) * 86400;
						}

					}
					else
					{
						int numberOfWeekday = weekDayNormal(timerTime);
						if (numberOfWeekday < weekDayC.toInt())
						{
							*timerTime = *timerTime + (weekDayC.toInt() - numberOfWeekday) * 86400;
							calcDayForWeekday(timerTime, dayC);
						}
						else
						{
							if (numberOfWeekday > weekDayC.toInt())
							{
								*timerTime = *timerTime + (7 - numberOfWeekday + weekDayC.toInt()) * 86400;
								calcDayForWeekday(timerTime, dayC);
							}
							else
							{
								calcDayForWeekday(timerTime, dayC);
							}
						}
					}
				}
			}
			else
			{
				String lst0;
				String lst1;
				String temp = weekDayC;
				temp.replace("/", "-");
				lst0 = getValue(&temp, '-', 0);
				lst1 = getValue(&temp, '-', 1);
				if (isNumber(lst0))
				{
					if (dayC == "*")
					{
						int numberOfWeekday = weekDayNormal(timerTime);
						if (numberOfWeekday < lst0.toInt())
						{
							*timerTime = *timerTime + (lst0.toInt() - numberOfWeekday) * 86400;
						}
						else
							if (numberOfWeekday > lst1.toInt())
								*timerTime = *timerTime + (7 - numberOfWeekday + lst0.toInt()) * 86400;
					}
					else
					{
						if (isNumber(dayC))
						{
							int numberOfWeekday = weekDayNormal(timerTime);
							if (numberOfWeekday < lst0.toInt())
							{
								*timerTime = *timerTime + (lst0.toInt() - numberOfWeekday) * 86400;
								 calcDayForWeekdayInterval(timerTime, dayC.toInt(), lst0, lst1);
							}
							else
							{
								if (numberOfWeekday > lst1.toInt())
								{
									*timerTime = *timerTime + (7 - numberOfWeekday + lst0.toInt()) * 86400;
									calcDayForWeekdayInterval(timerTime, dayC.toInt(), lst0, lst1);
								}
								else
								{
									calcDayForWeekdayInterval(timerTime, dayC.toInt(), lst0, lst1);
								}
							}
						}
						else
						{
							String lstDay0;
							String lstDay1;
							String tempDay = dayC;
							lstDay0 = getValue(&tempDay, '-', 0);
							lstDay1 = getValue(&tempDay, '-', 1);
							calcIntervalDayForWeekdayInterval(timerTime, lst0.toInt(), lst1.toInt(), lstDay0.toInt(), lstDay1.toInt());
						}
					}
				}
				else
				{
					if (weekDayNormal(timerTime) % lst1.toInt() == 0)
						*timerTime = *timerTime;
					else
						calcDayForWeekdaySteps(timerTime, cronFakeStr, lst1.toInt());
				}
			}

			//return timerTime;
		}
};

