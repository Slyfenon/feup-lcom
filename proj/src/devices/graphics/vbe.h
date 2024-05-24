#ifndef _LCOM_VBE_H_
#define _LCOM_VBE_H_

#include <lcom/lcf.h>

/* VBE Functions */
#define VIDEO_SERVICES 0X10
#define SET_VBE_MODE 0x4F02
#define SET_VBE_DISPLAY_START 0x4F07
#define VERTICAL_RETRACE 0x80

/* Auxiliary MACROS */
#define LINEAR_BIT BIT(14)
#define DIRECT 0x06

/* Graphic Modes */
#define DIRECT_COLOR_WITH_32BITS 0x14C

#endif
