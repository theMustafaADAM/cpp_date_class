#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "../../../Cpp_OOP_L1/OOP_Project_String_Class/include/clsString.h"

using namespace std;

class clsDate
{
    private:
        short _day = 1, _month = 1, _year = 1900;

    public:
        clsDate()
        {
            time_t t    = time(0);
            tm *now     = localtime(&t); /// for global time : gmtime(&t);
            _year       = now->tm_year + 1900;
            _month      = now->tm_mon  + 1;
            _day        = now->tm_mday;
        }
        clsDate(string strDate_DDMMYYYY)
        {
            vector<string> vDate;
            vDate   = clsString::Split(strDate_DDMMYYYY,"/");
            _day    = stoi(vDate[0]);
            _month  = stoi(vDate[1]);
            _year   = stoi(vDate[2]);

        }
        clsDate(short day, short month, short year) : _day(day), _month(month), _year(year) { }
        clsDate(short dateOrderInYear,  short Year)
        {
            clsDate date    = GetDateFromDaysCounter(_year, dateOrderInYear );
            _day        = date.Get_day();
            _month      = date.Get_month();
            _year       = date.Get_year();
        }
        virtual ~clsDate(){ }

        short Get_day()         { return _day; }
        void Set_day(short val) { _day = val; }

        short Get_month()           { return _month; }
        void Set_month(short val)   { _month = val; }

        short Get_year()            { return _year; }
        void Set_year(short val)    { _year = val; }

        void Print()
        {
            cout << DateToString() << endl;
        }
        static string DateToString(clsDate date)
        {
            return to_string(date.Get_day()) + "/" + to_string(date.Get_month()) + "/" + to_string(date.Get_year());
        }
        string DateToString()
        {
            return DateToString(*this);
        }

        static clsDate GetSystemDate()
        {
            time_t t    = time(0);
            tm *now     = localtime(&t);  /// for global time : gmtime(&t);
            short year  = now->tm_year + 1900;
            short month = now->tm_mon  + 1;
            short day   = now->tm_mday;
            return clsDate(day, month, year);
        }

        static string GetSystemDateTimeString()
        {
            time_t t    = time(0);
            tm *now     = localtime(&t);  /// for global time : gmtime(&t);
            short year  = now->tm_year + 1900;
            short month = now->tm_mon  + 1;
            short day   = now->tm_mday;
            short hour  = now->tm_hour;
            short minut = now->tm_min;
            short scond = now->tm_sec;
            return (to_string(day) +"/"+ to_string(month)+"/"+ to_string(year)+
                "-"+ to_string(hour)+":"+ to_string(minut)+":"+ to_string(scond));
        }

        static bool IsLeapYear(short year)
        {
            return (year % 4 == 0 && year % 100 != 0) ||(year % 400 == 0);
        }
        bool IsLeapYear()
        {
            return IsLeapYear(_year);
        }

        static short CountDaysInAMonth(short Year, short Month)
        {
            short Arr31Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            return ((Month == 2) ? (IsLeapYear(Year) ? 29 : 28 ) :  Arr31Days[Month - 1] );
        }
        short CountDaysInAMonth()
        {
            return CountDaysInAMonth(_year, _month);
        }

        clsDate GetDateFromDaysCounter(short Year, short DayCounter)
        {
            clsDate Date; short RemainingDays, MonthDays = 0, month;
            Year = Date.Get_year(); Date.Set_month(1); month = Date.Get_month();
            RemainingDays = DayCounter;
            while(true)
            {
                MonthDays = CountDaysInAMonth(Year, month);
                if(RemainingDays > MonthDays)
                {   RemainingDays -= MonthDays; ++month;   }
                else
                {   Date.Set_day(RemainingDays);  break;  }
            }
            Date.Set_month(month);
            return Date;
        }

        static bool IsValidDate(clsDate date)
        {
            if (date.Get_day()   < 1 || date.Get_day()   > 31) return false;
            if (date.Get_month() < 1 || date.Get_month() > 12) return false;
            if (date.Get_month() == 2 )
            {
                if (IsLeapYear(date.Get_year()))    {   if (date.Get_day() > 29) return false;  }
                if(!IsLeapYear(date.Get_year()))    {   if (date.Get_day() > 28) return false;  }
            }
            short DaysInMonth = CountDaysInAMonth(date.Get_year(),date.Get_month());
            if (date.Get_day() > DaysInMonth) return false;
            return true;
        }
        bool IsValid()
        {
            return IsValidDate(*this);
        }

