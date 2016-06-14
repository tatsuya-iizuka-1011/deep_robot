/*
  time.h - low level time and date functions
*/

/*
  July 3 2011 - fixed elapsedSecsThisWeek macro (thanks Vincent Valdy for this)
              - fixed  daysToTime_t macro (thanks maniacbug)
*/     

#ifndef _Time_h
#ifdef __cplusplus
#define _Time_h

#include <inttypes.h>
#ifndef __AVR__
#include <sys/types.h> // for __time_t_defined, but avr libc lacks sys/types.h
#endif


#if !defined(__time_t_defined) // avoid conflict with newlib or other posix libc
typedef unsigned long time_t;
#endif


// This ugly hack allows us to define C++ overloaded functions, when included
// from within an extern "C", as newlib's sys/stat.h does.  Actually it is
// intended to include "time.h" from the C library (on ARM, but AVR does not
// have that file at all).  On Mac and Windows, the compiler will find this
// "Time.h" instead of the C library "time.h", so we may cause other weird
// and unpredictable effects by conflicting with the C library header "time.h",
// but at least this hack lets us define C++ functions as intended.  Hopefully
// nothing too terrible will result from overriding the C library header?!
extern "C++" {
typedef enum {timeNotSet, timeNeedsSync, timeSet
}  timeStatus_t ;

typedef enum {
    dowInvalid, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, dowSaturday
} timeDayOfWeek_t;

typedef enum {
    tmSecond, tmMinute, tmHour, tmWday, tmDay,tmMonth, tmYear, tmNbrFields
} tmByteFields;	   

typedef struct  { 
  uint8_t Second; 
  uint8_t Minute; 
  uint8_t Hour; 
  uint8_t Wday;   // day of week, sunday is day 1
  uint8_t Day;
  uint8_t Month; 
  uint8_t Year;   // offset from 1970; 
} 	tmElements_t, TimeElements, *tmElementsPtr_t;

//convenience macros to convert to and from tm years 
#define  tmYearToCalendar(Y) ((Y) + 1970)  // full four digit year 
#define  CalendarYrToTm(Y)   ((Y) - 1970)
#define  tmYearToY2k(Y)      ((Y) - 30)    // offset is from 2000
#define  y2kYearToTm(Y)      ((Y) + 30)   

typedef time_t(*getExternalTime)();
//typedef void  (*setExternalTime)(const time_t); // not used in this version


/*==============================================================================*/
/* Useful Constants */
#define SECS_PER_MIN  (60UL)

/*============================================================================*/
/*  time and date functions   */
int     hour();            // the hour now 

void    hoge();

time_t now();              // return the current time as seconds since Jan 1 1970 
void    setTime(time_t t);
void    setTime(int hr,int min,int sec,int day, int month, int yr);
void    adjustTime(long adjustment);

/* date strings */ 
#define dt_MAX_STRING_LEN 9 // length of longest date string (excluding terminating null)
char* monthStr(uint8_t month);
char* dayStr(uint8_t day);
char* monthShortStr(uint8_t month);
char* dayShortStr(uint8_t day);
	
/* time sync functions	*/
timeStatus_t timeStatus(); // indicates if time has been set and recently synchronized
void    setSyncProvider( getExternalTime getTimeFunction); // identify the external time provider
void    setSyncInterval(time_t interval); // set the number of seconds between re-sync

/* low level functions to convert to and from system time                     */
void breakTime(time_t time, tmElements_t &tm);  // break time_t into elements
time_t makeTime(tmElements_t &tm);  // convert time elements into time_t

} // extern "C++"
#endif // __cplusplus
#endif /* _Time_h */

