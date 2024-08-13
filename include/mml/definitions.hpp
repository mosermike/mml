/**
 * @file definitions.hpp
 * @author Mike Moser
 * @brief Some definitions used in the library
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef MML_INCLUDE_MML_DEFINITIONS_HPP
#define MML_INCLUDE_MML_DEFINITIONS_HPP

// Definitions for the Bytes
#define _1B 	       8	//dd blockSize 1B
#define _1K 	    1000	//dd blockSize 1KB
#define _1KB	    1024	//dd blockSize 1K
#define _1M       1000000	//dd blockSize 1MB
#define _1MB      1048576	//dd blockSize 1M
#define _10M     10000000	//dd blockSize 10MB
#define _10MB    10485760	//dd blockSize 10M
#define _100M   100000000	//dd blockSize 100MB
#define _100MB  104857600	//dd blockSize 100M
#define _1G    1000000000	//dd blockSize 1GB
#define _1GB   1073741824	//dd blockSize 1G
#ifdef __ENVIRONMENT64__
#define _10G 10000000000 //dd blocksize _10G
#endif

#define S_DEVICE	6	// Gerät oder Partition DT_BLK aus dirent.h
#define S_CHARDEV	2	// Maus, seriell angeschlossene Geräte, etc. DT_CHR
#define S_DIR		4	// Ordner DT_DIR
#define S_FIFO		1	// DT_FIFO
#define S_SYMLNK	10	// symbolischer Link DT_LNK
#define S_FILE		8	// normale Datei DT_REG
#define S_SOCK		12	// Socket DT_SOCK
#define S_OTHER     14  // Other type

#define _sec		0	// Seconds
#define _min		1	// Minutes
#define _hour		2	// Hours
#define _day		3	// Days
#define _month		4	// Month
#define _year		5	// Year
#define _st1		6	// Summertime
#define _weekday	7   // Week day
#define _yearday	8   // Days since New Year
#define _kw			9   // Calendar Week

#define _y_sec 60*60*24*365.15
#define _d_sec 60*60*24

#endif

