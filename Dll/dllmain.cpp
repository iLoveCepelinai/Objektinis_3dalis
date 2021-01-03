// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Dll.h"



void failuKurimas(int ndkiekis, int studkiekis) {
    string tempVardas;
    string tempPavarde;

    string failopav = to_string(studkiekis);
    failopav += ".txt";

    ofstream failas(failopav);
    failas << setw(20) << "Vardas" << setw(20) << "Pavarde" << "\t";

    for (int i = 1; i <= ndkiekis; i++) {
        failas << "ND" << i << "\t";
    }

    failas << "Egz.";

    //pradedame irasineti duomenis
    for (int j = 1; j <= studkiekis; j++) {
        failas << endl;

        tempVardas = "Vardas" + to_string(j);
        failas << setw(20) << tempVardas;

        tempPavarde = "Pavarde" + to_string(j);
        failas << setw(20) << tempPavarde << "\t";

        for (int i = 1; i <= ndkiekis; i++) {
            failas << std::rand() % 10 + 1 << "\t";
        }

        failas << std::rand() % 10 + 1;
    }
    failas.close();
}

//--------------------KLASES--------------------//

void skaitymasKlase(int studkiekis, vector <Studentas>& grupele, string pasirinkimas) {
    auto start = std::chrono::high_resolution_clock::now();

    ifstream failas;
    string sVardai, sPavardes, sTemp, egzaminas;
    vector <string> ndMasyv;
    int m;  //namu darbu kiekis

    string failoPav = to_string(studkiekis);
    failoPav += ".txt";

    try {
        failas.open(failoPav);
    }
    catch (std::exception& e) {
        cout << "Failas " << failoPav << " nebuvo rastas" << endl;
    }

    try {
        if (!failas.good()) {
            throw failoPav;
        }
        failas >> sVardai >> sPavardes >> sTemp;
        while (sTemp != "Egz.") {
            ndMasyv.push_back(sTemp);
            failas >> sTemp;
        }
        egzaminas = sTemp;  //sie nuskaitymai pades tureti stulpeliu vardus, bet svarbiausia: bus zinomas namu darbu kiekis

        m = ndMasyv.size();
        ndMasyv.clear();

        string vardas, pavarde;
        int egz = 0;
        vector <int> pazymiai;

        grupele.reserve(studkiekis);

        while (!failas.eof()) { //skaito iki kol atsimusa i failo pabaiga
            failas >> vardas >> pavarde;

            int laikPaz;
            pazymiai.reserve(m);

            for (int i = 0; i < m; i++) {
                failas >> laikPaz;
                pazymiai.push_back(laikPaz);
            }

            failas >> egz;

            Studentas temp(vardas, pavarde, pazymiai, egz);
            pazymiai.clear();
            grupele.push_back(temp);
        }
        failas.close();
    }
    catch (string pav) {
        cout << pav << " failas neegzistuoja arba jo nepavyko atidaryti\n";
    }
    if (pasirinkimas == "vid") {
        for (auto& studentas : grupele) {
            studentas.galutinisVid();
        }
    }
    else {
        for (auto& studentas : grupele) {
            studentas.galutinisMed();
        }
    }
    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "Surasymas i klases ir klasiu surasymas i vektoriu uztruko: " << diff.count() << "s" << endl;
}

void skirstymasKlase(vector <Studentas>& grupele, vector <Studentas>& dundukai) {
    auto start = std::chrono::high_resolution_clock::now();

    int grupeDydis = size(grupele);
    dundukai.reserve(grupeDydis * 0.5);

    vector<Studentas>::iterator it = std::partition(grupele.begin(), grupele.end(), arSkolaKlase);
    std::move(grupele.begin(), it, back_inserter(dundukai));
    grupele.erase(grupele.begin(), it);

    /*
    while (it != grupele.end()) {
        if ((*it).gavoSkola()) {
            dundukai.push_back(*it); // dereference *it kad gauti element?
            it = grupele.erase(it); // perduodame it, gauname it
        }
        else
            ++it; // pereiti prie kito studento
    }*/

    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "Klase rusiavimas ir skirstymas i 2 vektorius uztruko: " << diff.count() << "s" << endl;
}

void surasymasKlase(vector <Studentas> dundukai, vector <Studentas> sukciukai, string pavDundukai, string pavSukciukai) {
    auto start = std::chrono::high_resolution_clock::now();
    ofstream failD(pavDundukai); // kuriame dunduku faila
    failD << setw(20) << "Vardas" << setw(20) << "Pavarde" << "\t" << "Galutinis";

    for (auto& dundukas : dundukai) {
        failD << endl;
        failD << setw(20) << dundukas.getVardas() << setw(20) << dundukas.getPavard() << "\t" << dundukas.getGal();
    }
    failD.close();

    ofstream failS(pavSukciukai); // kuriame sukckiuku faila
    failS << setw(20) << "Vardas" << setw(20) << "Pavarde" << "\t" << "Galutinis";
    for (auto& sukciukas : sukciukai) {
        failS << endl;
        failS << setw(20) << sukciukas.getVardas() << setw(20) << sukciukas.getPavard() << "\t" << sukciukas.getGal();
    }
    failS.close();

    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "Surasymas i 2 failus uztruko: " << diff.count() << "s" << endl;
}

