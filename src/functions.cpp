/**
 * @author Mike Moser
 * 
 * @name functions.cpp
 * Enthält verschiedene Funktionen
 * 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>		// fsync(),stdin_fileno,getpass
#include <definitions.hpp>
#include <algorithm>	// std::replace
#include <sys/mount.h>
#include <signal.h>

#include "functions.hpp"
#include <mml.hpp>


mml::string mml_pass;
mml::string mml_mount_name;


//Ein Vektor an einen anderen Vektor anhängen
std::vector<double> mml::functions::Add_Vector( std::vector <double> vector1 , std::vector <double> vector2){
	
	vector1.insert(vector1.end(), vector2.begin(), vector2.end());
	return vector1;	
}

std::vector<std::string> mml::functions::Add_Vector( std::vector <std::string> vector1 , std::vector <std::string> vector2){
	
	vector1.insert(vector1.end(), vector2.begin(), vector2.end());
	return vector1;	
}

double mml::functions::Mean_of_Vector( std::vector<double> values, bool ausgabe){
	
    double sum = 0;
	
    // Durchlauf durch den Vektor
    for(std::vector<double>::iterator it = values.begin(); it != values.end(); ++it){
       sum=sum+*it;                                 //Addition aller Werte
      
	// TODO
	//	if (ausgabe)
	//		std::cout << *it << " " << std::endl;    //Ausgabe aller Werte
    }
	
	if (ausgabe)
		std::cout << "The mean is: " << sum/values.size()  << std::endl;             //Ausgabe des Mittelwertes
    
    return sum/values.size();
}

double mml::functions::Mean_of_Array( double array[] , uint16_t length, bool ausgabe)	// Beispiel mit array a:    Mean_of_Array(a, (int) sizeof(a)/sizeof(a[0]), true); 
{

	std::vector<double> vectorx;
	double 				mean 	= 0;
	
    //Inhalt der Datei Zahl für Zahl einlesen
    for(uint16_t i = 0 ; i < length ; i++)
        vectorx.push_back(array[i]);  //den zuletzt eingelesenen Wert Zahl für Zahl einlesen
        
    mean = Mean_of_Vector(vectorx , ausgabe);
    
	return mean;
}

// Werte aus einer Datei in einen Vektor schreiben:
std::vector<double> mml::functions::Get_Values( std::string filepath, int16_t min_value) {	//Nach dem Zeichen border wird ausgegeben
	
	std::vector<double> values;	//Werte zum zurückgeben
	std::string 		value 	= "";			//String aus einer Linie
	std::size_t			pos		= 0;
	double 				value1	= 0;
	//Öffne die Datei:
	std::fstream input(filepath);
    
	
    //Überprüfung, ob die Datei geöffnet wurde
    if ( !input ){
        std::cerr << "file not found" << std::endl;
        
		//return ;
		
	}
    
	//Inhalt der Datei Zahl für Zahl einlesen
	while (! input.eof()){
		std::getline(input, value );
		
		pos = value.find("=");
		
		value = value.substr (pos+1);
		value1 = std::atof(value.c_str());
	
		if (value1 > min_value )	//Korrektur des Titels, das als Zahl 0 verwertet wird
			values.push_back(value1);
    }
    
    return values;
}



uint32_t mml::functions::cifs(std::string src, std::string dst , mml::string fstype, std::string user , std::string mml_pass){
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

bool mml::functions::unmount_dir(std::string mount_dir, std::string controlpoint){
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

std::string mml::functions::mount_Dir (mml::shell::arg args, std::string mountpath, mml::string mountpoint, mml::string controlpoint, std::string user, std::string pass1, const char* fstype, int count )
{
	
	std::string		dir 				= mountpath;
					mml_mount_name		= mountpoint; // nur zur Ausgabe von Mount the dev...
	int				mount_return		= 0;
	
	mml::check_root(args);
	
	for(uint32_t i = mml_mount_name.size(); i >= 0;i--) {
		if(mml_mount_name[i] == '/') {
			mml_mount_name = mml_mount_name.substr(i+1);
			break;
		}
	}
   
	std::cout << "Mount the device: "<< mml_mount_name << std::endl;
	
	if(!mml::Unix::exist(mountpoint.str())) {
		if(mountpoint[mountpoint.size()-1] != '/')
			mountpoint += "/";
		mountpoint.mkdir_p();
	
	}

	if(mml::Unix::exist(controlpoint.str()) && !(controlpoint == "")) {
		return pass1;
	}

	mount_return = cifs(mountpath, mountpoint.c_str(),fstype,user.c_str() ,mml_pass.c_str());
	
	if (mount_return != 0 && count < 2 && !mml::Unix::exist(controlpoint.str())){
	
		std::cout << "Das hat nicht funktioniert, bitte nochmal probieren!" << std::endl;
		
		count++;
		mml::thread::sleep(1);
		
		mount_Dir(args, mountpath, mountpoint, controlpoint, user, pass1 = shell::password("[cifs] Passwort für Laufwerk ",mml_mount_name.str()), fstype, count);
	}
	
	if (mount_return != 0 && count == 2 && !mml::Unix::exist(controlpoint.str())){
	
		count ++;
		
		std::cout << "mount: 3 Fehlversuche bei der Passworteingabe" << std::endl;
		exit(EXIT_FAILURE);
	}

	count = 0;
	
	return pass1;
}



std::size_t mml::functions::digits(double number){
	mml::string temp = mml::to_string(number);
	
	// Korrektur von std::to_string, da dies min. 8 Nachkommastellen anhängt
	//while(temp[temp.size()-1] == '0')
	//	temp = temp.sub(0,temp.size()-2);

	// Korrektur, wenn eine ganze Zahl vorhanden
	if(temp[temp.size()-1]== '.')
		temp = temp.sub(0,temp.size()-2);
	
	return temp.size();
}


void mml::functions::getline(std::ifstream& input, mml::string& String) {
	String.getline(input);
}


int mml::functions::get_random(int min, int max) {
	
	std::random_device rd;     // only used once to initialise (seed) engine
	
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	
	std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

	return uni(rng);
}


/*double mml::functions::smallest_num(std::vector<double> values) {
	std::sort(values.begin(), values.end());
	return values[0];
}*/

