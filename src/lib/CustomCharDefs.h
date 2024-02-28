#ifndef __CUSTOM_CHAR_DEFS_H__
#define __CUSTOM_CHAR_DEFS_H__

#include <stdint.h>

typedef const uint8_t cc_line_t;
typedef cc_line_t cchar_t[8];
#define CCHAR_T extern cchar_t

CCHAR_T CC_HEART;
CCHAR_T CC_BELL;
CCHAR_T CC_ALIEN;
CCHAR_T CC_CHECK;
CCHAR_T CC_SPEAKER;
CCHAR_T CC_SOUND;
CCHAR_T CC_SKULL;
CCHAR_T CC_LOCK;
CCHAR_T CC_THERMOMETER;
CCHAR_T CC_CELSIUS_SYMBOL;
CCHAR_T CC_FAN1;
CCHAR_T CC_FAN2;

#endif /*__CUSTOM_CHAR_DEFS_H__*/