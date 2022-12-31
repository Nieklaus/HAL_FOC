#ifndef __CurrentSense_H__
#define __CurrentSense_H__

#include "main.h"
#include "FOC_Define.h"
#include "InlineCurrentSense.h"
#include "arm_math.h"

DQCurrent_s getFOCCurrents(float angle_el);

#endif

