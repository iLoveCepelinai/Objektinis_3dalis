#ifndef _DLL_H_
#define _DLL_H_

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) //suteikiame kita pavadinima del savo patogumo
#else
#define DLL_API __declspec(dllimport)
#endif

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;
using std::ofstream;
using std::setw;
using std::fstream;
using std::ifstream;

extern "C"
class DLL_API Zmogus {
protected:
	string vardas_;
	string pavard_;

	Zmogus(string vardas, string pavarde) :
		vardas_{ vardas },
		pavard_{ pavarde }	{}
public:
	virtual string getVardas() = 0;
	virtual string getPavard() = 0;
};

extern "C"
class DLL_API Studentas : public Zmogus {
private:
	int egz_;
	vector<int> nd_;
	float galut_;
public:
	Studentas(string vardas, string pavarde, vector<int> nd, int egz) :
		Zmogus{ vardas, pavarde },
		nd_{ nd },
		egz_{ egz },
		galut_{ 0 } {}

	//copy construktirius
	/*Studentas(const Studentas& s) :
		vardas_{ s.vardas_ },
		pavard_{ s.pavard_ },
		egz_{ s.egz_ },
		galut_{ s.galut_ },
		nd_{ s.nd_ } {}*/

		/*
		//copy priskyrimo operatorius
		Studentas& operator=(const Studentas& s) {
			if (&s == this) return *this;
			vardas_ = s.vardas_;
			pavard_ = s.pavard_;
			egz_ = s.egz_;
			galut_ = s.galut_;
			nd_ = s.nd_;
			//delete s.nd_;
			return *this;
		}*/

		/*Studentas(Studentas&& s) :
			vardas_{ s.vardas_ },
			pavard_{ s.pavard_ },
			egz_{ s.egz_ },
			galut_{s.galut_},
			nd_{ std::move(s.nd_) } {}

		Studentas(const Studentas&) = default;*/

	~Studentas() { nd_.clear(); }

	void galutinisVid() {
		int suma = std::accumulate(std::begin(nd_), std::end(nd_), 0);
		float vid = suma * 1.0 / size(nd_);
		galut_ = 0.6 * egz_ + 0.4 * vid;
	}

	void galutinisMed() {
		std::sort(nd_.begin(), nd_.end());
		int dydis = size(nd_);
		float mediana;
		if (dydis % 2 == 0) {
			mediana = (nd_.at((dydis * 1.0) / 2 - 1) * 1.0 + nd_.at(dydis / 2)) * 1.0 / 2;
		}
		else {
			int index = (dydis * 1.0 - 1) / 2 + 0.5;
			mediana = nd_.at(index);
		}
		galut_ = 0.6 * egz_ + 0.4 * mediana;
	}

	float getGal() {
		return galut_;
	}

	int getEgz() {
		return egz_;
	}

	string getVardas() {
		return vardas_;
	}

	string getPavard() {
		return pavard_;
	}

	bool gavoSkola() {
		return galut_ < 5;
	}
};

extern "C"
struct DLL_API studentas {
	string vardas, pavard;
	vector <float> nd;
	float egz, galut;
};

extern "C"
DLL_API void failuKurimas(int, int);

extern "C"
DLL_API void skaitymasKlase(int, vector <Studentas>&, string);

extern "C"
DLL_API void skirstymasKlase(vector <Studentas>&, vector <Studentas>&);

extern "C"
DLL_API void surasymasKlase(vector <Studentas>, vector <Studentas>, string, string);

extern "C"
DLL_API void skaitymasStruct(int, vector <studentas>&, string);

extern "C"
DLL_API void skirstymasStruct(vector <studentas>&, vector <studentas>&);

extern "C"
DLL_API void surasymasStruct(vector <studentas>, vector <studentas>, string, string);

extern "C"
DLL_API bool arSkolaKlase(Studentas);

extern "C"
DLL_API bool arSkolaStruct(studentas);

#endif // !_DLL_H_
