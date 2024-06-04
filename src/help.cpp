/**
 * : @author Mike Moser
 * : 
 * : @file help.cpp
 * : @note This file contains functions to print out a help page for the different 'programes' here
 * : 
*/
#include <iostream>
#include <fstream>

#include "mml/help.hpp"
#include "mml/shell.hpp"


void mml::help::header(std::string command) noexcept {
	
	mml::shell::chapter("NAME",true);
	std::cout << "\t" << command << " - " << command << std::endl;
	mml::shell::letter("white");
	mml::shell::chapter("CALL",true);
	mml::shell::chapter("\t" + command,false);
	mml::shell::chapter("DESCRIPTION",true);
}

void mml::help::foot(std::string version, std::string month, int year, std::string author) noexcept {
	
	mml::shell::chapter("AUTHOR",true);
	std::cout << "Written from " << author << std::endl << std::endl;
	std::cout << "Version: " << version << "\t\t\t\t\t\t" << month << " " << year << std::endl;
}


/*
void mml::help::check_root() {
	
	//mml::help::status("check_root");
	header("Check for root rights");
	
	std::cout << "\tCheck, whether the executing user has root rights or not." << std::endl << std::endl;
	std::cout << "\tNecessary arguments for long option are also for short necessary." << std::endl;
	
	mml::shell::option("-h,--help","Shows the help page.");
	mml::shell::option("-l, --log"  , "Print the log file.");
	mml::shell::option("-lr, --log_reset", "Reset of the logfile (without backup)");
	mml::shell::option("-lb, --log_backup", "Backup of the logfile");
	mml::shell::option("-v, --verbose", "Verbose printouts (only for logging purposes)");
	
	//foot();
}

void mml::help::cifs() {
	
	//mml::help::status("cifs");
	
	header("Mount of partitions");
	
	std::cout << "\tMount of specific partitions like the MyCloud or the ftp server." << std::endl << std::endl;
	std::cout << "\tNecessary arguments for long option are also for short necessary." << std::endl;
	
	mml::shell::option("-b,--fritzbox","mount the fritzbox nas");
	mml::shell::option("-dreambox","mount the partition of the dreambox, be sure that the dreambox is connected");
	mml::shell::option("-f,--force","den Server nicht anpingen.");
	mml::shell::option("-h,--help","Shows the help page.");
	mml::shell::option("-m","mount the partition Mike of WD MyCloud");
	mml::shell::option("-M,--mediathek","mount the partition Mediathek of WD MyCloud");
	mml::shell::option("-n,--nextcloud","mount the cloud Nextcloud");
	mml::shell::option("-p","mount the partition My_Passport of WD MyCloud");
	mml::shell::option("-r","mount the ftp server");
	mml::shell::option("-s","mount the partition Sicherungen of WD MyCloud");
	mml::shell::option(" -u","to unmount one or more partition(s)");
	mml::shell::option("-usb","mount an USB, you have to give the device name with dev=sdX1, and if the format isn't ntfs\n\t\tyou have to add the format as another argument with fs=ext4");
	mml::shell::option("-user","to mount the ftp server with another user as ftp");
	mml::shell::option("-w","mount all partitions of WD MyCloud");
	
	//foot();
}

void mml::help::convert() {
	
	//mml::help::status("Convert");
	
	header("Convert different types of photos to jpeg");
	
	std::cout << "\tConvert different types of photos like NEF to JPG. Additionally it is possible to change the time of photos" << std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	
	mml::shell::option("if=", "Source from where the date is taken");
	mml::shell::option("of=", "Destination where the date is changed");
	mml::shell::option("-a, --all","Also list hidden files and directory.");
	mml::shell::option("-e,--extend", "Extend to detect other file endings like jpg, heif, mp4, etc.. Just for change the date.");
	mml::shell::option("-h,--help","Shows the help page.");
	mml::shell::option("-o,--only-date","Only change the date and don't convert anything.");
 	mml::shell::option("-p, --picture", "Change date of pictures with an eventually conversion.");
	mml::shell::option("-r, --recursive", "Change date of pictures recursively (used in ls function).");
	mml::shell::option("-s, --singlefile", "Change date of a single file from another file.");
	mml::shell::option("-v, --verbose", "Verbose output.");
	mml::shell::option("-w,--wdmycloud", "Use a predefined input for uploaded picture from the iPhone (Should be revised).");
	
	//foot();
}


void mml::help::cop(){
	
	//mml::help::status("cop");
	
	header("Kopieren von Dateien und Ordner auf Netzwerkfestplatten");
	
	std::cout << "\tKopieren von Dateien auf der SSD auf die MyCloud oder den FTP Server." << std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	
	mml::shell::option("bs=BYTES","liest und schreibt bis zu BYTES bytes zur gleichen Zeit (Standard: 10MB)");
	mml::shell::option("-a, --all","auch versteckte Dateien kopieren.");
	mml::shell::option("-b, --backup","Backup der Nextcloud Dateiein durchführen (Nur nextcloud).");
	mml::shell::option("-d, --delete","bestehende Dateien löschen.");
	mml::shell::option("-f, --force","bestehende Dateien überschreiben.");
	mml::shell::option("-F", "bestehende immer Dateien überschreiben.");
// 	mml::shell::option("-ftp","Nur das Sichern der Dateien auf dem FTP Server");
	mml::shell::option("-h,--help","zeigt diese Hilfe an");
	mml::shell::option("-L,--Linux","sichert nur die Daten auf der Cloud und nicht auf dem FTP Server");
	mml::shell::option("-l,--log","Logdatei ausgeben.");
	mml::shell::option("-m, --human","Größen in menschenlesbarem Format ausgeben.");
	mml::shell::option("-n, --no","Keine Dateien überschreiben.(Betaversion für Backup bei Nextcloud)");
	mml::shell::option("-p, --progress","Zeigt den Fortschritt und die Zeit an.");
	mml::shell::option("--push","Führt ein 'git pull' auf der Sicherunge Documents.git durch.");
	mml::shell::option("-s,--Studium","lokales Speichern der aktuellen Vorlesungen");
	mml::shell::option("-t, --Timer","Ausgabe der Dauer des Kopiervorgangs");
	mml::shell::option("-v,--verbose","durchgeführte Tätigkeiten erklären");
	mml::shell::option("-w","Sichern der Dateien von der Windowspartition");
	
	//foot();
	
}


void mml::help::copy() {
	
	//mml::help::status("copy");

	header("Kopieren von Dateien und Verzeichnissen"," if=QUELLE of=ZIEL ");

	std::cout << "\tCopy from SOURCE to GOAL." << std::endl << std::endl;
	std::cout << "\tNecessary arguments for long options are also needed for short ones." << std::endl;
	mml::shell::option("bs=BYTES","reads and writes with up to BYTES bytes at the same time (Standard: 100MB)");
	mml::shell::option("if=SOURCE","from where data is copied.");
	mml::shell::option("of=GOAL","to where data is copied.");
	mml::shell::option("-a, --all","include hidden files.");
	mml::shell::option("-e, --exclude","only copy files without this string");
	mml::shell::option("-f, --force","do not check whether the file exists, overwrite if file exists.");
	mml::shell::option("-h, --help","shows this help page.");
	mml::shell::option("-m, --human","write outputs in human readable formats.");
	mml::shell::option("-n, --no","do not overwrite existing files.");
	mml::shell::option("-i, --include","only copy files and directories including this string.");
	mml::shell::option("-p, --progress","show the progress of copying each file.");
	mml::shell::option("-r, --recursive","auch die Inhalte der Unterverzeichnisse kopieren.");
	mml::shell::option("-t, --Timer","Ausgabe der Dauer des Kopiervorgangs");
	mml::shell::option("-v, --verbose","durchgeführte Tätigkeiten erklären");
	mml::shell::option("-vv", "More verbose printouts explaining when what is executed.");

	//foot();
	
}

void mml::help::farben() {
	
	//mml::help::status("farben");
	
	header("Ändern der Formatierung","[OPTION] -t TEXT ");
	
	std::cout << "\tDieses Programm ändert die Ausgabe eines Textes" << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	mml::shell::option("-h, --help","zeigt diese Hilfe an.");
	mml::shell::option("-l, --letter","Ändert die Schriftfarbe.");
	mml::shell::option("-t, --text","Dieser Text wird verändert angezeigt.");
	mml::shell::option("-b, --background","Ändert den Hintergrund.");
	mml::shell::option("-f, --formation","Ändert die Formatierung.");
	mml::shell::option("-n, --normal","Alle neuen Einstellungen rückgängig machen");
	
	//foot();
}

void mml::help::finanzen() {
	
	//mml::help::status("finanzen");
	
	header("Daten von Finanzchecker App anpassen","[OPTION] -t TEXT ");
	
	std::cout << "\tDieses Programm ändert die csv datei in ein einfacheres Format." << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	mml::shell::option("-h, --help", "zeigt diese Hilfe an.");
	mml::shell::option("-i, --input","Input file.");
	mml::shell::option("-o, --output","Speicherort.");
	mml::shell::option("-v, --verbose","Zeige zusätzliche Infos.");
	mml::shell::option("    --verbose-extra","Zeige zusätzliche debug infos.");
	
	//foot();
}
	
	
void mml::help::hhelp() {
	//mml::help::status("hhelp");
	header("Anzeigen der vorhandenen Befehle in /usr/local/bin");
	std::cout << "\tAnzeige der vorhandenen, selbst geschriebenen Befehlen in dem Ordner /usr/local/bin." << std::endl << std::endl;
	mml::shell::chapter("\nVorhandene Befehle:\n",true);
	mml::shell::option("-a,--all","zeigt alle verfügbaren Programme mit Kurzbeschreibung an");
	mml::shell::option("-c,--command","zeigt die Hilfeseite von einem angegebenen Programm an");
	mml::shell::option("-h,--help","zeigt diese Hile an");
	//foot();
}
void mml::help::hhelp_commands() {
	// TODO automatische Erstellung aus anderer hilfeseite?
	mml::Unix::User user;
	//mml::help::status("hhelp");
	header("Anzeigen der vorhandenen Befehle in /usr/local/bin");
	std::cout << "Test" << std::endl;
	std::cout << "\tAnzeige der vorhandenen, selbst geschriebenen Befehlen in dem Ordner /usr/local/bin." << std::endl << std::endl;
	std::cout << "Test" << std::endl;
	mml::shell::chapter("\nVorhandene Befehle:\n",true);
	mml::shell::option("autostart.sh:","Skripte die automatisch beim Start ausgeführt werden.(nicht verwendet)");
	mml::shell::option("backup:", "Backup der Partition erstellen auf eine externe Partition.");
	if(user.check("host","gentoo-i5"))
		mml::shell::option("cewe:", "Öffnen des Programmes Cewe zum Erstellen von Fotobücher.");
	else
		mml::shell::option("cewe:", "Öffnen des Programmes Cewe zum Erstellen von Fotobücher.(Nicht installiert)");
	mml::shell::option("check_root:", "Überprüfen, ob das Skript mit Superuser Rechten ausgeführt wird.");
	mml::shell::option("cifs:","Einbinden von verschiedenen Partitionen: Dreambox, SSD, USB und WD MyCloud.");
	mml::shell::option("Convert:","Convert a photo from NEF to JPG or change the date of media files.");
	mml::shell::option("cop:","Kopieren von Dateien von Linux zur Sicherung bzw. den Ordner Studium sichern.");
	mml::shell::option("copy:","kopieren von Dateien und Ordner.");
	mml::shell::option("create_tmpfile:","Eine temporäre Datei erstellen, die nicht auf den Git-Server geladen wird.");
	mml::shell::option("du10","Darstellung der 10 größten Ordner/Dateien im aktuellen Pfad.");
	mml::shell::option("etcher:","Verknüpfung zum Programm etcher.");
	mml::shell::option("farben:","Ändern der Formatierungen der Textausgabe.");
	mml::shell::option("git_clean:","Nicht mehr verwendete Dateien aus .git löschen");
	mml::shell::option("git_reset:","Reset auf den Stand des Git-Servers");
	mml::shell::option("grub:","Kurzbefehl für grub-mkconfig -o /boot/grub/grub.cfg.");
	mml::shell::option("hhelp:","Alle verfügbaren Befehle in /usr/local/bin anzeigen.");
	mml::shell::option("iTunes:","iTunes starten.");
	mml::shell::option("latexsearch:","Bestimmen der Anzahl an Wörtern in tex Dateien.(Betaversion)");
	mml::shell::option("make_kernel:", "Aktuell ausgewählten Kernel kompilieren.");
	mml::shell::option("medieval:", "Starten des Spiels Medieval II: Total War in Steam.");
	mml::shell::option("movebyte:","verschieben von Dateien");
	mml::shell::option("pong","Anpingen eines Netzwerkgerätes");
	mml::shell::option("qtwebflix","Netflix starten");
	mml::shell::option("ramdisk:","Die PORTAGE_TMPDIR-Größe ändern auf dem RAM.");
	mml::shell::option("rechner:","Rechnen von verschiedenen Sachen.");
	mml::shell::option("replaceText","Text in allen Dateien im aktuellen Ordner und Unterordner ersetzen");
	mml::shell::option("repoAdd.sh:","neue Repository hinzufügen");
	mml::shell::option("resolution:","automatische Einstellung der Aufloesung eines Displays für alte Monitore.(alt)");
	mml::shell::option("sha256:", "Überprüfen, ob eine gedownloadete Datei nicht verändert wurde anhand der SHA256-Checksumme.");
	mml::shell::option("sucheText:","Suche Text in allen Dateien rekursiv");
	mml::shell::option("sizeof","Größe eines Ordners angeben.(Betaversion)");
	mml::shell::option("statistik","Statistische Berechnungen durchführen.");
	mml::shell::option("ssh1:","SSH Verbindung mit dem Raspberry Pi");
	mml::shell::option("swapfile","Eine Swapfile generieren und aktivieren von 4.7 GB");
	mml::shell::option("todos:","Anzahl der Todos für die verschiedenen oder dem aktuellen Gerät(e) anzeigen.");
	mml::shell::option("uplay:","Uplay starten.");
	mml::shell::option("userinfo:","Ausgabe von benutzer- und computerspezifische Informationen.");
	mml::shell::option("vpn:","VPN Verbindung mit dem Raspberry Pi.(Nicht verwendbar durch Portsperrung)");
	mml::shell::option("win:","Neustart mit Windows Boot Manager\n");
	
	//foot();
	
}

void mml::help::R_cop(){
	
	//mml::help::status("Raspberry/cop");
	
	header("Kopieren von Dateien und Ordner auf Netzwerkfestplatten");
	
	std::cout << "\tKopieren von Dateien auf dem Pi auf die MyCloud oder den FTP Server." << std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	
	mml::shell::option("bs=BYTES","liest und schreibt bis zu BYTES bytes zur gleichen Zeit (Standard: 10MB)");
	mml::shell::option("-a, --all","auch versteckte Dateien kopieren.");
	mml::shell::option("-b, --backup","Backup von Nextcloud Daten.");
	mml::shell::option("-bd, --backup-doku","Backup vom Dokuwiki.");
	mml::shell::option("-bg, --backup-gogs","Backup von Gogs Repositories.");
	mml::shell::option("-bs, --backup-studium","Backup vom Studium Ordner.");
	mml::shell::option("-d, --delete","bestehende Dateien löschen.");
	mml::shell::option("-f, --force","bestehende Dateien überschreiben.");
	mml::shell::option("-h,--help","zeigt diese Hilfe an");
	mml::shell::option("-p, --progress","Zeigt den Fortschritt und die Zeit an.");
	mml::shell::option("-t, --Timer","Ausgabe der Dauer des Kopiervorgangs");
	mml::shell::option("-v,--verbose","durchgeführte Tätigkeiten erklären");
		
	//foot();
	
}

void mml::help::R_dns_filter(){
	
	//mml::help::status("Raspberry/dns_filter");
	
	header("Herausfiltern von unnötigen Informationen in dnsmasq.log");
	
	std::cout << "\tHerausfiltern von unnötigen Informationen aus der aktuellen Log-Datei von dnsmasq.log." << std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	
	mml::shell::option("bs=BYTES","liest und schreibt bis zu BYTES bytes zur gleichen Zeit (Standard: 100MB) beim Kopieren");
	mml::shell::option("-a, --all","auch versteckte Dateien kopieren.");
	mml::shell::option("-f, --force","keine Überprüfung, ob das Zielverzeichnis bereits existiert beim Kopieren.(Standard: aktiv)");
	mml::shell::option("-h, --help","zeigt diese Hilfe an.");
	mml::shell::option("-i, --file","benutzen einer anderen Log-Datei.");
	mml::shell::option("-l, --log"  , "Ausgabe der Logdatei.");
	mml::shell::option("-lr, --log_reset", "Zurücksetzen der Logdatei");
	mml::shell::option("-lb, --log_backup", "Backup der Logdatei");
	mml::shell::option("-p, --progress","Zeigt den Fortschritt und die Zeit an beim Kopieren.");
	mml::shell::option("-r, --recursive","auch die Inhalte der Unterverzeichnisse kopieren.");
	mml::shell::option("-s, --sort", " zusätzlich eine sortierte Liste ohne Zeitangabe ausgeben in /tmp/dnsmasq_sort.log");
	mml::shell::option("-t, --Timer","Ausgabe der Dauer des Kopiervorgangs");
	mml::shell::option("-v, --verbose","durchgeführte Tätigkeiten erklären beim Kopieren");
	
	//foot();
	
}

void mml::help::rechner() {

	//mml::help::status("rechner");

	header("Führt verschiedene Berechungen durch.");
	
	std::cout << "\tDieses Programm führt verschiedene Berechnungen durch abhängig von den Argumenten." << std::endl;
	std::cout << "\tBei der Verwendung von Klammern sind Anführunszeichen notwendig bei der Gleichung."	<< std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	mml::shell::option("-a, --adjunct" , "Adjunkte einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("-c, --calculate" , "Gleichung lösen mit allen Operatoren.");
	mml::shell::option("-cs, --calculations" , "Mehrere verschiedene Gleichungen lösen mit allen Operatoren.");
	mml::shell::option("-d, --det" , "Determinante einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("    --grad" , "Ausgabe oder Angabe in Grad in Abhängigkeit des Operators.");
	mml::shell::option("-h, --help" , "Ausgabe dieser Hilfe.");
	mml::shell::option("-i, --inverse" , "Inverse einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("-k, --comment"  , "Kommentar in die Logdatei hinter Rechnung.");
	mml::shell::option("-l, --log"  , "Ausgabe der Logdatei.");
	mml::shell::option("-lr, --log_reset", "Zurücksetzen der Logdatei");
	mml::shell::option("-lb, --log_backup", "Backup der Logdatei");
	mml::shell::option("-m, --matrix" , "Multiplzieren und Addieren von Matrizen.Matrixform [[1.,Reihe],[2.,Reihe]]");
	mml::shell::option("-ml, --matrix-latex" , "Format in Latex. (Achtung Matrix endet und startet mit '|')");
	mml::shell::option("-t, --timer", "Ausgabe der Dauer der Berechnung");
	mml::shell::option("-tr, --transpose" , "Transponierte einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("-u" , "Wertzuweisung einer oder mehreren unbekannten Variable(n) mit Trennzeichen ':' in der Gleichung. z.B. -u x=2");
	mml::shell::chapter("Verfügbare Operationen:", true);
	mml::shell::option("+" , "Addition verschiedener Werte.");
	mml::shell::option("-" , "Subtrahieren verschiedener Werte.");
	mml::shell::option("*", "Multiplikation verschiedener Werte.");
	mml::shell::option("/" , "Dividieren von zwei Zahlen(alt).");
	mml::shell::option("//" , "Dividieren von mehreren Zahlen(alt).");
	mml::shell::option("d" , "Ableiten einer Funktion. Direkt als Parameter übergeben(alt).");
	mml::shell::option("^" , "Multiplizieren einer Basis zu einem Exponenten.");
	mml::shell::option("^(" , "Multiplizieren einer Basis zu einem Exponenten.");
	mml::shell::option("exp(x)" , "Berechnen von exp^(x).");
	mml::shell::option("sin(x)" , "sin berechnen von x.");
	mml::shell::option("cos(x)" , "cos berechnen von x.");
	mml::shell::option("tan(x)" , "tan berechnen von x.");
	mml::shell::option("arcsin(x)" , "arcsin berechnen von x.");
	mml::shell::option("arccos(x)" , "arccos berechnen von x.");
	mml::shell::option("arctan(x)" , "arctan berechnen von x.");
	mml::shell::option("ln(x)" , "logarithmus naturalis berechnen von x.");
	mml::shell::option("log(x)" , "10er Logarithmus berechnen von x.");
	mml::shell::option("log2(x)" , "2er Logarithmus berechnen von x.");
	mml::shell::option("logb(x)" , "Logarithmus zur Basis b berechnen von x.");
	mml::shell::option("sqrt(x)" , "Wurzel ziehen von x.");
	std::cout << std::endl;
	mml::shell::chapter("Optionen bei --calculations:",true);
	mml::shell::option("rx", "Verwendung des Ergebnisses von Gleichung x, rx wird in der neuen Gleichung ersetzt");
	std::cout << std::endl;
	mml::shell::chapter("Sonstiges:", true);
	std::cout << "\tVorhandene Konstanten: pi, exp,E , P_c, P_k, P_m, P_e, P_G, P_h, P_µ, P_NA, P_u" << std::endl;
	std::cout << "\tVorhandene Potenzen:   p, n, µ, m, k, M, G, T oder mit e" << std::endl << std::endl;
		
	//foot();
}

void mml::help::sizeof_h() {

	//mml::help::status("sizeof");

	header("Berechnet die Größen von verschiedenen Objekte.");
	
	std::cout << "\tDieses Programm führt verschiedene Berechnungen durch abhängig von den Argumenten." << std::endl;
	std::cout << "\tBei der Verwendung von Klammern sind Anführunszeichen notwendig bei der Gleichung."	<< std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	std::cout << "\tMögliche Berechnungen für Partitionen, Ordner, Dateien." << std::endl;
	mml::shell::option("-h, --help" , "Ausgabe dieser Hilfe.");
	mml::shell::option("-n, --human","Größen in menschenlesbarem Format ausgeben.");
			
	//foot();
}

void mml::help::statistik() {

	//mml::help::status("statistik");

	header("Berechnung von statistischen Werten.");
	
	std::cout << "\tDieses Programm führt verschiedene Berechnungen im Rahmen der Statistik durch abhängig von den Argumenten." << std::endl;
	std::cout << "\tHier können wichtige Berechnungen für Auswertungen durchgeführt werden, die aus der Statistik kommen."	<< std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	std::cout << "\tMögliche Berechnungen für Partitionen, Ordner, Dateien." << std::endl;
	mml::shell::option("-f, --file" , "Daten aus einer Datei importieren");
	mml::shell::option("-f1, --file1", "x-Werte für die lineare Regression");
	mml::shell::option("-f2, --file2", "y-Werte für die lineare Regression");
	mml::shell::option("-h, --help" , "Ausgabe dieser Hilfe.");
	mml::shell::option("-k, --Kovarianz","Berechnung der Kovarianz");
	mml::shell::option("-l, --log"  , "Ausgabe der Logdatei.");
	mml::shell::option("-lr, --log_reset", "Zurücksetzen der Logdatei");
	mml::shell::option("-lb, --log_backup", "Backup der Logdatei");
	mml::shell::option("-L, --lineareRegression","Durchführung einer linearen Regression der Form y = a + b*x. Eingabe der Werte über std::cin");
	mml::shell::option("-o, --oldData","Übernahme der alten Werte");
	mml::shell::option("-p, --python","Übernahme der Daten aus einem mitgegebenen Python Array.");
	mml::shell::option("-r, --round","Gerundete Ausgaben");
	mml::shell::option("-s, --Standardabweichung","Durchführung der Berechnung des Mittelwertes mit der Standardabweichung. Eingabe der Werte über std::cin");
	mml::shell::option("-T, --t-value","t-value berechnen");
	mml::shell::option("-t, --t-value","Zeit ausgeben (ohne Eingabe)");
	mml::shell::option("-wm, --weightmean", "Gewichteter Mittelwert berechnen.");
	mml::shell::option("-v, --verbose","Ausgabe der Berechnungsschritten.");
	
	
	
	//foot();
}

void mml::help::timer() {

	//mml::help::status("timer");

	header("Timer.");
	
	std::cout << "\tDieses Programm führt verschiedene Berechnungen im Rahmen der Statistik durch abhängig von den Argumenten." << std::endl;
	std::cout << "\tHier können wichtige Berechnungen für Auswertungen durchgeführt werden, die aus der Statistik kommen."	<< std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	std::cout << "\tMögliche Berechnungen für Partitionen, Ordner, Dateien." << std::endl;
	
	mml::shell::option("-h, --help" , "Ausgabe dieser Hilfe.");
	mml::shell::option("-H, --hour", "Einstellen wie viele Stunden.");
	mml::shell::option("-l, --log"  , "Ausgabe der Logdatei.");
	mml::shell::option("-lr, --log_reset", "Zurücksetzen der Logdatei");
	mml::shell::option("-lb, --log_backup", "Backup der Logdatei");
	mml::shell::option("-m, --minute", "Einstellen wie viele Minuten.");
	mml::shell::option("-S, --stopwatch", "Start a stopwatch to count.");
	mml::shell::option("-s, --second", "Einstellen wie viele Sekunden.");
	mml::shell::option("-t, --timer", "Timer benutzen.");
	mml::shell::option("-v, --verbose","Ausgabe der verbleibenden Zeit.");
			
	//foot();
}

void mml::help::todos() {
	
	//mml::help::status("todos");

	header(" - Gibt die Anzahl an TODO's aus");
	
	std::cout << "\tGibt die Anzahl der TODO's aus. Ohne Parameterübergabe werden die Todos des aktuellen Gerätes ausgegeben" << std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	mml::shell::option("-h,--help","zeigt diese Hilfe an");
	mml::shell::option("-i5,--gentoo-i5","TODO's Ausgabe des Gerätes gentoo-i5");
	mml::shell::option("-i7,--gentoo-i7","TODO's Ausgabe des Gerätes gentoo-i7");
	mml::shell::option("-pi,--raspberrypi","TODO's Ausgabe des Gerätes raspberrypi");
	
	//foot();
}
void mml::help::userinfo() {
	
	//mml::help::status("userinfo");
	
	header("Ausgabe von Benutzerinfos");
	
	std::cout << "\tGibt verschiedene Infos zum Benutzer und computerspezifische Infos" << std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	
	mml::shell::option("-a,--all","Alle Informationen ausgeben");
	mml::shell::option("-d,--domain","Aktueller Domain ausgeben");
	mml::shell::option("-e,--home","Aktueller Home-Pfad ausgeben");
	mml::shell::option("-g,--gid","Aktuelle GID ausgeben");
	mml::shell::option("-h,--help","zeigt diese Hilfe an");
	mml::shell::option("-i,--uid","Aktuelle UID ausgeben");
	mml::shell::option("-ie,--ip-address-e","IP-Adresse der Ethernet Karte ausgeben");
	mml::shell::option("-iw,--ip-address-w","IP-Adresse der Wlan-Karte ausgeben");
	mml::shell::option("-l,--loginname","Aktueller Name des eingeloggten Benutzers ausgeben");
	mml::shell::option("-lg,--logingid","Aktuellen GID des eingeloggten Benutzers ausgeben");
	mml::shell::option("-lu,--loginuid","Aktuellen UID des eingeloggten Benutzers ausgeben");
	mml::shell::option("-n,--hostname","Aktueller Hostname ausgeben");
	mml::shell::option("-o,--only","Nur die Informationen ausgeben");
	mml::shell::option("-p,--path","Aktueller Standardpath ausgeben");
	mml::shell::option("-r,--groups","Alle aktuelle Gruppen des Benutzers ausgeben");
	mml::shell::option("-s,--shell","der Standardbefehl der Shell ausgeben");
	mml::shell::option("-w,--pwd","Aktueller Pfad ausgeben");
	mml::shell::option("-u,--user","Aktuellen Benutzer ausgeben");
		
		
	//foot();
}

void mml::help::help(mml::string output) {
	switch(output.hash()) {
		case mml::const_string_hash("check_root") :
			mml::help::check_root();
			break;
		case mml::const_string_hash("cifs") :
			mml::help::cifs();
			break;
		case mml::const_string_hash("Convert") :
			mml::help::convert();
			break;
		case mml::const_string_hash("cop") :
			mml::help::cop();
			break;
		case mml::const_string_hash("copy") :
			mml::help::copy();
			break;
		
		case mml::const_string_hash("farben") :
			mml::help::farben();
			break;

		case mml::const_string_hash("finanzen") :
			mml::help::finanzen();
			break;

		case mml::const_string_hash("hhelp") :
			mml::help::hhelp();
			break;
			
		case mml::const_string_hash("hhelp_commands") :
			mml::help::hhelp_commands();
			break;
		
		case mml::const_string_hash("R_cop") :
			mml::help::R_cop();
			break;
		
		case mml::const_string_hash("R_dns_filter") :
			mml::help::R_dns_filter();
			break;
			
		//case mml::functions::const_string_hash("R_nas") :
			//mml::help::R_nas();
		//	break;
			
		case mml::const_string_hash("rechner") :
			mml::help::rechner();
			break;
			
		case mml::const_string_hash("sizeof") :
			mml::help::sizeof_h();
			break;
			
		case mml::const_string_hash("statistik") :
			mml::help::statistik();
			break;
			
		case mml::const_string_hash("timer") :
			mml::help::timer();
			break;
			
		case mml::const_string_hash("todos") :
			mml::help::todos();
			break;
			
		case mml::const_string_hash("userinfo") :
			mml::help::userinfo();
			break;
		
		default:
			std::cout << "Wrong Parameter or not existing help page of the program " << output << std::endl;
			break;
			
	}
	
	exit(0);
	
}

*/