        static short NumberOfDaysInYear(short year)
        {
            return IsLeapYear(year) ? 365 : 364;
        }
        short NumberOfDaysInYear()
        {
            return NumberOfDaysInYear(_year);
        }

        static short NumberOfHourInYear(short year)
        {
            return NumberOfDaysInYear(year) * 24;
        }
        short NumberOfHourInYear()
        {
            return NumberOfHourInYear(_year);
        }

        static int NumberOfMinutesInYear(short year)
        {
            return NumberOfHourInYear(year) * 60;
        }
        int NumberOfMinutesInYear()
        {
            return NumberOfMinutesInYear(_year);
        }

        static int NumberOfSecondsInYear(short year)
        {
            return NumberOfMinutesInYear(year) * 60;
        }
        int NumberOfSecondsInYear()
        {
            return NumberOfSecondsInYear(_year);
        }

        static short NumberOfHoursInMonth(short year, short month)
        {
            return CountDaysInAMonth(year, month) * 24;
        }
        short NumberOfHoursInMonth()
        {
            return NumberOfHoursInMonth(_year, _month);
        }

        static int NumberOfMinutesInMonth(short year, short month)
        {
            return NumberOfHoursInMonth(year, month) * 60;
        }
        int NumberOfMinutesInMonth()
        {
            return NumberOfMinutesInMonth(_year, _month);
        }

        static int NumberOfSecondsInMonth(short year, short month)
        {
            return NumberOfMinutesInMonth(year,month) * 60;
        }
        int NumberOfSecondsInMonth()
        {
            return NumberOfSecondsInMonth(_year, _month);
        }

        static short DayOfWeekOrder(short Year, short Month, short Day)
        {
            short a = (14-Month)/12; short y = Year-a;
            short m = Month+(12*a)-2;
            short d = (Day+y+(y/4)-(y/100)+(y/400)+(31*m/12))%7;
            return d;
        }
        short DayOfWeekOrder()
        {
            return DayOfWeekOrder(_year,_month,_day);
        }

