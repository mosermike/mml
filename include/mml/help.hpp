/**
 * @author Mike Moser
 * 
 * @file help.hpp
 * @note Enthält verschiedene Hilfeseiten für C++-Programme
 * 
*/

//#ifdef __HELP__EXIST__

#ifndef __HELP__
#define __HELP__

#include <mml.hpp>

// TODO letzte Zeile Informationen bestimmen (Version, Jahr)

namespace mml {
	namespace help {
		

		/**
		 * @note Ausgabe der jeweiligen Hilfetexte
		 * 
		 * @author Mike
		 */
		void check_root();
		void cifs();
		void convert();
		void cop();
		void copy();
		void farben();
		void finanzen();
		void hhelp();
		void hhelp_commands();
		void R_cop();
		// TODO void R_nas();
		void R_dns_filter();
		void rechner();
		void sizeof_h();
		void statistik();
		void timer();
		void todos();
		void userinfo();
		
		/**
		 * @note Ausgabe der Fußzeile mit Angabe zum Autor und Datum
		 * 
		 * @author Mike
		 */
		void foot();
		
		// TODO sha256

		/**
		 * @note Ausgabe des Headers, dass nur von Variablen abhängig ist
		 * 
		 * @author Mike
		 */
		void header(std::string befehl, std::string option = "");
		
		/**
		 * @note Ausgabe in der Konsole
		 * 
		 * @author Mike
		 */
		void help(mml::string output);
	
		/**
		 * @note Status-Informationen bestimmen
		 * 
		 * @author Mike
		 */
		void status(mml::string befehl);
		
		// TODO nur Ausgabe von C++-Programmen bei hhelp
		
	}
}

#endif
//#endif