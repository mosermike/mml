/**
 * @file User.cpp
 * @author Mike Moser
 * @brief Function definitions for the class User
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <string>
#include <string.h>
#include <fstream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <locale>	// for getting language of the user

#include "mml/Unix.hpp"
#include "mml/file.hpp"

bool mml::Unix::User::operator==(const std::string testuser){
 	if( this->username.str() == testuser)
		return true;
	return false;
}

bool mml::Unix::User::operator==(uid_t testuid){
	if( this->uid == testuid)
		return true;
	return false;
}

bool mml::Unix::User::operator!=(const std::string testuser){
	if((this->username).str() != testuser)
		return true;
	return false;
	
}
bool mml::Unix::User::operator!=(uid_t testuid){
	if( this->uid != testuid)
		return true;
	return false;
}



std::string mml::Unix::User::geteuser() {
	return std::string(pw->pw_name);
}
std::string mml::Unix::User::gethomedir() {
	return std::string(pw->pw_dir);
}

std::string mml::Unix::User::getdefaultshell() {
	return std::string(pw->pw_shell);
}

std::string mml::Unix::User::getdomain() {
	
	#if __unix__ || __linux__ // search on linux otherwise return unknown
	mml::string temp = "";
	std::ifstream input("/etc/resolv.conf"); // File where typically the information is found
	while (!input.eof()){
		std::string temp_str;
		std::getline(input,temp_str);
		if(((mml::string)temp_str).exist("domain")) {
			temp = temp.replace("domain ", "");
			break;
		}
	}
	if(temp == "") {
		 temp = "Unknown";
	}
	
	input.close();
	return temp.str();

	#else
	return "Unknown Operating System"
	#endif
}

uid_t mml::Unix::User::getloginuid() {
	const passwd *pw1 = getpwnam(getlogin());
	
	if(pw1 == NULL)
		throw std::runtime_error("ERROR: user function getloginuid @ User.cpp line 101");
	
	return pw1->pw_uid;
}

gid_t mml::Unix::User::getlogingid() {
	const passwd *pw1 = getpwnam(getlogin());
	
	if(pw1 == NULL)
		throw std::runtime_error("ERROR: user function getlogingid @ User.cpp line 110");
	
	return pw1->pw_gid;    
}

std::string mml::Unix::User::getlocale() {
	return std::locale("").name().c_str();
}

std::string mml::Unix::User::getloginname() {
	return (this->loginname).str();
}

std::vector<gid_t> mml::Unix::User::getgrgid(){
	
	std::vector <gid_t> gids_temp (mml::file::num_lines("/etc/group"));
	gid_t* groups_gid = gids_temp.data();
		
	if(groups_gid == NULL)
		throw std::runtime_error("ERROR: user function getgrgid @ User.cpp line 118");
	
	if ((getgrouplist(geteuser().c_str(), uid, groups_gid, &ngroups)) == -1)
		getgrouplist(geteuser().c_str(), uid, groups_gid, &ngroups);
	
	return gids_temp;
}
// const std::vector<mml::string> mml::Unix::User::getgrlist()
// {
// 	
// 	struct group *gr;
// 	std::vector<mml::string>	groups;
// 			
// 	for ( int j = 0; j < ngroups; j++) {
// 		gr = ::getgrgid(this->gids[j]);
// 		if (gr != NULL)
// 			groups.push_back((std::string) gr->gr_name);
// 	}
// 	
// 	return groups;
// }

const std::vector<mml::string> mml::Unix::User::getgrlist()
{
	
	struct group *gr;
	std::vector<mml::string>	groups;
			
	for ( int j = 0; j < ngroups; j++) {
		gr = ::getgrgid(this->gids[j]);
		if (gr != NULL)
			groups.push_back((mml::string) gr->gr_name);
	}
	
	return groups;
}

std::string mml::Unix::User::gethost(){
	std::string temp;
	char hostname[HOST_NAME_MAX];
		
	gethostname(hostname, HOST_NAME_MAX);
	
	temp = hostname;
	
	return temp;	
}

mml::string mml::Unix::User::setPWD() {
	this->pwd = get_current_dir_name();
	return this->pwd;
}

void mml::Unix::User::cout(mml::string output) {

	switch(output.hash()) {
		case mml::const_string_hash("uid") :
			std::cout << "UID: \t\t\t"		<< this->uid << std::endl;
			break;
			
		case mml::const_string_hash("login_uid") :
			std::cout << "LOGIN_UID: \t\t"	<< this->login_uid << std::endl;
			break;
			
		case mml::const_string_hash("gid") :
			std::cout << "GID: \t\t\t"		<< this->gid << std::endl;
			break;
			
		case mml::const_string_hash("login_gid") :
			std::cout << "LOGIN_GID \t\t"		<< this->login_gid << std::endl;
			break;
			
		case mml::const_string_hash("username") :
			std::cout << "USERNAME: \t\t"		<< this->username<< std::endl;
			break;
			
		case mml::const_string_hash("loginname") :
			std::cout << "LOGINNAME: \t\t"	<< this->loginname << std::endl;
			break;
			
		case mml::const_string_hash("home") :
			std::cout << "HOME: \t\t\t"		<< this->home << std::endl;
			break;
			
		case mml::const_string_hash("defaultshell") :
			std::cout << "SHELL: \t\t\t"		<< this->defaultshell << std::endl;
			break;
		
		case mml::const_string_hash("host") :
			std::cout << "HOSTNAME: \t\t" 	<< this->hostname << std::endl;
			break;
			
		case mml::const_string_hash("hostname") :
			std::cout << "HOSTNAME: \t\t" 	<< this->hostname << std::endl;
			break;
			
		case mml::const_string_hash("iw") :
			std::cout << "WLAN IP-ADRESSE: \t" 	<< this->ip_w << std::endl;
			break;
		
		case mml::const_string_hash("ie") :
			std::cout << "LAN IP-ADRESSE: \t" 	<< this->ip_e << std::endl;
			break;
			
		case mml::const_string_hash("domain") :
			std::cout << "DOMAIN: \t\t" 	<< this->domain << std::endl;
			break;
		
		case mml::const_string_hash("path") :
			std::cout << "PATH: \t\t\t" 	<< this->path << std::endl;
			break;
			
		case mml::const_string_hash("pwd") :
			std::cout << "PWD: \t\t\t"		<< this->pwd << std::endl;
			break;
			
		case mml::const_string_hash("groups") :
			std::cout << "GROUPS: \t\t";
			for(uint32_t i = 0; i < this->groups.size(); i++)
				std::cout << this->gids[i] << " (" << this->groups[i] << ") ";
			std::cout << std::endl;
			break;

		default:
			std::cout << "Wrong Parameter"	<< std::endl;
			break;
		
	}
	
	
}
bool mml::Unix::User::check(mml::string option, int value) {
	return check(option,std::to_string(value));
}
bool mml::Unix::User::check(mml::string option, std::string value) {
	
	std::vector<std::string> paths;
	std::string path_str = this->path.str();
	std:: string temp = "";
	
	switch(option.hash()) {
		case mml::const_string_hash("uid") :
			return std::to_string(this->uid) == value ? true : false;
			break;
			
		case mml::const_string_hash("login_uid") :
			return std::to_string(this->login_uid) == value ? true : false;
			break;
			
		case mml::const_string_hash("gid") :
			return std::to_string(this->gid) == value ? true : false;
			break;
			
		case mml::const_string_hash("login_gid") :
			return std::to_string(this->login_gid) == value ? true : false;
			break;
			
		case mml::const_string_hash("username") :
			return this->username == value ? true : false;
			break;
			
		case mml::const_string_hash("loginname") :
			return this->loginname == value ? true : false;
			break;
			
		case mml::const_string_hash("home") :
			return this->home == value ? true : false;
			break;
			 
		case mml::const_string_hash("defaultshell") :
			return this->defaultshell == value ? true : false;
			break;
		
		case mml::const_string_hash("host") :
			return this->hostname == value ? true : false;
			break;
			
		case mml::const_string_hash("hostname") :
			return this->hostname == value ? true : false;
			break;
			
		case mml::const_string_hash("iw") :
			return this->ip_w == value ? true : false;
			break;
			
		case mml::const_string_hash("ie") :
			return this->ip_e == value ? true : false;
			break;
			
		case mml::const_string_hash("domain") :
			return this->domain == value ? true : false;
			break;
		
		case mml::const_string_hash("pwd") :
			return this->pwd == value ? true : false;
			break;
			
		case mml::const_string_hash("path") :

			
			for(uint32_t i = 0; i < path_str.size(); i++) {
				if(path_str[i] == ':') {
					paths.push_back(path_str.substr(0,i));
					path_str = path_str.substr(i+1);
					i = 0;
				}
				
			}
			for(uint32_t i = 0; i < paths.size(); i++) {
				if(paths[i] == value)
					return true;
			}
			return false;
			
			break;
		
		case mml::const_string_hash("groups") :
			
			for(uint32_t i = 0; i < this->groups.size(); i++) {
				if(this->groups[i] == value)
					return true;
			}
			return false;
			break;

		default:
			std::cout << "Wrong Parameter"	<< std::endl;
			break;
		
	}
	return false;
}
