#line 1 "C:\\Users\\jlnbo\\repos\\pet_feeder\\menu6\\back_up\\custom_char_defs.hpp"

/**
 * Use https://maxpromer.github.io/LCD-Character-Creator/
 * to create custom chars
 * 
 * To add new definition
 * Add '\' character at the of the last line
 * Add CC_LINE_PARSER(<NAME>, CC_DATA(<8_BYTES_ARRAY>))
 * <8_BYTES_ARRAY> is obtained from the website
 */

const uint8_t _CCHeart[8];
const uint8_t _CCBell[8];
const uint8_t _CCAlien[8];
const uint8_t _CCCheck[8];
const uint8_t _CCSpeaker[8];
const uint8_t _CCSound[8];
const uint8_t _CCSkull[8];
const uint8_t _CCLock[8];

#define CC_DATA(...) {__VA_ARGS__}

#define CC_DEFS(CC_LINE_PARSER) \
CC_LINE_PARSER(CC_TICK,  CC_DATA(0x00,0x01,0x03,0x16,0x1C,0x08,0x00,0x00))\
CC_LINE_PARSER(CC_HEART, CC_DATA(0x00,0x01,0x03,0x16,0x00,0x08,0x00,0x00))