std::size_t mml::functions::smallest_num(std::vector<std::size_t> values, std::size_t pos) {
	std::sort(values.begin(), values.end());
	return values[pos];
}

uint32_t mml::functions::count_sym(std::string test, char symbol) {
	uint32_t count = 0;
	for(uint32_t i = 0; i < test.size(); i++) {
		if(test[i] == symbol)
			count++;
	}
	
	return count;
}

void mml::functions::cout(std::vector<std::string> vec) {
	for(uint32_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
}

void mml::functions::cout(std::vector<mml::string> vec) {
	for(uint32_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
}

void mml::functions::cout(std::vector<double> vec) {
	for(uint32_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
}

void mml::functions::cout(std::vector<int> vec) {
	for(uint32_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
}
	
std::string mml::functions::declare_month(int month_nr) {
	switch(month_nr) {
		case(1) :	return "Januar";
		case(2) :	return "Februar";
		case(3) :	return "März";
		case(4) :	return "April";
		case(5) :	return "Mai";
		case(6) :	return "Juni";
		case(7) :	return "Juli";
		case(8) :	return "August";
		case(9) :	return "September";
		case(10) :	return "Oktober";
		case(11) :	return "November";
		case(12) :	return "Dezember";
		default  :	return "";
	}
}
std::vector<std::string> mml::functions::erase(std::vector<std::string> data){
    
	while(!data.empty())
		data.pop_back();	// Da eine Initialisierung stattfindet am Anfang
	
	return data;

}

std::vector<mml::string> mml::functions::erase(std::vector<mml::string> data){
    
	while(!data.empty())
		data.pop_back();	// Da eine Initialisierung stattfindet am Anfang
	
	return data;

}

std::vector<double> mml::functions::erase(std::vector<double> data){
	
	while(!data.empty())
		data.pop_back();	// Da eine Initialisierung stattfindet am Anfang
	
	return data;
}

std::vector<int> mml::functions::erase(std::vector<int> data){
	while(!data.empty())
		data.pop_back();	// Da eine Initialisierung stattfindet am Anfang
	
	return data;
}

std::string mml::functions::random_str(uint32_t letters, std::string value) {
	
	for(uint32_t i = 0; i < letters; i++)
		value += static_cast<char> (mml::functions::get_random(97,122));
	
	return value;
}





// Alle Zeichen eines Strings in Kleinbuchstaben
std::string mml::functions::lower(std::string input){

	for(uint16_t i = 0; i < (uint16_t) input.size(); i++)
		input[i] = tolower(input[i]);
	return input;

}


/*
 * #if defined(__APPLE__) || defined(__FreeBSD__)
	const char * appname = getprogname();
	#elif defined(_GNU_SOURCE)
	const char * appname = program_invocation_name;
	#else
	const char * appname = "?";
	#endif
*/