//-------------------STRUCTAI-------------------//

void skaitymasStruct(int studkiekis, vector <studentas>& grupele, string pasirinkimas) {
    auto start = std::chrono::high_resolution_clock::now();
    ifstream failas;
    string sVardai, sPavardes, sTemp, egzaminas;
    vector <string> ndMasyv;
    int m;  //namu darbu kiekis

    string failoPav = to_string(studkiekis);
    failoPav += ".txt";


    try {
        failas.open(failoPav);
    }
    catch (std::exception& e) {
        cout << "Failas " << failoPav << " nebuvo rastas" << endl;
    }

    try {
        if (!failas.good()) {
            throw failoPav;
        }
        failas >> sVardai >> sPavardes >> sTemp;
        while (sTemp != "Egz.") {
            ndMasyv.push_back(sTemp);
            failas >> sTemp;
        }
        egzaminas = sTemp;  //sie nuskaitymai pades tureti stulpeliu vardus, bet svarbiausia: bus zinomas namu darbu kiekis

        m = ndMasyv.size();
        ndMasyv.clear();

        while (!failas.eof()) { //skaito iki kol atsimusa i failo pabaiga
            studentas laik;
            failas >> laik.vardas >> laik.pavard;

            float laikPaz;

            for (int i = 0; i < m; i++) {
                failas >> laikPaz;
                laik.nd.push_back(laikPaz);
            }

            failas >> laik.egz;
            grupele.push_back(laik);
            laik.nd.clear();
        }
        failas.close();
    }
    catch (string pav) {
        cout << pav << " failas neegzistuoja arba jo nepavyko atidaryti\n";
    }


    //skaiciavimas pagal vidurki:
    if (pasirinkimas == "vid") {
        float suma;
        float vid = 0;
        for (auto& studenciokas : grupele) {
            suma = std::accumulate(std::begin(studenciokas.nd), std::end(studenciokas.nd), 0.0);
            vid = suma / m;
            studenciokas.galut = 0.6 * studenciokas.egz + 0.4 * vid;
        }
    }

    //skaiciavimas pagal mediana:
    else {
        double mediana;
        for (auto& studenciokas : grupele) {
            std::sort(studenciokas.nd.begin(), studenciokas.nd.end());
            if (m % 2 == 0) {
                mediana = (studenciokas.nd.at((m * 1.0) / 2 - 1) + studenciokas.nd.at(m / 2)) / 2;
            }
            else {
                int index = (m * 1.0 - 1) / 2 + 0.5;
                mediana = studenciokas.nd.at(index);
            }
            studenciokas.galut = 0.6 * studenciokas.egz + 0.4 * mediana;
        }
    }
    std::chrono::duration<float> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "Skaitymas nuo failo ir surasymas i structus uztruko: " << diff.count() << "s" << endl;
}

void skirstymasStruct(vector <studentas>& grupele, vector <studentas>& dundukai) {
    auto start = std::chrono::high_resolution_clock::now();

    int grupeDydis = size(grupele);
    dundukai.reserve(grupeDydis * 0.5);

    vector<studentas>::iterator it = std::partition(grupele.begin(), grupele.end(), arSkolaStruct);
    std::move(grupele.begin(), it, back_inserter(dundukai));
    grupele.erase(grupele.begin(), it);

    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "Struct rusiavimas ir skirstymas i 2 vektorius uztruko: " << diff.count() << "s" << endl;
}

void surasymasStruct(vector <studentas> dundukai, vector <studentas> sukciukai, string pavDundukai, string pavSukciukai) {
    auto start = std::chrono::high_resolution_clock::now();
    ofstream failD(pavDundukai); // kuriame dunduku faila
    int ndKiekis = dundukai.front().nd.size();    //paimame belenkoki vektoriaus elementa (studenta) ir patikriname kiek jis turi nd

    failD << setw(20) << "Vardas" << setw(20) << "Pavarde" << "\t" << "Galut.";

    for (auto& dundukas : dundukai) {
        failD << endl;
        failD << setw(20) << dundukas.vardas << setw(20) << dundukas.pavard << "\t" << dundukas.galut;
    }
    failD.close();

    ofstream failS(pavSukciukai); // kuriame sukciuku faila

    failS << setw(20) << "Vardas" << setw(20) << "Pavarde" << "\t" << "Galut.";

    for (auto& sukciukas : sukciukai) {
        failS << endl;
        failS << setw(20) << sukciukas.vardas << setw(20) << sukciukas.pavard << "\t" << sukciukas.galut;
    }
    failS.close();
    std::chrono::duration<float> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "2 sarasu surasymas i 2 failus uztruko: " << diff.count() << "s" << endl;
}

//------------Pagalbines funkcijos--------------//

bool arSkolaKlase(Studentas stud) {
    return stud.gavoSkola();
}

bool arSkolaStruct(studentas stud) {
    return stud.galut < 5;
}

