/**
 * @file Unix.cpp
 * @author Mike Moser
 * @brief Different Unix based functions
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
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
#include <filesystem>
#include <sys/types.h>
#include <time.h>
#include <utime.h>
#include <filesystem>
#include <sys/mount.h>
#include <thread>
#include <chrono>
#include <system_error>
#include <mntent.h>
#include <cstring>

#include "mml/file.hpp"
#include "mml/Unix.hpp"
#include "mml/standards.hpp"

mml::string mml_pass;
mml::string mml_mount_name;

uid_t mml::Unix::getUserIdByName(const char *name) {
    struct passwd *pwd = getpwnam(name); /* don't free, see getpwnam() for details */
    if(pwd == NULL) {
		throw std::runtime_error(("Failed to get userId from groupname : " + (std::string) name));
	} 
    return pwd->pw_uid;
}

gid_t mml::Unix::getGroupIdByName(const char *name)
{
    struct group *grp = getgrnam(name); /* don't free, see getgrnam() for details */
    if(grp == NULL) {
        throw std::runtime_error(("Failed to get groupId from groupname : " + (std::string)  name).c_str());
    } 
    return grp->gr_gid;
	
}

uid_t mml::Unix::getFileUID (const char* file){
	struct stat sb;
	
	if (!std::filesystem::exists(file)) {
        std::error_code ec = std::make_error_code(std::errc::no_such_file_or_directory);
        throw std::filesystem::filesystem_error("File" + (std::string) file + " does not exist", ec);
	}
	return sb.st_uid;
}

bool mml::Unix::exist_onepath(mml::string path){
	if (std::filesystem::exists(path.str()))
		return true;
	return false;
}

int32_t mml::Unix::filetype(mml::string filepath){
	const std::filesystem::path& p(filepath.str());
	std::filesystem::file_status s = std::filesystem::symlink_status(p);

	if (!std::filesystem::exists(p)) {
		std::error_code ec = std::make_error_code(std::errc::no_such_file_or_directory);
        throw std::filesystem::filesystem_error("[filetype] File '" + filepath.str() + "' does not exist", ec);
	}

	if (std::filesystem::is_regular_file(s))
		return S_FILE;
	else if (std::filesystem::is_directory(s))
		return S_DIR;
	else if (std::filesystem::is_symlink(s))
		return S_SYMLNK;
	else if (std::filesystem::is_block_file(s))
		return S_DEVICE;
	else if (std::filesystem::is_character_file(s))
		return S_CHARDEV;
	else if (std::filesystem::is_fifo(s))
		return S_FIFO;
	else if (std::filesystem::is_socket(s))
		return S_SOCK;
	else if (std::filesystem::is_other(s))
		return S_OTHER;
	else
        throw std::runtime_error("[filetype] Type of " + filepath.str() + " unknown."); // unknown type
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
	
	throw std::runtime_error("[PID] No PID found to the process '" + process + "'");
	return 0;
}

bool mml::Unix::isdir(mml::string path) {
	return filetype(path.str()) == S_DIR;
}

bool mml::Unix::isfile(mml::string path) {
	return filetype(path.str()) == S_FILE;
}

bool mml::Unix::ismounted(std::string mountpoint) {
    FILE *fp;
    struct mntent mnt;
    char buf[1024];

	// Check if directory exists
	mml::Unix::exist(mountpoint);

    // Open the file containing mount information
    fp = setmntent("/proc/mounts", "r");
    if (fp == NULL) {
        throw std::runtime_error("[ismounted] setmtent did not work");
    }

    // Loop through each entry in the file
    while (getmntent_r(fp, &mnt, buf, sizeof(buf)) != NULL) {
        if (strcmp(mnt.mnt_dir, mountpoint.c_str()) == 0) {
            // Found the mount point in the list
            endmntent(fp);
            return true;
        }
    }

    // Close the file pointer
    endmntent(fp);

    return false;
}

bool mml::Unix::issymlink(mml::string path) {
	return filetype(path.str()) == S_SYMLNK;
}


