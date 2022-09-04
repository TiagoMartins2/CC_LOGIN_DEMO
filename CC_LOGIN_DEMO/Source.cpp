#include <iostream>
#include <string>
#include <eidlib.h>
#include <eidlibcompat.h>
#include <eidlibcompat.h>
#include <eidlibdefines.h>
#include <eidlibException.h>
#include <eidErrors.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

using namespace eIDMW;
using namespace std;


PTEID_ReaderContext& ReturnReader();
PTEID_EIDCard& ReturnEIDCard();
PTEID_EId& ReturnEID();
PTEID_Pin& ReturnADDR_PIN();
PTEID_Pin& ReturnAUTH_PIN();
bool checkUser(char pinInserted[100]);
bool checkIDUser(char user[]);
string getFullName();


int main() {
	char user[] = "152863567";
	string p;
	//PTEID_InitSDK();

	do{
		cout << "===============================" << endl;
		cout << "           LOG IN" << endl;
		cout << "===============================" << endl;
		cout << "\n\n\nPress any to continue..." << endl;
		cout << "Press 0 to leave..." << endl;
		cout << "\n\n\n===============================" << endl;
		cout << "===============================" << endl;
		cin >> p;

		if (p != "0") {
			system("CLS");
			cout << "===============================" << endl;
			cout << "           LOG IN" << endl;
			cout << "===============================" << endl;
			cout << "\n\n\nInsert the Password (PIN da Morada)..." << endl;
			cout << "\n\n\n===============================" << endl;
			cout << "===============================" << endl;

			char csPin[1000];
			cin >> csPin;

			
			/*p = "0";*/
			if (checkUser(csPin) == 0 && checkIDUser(user) == 0) {
				system("CLS");
				cout << "===============================" << endl;
				cout << "           MENU" << endl;
				cout << "===============================" << endl;
				cout << "\n\n\nWelcome " << getFullName() << endl;
				cout << "\n\n\n Press 0 to leave... " << endl;
				cout << "\n\n\n===============================" << endl;
				cout << "===============================" << endl;
					
				p = "a";
				cin >> p;
			}		
		}
	} while (p != "0");

	//PTEID_ReleaseSDK();
	return 0;
}






//RETURN THE SMART CARD READER CONNECTED TO THE SYSTEM
PTEID_ReaderContext& ReturnReader() {
	PTEID_InitSDK();

	PTEID_ReaderContext& readerC = PTEID_ReaderSet::instance().getReader();
	return readerC;

	PTEID_ReleaseSDK();
}



//RETURN THE EIDCard OBJECT
PTEID_EIDCard& ReturnEIDCard() {
	PTEID_InitSDK();

	try {
		PTEID_EIDCard& eIDCard = ReturnReader().getEIDCard();
		return eIDCard;
	}
	catch (PTEID_ExNoReader& e)
	{
		std::cerr << "No readers found!" << std::endl;
	}
	catch (PTEID_ExNoCardPresent& e)
	{
		std::cerr << "No card found in the reader!" << std::endl;
	}
	catch (PTEID_Exception& e)
	{
		std::cerr << "Caught exception in some SDK method. Error: " << e.GetMessage() << std::endl;
	}

	PTEID_ReleaseSDK();
}



//RETURN THE eID OBJECT
PTEID_EId& ReturnEID() {
	PTEID_InitSDK();

	try {
		PTEID_EId& eid = ReturnEIDCard().getID();
		return eid;
	}
	catch (PTEID_ExNoReader& e)
	{
		std::cerr << "No readers found!" << std::endl;
	}
	catch (PTEID_ExNoCardPresent& e)
	{
		std::cerr << "No card found in the reader!" << std::endl;
	}
	catch (PTEID_Exception& e)
	{
		std::cerr << "Caught exception in some SDK method. Error: " << e.GetMessage() << std::endl;
	}

	PTEID_ReleaseSDK();
}



//GET ADDRESS PIN
PTEID_Pin& ReturnADDR_PIN() {
	PTEID_InitSDK();

	PTEID_Pins& pins = ReturnEIDCard().getPins();
	PTEID_Pin& pin = pins.getPinByPinRef(PTEID_Pin::ADDR_PIN);
	return pin;

	PTEID_ReleaseSDK();
}



//GET AUTHENTICATION PIN
PTEID_Pin& ReturnAUTH_PIN() {
	PTEID_InitSDK();

	PTEID_Pins& pins = ReturnEIDCard().getPins();
	PTEID_Pin& pin = pins.getPinByPinRef(PTEID_Pin::AUTH_PIN);
	return pin;

	PTEID_ReleaseSDK();
}



//CHECK IF THE PASSWORD IS CORRECT 
bool checkUser(char pinInserted[100]) {
	PTEID_InitSDK();

	PTEID_Pin& pinAUTH = ReturnAUTH_PIN();
	unsigned long triesLeft;
	bool a = pinAUTH.verifyPin(pinInserted, triesLeft, true);
	return a;

	PTEID_ReleaseSDK();
}



//CHECK IF THE Civilian ID Number is the same as in the database
bool checkIDUser(char user[]) {
	PTEID_InitSDK();

	try {
		PTEID_EId& userI = ReturnEID();
		bool a = strcmp(userI.getCivilianIdNumber(), user);
		return a;
	}
	catch (PTEID_ExNoReader& e)
	{
		std::cerr << "No readers found!" << std::endl;
	}
	catch (PTEID_ExNoCardPresent& e)
	{
		std::cerr << "No card found in the reader!" << std::endl;
	}
	catch (PTEID_Exception& e)
	{
		std::cerr << "Caught exception in some SDK method. Error: " << e.GetMessage() << std::endl;
	}

	PTEID_ReleaseSDK();
}



//RETURN THE NAME AND SURNAME OF THE USER
string getFullName() {
	PTEID_InitSDK();

	PTEID_EId& userN = ReturnEID();
	string name = userN.getGivenName();
	string surname = userN.getSurname();
	string fullname = name + " " + surname;
	return fullname;

	PTEID_ReleaseSDK();
}