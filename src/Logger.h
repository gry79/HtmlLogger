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
        void info(int msg);
        void info(long msg);
        void info(unsigned int msg);
        void info(unsigned long msg);
        void info(double msg);
        void info(float msg);
        void debug(String msg);
        void debug(int msg);
        void debug(long msg);
        void debug(unsigned int msg);
        void debug(unsigned long msg);
        void debug(double msg);
        void debug(float msg);
        void error(String msg);
        void error(int msg);
        void error(long msg);
        void error(unsigned int msg);
        void error(unsigned long msg);
        void error(double msg);
        void error(float msg);
        void addBuffer(String msg);
        void addBuffer(int msg);
        void addBuffer(long msg);
        void addBuffer(unsigned int msg);
        void addBuffer(unsigned long msg);
        void addBuffer(double msg);
        void addBuffer(float msg);
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
        void log(int msg, String type);
        void log(long msg, String type);
        void log(unsigned int msg, String type);
        void log(unsigned long msg, String type);
        void log(double msg, String type);
        void log(float msg, String type);
        String string00(int);
};

#endif
