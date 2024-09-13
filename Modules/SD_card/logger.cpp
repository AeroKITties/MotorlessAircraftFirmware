#include "logger.hpp"

#include <cstddef>

#include "stm32f4xx_hal.h"
#include "swo_debug.hpp"

extern "C" {
#include "ff.h"
#include "sd_file_handling.h"
}

Logger::Logger() {}

void Logger::Configure() {
    Mount_SD("/");

    uint16_t file_count = 0;
    Count_Files(logFolder, &file_count);
    file_count++;

    sprintf(fileName, "log_%d.textlog", file_count);
    sprintf(filePath, "%s/%s", logFolder, fileName);

    Create_Dir(logFolder);
    Remove_File(filePath);
    Create_File(filePath);

    Unmount_SD("/");
}

void Logger::WriteCachedLines() {
    if (cache_size < LOGGER_CACHE_SIZE) return;

    long t0 = HAL_GetTick();

    std::string str_cache = cache.str();
    char* char_cache = const_cast<char*>(str_cache.c_str());
    Mount_SD("/");
    FRESULT write_result = Update_File(filePath, char_cache);
    Unmount_SD("/");

    long t1 = HAL_GetTick();

    if (write_result == FR_OK)
        swoTerminal7 << 0 << " " << HAL_GetTick() << " " << t1 - t0 << std::endl;
    else
        swoTerminal7 << 1 << " " << HAL_GetTick() << " " << t1 - t0 << std::endl;

    cache.str("");
    cache_size = 0;
}

Logger logger = Logger();