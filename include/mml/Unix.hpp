/**
 * : @author Mike Moser
 * : 
 * : @name Unix.hpp
 * :
 * : @brief Contains different functions and the class Unix for unix-specific things
 * : 
*/

#ifndef MML_INCLUDE_MML_UNIX_HPP
#define MML_INCLUDE_MML_UNIX_HPP

#ifdef __linux__

#include <iostream>
#include <stdlib.h>     /* getenv */
#include <string>
#include <bits/local_lim.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string>
#include <sys/stat.h>

#include "mml/shell.hpp"
#include "mml/string.hpp"
#include "mml/vector.hpp"
#include "mml/standards.hpp"

namespace mml{
	//namespace shell{
	//	class arg;
	//}
	//namespace functions{
	//	typedef mml::shell::arg vector;	
	//}
	namespace Unix{
		
		
		class User{
		private:
			
				  int					ngroups			= 1;
			const uid_t					uid				= geteuid ();
			const uid_t					login_uid		= getloginuid();
			const gid_t					gid				= getegid();
			const gid_t					login_gid		= getlogingid();
			const passwd				*pw				= getpwuid (uid);
				  std::vector<gid_t>	gids			= getgrgid();
				  mml::string			username		= geteuser();
				  mml::string			locale			= getlocale();
				  mml::string			loginname		= getlogin(); 
				  mml::string			home			= gethomedir();
				  mml::string			defaultshell	= getdefaultshell();
				  mml::string			hostname		= gethost();
				  mml::string			domain			= getdomain();
				  mml::string			path			= std::getenv("PATH");
				  mml::string			pwd				= get_current_dir_name();
				  std::vector<mml::string> groups			= getgrlist();
				  
			
			/**
			 * @brief Returns different values for initialisation			 * 
			 * @return searched value
			 */
			std::string geteuser();						// Returns the effective user who executes this process
			std::string getlocale();					// Returns the language of the user
			std::string getloginname();					// Returns the login name
			std::string gethomedir();					// Returns the home path
			std::string getdefaultshell();				// Returns the default shell
			std::string getdomain();					// Returns the current domain name
			std::string gethost();						// Returns the host name
			uid_t getloginuid();						// Returns the UID of the logged in user
			gid_t getlogingid();						// Returns the GID of the logged in user
			std::vector<gid_t> getgrgid();				// Returns the different groups (only of the current user?)
			const std::vector<mml::string> getgrlist();	// Returns the different groups of the current user
			

		public:
			User() {};
			
			User(const User &User_copy) {pw = User_copy.pw;}
			
			
			User &operator=(const User &User_temp){
				pw = User_temp.pw;
				return *this;
			}
			
			/**
			 * @brief User name equal to a user
			 * @param testuser User Name
			 * @return true if users are the same
			 */
			bool operator==(std::string testuser);
			/**
			 * @brief User not name equal to a user
			 * @param testuser User Name
			 * @return true if users are different
			 */
			bool operator!=(const std::string testuser);
			
			/**
			 * @brief Compare the UID (equal)
			 * @param testuid UID to be tested
			 * @return true if UID are the same
			 */
			bool operator==(uid_t testuid);
			
			/**
			 * @brief Compare the UID (unequal)
			 * @param testuid UID to be tested
			 * @return true if UID are different
			 */
			bool operator!=(uid_t testuid);
			
			/**
			 * @brief Refresh actual path
			 * @return Actual path
			 */
			mml::string setPWD();
			
			/**
			 * @brief Retur User Data
			 * @return return the wished user information
			 */
			uid_t						get_euid()		{ return this->uid;}			// Executing UID
			uid_t						get_uid()		{ return this->login_uid;}		// Login UID
			gid_t 						get_egid()		{ return this->gid;}			// Executing GID
			gid_t 						get_gid()		{ return this->login_gid;}		// Login GID
			mml::string					get_user()		{ return this->username;}		// Executing User
			mml::string					get_locale()	{ return this->locale;}			// Language of the user
			mml::string					get_login()		{ return this->loginname;}		// Login User
			mml::string					get_host()		{ return this->hostname;}		// Hostname
			mml::string					get_home()		{ return this->home;}			// Home path of the user
			mml::string					get_shell()		{ return this->defaultshell;}	// Default shell
			mml::string					get_domain()	{ return this->domain;}			// Domain name
			mml::string					get_path()		{ return this->path;}			// Path
			mml::string					get_pwd()		{ return this->pwd;}			// Actual path
			std::vector<mml::string>	get_groups()	{ return this->groups;}			// Groups

			
			/**
			 * @brief Printing out information
			 * @param output Determines which information is printed
			 *         Options are: uid, login_uid, gid, login_gid, username, loginname, home, defaultshell, host, hostname, iw, ie, domain, path, pwd, groups
			 */
			void cout(mml::string output);
			
