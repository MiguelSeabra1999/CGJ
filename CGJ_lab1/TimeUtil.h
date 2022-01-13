#pragma once
/**/
#include <chrono>
#include <ctime>
#include <sys/timeb.h>
#include <time.h>
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


class TimeUtil {
private:
    long long initialization_time;
    long long time_of_last_frame;
    long long time_since_last_frame;
    long long time_since_initialization;
public:

    void updateCycle() {
        //cout << "here" << endl;
        long long millisec_since_epoch = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
            ).count();
        time_of_last_frame = time_since_initialization;
        time_since_initialization = millisec_since_epoch - initialization_time;
        time_since_last_frame = time_since_initialization - time_of_last_frame;
    }

    void init() {
        cout << duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
            ).count() << endl;
        initialization_time = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
            ).count();

    }

    float GetTimeSinceLastFrame() {
        return time_since_last_frame;
    }

    float GetTimeOfLastFrame() {
        return time_of_last_frame;
    }

    float GetTimeSinceInit() {
        return time_since_initialization;
    }

    float GetInitTime() {
        return initialization_time;
    }

};
/**/