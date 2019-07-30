#include "Logger.h"

Logger::Logger() {
    _CE = new Timezone(_CEST, _CET);
    _ntpUDP = new WiFiUDP();
    _timeClient = new NTPClient(*_ntpUDP, "ch.pool.ntp.org", 0, 60000);

    _timeClient->begin();

    _buffer = "";
    _logMsgCounter = 0UL;

    clearLog();
    info(F("Logger init complete"));
}

void Logger::clearLog() {
    memset(_log, 0, sizeof(_log));
    _currPos = 0;
}

void Logger::info(String msg) {
    log(msg, " INFO  ");
}

void Logger::info(int msg) {
    log(msg, " INFO  ");
}

void Logger::info(long msg) {
    log(msg, " INFO  ");
}

void Logger::info(unsigned int msg) {
    log(msg, " INFO  ");
}

void Logger::info(unsigned long msg) {
    log(msg, " INFO  ");
}

void Logger::info(double msg) {
    log(msg, " INFO  ");
}

void Logger::info(float msg) {
    log(msg, " INFO  ");
}

void Logger::debug(String msg) {
    log(msg, " DEBUG ");
}

void Logger::debug(int msg) {
    log(msg, " DEBUG ");
}

void Logger::debug(long msg) {
    log(msg, " DEBUG ");
}

void Logger::debug(unsigned int msg) {
    log(msg, " DEBUG ");
}

void Logger::debug(unsigned long msg) {
    log(msg, " DEBUG ");
}

void Logger::debug(double msg) {
    log(msg, " DEBUG ");
}

void Logger::debug(float msg) {
    log(msg, " DEBUG ");
}

void Logger::error(String msg) {
    log(msg, " ERROR ");
}

void Logger::error(int msg) {
    log(msg, " ERROR ");
}

void Logger::error(long msg) {
    log(msg, " ERROR ");
}

void Logger::error(unsigned int msg) {
    log(msg, " ERROR ");
}

void Logger::error(unsigned long msg) {
    log(msg, " ERROR ");
}

void Logger::error(double msg) {
    log(msg, " ERROR ");
}

void Logger::error(float msg) {
    log(msg, " ERROR ");
}

void Logger::addBuffer(String msg) {
    _buffer += msg;
}

void Logger::addBuffer(int msg) {
    _buffer += String(msg);
}

void Logger::addBuffer(long msg) {
    _buffer += String(msg);
}

void Logger::addBuffer(unsigned int msg) {
    _buffer += String(msg);
}

void Logger::addBuffer(unsigned long msg) {
    _buffer += String(msg);
}

void Logger::addBuffer(double msg) {
    _buffer += String(msg);
}

void Logger::addBuffer(float msg) {
    _buffer += String(msg);
}

void Logger::log(String msg, String type) {
    _buffer += msg;
    _buffer = getTimeNow() + type + _buffer;
    size_t num = (_buffer.length() > LOGGER_MAX_ENTRY_LENGTH - 1) ? LOGGER_MAX_ENTRY_LENGTH - 1 : _buffer.length();
    strncpy(
        _log[_currPos],
        _buffer.c_str(),
        num
    );
    _log[_currPos][num] = 0;
    _currPos++;

    if (_currPos == LOGGER_HISTORY_SIZE) {
        _currPos = 0;
    }

    _buffer = "";

    _logMsgCounter++;
}

void Logger::log(int msg, String type) {
    log(String(msg), type);
}

void Logger::log(long msg, String type) {
    log(String(msg), type);
}

void Logger::log(unsigned int msg, String type) {
    log(String(msg), type);
}

void Logger::log(unsigned long msg, String type) {
    log(String(msg), type);
}

void Logger::log(double msg, String type) {
    log(String(msg), type);
}

void Logger::log(float msg, String type) {
    log(String(msg), type);
}

String Logger::getLastLogMsg() {
    return String(_log[_currPos == 0 ? (LOGGER_HISTORY_SIZE - 1) : (_currPos - 1)]);
}

String Logger::getAllMsgsAsString() {
    String buffer = "";
    uint8_t pos = _currPos;
    uint8_t startPos = _currPos;
    do {
        if (_log[pos][0] != 0) {
            buffer += String(_log[pos]);
            buffer += "\n";
        }
        pos++;
        if (pos == LOGGER_HISTORY_SIZE) {
            pos = 0;
        }
    }
    while (pos != startPos);
    buffer.trim();
    return buffer;
}

String Logger::getAllMsgsAsTextarea() {
    String buffer = "";
    buffer += F("<textarea rows=\"30\" style=\"width:100%; font-family:Consolas; font-size:16px;\" readonly>");
    buffer += getAllMsgsAsString();
    buffer += F("</textarea>");
    return buffer;
}

void Logger::update() {
    _timeClient->update();
}

String Logger::string00(int val) {
  char tmp[3];
  sprintf(tmp, "%02d", val);
  return String(tmp);
}

String Logger::getTimeNow() {
  time_t utc = _timeClient->getEpochTime();
  _localTime = _CE->toLocal(utc);
  String timeNow = string00(hour(_localTime));
  timeNow += ":";
  timeNow += string00(minute(_localTime));
  timeNow += ":";
  timeNow += string00(second(_localTime));
  return timeNow;
}

unsigned long Logger::getMsgCounter() {
    return _logMsgCounter;
}
