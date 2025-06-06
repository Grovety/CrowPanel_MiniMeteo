#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#define TENDENCY_UPDATE_PERIOD_MS (5 * 60 * 1000)           // 5 min
#define HISTORY_UPDATE_PERIOD_MS  (15 * 60 * 1000)          // 15 min
#define HISTORY_LENGTH_MS         (60 * 60 * 1000 * 24 * 2) // 2 days
#define HISTORY_SIZE                                                           \
    (HISTORY_LENGTH_MS / HISTORY_UPDATE_PERIOD_MS) // 192: every 15 mins

#define DEVICE_ADV_UPDATE_PERIOD_MS  3000
#define DEVICE_CHAR_UPDATE_PERIOD_MS (5 * 60 * 1000) // 5 min
#define DEVICE_CONNECT_TIMEOUT_MS    2000
#define DEVICE_NUM                   7
#define DEVICE_HISTORY_QUERY_SIZE    HISTORY_SIZE

#endif
