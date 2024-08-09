/**
 * @author Mike Moser
 * 
 * @name functions.cpp
 * Enthält verschiedene Funktionen
 * 
*/

#include <iostream>
#include <string>
#include <vector>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <bits/local_lim.h>
#include <unistd.h> // getlogin_r
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sys/types.h>
#include <time.h>
#include <utime.h>
#include <filesystem>
#include <sys/mount.h>
#include <thread>
#include <chrono>

#include "mml.hpp"
#include "mml/file.hpp"
#include "mml/Unix.hpp"

mml::string mml_pass;
mml::string mml_mount_name;

uid_t mml::Unix::getUserIdByName(const char *name)
{
    struct passwd *pwd = getpwnam(name); /* don't free, see getpwnam() for details */
    if(pwd == NULL) {
		std::cout << "Failed to get userId from groupname : " <<  name;
	} 
    return pwd->pw_uid;
}

gid_t mml::Unix::getGroupIdByName(const char *name)
{
    struct group *grp = getgrnam(name); /* don't free, see getgrnam() for details */
    if(grp == NULL) {
        std::cout << "Failed to get groupId from groupname : " <<  name;
    } 
    return grp->gr_gid;
	
}

uid_t mml::Unix::getFileUID (const char* file){
	struct stat sb;
	
	if (stat(file, &sb) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}
	return sb.st_uid;
}

uint32_t mml::Unix::cifs(std::string src, std::string dst , mml::string fstype, std::string user , std::string mml_pass){
	std::string data = "";
	
	if(user != "")
		data = data + "username=" + user + ",";
	
	if(mml_pass != "")
		data = data + "password=" + mml_pass + ",";
	
	data += "gid=1000,uid=1000";
	
	if(fstype.exist("cifs"))
		data += ",vers=3.0";
	
	int16_t mount_return = mount(src.c_str(), dst.c_str(),fstype.c_str(),0,data.c_str());
	return mount_return;
	
}

bool mml::Unix::exist(std::string path){
	struct stat sb;
	
	if (stat(path.c_str(), &sb) == -1)
		return false;
	return true;
}

bool mml::Unix::exist(std::string path1, std::string path2) {
	return exist(path1) && exist(path2);
}

bool mml::Unix::exist(std::string path1, std::string path2, std::string path3) {
	return exist(path1) && exist(path2) && exist(path3);
}

int32_t mml::Unix::filetype(std::string filepath){
	struct stat sb;
	
	if (stat(filepath.c_str(), &sb) == -1) {
		//perror("stat");
		std::cout << "[fileType] No such file or directory (" << filepath << ")" << std::endl;
		exit(EXIT_FAILURE);
	}

    switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:	return S_DEVICE;		// Gerät oder Partition
		case S_IFCHR:	return S_CHARDEV;		// Maus, seriell angeschlossene Geräte, etc.
		case S_IFDIR:	return S_DIR;			// Ordner
		case S_IFIFO:	return S_FIFO;
		case S_IFLNK:	return S_SYMLNK;		// symbolischer Link
		case S_IFREG:	return S_FILE;			// normale Datei
		case S_IFSOCK:	return S_SOCK;  		// Socket
		default:		return EXIT_FAILURE;	// nicht bekannt
    }
}

char* mml::Unix::getHost () {
	char hostname[HOST_NAME_MAX];
	char* return_name = new char[HOST_NAME_MAX];
	
	gethostname(hostname, HOST_NAME_MAX);
	
	strcpy(return_name,hostname);
	
	return return_name;
}

mml::string mml::Unix::get_process_name_by_pid(const pid_t pid){
	std::ifstream	process			((std::string)"/proc/" + std::to_string(pid) + "/comm");
	std::string		process_name	= "";
	
	std::getline(process,process_name);
	
	return process_name;
}

pid_t mml::Unix::get_pid_by_process_name(const std::string process, int start) {
	
	for( pid_t i = start; i < 100000; i++) {
		if(mml::Unix::exist((std::string)"/proc/" + std::to_string(i))) {
			std::ifstream	process1			((std::string)"/proc/" + std::to_string(i) + "/comm");
			std::string		process_name	= "";
			std::getline(process1,process_name);
			
			// process found?
			if(process_name == process)
				return i;
		}
	}
	
	mml::shell::warn("[PID] No PID found to the process '" + process + "'");
	return 0;
}

