#ifndef __DEF_H
#define __DEF_H

typedef enum
{
    OK                             = 0,
    ERR                            = -1,
    ERR_EMPTY                      = -2,
    ERR_FULL                       = -3,
    ERR_TIMEOUT                    = -4,
    ERR_BUSY                       = -5,
    ERR_NO_MEMORY                  = -6,
    ERR_IO                         = -7,
    ERR_INVALID                    = -8,
    ERR_MEM_OVERLAY                = -9,
    ERR_MALLOC                     = -10,
    ERR_NOT_ENOUGH                 = -11,
    ERR_NO_SYSTEM                  = -12,
    ERR_BUS                        = -13,
} err_t;

typedef unsigned char bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define true   1
#define false  0



#endif

