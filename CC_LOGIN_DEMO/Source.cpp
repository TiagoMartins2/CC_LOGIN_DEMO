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
bool checkADDRPinUser(char pinInserted[100]);
bool checkAUTHPinUser(char pinInserted[100]);
bool checkIDUser(string user);
string getFullName();
int getNumberReaders();
int getNumberTriesAUTH();
int getNumberTriesADDR();
bool checkCardPresent();


int main() {
	string userS = "152863567";
	string p;
	PTEID_InitSDK();

	do{
		system("CLS");
		cout << "===============================" << endl;
		cout << "           LOG IN" << endl;
		cout << "===============================" << endl;
		cout << "\n\n\nPress any to continue..." << endl;
		cout << "Press 0 to leave..." << endl;
		cout << "\n\n\n===============================" << endl;
		cout << "===============================" << endl;
		cin >> p;

		if (getNumberReaders() <= 0) {
			system("CLS");
			cout << "===============================" << endl;
			cout << "     LEITOR NAO ENCONTRADO" << endl;
			cout << "===============================" << endl;
			cout << "\n\n\nPress any to leave..." << endl;
			cout << "\n\n\n===============================" << endl;
			cout << "===============================" << endl;
			string leave;
			cin >> leave;
			p = "0";
		}

		else if (checkCardPresent() == 0) {
			system("CLS");
			cout << "===============================" << endl;
			cout << "     CARTAO NÃO ENCONTRADO" << endl;
			cout << "===============================" << endl;
			cout << "\n\n\nPress any to leave..." << endl;
			cout << "\n\n\n===============================" << endl;
			cout << "===============================" << endl;
			string leave;
			cin >> leave;
			p = "0";
		}

		else if (getNumberTriesADDR() == 0) {
			system("CLS");
			cout << "===============================" << endl;
			cout << "        PIN BLOQUEADO" << endl;
			cout << "===============================" << endl;
			cout << "\n\n\nPress any to leave..." << endl;
			cout << "\n\n\n===============================" << endl;
			cout << "===============================" << endl;
			string leave;
			cin >> leave;
			p = "0";

		}
		else {

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


				if (checkADDRPinUser(csPin) == 1 && checkIDUser(userS) == 1) {
					system("CLS");
					cout << "===============================" << endl;
					cout << "           MENU" << endl;
					cout << "===============================" << endl;
					cout << "\n\n\nWelcome " << getFullName() << endl;
					cout << "\n\n\nPress any to continue..." << endl;
					cout << "\n\n Press 0 to leave... " << endl;
					cout << "\n\n\n===============================" << endl;
					cout << "===============================" << endl;

					cin >> p;
				}
				else if(checkADDRPinUser(csPin) == 0) {
					system("CLS");
					cout << "===============================" << endl;
					cout << "         LOG IN ERROR" << endl;
					cout << "===============================" << endl;
					cout << "\n\n\nWrong PIN inserted" << endl;
					cout << "\nPress any to continue..." << endl;
					cout << "\nPress 0 to leave... " << endl;
					cout << "\n\n\n===============================" << endl;
					cout << "===============================" << endl;
					cin >> p;
				}
				else if(checkIDUser(userS) == 0) {
					system("CLS");
					cout << "===============================" << endl;
					cout << "         LOG IN ERROR" << endl;
					cout << "===============================" << endl;
					cout << "\n\n\nNNo user found with the same ID" << endl;
					cout << "\nPress any to continue..." << endl;
					cout << "\nPress 0 to leave... " << endl;
					cout << "\n\n\n===============================" << endl;
					cout << "===============================" << endl;
					cin >> p;
				}
			}
		}
	} while (p != "0");

	PTEID_ReleaseSDK();
	return 0;
}






