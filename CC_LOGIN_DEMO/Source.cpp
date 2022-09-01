#include <iostream>
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

int main() {

	string p;
	string check_login;
	PTEID_InitSDK();
	PTEID_Config::SetTestMode(true); //MODO TESTE!!!!
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
			cout << "\n\n\nInsert the CC Card" << endl;

			try {
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				PTEID_ReaderSet& readerSet = PTEID_ReaderSet::instance();
				PTEID_ReaderContext& readerContext = readerSet.getReader();
				PTEID_EIDCard& eidCard = readerContext.getEIDCard();
				PTEID_EId& eid = eidCard.getID();
				check_login = eid.getCountry();
			}
			catch (PTEID_ExNoReader& e)
			{
				std::cerr << "No readers found!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				p = "0";
			}
			catch (PTEID_ExNoCardPresent& e)
			{
				std::cerr << "No card found in the reader!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				p = "0";
			}
			catch (PTEID_Exception& e)
			{
				std::cerr << "Caught exception in some SDK method. Error: " << e.GetMessage() << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				p = "0";
			}
			if (!check_login.empty()) {
				
				system("CLS");
				cout << "===============================" << endl;
				cout << "           LOG IN" << endl;
				cout << "===============================" << endl;
				cout << "\n\n\nInsert the CC PIN" << endl;

			}
			else {
				
			}
			
		}
	} while (p != "0");
	PTEID_ReleaseSDK();
	return 0;
}



