/*
 * Autor: Mike Moser
 * 
 * Library definitions.h
 * Different definitions
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
#ifdef UINT64_MAX
#define _10G 10000000000 //dd blocksize _10G
#endif

// #define S_DEVICE	10	// Gerät oder Partition
// #define S_CHARDEV	11	// Maus, seriell angeschlossene Geräte, etc.
// #define S_DIR		12	// Ordner
// #define S_FIFO		13
// #define S_SYMLNK	14	// symbolischer Link
// #define S_FILE		15	// normale Datei
// #define S_SOCK		16	// Socket
#define S_DEVICE	6	// Gerät oder Partition DT_BLK aus dirent.h
#define S_CHARDEV	2	// Maus, seriell angeschlossene Geräte, etc. DT_CHR
#define S_DIR		4	// Ordner DT_DIR
#define S_FIFO		1	// DT_FIFO
#define S_SYMLNK	10	// symbolischer Link DT_LNK
#define S_FILE		8	// normale Datei DT_REG
#define S_SOCK		12	// Socket DT_SOCK

#define _sec		0	// Sekunde
#define _min		1	// Minute
#define _hour		2	// Stunde
#define _day		3	// Tag
#define _month		4	// Monat
#define _year		5	// Jahr
#define _st1		6	// Summertime
#define _weekday	7  // Wochentag
#define _yearday	8  // Tage seit Neujahr
#define _kw			9   // Kalenderwoche

#define _y_sec 60*60*24*365 
#define _m_sec
#define _d_sec
// Logdateien
#define _check_root_log 	"/var/log/check_root.log"
#define _cifs_log 			"/var/log/cifs.log"
#define _cop_log 			"/var/log/cop.log"
#define _copy_log 			"/var/log/copy.log"
//#define _rechner_log 		"/var/log/rechner.log"
#define _statistik_log 		"/var/log/statistik.log"
#define _timer_log			"/var/log/timer.log"

// Logdateien Raspberry
#define _backup_log "/var/log/backup.log"

// IP-Adressen
#define _alma		    "192.168.20.99"
#define _printer		"192.168.20.20"

// home file
#ifndef _location
#define _location       (std::string) "to nowhere"
#endif


#endif