//RETURN THE SMART CARD READER CONNECTED TO THE SYSTEM
PTEID_ReaderContext& ReturnReader() {
	
	PTEID_InitSDK();
	
	try {
		PTEID_ReaderContext& readerC = PTEID_ReaderSet::instance().getReader();
		return readerC;
	}
	catch (PTEID_ExNoReader& e)
	{
		std::cerr << "No readers found!555" << std::endl;
	}
	catch (PTEID_Exception& e)
	{
		std::cerr << "Caught exception in some SDK method. Error: " << e.GetMessage() << std::endl;
	}
	
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
		std::cerr << "No readers found!444" << std::endl;
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
		std::cerr << "No readers found!111" << std::endl;
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

	try {
		PTEID_Pins& pins = ReturnEIDCard().getPins();
		PTEID_Pin& pin = pins.getPinByPinRef(PTEID_Pin::ADDR_PIN);
		return pin;
	}
	catch (PTEID_ExNoReader& e)
	{
		std::cerr << "No readers found!222" << std::endl;
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



//GET AUTHENTICATION PIN
PTEID_Pin& ReturnAUTH_PIN() {
	PTEID_InitSDK();

	try {
		PTEID_Pins& pins = ReturnEIDCard().getPins();
		PTEID_Pin& pin = pins.getPinByPinRef(PTEID_Pin::AUTH_PIN);
		return pin;
	}
	catch (PTEID_ExNoReader& e)
	{
		std::cerr << "No readers found!333" << std::endl;
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



//CHECK IF THE ADDRESS PIN IS CORRECT 
bool checkADDRPinUser(char pinInserted[100]) {
	PTEID_InitSDK();

	PTEID_Pin& pinADDR = ReturnADDR_PIN();
	if (pinADDR.getTriesLeft() > 0) {
		unsigned long triesLeft;
		bool a = pinADDR.verifyPin(pinInserted, triesLeft, true);
		return a;
	}
	else {
		cout << "This pin has no more tries left..." << endl;
		return 0;
	}

	PTEID_ReleaseSDK();
}



//CHECK IF THE AUTHENTICATION PIN IS CORRECT 
bool checkAUTHPinUser(char pinInserted[100]) {
	PTEID_InitSDK();

	PTEID_Pin& pinAUTH = ReturnAUTH_PIN();
	if (pinAUTH.getTriesLeft() > 0) {
		unsigned long triesLeft;
		bool a = pinAUTH.verifyPin(pinInserted, triesLeft, true);
		return a;
	}
	else {
		cout << "This pin has no more tries left..." << endl;
		return 0;
	}

	PTEID_ReleaseSDK();
}



//CHECK IF THE Civilian ID Number is the same as in the database
bool checkIDUser(string userS) {
	PTEID_InitSDK();

	try {
		PTEID_EId& userI = ReturnEID();
		string userID = userI.getCivilianIdNumber();
		bool a = userID == userS;
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



//RETURN THE NUMBER OF READERS
int getNumberReaders() {
	PTEID_InitSDK();

	PTEID_ReaderSet& readerSet = PTEID_ReaderSet::instance();
	int reader_count = readerSet.readerCount();
	return reader_count;

	PTEID_ReleaseSDK();
}



//RETURN THE NUMBER OF TRIES LEFT IN AUTH PIN
int getNumberTriesAUTH() {
	PTEID_InitSDK();

	PTEID_Pin& pinAUTH = ReturnAUTH_PIN();
	int tries = pinAUTH.getTriesLeft();
	return tries;

	PTEID_ReleaseSDK();
}



//RETURN THE NUMBER OF TRIES LEFT IN ADDR PIN
int getNumberTriesADDR() {
	PTEID_InitSDK();

	PTEID_Pin& pinADDR = ReturnADDR_PIN();
	int tries = pinADDR.getTriesLeft();
	return tries;

	PTEID_ReleaseSDK();
}



//RETURN THE NUMBER OF EXISTING CARDS
bool checkCardPresent() {
	PTEID_InitSDK();

	PTEID_ReaderContext& readerC = PTEID_ReaderSet::instance().getReader();
	bool cardPresent = readerC.isCardPresent();
	return cardPresent;

	PTEID_ReleaseSDK();
}