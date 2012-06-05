#include "../include/time.h"
#include "../include/kasm.h"

#define CMOS_ADDRESS 0x70
#define CMOS_DATA    0x71

char
read_cmos_register(unsigned int number)
{
    _outb(number, CMOS_ADDRESS);
    return _inb(CMOS_DATA);
}

int
get_update_in_progress_flag(void)
{
    _outb(0x0A, CMOS_ADDRESS);
    return _inb(CMOS_DATA) & 0x80;
}

time_t
time(time_t *time)
{
    /* TODO: check update flag, fix overflow * */
    unsigned char sec  = read_cmos_register(0x00);
    unsigned char min  = read_cmos_register(0x02);
    unsigned char hour = read_cmos_register(0x04);
    unsigned char day  = read_cmos_register(0x04);
    unsigned char mon  = read_cmos_register(0x04);
    unsigned char year = read_cmos_register(0x04);
    /* the century register may not be available*/
    unsigned char century = read_cmos_register(0x04);
    
    year = year + (century - 1) * 100;

    /* copied from linux kernel/time.c:mktime */
    return ((((time_t)
              (year/4 - year/100 + year/400 + 367*mon/12 + day) +
              year*365 - 719499
        )*24 + hour /* now have hours */
      )*60 + min /* now have minutes */
    )*60 + sec; /* finally seconds */
}


