#pragma once
#include <sstream>
#include <string>
#include <iomanip>

#define LOGGER_CACHE_SIZE 128

class Logger {
   public:
    Logger();
    void Configure();
    void WriteCachedLines();

    void LogCustomMessage(std::string s);
    void LogServoOutput(float servo_elevator, float servo_ailerones);
    void LogAngles(float pitch, float roll);
    void LogAccelRawData(float ax, float ay, float az, float gx, float gy, float gz);
    void LogAccelRawDataNoF(float ax, float ay, float az, float gx, float gy, float gz);
    void LogPID(char type, float p, float i, float d);

   private:
    char logFolder[32] = "logs";
    char fileName[32];
    char filePath[64];

    std::stringstream cache;
    int cache_size = 0;
};

extern Logger logger;