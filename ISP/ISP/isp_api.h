#ifndef __ISP_API_H__
#define __ISP_API_H__

#include "datatype.h"

void readbmp(UNSG8 *filenm, UNSG8 *input_buff);
void savebmp(UNSG8 *filenm, UNSG8 *output_buff);

#endif