bool mml::Unix::mkdir_p(std::string value) {
	mml::string make_dir = "";	// string to create the directories
	mml::string temp=value;		// Save the value to create directories step by step
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

bool mml::Unix::mountFS(std::string mountpath, mml::string mountpoint, std::string user, std::string pass1, const char* fstype)
{
	
	std::string		dir 				= mountpath;
	std::string 	mml_mount_name		= mountpoint.str(); // nfor printing the mount name
	int				mount_return		= 0;
	
	// Make sure that this function is executed as the root
	mml::check_root("mount_dir");
	
	// Get the name of the last directory
	mml_mount_name = mountpoint.substr(mountpoint.rfind('/')+1).str();
   
	// Create the mount point if it does not exist
	if(!mml::Unix::exist(mountpoint.str())) {
		if(mountpoint[mountpoint.size()-1] != '/')
			mountpoint += "/";
		mountpoint.mkdir_p();
	
	}

	std::cout << "Mount the device "<< mml_mount_name << std::endl;
	
	

	if(mml::Unix::ismounted(mountpoint.c_str())) {
		std::cout << mountpoint << " is already mounted." << std::endl;
		return false;
	}

	int count = 0;

	do {
		//mount_return = c#ifs(mountpath, mountpoint.c_str(),fstype,user.c_str() ,pass1.c_str());
		std::string data = "";
		if(user != "")
			data = data + "username=" + user + ",";
		if(mml_pass != "")
			data = data + "password=" + pass1 + ",";
		
		data += "gid=1000,uid=1000";
		
		if(((mml::string) fstype).exist("cifs"))
			data += ",vers=3.0";
		
		mount(mountpath.c_str(), mountpoint.c_str(),fstype,0,data.c_str());
		
		if (!mml::Unix::ismounted(mountpoint.str())){
		
			std::cout << "This did not work, try again!" << std::endl;
			
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			
			pass1 = shell::password("[cifs] Password for device ",mml_mount_name);
		}	
		count++;
	} while (count < 3 && !mml::Unix::ismounted(mountpoint.str()));
	
	if (!mml::Unix::ismounted(mountpoint.str())){		
		std::cout << "mount: 3 incorrect password attempts" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	count = 0;
	
	return mml::Unix::ismounted(mountpoint.str());
}

mml::Unix::permissions mml::Unix::perms(std::string path) {
	std::filesystem::perms perm_file = std::filesystem::status(path).permissions();

	mml::Unix::permissions file;
	auto read_permission = [](std::filesystem::perms perm_file, bool &read, bool &write, bool &exec,
						std::filesystem::perms perm_a, std::filesystem::perms perm_r, std::filesystem::perms perm_w, std::filesystem::perms perm_e
							) {
			read  = std::filesystem::perms::none != (perm_r & perm_file);
			write = std::filesystem::perms::none != (perm_w & perm_file);
			exec  = std::filesystem::perms::none != (perm_e & perm_file);
	};
	
	read_permission(perm_file, file.owner_read, file.owner_write, file.owner_exec, std::filesystem::perms::owner_all,std::filesystem::perms::owner_read,std::filesystem::perms::owner_write,std::filesystem::perms::owner_exec);
	read_permission(perm_file, file.group_read, file.group_write, file.group_exec, std::filesystem::perms::group_all,std::filesystem::perms::group_read,std::filesystem::perms::group_write,std::filesystem::perms::group_exec);
	read_permission(perm_file, file.others_read, file.others_write, file.others_exec, std::filesystem::perms::others_all,std::filesystem::perms::others_read,std::filesystem::perms::others_write,std::filesystem::perms::others_exec);

	return file;
}



bool mml::Unix::perm_to_write(std::string path) {
	std::cout << "TEST123" << std::endl;
	mml::Unix::User user;
	std::cout << "TESTX" << std::endl;
	if(user.get_user() == "root")
		return true;
	std::cout << "TESTX" << std::endl;
	permissions perm = perms(path);
	std::cout << "TESTX" << std::endl;
	struct stat sb;
	stat(path.c_str(), &sb);	// Zuordnung der Infos
	std::cout << "TESTX" << std::endl;
	// Permissions for the creator of the file/directory
	if(sb.st_uid == user.get_uid()) {
		if(perm.owner_write)
			return true;
	}
	std::cout << "TESTX" << std::endl;
	// Permissions for the group
	if(sb.st_gid == user.get_gid()) {
		if(perm.group_write)
			return true;
	}
	std::cout << "TESTX" << std::endl;
	// Permissions for other
	if(perm.others_write)
		return true;
	std::cout << "TESTX" << std::endl;
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


bool mml::Unix::unmount(std::string mountpoint, bool force){
	std::size_t pos	= 0;
	bool return_unmount = false;
	
	std::cout << "Unmount the device: "<< mountpoint.substr(mountpoint.rfind('/')) << std::endl;

	if(force) {
		do {
			return_unmount = umount2(mountpoint.c_str(),MNT_FORCE);
		} while(mml::Unix::ismounted(mountpoint));
	}
	else
		return_unmount = umount(mountpoint.c_str());
	
	return return_unmount;
}
