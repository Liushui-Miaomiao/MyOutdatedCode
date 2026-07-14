#ifndef _UTILS_H_
#define _UTILS_H_

#include "stdafx.h"

#if defined(DEBUG) && DEBUG == 1
	void debug_msg(const char *format, ...);
	#define DEBUG_MSG(_Format, ...)			\
		debug_msg(_Format, ##__VA_ARGS__);
#else
	#define DEBUG_MSG(_Format, ...)
#endif

int      is_digit        (const char             *str );
int      get_current_name(      char             *name);
int      is_exist        (const char             *path);
int      is_enc_file     (      struct FILE_info *info);
int      get_file_ext    (      struct FILE_info *info);
uint32_t get_file_size   (             FILE      *file);
int      get_org_ext     (      struct FILE_info *info);
int      is_txt_file     (const struct FILE_info *info);
int      change_ext      (      struct FILE_info *info);

#endif
