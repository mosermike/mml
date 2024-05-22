/**
 * : @author Mike Moser
 * : 
 * : @name Unix.hpp
 * :
 * : @note Enthält verschiedene Funktionen für unixspezifische Funktionen
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
#include "mml/shell.hpp"
#include "mml/vector.hpp"

namespace mml{
	namespace shell{
		class arg;
	}
	namespace functions{
		typedef mml::shell::arg vector;	
	}
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
#if __amd64__
				  mml::string			ip_w			= getip("wlp0s20f3");
				  mml::string			ip_e			= getip("enp1s0");
#elif __aarch64__
				  mml::string			ip_w			= getip("wlan0");
				  mml::string			ip_e			= getip("eth0");
#else
#error "Architektur nicht definiert"
#endif
				  std::vector<mml::string> groups			= getgrlist();
				  
			
			/**
			 * @note Gibt verschiedene Werte zurück zur Initialisierung
			 * 
			 * @return gesuchter Wert
			 * @author Mike
			 */
			std::string geteuser();						// Gibt den effektiven User zurück, der den Prozess ausführt
			std::string getlocale();					// Returns the language of the user
			std::string getloginname();					// Gibt den Loginname zurück
			std::string gethomedir();					// Gibt den Home-Pfad zurück
			std::string getip(std::string iface);		// Gibt die aktuelle IP-Adresse des Wlan-Moduls zurück
			std::string getdefaultshell();				// Gibt die default Shell zurück
			std::string getdomain();					// Gibt die aktuelle Domain zurück
			std::string gethost();						// Gibt den Namen des PC's zurück
			uid_t getloginuid();						// gibt die eingeloogte UID zurück
			gid_t getlogingid();						// Gibt die eingeloggte GID zurück
			std::vector<gid_t> getgrgid();				//** Gibt die verschiedenen GIDs zurück, in dem der aktuelle User ist @note Größe achten(50) **/ 
// 			const std::vector<mml::string> getgrlist();	// Gibt alle Gruppen zurück, in dem der aktuelle User ist
			const std::vector<mml::string> getgrlist();	// Gibt alle Gruppen zurück, in dem der aktuelle User ist
			

		public:
			User() {};
			// Mit Initialisierung eines Vektors:
			User(const User &User_copy) {pw = User_copy.pw;}	// Kopierkonstruktor
			
			// Als Kopierkonstruktor:
			User &operator=(const User &User_temp){
				pw = User_temp.pw;
				return *this;
			}
			
			/**
			 * @note Username vergleichen
			 * 
			 * @return true oder false
			 * @author Mike
			 */
			bool operator==(std::string testuser);
			bool operator!=(const std::string testuser);
			
			/**
			 * @note UID vergleichen
			 * 
			 * @return true oder false
			 * @author Mike
			 */
			bool operator==(uid_t testuid);
			bool operator!=(uid_t testuid);
			
			
						

			/**
			 * @note Infos aktualisieren
			 * 
			 * @author Mike
			 */
			mml::string setPWD();
			
			/**
			 *  @note User Daten zurückgeben an Programm
			 * 
			 * @author Mike
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
			mml::string					get_iw()		{ return this->ip_w;}			// IP-Address Wlan
			mml::string					get_ie()		{ return this->ip_e;}			// IP-Address Ethernet
			mml::string					get_domain()	{ return this->domain;}			// Domain name
			mml::string					get_path()		{ return this->path;}			// Path
			mml::string					get_pwd()		{ return this->pwd;}			// Actual path
			std::vector<mml::string>	get_groups()	{ return this->groups;}			// Groups

			
			/**
			 * @note Printing out information
			 * 
			 * @author Mike
			 */
			void cout(mml::string output);
			
			/** 
			 * @note Checking whether this option exists and if yes, then return 
			 * 
			 * @param 
			 * @return true, wenn gleich
			 * @author Mike
			 */
			bool check(mml::string option, int value);
			bool check(mml::string option, std::string value);
			
			~User() {}
		};
		
		/**
		 * @note Gibt die UID des Eigentümers einer Datei aus
		 * 
		 * @param char* Path to file
		 * @return UID Nummer der Datei/Ordner
		 * @author Mike
		 */
		uid_t getFileUID (const char* file); 
		
		/**
		 * @note Informationen über einen Benutzer
		 * 
		 * @return UID oder GID eines Benutzers
		 * @author Mike
		 */
		char* getHost ();
		uid_t getUserIdByName(const char *name);
		gid_t getGroupIdByName(const char *name);
		
		/**
		 * @note Überprüft, ob ein oder mehrerer Pfad existiert
		 * 
		 * @param string Path(s) to be checked
		 * @return true, wenn existent
		 * @author Mike
		 */
		bool exist(std::string path);
		bool exist(std::string path1, std::string path2);
		bool exist(std::string path1, std::string path2, std::string path3);
		
		/**
		 * @note Typ bestimmen, ob das Ziel eine Datei, Ordner etc. ist
		 * 
		 * @param string Filepath
		 * @return Gibt eine Zahl zurück. Interpretierung siehe definitions.hpp
		 * @author Mike
		*/
		int32_t  filetype(std::string filepath);
		/**
		 * @note Gibt den Namen zu einem PID zurück
		 * 
		 * @param pid_t PID of the process
		 * @return Prozessname zur passenden PID
		 * @author Mike
		 */
		mml::string get_process_name_by_pid(const pid_t pid);
		
		/**
		 * @note Gibt die Prozesszahl zurück
		 * 
		 * @return PID
		 * @author Mike
		 */
		pid_t get_pid_by_process_name(const std::string process, int start = 0);
		
		/**
		 * @note Erstellen von Ordnern
		 * 
		 * @return true, wenn erfolgreich
		 * @author Mike
		 */		
		bool mkdir_p(std::string value);
		
		/**
		 * @note Berechtigung zurückgeben
		 * 
		 * @return mml::string
		 * @author Mike
		 */
		mml::string perms(std::string path);

		/**
		 * @note Berechtigung zu schreiben
		 * 
		 * @return bool
		 * @author Mike
		 */
		bool perm_to_write(std::string path);

		/**
		 * @note Änderungsdatum setzen von einer Datei auf die andere
		 * 
		 * @param src_file Source file
		 * @param dst_file Destination file
		 * @param verbose Verbose output
		 * @return true, wenn erfolgreich
		 * @author Mike
		 **/
		bool set_date(std::string src_file, std::string dst_file, bool verbose = false);

		/**
		 * @note Deletes a directory structure
		 * 
		 * @param file String to what should be removed
		 * @return true, wenn erfolgreich
		 * @author Mike
		 **/
		void remove(std::string file);
	}
}

#else
#error Not supported on this OS
#endif

#endif
