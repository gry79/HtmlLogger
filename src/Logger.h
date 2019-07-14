#ifndef __LOGGER_H_
#define __LOGGER_H_

#include <Arduino.h>
#include <WString.h>
#include <NTPClient.h>
#include <Time.h>
#include <Timezone.h>
#include <WiFiUdp.h>

#ifndef LOGGER_HISTORY_SIZE
#define LOGGER_HISTORY_SIZE 20
#endif
#ifndef LOGGER_MAX_ENTRY_LENGTH
#define LOGGER_MAX_ENTRY_LENGTH 100
#endif

class Logger {
    public:
        Logger();
        void info(String msg);
        void debug(String msg);
        void error(String msg);
        void addBuffer(String msg);
        String getLastLogMsg();
        String getAllMsgsAsString();
        String getAllMsgsAsTextarea();
        void clearLog();
        void update();
        String getTimeNow();
        unsigned long getMsgCounter();

    private:
        // Central European Time (Frankfurt, Paris, Bern)
        TimeChangeRule _CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Central European Summer Time
        TimeChangeRule _CET = {"CET ", Last, Sun, Oct, 3, 60};       // Central European Standard Time
        Timezone *_CE;

        WiFiUDP *_ntpUDP;
        NTPClient *_timeClient;
        time_t _localTime;

        char _log[LOGGER_HISTORY_SIZE][LOGGER_MAX_ENTRY_LENGTH];
        uint8_t _currPos;
        String _buffer;
        unsigned long _logMsgCounter;

        void log(String msg, String type);
        String string00(int);
};

#endif