bool mml::Unix::mkdir_p(std::string value) {
	mml::string make_dir = "";	// string to create the directories
	mml::string temp=value;					// Save the value to create directories step by step
	std::size_t pos;			// Position of '/'
	pos = temp.find("/",1);

	// Check if the directory exists already to save computing time
	if (mml::Unix::exist(value) && mml::Unix::filetype(value) == S_DIR)
		return 0;

	do{
		make_dir += temp.substr(0,pos);
		temp = temp.substr(pos,temp.size()-pos);

		// Check if the dir exists as a non-directory, otherwise create it
		if(mml::Unix::exist(make_dir.c_str()) && mml::Unix::filetype(make_dir.str()) != S_DIR)
			throw std::runtime_error("[mkdir_p] Cannot create directory " + make_dir.str() + " as it already exists as a non-directory!");
		else
			mkdir(make_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

		// Determine new position for the new directory if not at the end
		pos = temp.find("/",1);
	} while(pos < std::string::npos);

	// Now create the last directory
	if(!mml::Unix::exist(value))
				mkdir(value.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

	return mml::Unix::exist(value);
	
}


std::string mml::Unix::mount_Dir (std::string mountpath, mml::string mountpoint, mml::string controlpoint, std::string user, std::string pass1, const char* fstype, int count )
{
	
	std::string		dir 				= mountpath;
	std::string 	mml_mount_name		= mountpoint.str(); // nur zur Ausgabe von Mount the dev...
	int				mount_return		= 0;
	
	mml::check_root("mount_dir");
	
	for(std::size_t i = mml_mount_name.size(); i < mml_mount_name.size();i--) {
		if(mml_mount_name[i] == '/') {
			mml_mount_name = mml_mount_name.substr(i+1);
			break;
		}
	}
   
	std::cout << "Mount the device "<< mml_mount_name << std::endl;
	
	if(!mml::Unix::exist(mountpoint.str())) {
		if(mountpoint[mountpoint.size()-1] != '/')
			mountpoint += "/";
		mountpoint.mkdir_p();
	
	}

	if(mml::Unix::exist(controlpoint.str()) && !(controlpoint == "")) {
		return pass1;
	}

	mount_return = cifs(mountpath, mountpoint.c_str(),fstype,user.c_str() ,pass1.c_str());
	
	if (mount_return != 0 && count < 2 && !mml::Unix::exist(controlpoint.str())){
	
		std::cout << "This did not work, try again!" << std::endl;
		
		count++;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		
		mount_Dir(mountpath, mountpoint, controlpoint, user, pass1 = shell::password("[cifs] Password for device ",mml_mount_name), fstype, count);
	}
	
	if (mount_return != 0 && count == 2 && !mml::Unix::exist(controlpoint.str())){
	
		count ++;
		
		std::cout << "mount: 3 incorrect password attempts" << std::endl;
		exit(EXIT_FAILURE);
	}

	count = 0;
	
	return pass1;
}

mml::string mml::Unix::perms(std::string path) {
	struct stat sb;
	stat(path.c_str(), &sb);	// Zuordnung der Infos
	int number = sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
	
	// convert decimal to octal
	int temp; 
	int base = 8;
    int octal = 0;
	int i = 1;
	
    while(number != 0) {
        temp = number % base;
        number = number / base;
        octal = octal + (temp*i);
        i = i*10;
    }
	
	return mml::to_string(octal);
}

bool mml::Unix::perm_to_write(std::string path) {
	mml::Unix::User user;
	
	if(user.get_user() == "root")
		return true;
	
	mml::string perm = perms(path);

	struct stat sb;
	stat(path.c_str(), &sb);	// Zuordnung der Infos
	
	// Permissions for the creator of the file/directory
	if(sb.st_uid == user.get_uid()) {
		if(perm[0] == '2' || perm[0] == '3' || perm[0] == '6' || perm[0] == '7')
			return true;
	}

	// Permissions for the group
	if(sb.st_gid == user.get_gid()) {
		if(perm[1] == '2' || perm[1] == '3' || perm[1] == '6' || perm[1] == '7')
			return true;
	}
	
	// Permissions for other
	if(perm[2] == '2' || perm[2] == '3' || perm[2] == '6' || perm[2] == '7')
		return true;
	
	
	return false;
	
}

void mml::Unix::remove(std::string file) {
	std::filesystem::remove_all(file);
}

bool mml::Unix::set_date(std::string src_file, std::string dst_file, bool verbose) {
	
	struct stat			src;
	struct stat			dst;
	time_t				mtime;
	time_t				atime;
	time_t				mtime_new;
	struct	utimbuf		new_times;

	stat(src_file.c_str(), &src);
	mtime = src.st_mtime; // Sekunde seit 1970 // mtime nicht ctime!
	atime = src.st_atime; // Sekdunde seit 1970

	// Check if the times are already the same
	stat(dst_file.c_str(), &dst);
	if (mtime == dst.st_mtime && atime == dst.st_atime) {
		return true;
	}
	
	// Zeiten in struct schreiben:
	new_times.actime = atime;		// Zeit von letzter Zugriff
	new_times.modtime = mtime;		// Zeit von letzter Statusänderung
	
	// Zeiten schreiben in neue Datei:
	utime(dst_file.c_str(), &new_times);
	stat(dst_file.c_str(), &dst);
	mtime_new = dst.st_mtime;

	if(verbose)
		std::cout << "Change time of " << dst_file << " to time of " << src_file << std::endl;
	
	return mtime_new == mtime ? true : false;
}


bool mml::Unix::unmount_dir(std::string mount_dir, std::string controlpoint){
	std::string dir = mount_dir;
	std::size_t 	pos	= 0;
	bool				return_unmount = false;
	
	do{
		pos = dir.find("/");
		dir = dir.substr(pos+1);
	} while(pos < std::string::npos);
	
	std::cout << "Unmount the device: "<< dir << std::endl;

	do {
		return_unmount = umount2(mount_dir.c_str(),MNT_FORCE);
		if(controlpoint == "")
			break;
	} while(mml::Unix::exist(controlpoint));
	
	return return_unmount;
}
