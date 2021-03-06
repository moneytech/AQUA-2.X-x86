
#include "../common/sprintf.h"
#include "../drivers/cmos.h"

const char month_names[12][16] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
	
};

char clock_digital[6];
char clock_date_words[32];

static void update_time(void);

void time_wait_ms(int ms) {
	update_time();
	
	unsigned char old = cmos_second;
	unsigned char seconds = ms / 1000;
	
	while (seconds--) {
		while (old == cmos_second) {
			glib_update();
			update_time();
			
		}
		
	}
	
}

unsigned int time_schedule(int cps, void* func) {
	return 0; /// TODO
	
}

void time_remove(unsigned int id) {
	/// TODO
	
}

static void update_time(void) {
	cmos_read_rtc();
	
}

unsigned char time_seconds(void) {
	update_time();
	return cmos_second;
	
}

unsigned char time_minutes(void) {
	update_time();
	return cmos_minute;
	
}

unsigned char time_hours(void) {
	update_time();
	return cmos_hour;
	
}

unsigned char time_day(void) {
	update_time();
	return cmos_day;
	
}

unsigned char time_month(void) {
	return cmos_month < 1 ? 0 : cmos_month - 1;
	
}

char* time_month_name(void) {
	update_time();
	return (char*) month_names[time_month()];
	
}

unsigned char time_year(void) {
	update_time();
	return cmos_year;
	
}

char* time_clock_digital(void) {
	sprintf(clock_digital, time_minutes() < 10 ? "%d:0%d" : "%d:%d", time_hours(), time_minutes());
	return (char*) clock_digital;
	
}

char* time_clock_date_words(void) {
	sprintf(clock_date_words, "%d of %s %d\0", time_day(), time_month_name(), time_year() + 1900);
	return (char*) clock_date_words;
	
}

void time_update(void) {
	time_clock_digital();
	time_clock_date_words();
	
}

void init_time(void) {
	time_clock_digital();
	time_clock_date_words();
	
}
