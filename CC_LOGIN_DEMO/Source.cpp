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
			cout << "\n\n\nInsert the Password (PIN of the CC Card)..." << endl;
			
			char pin_inserted;
			cin >> pin_inserted;

			char cc_pin;
			try {
				PTEID_ReaderSet& readerSet = PTEID_ReaderSet::instance();
				PTEID_ReaderContext& readerContext = readerSet.getReader();
				PTEID_EIDCard& eidCard = readerContext.getEIDCard();
				PTEID_EId& eid = eidCard.getID();
				PTEID_Pins& pins = eidCard.getPins();
				check_login = eid.getCountry();

				for (int i = 0; i < pins.count(); i++) {
					PTEID_Pin& pin = pins.getPinByNumber(i);
					
					if (strcmp(pin.getLabel(), "PIN da Autenticação") == 0) {
						cout << "SUCESSO" << endl;
					}
					else {
						cout << "Nao ao sucesso" << endl;
					}
				}
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
		}
	} while (p != "0");
	PTEID_ReleaseSDK();
	return 0;
}



