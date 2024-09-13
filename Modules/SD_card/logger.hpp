#pragma once
#include <sstream>
#include <string>

#define LOGGER_CACHE_SIZE 128

class Logger {
   public:
    Logger();
    void Configure();
    void WriteCachedLines();

    void LogCustomMessage(std::string s);
    void LogAccelRawData(float ax, float ay, float az, float gx, float gy, float gz);

   private:
    char logFolder[32] = "logs";
    char fileName[32];
    char filePath[64];

    std::stringstream cache;
    int cache_size = 0;
};

extern Logger logger;