#include "../Dll/Dll.h"

int main() {
	vector <Studentas> grupe, dundukai;
	vector <studentas> grupeS, dundukaiS;
	vector <int> pazymiai;

	string pasirinkimas;

	do {
		cout << "Iveskite pagal ka skaiciuosite vidurki (vid/med)" << endl;
		cin >> pasirinkimas;
		try {
			if (pasirinkimas != "vid" && pasirinkimas != "med") {
				throw pasirinkimas;
			}
		}
		catch (string pas) {
			cout << "Jusu ivestas pasirinkimas " << pas << " neatitinka reikalavimu. Kartokite:\n";
		}
	} while (pasirinkimas != "vid" && pasirinkimas != "med");

	cout << "--------------Klases-------------" << endl;
	cout << "-------------100 000-------------" << endl;
	failuKurimas(5, 100000);
	skaitymasKlase(100000, grupe, pasirinkimas);
	skirstymasKlase(grupe, dundukai);
	surasymasKlase(dundukai, grupe, "100000_dundukai.txt", "100000_sukciukai.txt");

	grupe.clear(), dundukai.clear();

	cout << "-------------1 000 000-------------" << endl;
	failuKurimas(5, 1000000);
	skaitymasKlase(1000000, grupe, pasirinkimas);
	skirstymasKlase(grupe, dundukai);
	surasymasKlase(dundukai, grupe, "1000000_dundukai.txt", "1000000_sukciukai.txt");

	grupe.clear(), dundukai.clear();

	cout << "--------------Struct-------------" << endl;
	cout << "-------------100 000-------------" << endl;
	skaitymasStruct(100000, grupeS, pasirinkimas);
	skirstymasStruct(grupeS, dundukaiS);
	surasymasStruct(dundukaiS, grupeS, "100000s_dundukai.txt", "100000s_sukciukai.txt");

	grupeS.clear(), dundukaiS.clear();

	cout << "-------------1 000 000-------------" << endl;
	skaitymasStruct(1000000, grupeS, pasirinkimas);
	skirstymasStruct(grupeS, dundukaiS);
	surasymasStruct(dundukaiS, grupeS, "1000000s_dundukai.txt", "1000000s_sukciukai.txt");

	grupeS.clear(), dundukaiS.clear();

	return 0;
}