        static string DayShortName(short Day)
        {
            string DayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};
            return (DayNames[Day]);
        }
        string DayShortName()
        {
            string DayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};
            return DayNames[DayOfWeekOrder(_year,_month,_day)];
        }

        static string MonthShortName(short Month)
        {
            string MonthName[12] = {  "Jan", "Fab", "Mar", "Apr", "May", "Jun",
                                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
            return (MonthName[Month-1]);
        }
        string MonthShortName()
        {
            return MonthShortName(_month);
        }

        static void PrintMonthCalendar(short Year, short Month)
        {
            short FrstDay = DayOfWeekOrder(Year, Month, 1);
            short NmbrDay = CountDaysInAMonth(Year,Month);
            printf( "\n  ---------------------  %s  ---------------------\n\n",
            MonthShortName(Month-1).c_str());
            printf("    Sun    Mon    Tue    Wed    Thr    Fri    Sat\n\n");
            ///Print Spaces
            short i;
            for (i=0; i < FrstDay; ++i)
                printf("       ");
            for(short j =1; j <= NmbrDay; ++j)
            {
                printf("%7d", j);   if(++i == 7)    i = 0;    printf("\n");
            }
            cout << "\n   -----------------------------------------------\n" << endl;
        }
        void PrintMonthCalendar()
        {
            PrintMonthCalendar(_year,_month);
        }

        static void PrintYearCalendar(short Year)
        {
            printf("\n   -----------------------------------------------\n");
            cout << "\n\t\tCalendar of " << Year << endl;
            printf("\n   -----------------------------------------------\n");
            for (short i =1; i <=12; ++i)
            {
                PrintMonthCalendar(Year, i);
            }
        }
        void PrintYearCalendar()
        {
            printf("\n   -----------------------------------------------\n");
            cout << "\n\t\tCalendar of " << _year << endl;
            printf("\n   -----------------------------------------------\n");
            for (short i = 1; i <= 12; ++i)
            {
                PrintMonthCalendar(_year, i);
            }
        }

        static short CountDayFromBeginingYear(short day, short month, short year)
        {
            short dayCounter=0;
            for (short i =1; i <= month -1; ++i)
            {
                dayCounter += CountDaysInAMonth(year,i);
            }
            dayCounter += day;
            return dayCounter;
        }
        short CountDayFromBeginingYear()
        {
            short dayCounter=0;
            for (short i =1; i <= _month -1; ++i)
            {
                dayCounter += CountDaysInAMonth(_year,i);
            }
            dayCounter += _day;
            return dayCounter;
        }

        static clsDate GetDateFromDaysOrderInYear(short Year, short DayOrder)
        {
            clsDate Date;
            short RemainingDays= DayOrder, MonthDays= 0 , month=0;
            Date.Set_year(Year);
            Date.Set_month(1);
            month = Date.Get_month();
            while(true)
            {
                MonthDays = CountDaysInAMonth(Year, Date.Get_month());
                if(RemainingDays > MonthDays)
                {   RemainingDays -= MonthDays; ++month;
                }
                else
                {   Date.Set_day(RemainingDays);  break; }
            } Date.Set_month(month);
            return Date;
        }

        void AddDays(short days)
        {
            short remainDays = days + CountDayFromBeginingYear(_year,_month,_day);
            short monthDays =0; _month =1;
            while(true)
            {
                monthDays = CountDaysInAMonth(_year, _month);
                if(remainDays > monthDays)
                {
                    remainDays -= monthDays;    ++_month;
                    if(_month > 12)
                    {   _month =1; ++_year;   }
                }   else    {
                    _day = remainDays;    break;  }
            }
        }
        static bool IsDate1BeforeDate2(clsDate FrstDate, clsDate ScndDate)
        {
            return (FrstDate.Get_year() < ScndDate.Get_year()) ? true
            : ((FrstDate.Get_year() == ScndDate.Get_year()) ? (FrstDate.Get_month() < ScndDate.Get_month() ? true
            : (FrstDate.Get_month() == ScndDate.Get_month() ? FrstDate.Get_day() < ScndDate.Get_day() : false)): false);
        }
        bool IsDate1BeforeDate2(clsDate ScndDate)
        {
            return IsDate1BeforeDate2(*this, ScndDate);
        }

        static bool IsDate1EqualDate2(clsDate FrstDate, clsDate ScndDate)
        {
            return (FrstDate.Get_year() == ScndDate.Get_year()) ? ((FrstDate.Get_month() == ScndDate.Get_month())
                    ? ((FrstDate.Get_day() == ScndDate.Get_day()) ? true : false ): false ) : false ;
        }
        bool IsDate1EqualDate2(clsDate ScndDate)
        {
            return IsDate1EqualDate2(*this, ScndDate);
        }

        static bool IsLastDayAMonth(clsDate Dates)
        {
            return (Dates.Get_day() == CountDaysInAMonth(Dates.Get_year(),Dates.Get_month()));
        }
        bool IsLastDayAMonth()
        {
            return IsLastDayAMonth(*this);
        }

        static bool IsFrstDayAMonth(clsDate Dates)
        {
            return (Dates.Get_day() == 1);
        }
        bool IsFrstDayAMonth()
        {
            return IsFrstDayAMonth(*this);
        }

        static bool IsLastMonthAYear(short Month)
        {
            return (Month == 12);
        }

        static bool IsFrstMonthAYear(short Month)
        {
            return (Month == 1);
        }

        static clsDate AddOneDay(clsDate & Dates)
        {
            short day = Dates.Get_day() , year= Dates.Get_year(), month = Dates.Get_month();
            if(IsLastDayAMonth(Dates))
            {
                if(IsLastMonthAYear(Dates.Get_month()))
                {
                    Dates.Set_month(1); Dates.Set_day(1); ++year; Dates.Set_year(year);
                }else
                {
                    Dates.Set_day(1); ++month; Dates.Set_month(month);
                }
            }else
            {
                ++day; Dates.Set_day(day);
            }
            return Dates;
        }
        void AddOneDay()
        {
            *this = AddOneDay(*this);
        }

        static clsDate AddMultiDay(clsDate &Dates,short Days)
        {
            for(short i = 1; i <= Days; ++i)
            {
                Dates = AddOneDay(Dates);
            }
            return Dates;
        }
        void AddMultiDay(short days)
        {
            *this = AddMultiDay(*this, days);
        }

        static void SwapDates(clsDate& frstDate, clsDate& scndDate)
        {
            clsDate tempDate;       tempDate = frstDate;
            frstDate = scndDate;    scndDate = tempDate;
        }

        static int DifferenceBetweenTowDates(clsDate FrstDate, clsDate ScndDate, bool includeLastDate = false)
        {
            short days = 0, swapflag = 1;
            /// handle negative dates
            if(!IsDate1BeforeDate2(FrstDate,ScndDate))
            {
                SwapDates(FrstDate,ScndDate);   swapflag = -1;
            }
            while (IsDate1BeforeDate2(FrstDate,ScndDate))
            {
                FrstDate = AddOneDay(FrstDate);  ++days;
            }
            return includeLastDate ? ++days * swapflag : days * swapflag;
        }
        int DifferenceBetweenTowDates(clsDate date, bool includeLastDays = false)
        {
            return DifferenceBetweenTowDates(*this, date, includeLastDays);
        }

        static int CalculateAgesInDays(clsDate BirthDate)
        {
            return DifferenceBetweenTowDates(BirthDate, clsDate::GetSystemDate(), true);
        }

        static clsDate AddOneWeek(clsDate& Dates)
        {
            for(short i = 1; i <=7; ++i )
            {
                Dates = AddOneDay(Dates);
            }
            return Dates;
        }
        void AddOneWeek()
        {
            AddOneWeek(*this);
        }

        static clsDate AddMultiWeek(clsDate& Dates, short weeks)
        {
            for(short i = 1; i <= weeks; ++i )
            {
                Dates = AddOneWeek(Dates);
            }
            return Dates;
        }
        void AddMultiWeek(short weeks)
        {
            AddMultiWeek(*this, weeks);
        }

        static clsDate AddOneMonth(clsDate& Dates)
        {
            short year = Dates.Get_year(), month = Dates.Get_month();
            if(Dates.Get_month() ==12)
                {   Dates.Set_month(1); ++year;  }
            else
                {   ++month;  }
            Dates.Set_year(year); Dates.Set_month(month);
            short daysOfthisMonth = CountDaysInAMonth(Dates.Get_year(),Dates.Get_month());
            if(Dates.Get_day() > daysOfthisMonth)
                Dates.Set_day(daysOfthisMonth);
            return Dates;
        }
        void AddOneMonth()
        {
            AddOneMonth(*this);
        }

        static clsDate AddMultiMonths(clsDate& Dates, short months)
        {
            for(short i = 1; i <= months; ++i )
            {
                Dates = AddOneMonth(Dates);
            }
            return Dates;
        }
        void AddMultiMonths(short months)
        {
            AddMultiMonths(*this, months);
        }

        static clsDate AddOneYear(clsDate &Date)
        {
            short year = Date.Get_year(); ++year;
            Date.Set_year(year);
            return Date;
        }
        void AddOneYear()
        {
            AddOneYear(*this);
        }

        static clsDate AddMultiYear(clsDate & Date, short years)
        {
            short year = Date.Get_year(); year += years;
            Date.Set_year(year);
            return Date;

        }
        void AddMultiYear(short years)
        {
            AddMultiYear(*this,years);
        }

        static clsDate AddOneDecade(clsDate &Date)
        {
            short year = Date.Get_year(); year += 10;
            Date.Set_year(year);
            return Date;
        }
        void AddOneDecade()
        {
            AddOneDecade(*this);
        }

        static clsDate AddMultiDecade(clsDate & Date, short decades)
        {
            short year = Date.Get_year(); year += decades * 10;
            Date.Set_year(year);
            return Date;

        }
        void AddMultiDecade(short decades)
        {
            AddMultiDecade(*this,decades);
        }

        static clsDate AddOneCountry(clsDate &Date)
        {
            short year = Date.Get_year(); year += 100;
            Date.Set_year(year);
            return Date;
        }
        void AddOneCountry()
        {
            AddOneCountry(*this);
        }

        static clsDate AddOneMillennium(clsDate &Date)
        {
            short year = Date.Get_year(); year += 1000;
            Date.Set_year(year);
            return Date;
        }
        void AddOneMillennium()
        {
            AddOneMillennium(*this);
        }
///----------------------------------------------------------------------------------------------
        static clsDate LimitOneDay(clsDate& Dates)
        {
            short day = Dates.Get_day() , year= Dates.Get_year(), month = Dates.Get_month();
            /// Validation for last days
            if(IsValidDate(Dates))    {
            if(IsFrstDayAMonth(Dates))  {
            if(IsFrstMonthAYear(Dates.Get_month())) {
                --year;   Dates.Set_month(12);    Dates.Set_day(1);  }
                else{  --month;  Dates.Set_day(CountDaysInAMonth(Dates.Get_year(),Dates.Get_month()));  }
                }   else { --day;
                }
                Dates.Set_day(day); Dates.Set_month(month); Dates.Set_year(year);
                return Dates;
                }   else    {   cout << "\n\nDay out of limit .. Try Again" << endl;
                Dates.Set_day(day); Dates.Set_month(month); Dates.Set_year(year);
                return Dates;   }
        }
        void LimitOneDay()
        {
            *this = LimitOneDay(*this);
        }

        static clsDate LimitMultiDay(clsDate& Dates,short Days)
        {
            for(short i = Days; i >= 1; --i)
            {
                Dates = LimitOneDay(Dates);
            }
            return Dates;
        }
        void LimitMultiDay(short days)
        {
            *this = LimitMultiDay(*this, days);
        }

        static clsDate LimitOneWeek(clsDate& Dates)
        {
            for(short i = 7; i >=1; --i )
            {
                Dates = LimitOneDay(Dates);
            }
            return Dates;
        }
        void LimitOneWeek()
        {
            LimitOneWeek(*this);
        }

        static clsDate LimitMultiWeek(clsDate& Dates, short weeks)
        {
            for(short i = weeks; i >= 1; --i )
            {
                Dates = LimitOneWeek(Dates);
            }
            return Dates;
        }
        void LimitMultiWeek(short weeks)
        {
            LimitMultiWeek(*this, weeks);
        }

        static clsDate LimitOneMonth(clsDate& Dates)
        {
            short year = Dates.Get_year(), month = Dates.Get_month();
            if(Dates.Get_day() == 1)
                {   Dates.Set_day(CountDaysInAMonth(Dates.Get_year(),Dates.Get_month()));   }
            if(Dates.Get_month() == 1)
                {   Dates.Set_month(12);
                    --year;    Dates.Set_year(year);
                }
            else
                {   --month; Dates.Set_month(month);  }
            return Dates;
        }
        void LimitOneMonth()
        {
            LimitOneMonth(*this);
        }

        static clsDate LimitMultiMonths(clsDate& Dates, short months)
        {
            for(short i = months; i >= 1; --i )
            {
                Dates = LimitOneMonth(Dates);
            }
            return Dates;
        }
        void LimitMultiMonths(short months)
        {
            LimitMultiMonths(*this, months);
        }

        static clsDate LimitOneYear(clsDate &Date)
        {
            short year = Date.Get_year(); --year;
            Date.Set_year(year);
            return Date;
        }
        void LimitOneYear()
        {
            LimitOneYear(*this);
        }

        static clsDate LimitMultiYear(clsDate & Date, short years)
        {
            short year = Date.Get_year(); year -= years;
            Date.Set_year(year);
            return Date;
        }
        void LimitMultiYear(short years)
        {
            LimitMultiYear(*this,years);
        }

        static clsDate LimitOneDecade(clsDate &Date)
        {
            short year = Date.Get_year(); year -= 10;
            Date.Set_year(year);
            return Date;
        }
        void LimitOneDecade()
        {
            LimitOneDecade(*this);
        }

        static clsDate LimitMultiDecade(clsDate & Date, short decades)
        {
            short year = Date.Get_year(); year -= decades * 10;
            Date.Set_year(year);
            return Date;
        }
        void LimitMultiDecade(short decades)
        {
            LimitMultiDecade(*this,decades);
        }

        static clsDate LimitOneCountry(clsDate &Date)
        {
            short year = Date.Get_year(); year -= 100;
            Date.Set_year(year);
            return Date;
        }
        void LimitOneCountry()
        {
            LimitOneCountry(*this);
        }

        static clsDate LimitOneMillennium(clsDate &Date)
        {
            short year = Date.Get_year(); year -= 1000;
            Date.Set_year(year);
            return Date;
        }
        void LimitOneMillennium()
        {
            LimitOneMillennium(*this);
        }
///-------------------------------------------------------------------------------------------------

        static bool IsEndOfWeek(clsDate date)
        {
            return DayOfWeekOrder(date.Get_year(), date.Get_month(), date.Get_day()) == 6;
        }
        bool IsEndOfWeek()
        {
            return IsEndOfWeek(*this);
        }

        static bool IsWeekend(clsDate date)
        {
            short dayIndex = 0;
            dayIndex = DayOfWeekOrder(date.Get_year(), date.Get_month(), date.Get_day());
            return (dayIndex == 6 || dayIndex == 5);
        }
        bool IsWeekend()
        {
            return IsWeekend(*this);
        }

        static bool IsBusinessDay(clsDate date)
        {
            return !IsWeekend(date);
        }
        bool IsBusinessDay()
        {
            return IsBusinessDay(*this);
        }

        static short DaysUntillEndOfWeek(clsDate date)
        {
            return 6 - DayOfWeekOrder(date.Get_year(), date.Get_month(), date.Get_day());
        }
        short DaysUntillEndOfWeek()
        {
            return DaysUntillEndOfWeek(*this);
        }

        static short DaysUntillEndOfMonth(clsDate date)
        {
            clsDate endOfMonth;
            endOfMonth.Set_day(CountDaysInAMonth(date.Get_year(),date.Get_month()));
            endOfMonth.Set_month(date.Get_month());
            endOfMonth.Set_year(date.Get_year());
            return DifferenceBetweenTowDates(date,endOfMonth,true);
        }
        short DaysUntillEndOfMonth()
        {
            return DaysUntillEndOfMonth(*this);
        }

        static short DaysUntillEndOfYear(clsDate date)
        {
            clsDate endOfMonth;
            endOfMonth.Set_day(31);
            endOfMonth.Set_month(12);
            endOfMonth.Set_year(date.Get_year());
            return DifferenceBetweenTowDates(date,endOfMonth,true);
        }
        short DaysUntillEndOfYear()
        {
            return DaysUntillEndOfYear(*this);
        }

        static short CalculateBusinessDays(clsDate frstDate, clsDate scndDate)
        {
            short dayCounter = 0;
            while(IsDate1BeforeDate2(frstDate,scndDate))
            {
                if(IsBusinessDay(frstDate))   ++dayCounter;
                frstDate = AddOneDay(frstDate);
            }
            return dayCounter;
        }
        short CalculateBusinessDays(clsDate scndDate)
        {
            return CalculateBusinessDays(*this, scndDate);
        }
        static short CalculateActualDays(clsDate frstDate, clsDate scndDate)
        {
            return CalculateBusinessDays(frstDate, scndDate);
        }

        static clsDate CalculateReturnDate(clsDate frstDate, short Days)
        {
            short weekendCounter = 0;
            for(short i = 1; i <= Days; ++i)
            {
                if(IsWeekend(frstDate)) ++weekendCounter;
                frstDate = AddOneDay(frstDate);
            }
            for(short j = 1; j <= weekendCounter; ++j)
            {
                frstDate = AddOneDay(frstDate);
            }
            return frstDate;
        }
        clsDate CalculateReturnDate(short Days)
        {
            return CalculateReturnDate(*this, Days);
        }

        static bool IsDate1AfterDate2(clsDate frstDate, clsDate scndDate)
        {
            return (!IsDate1BeforeDate2(frstDate, scndDate) && !IsDate1EqualDate2(frstDate, scndDate));
        }
        bool IsDate1AfterDate2(clsDate date2)
        {
            return IsDate1AfterDate2(*this, date2);
        }

        enum enCompareDates{ Befor=-1, Equal = 0, After = 1};
        static enCompareDates CompareTowDates(clsDate frstDate, clsDate scndDate)
        {
            if(IsDate1BeforeDate2(frstDate,scndDate) && !IsDate1EqualDate2(frstDate,scndDate))
            {   return enCompareDates::Befor;   }
            if(IsDate1AfterDate2(frstDate,scndDate) && !IsDate1EqualDate2(frstDate,scndDate))
            {   return enCompareDates::After;   }
                return enCompareDates::Equal;
        }
        enCompareDates CompareTowDates(clsDate scndDate)
        {
            return CompareTowDates(*this, scndDate);
        }
};