			/** 
			 * @brief Checking whether this option exists and if yes, then return 
			 * 
			 * @param option which option (the same values as the output variable in `cout`)
			 * @param value Value to be checked for
			 * @return true, if equal
			 */
			bool check(mml::string option, int value);
			bool check(mml::string option, std::string value);
			
			~User() {}
		};

		/**
		 * @brief Checks if a path exists
		 * 
		 * @param path Path to be checked
		 * @return true, if all exists
		 */
		bool exist_onepath(mml::string path);

		// Template function to check the existence of multiple paths
		template<typename... Args> bool exist(const Args&... args) {
    		return (... || exist_onepath(mml::to_string(args)));
		}
		

		/**
		 * @brief Determine UID of a file
		 * @param char* Path to file
		 * @return UID Number
		 */
		uid_t getFileUID (const char* file); 
		
		/**
		 * @brief Information about the user
		 * @return UID or GID of a user
		 */
		char* getHost ();
		uid_t getUserIdByName(const char *name);
		gid_t getGroupIdByName(const char *name);
		
		/**
		 * @brief Determine the type of an object
		 * @param string Filepath
		 * @return number corresponding to the type of the object
		 * @note The numbers have the following meaning:
		 * -  1: DT_FIFO
		 * -  2: Serial connected device, mouse, etc.
		 * -  4: Directory
		 * -  6: Device or partition
		 * -  8: normal file
		 * - 10: symbolic link
		 * - 12: Socket
		 * - 14: other
		*/
		int32_t filetype(mml::string filepath);

		/**
		 * @brief Returns the name of a PID
		 * @param pid_t PID of the process
		 * @return process name
		 */
		mml::string get_process_name_by_pid(const pid_t pid);
		
		/**
		 * @brief returns the process number of a process name
		 * @param process Process Name
		 * @param start Start Value to look for the PID number
		 * @return PID
		 */
		pid_t get_pid_by_process_name(const std::string process, int start = 0);
		
		/**
		 * @brief Checks if a path is a directory
		 * @param path Path to the object to be tested
		 * @return true if a directory
		 */
		bool isdir(mml::string path);

		/**
		 * @brief Checks if a path is a file
		 * @param path Path to the object to be tested
		 * @return true if a file
		 */
		bool isfile(mml::string path);

		/**
		 * @brief Checks if a mount point is mounted
		 * @param mountpoint Path to the mount point
		 * @return true if mounted
		 * @throw runtime_error if setmtent did not work properly
		 */
		bool ismounted(std::string mountpoint);

		/**
		 * @brief Checks if a path is a symlink
		 * @param path Path to the object to be tested
		 * @return true if a symlink
		 */
		bool issymlink(mml::string path);

		/**
		 * @brief Create a directory
		 * @return true, if successfull
		 * @throw runtime_error : if directory already exists as a non-directory
		 */		
		bool mkdir_p(std::string value);
		
		/**
		 * @brief Mount a partition
		 * @param mountpath Path to the partition which should be mounted
		 * @param mountpoint where the partition should be mounted
		 * @param user Username 
		 * @param pass1 Password
		 * @param fstype Filesystem Type, e.g. cifs
		 * @return true if mounted
		*/
		bool mountFS(std::string mountpath, string mountpoint, std::string user, std::string pass1, const char* fstype);
	
		/**
		 * @brief Struct with the permissions of an object
		 * @details Execute the function perms to get the permission with the filled entries
		 */
		struct permissions {
			bool owner_read = false;
			bool owner_write = false;
			bool owner_exec = false;
			bool group_read = false;
			bool group_write = false;
			bool group_exec = false;
			bool others_read = false;
			bool others_write = false;
			bool others_exec = false;
		};

		/**
		 * @brief Check permissions of an object
		 * @param path Path to the object to be checked
		 * @return permissions in a struct
		 * @details The structure has 9 bools each self-explainatory what permission exists
		 */
		permissions perms(std::string path);
		/**
		 * @brief chekc if user has permission to write
		 * @param path Path to check for the permission
		 * @return bool
		 */
		bool perm_to_write(std::string path);

		/**
		 * @brief Deletes a directory structure
		 * 
		 * @param file String to what should be removed
		 * @return true, if successful
		 **/
		void remove(std::string file);

		/**
		 * @brief Change date of a file from another
		 * 
		 * @param src_file Source file
		 * @param dst_file Destination file
		 * @param verbose Verbose output
		 * @return true, if successful
		 **/
		bool set_date(std::string src_file, std::string dst_file, bool verbose = false);


		/**
		 * @brief Unmount a partition
		 * @param mountpoint String, where the directory is mounted
		 * @param force Force the unmount
		 * @return bool
		*/
		bool unmount(std::string mountpoint, bool force);
	}
}

#else
#error Not supported on this OS
#endif

#endif
