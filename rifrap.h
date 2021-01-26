#ifndef _RIFRAP_H_
#define _RIFRAP_H_

int rif2rap(const uint8_t* idps_key, const char* exdata_path, const char* rif_file, const char* rap_path);

int rap2rif(const uint8_t* idps_key, const char* exdata_path, const char* rap_file, const char *rif_path);

#endif
