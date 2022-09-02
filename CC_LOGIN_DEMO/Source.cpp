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


int main() {
	char user[] = "152863567";
	string p;
	PTEID_InitSDK();

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

			try {
				PTEID_ReaderSet& readerSet = PTEID_ReaderSet::instance();
				PTEID_ReaderContext& readerContext = PTEID_ReaderSet::instance().getReader();
				PTEID_EIDCard& eidCard = readerContext.getEIDCard();
				PTEID_EId& eid = eidCard.getID();
				PTEID_Pins& pins = eidCard.getPins();
				
				unsigned long triesLeft;
				//Get the specific PIN object needed
				//ADDR_PIN - Address Pin
				//AUTH_PIN - Authentication Pin
				//SIGN_PIN - Signature Pin
				//MUDAR PARA AUTHENTICATION PIN
				PTEID_Pin& pin = pins.getPinByPinRef(PTEID_Pin::ADDR_PIN);
				p = "0";
				if (pin.verifyPin(csPin, triesLeft, true) && strcmp(eid.getCivilianIdNumber(), user) == 0) {
					system("CLS");
					cout << "===============================" << endl;
					cout << "           MENU" << endl;
					cout << "===============================" << endl;
					cout << "\n\n\nWelcome " << eid.getGivenName() << " " << eid.getSurname() << endl;
					cout << "\n\n\n Press 0 to leave... " << endl;
					cout << "\n\n\n===============================" << endl;
					cout << "===============================" << endl;
					
					p = "a";
					cin >> p;
				}
			}
			catch (PTEID_ExNoReader& e)
			{
				std::cerr << "No readers found!" << std::endl;
				p = "0";
			}
			catch (PTEID_ExNoCardPresent& e)
			{
				std::cerr << "No card found in the reader!" << std::endl;
				p = "0";
			}
			catch (PTEID_Exception& e)
			{
				std::cerr << "Caught exception in some SDK method. Error: " << e.GetMessage() << std::endl;
				p = "0";
			}		
			PTEID_ReleaseSDK();
		}
	} while (p != "0");
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

	PTEID_EIDCard& eIDCard = ReturnReader().getEIDCard();
	return eIDCard;

	PTEID_ReleaseSDK();
}



//RETURN THE eID OBJECT
PTEID_EId& ReturnEID() {
	PTEID_InitSDK();

	PTEID_EId& eid = ReturnEIDCard().getID();
	return eid;

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
//IF RETURN 1 IS FALSE 
//IF RETURN 0 IS TRUE
bool checkUser(char pinInserted[100]) {
	PTEID_InitSDK();

	PTEID_Pin& pinAUTH = ReturnAUTH_PIN();
	unsigned long triesLeft;
	bool a = pinAUTH.verifyPin(pinInserted, triesLeft, true);
	return a;

	PTEID_ReleaseSDK();
}

