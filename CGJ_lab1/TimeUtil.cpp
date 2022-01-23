#include "TimeUtil.h"

long long TimeUtil::initialization_time = 0.0f;
long long TimeUtil::time_of_last_frame = 0.0f;
long long TimeUtil::time_since_last_frame = 0.0f;
long long TimeUtil::time_since_initialization = 0.0f;
float TimeUtil::deltaTime = 0.0f;
float TimeUtil::time = 0.0f;