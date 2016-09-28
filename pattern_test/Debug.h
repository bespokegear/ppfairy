#pragma once

#ifdef DEBUG
#define DB(...) do { Serial.print(__VA_ARGS__); } while (0)
#define DBLN(...) do { Serial.println(__VA_ARGS__); } while (0)
#else
#define DB(...) do {} while (0)
#define DBLN(...) do {} while (0)
#endif

