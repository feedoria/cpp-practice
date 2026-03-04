#include <iostream>
#include <string>
using namespace std;

class IThrowable
{
public:
	virtual int throwSomething() = 0;
};

class PersonajJoc : public IThrowable
{
protected:
	string nume;
	int nrLovituri;
	int* puncteLovitura;

public:

	// constr default
	PersonajJoc()
	{
		nume = "Anonim";
		nrLovituri = 0;
		puncteLovitura = nullptr;
	}

	// constr toti param
	PersonajJoc(string _nume, int _nrLovituri, int* _puncteLovitura)
	{
		nume = _nume; 
		nrLovituri = _nrLovituri;
		puncteLovitura = new int[nrLovituri];
		for (int i = 0; i < nrLovituri; i++)
		{
			puncteLovitura[i] = _puncteLovitura[i];
		}
	}

	// constr copiere 
	PersonajJoc(const PersonajJoc& pj)
	{
		this->nume = pj.nume;
		this->nrLovituri = pj.nrLovituri;
		this->puncteLovitura = new int[this->nrLovituri];
		for (int i = 0; i < nrLovituri; i++)
		{
			puncteLovitura[i] = pj.puncteLovitura[i];
		}
	}

	// set vector cu puncte lovituri 
	void setLovituri(int _nrLovituri, int* _puncteLovitura)
	{
		delete[] puncteLovitura;
		this->nrLovituri = 0;
		this->nrLovituri = _nrLovituri;
		this->puncteLovitura = new int[nrLovituri];
		for (int i = 0; i < nrLovituri; i++)
		{
			puncteLovitura[i] = _puncteLovitura[i];
		}
	}

	friend ostream& operator<<(ostream& out, const PersonajJoc& pj);

	// supraincarcare operator >= in forma obiect += valoare pt a modif val atribut
	PersonajJoc& operator+=(float valoare)
	{
		int* copie;
		copie = new int[this->nrLovituri+1];
		for (int i = 0; i < nrLovituri; i++)
		{
			copie[i] = puncteLovitura[i];
		}
		copie[this->nrLovituri] = valoare;
		delete[] puncteLovitura;
		this->nrLovituri++;
		puncteLovitura = new int[this->nrLovituri];
		for (int i = 0; i < nrLovituri; i++)
		{
			puncteLovitura[i] = copie[i];
		}
		delete[] copie;
		return *this;
	}

	// >= comparam numele lexicografic
	bool operator>=(const PersonajJoc& pj)
	{
		if (nume.compare(pj.nume) > 0)
			return true;
		else
			return false;
	}
	 
	int throwSomething() override
	{
		int suma = 0; 
		for (int i = 0; i < nrLovituri; i++)
		{
			suma += puncteLovitura[i];
		}
		return suma;
	}

	~PersonajJoc()
	{
		delete[] puncteLovitura;
	}
};

ostream& operator<<(ostream& out, const PersonajJoc& pj)
{
	out << "Numele persj: " << pj.nume << endl;
	out << "Nr lovituri: " << pj.nrLovituri << endl;
	out << "Vectorul cu punctele pt fiecare lovitura: " << endl;
	for (int i = 0; i < pj.nrLovituri; i++)
	{
		out << "Puncte lovitura " << i + 1 << ": " << pj.puncteLovitura[i] << endl;
	}
	return out;
}

enum TipVrajitor
{
	defaultV,
	necromancer,
	elf,
	divine
};

class Vrajitor : public PersonajJoc, public IThrowable
{
	TipVrajitor tipVrajitor = defaultV;
	int numarVraji = 0;

public:
	// constr default
	Vrajitor() : PersonajJoc()
	{

	}
	//constructor cu toti param  explicit
	Vrajitor(string _nume, int _nrLovituri, int* _puncteLovitura, TipVrajitor _tipVrajitor, int _numarVraji) : PersonajJoc(_nume, _nrLovituri, _puncteLovitura)
	{
		tipVrajitor = _tipVrajitor;
		numarVraji = _numarVraji;
	}

	int throwSomething() override
	{
		return PersonajJoc::throwSomething() * 2;
	}

	friend ostream& operator<<(ostream& out, const Vrajitor& w);
};

ostream& operator<<(ostream& out, const Vrajitor& w)
{
	out << (PersonajJoc&)w;
	out << "Tipul vrajitorului: "<<w.tipVrajitor << endl;
	out << "Nr vraji: "<< w.numarVraji << endl;
	return out;
}

int main()
{
	PersonajJoc p1;
	int v1[] = { 1,2,3 };
	PersonajJoc p2("Batman", 3, v1);
	PersonajJoc p3(p2);
	int v2[] = { 5,5 };
	p2.setLovituri(2, v2);
	cout << p1 << p2 << p3;
	cout << "Marim vectorul puncteLovitura si adaugam valoarea 5" << endl;
	p2 += 5;
	cout << "Acum p2 devine: /n"<<p2;
	bool ok = p2 >= p1;
	cout << ok;
	Vrajitor w1("Victor", 3, v1, necromancer, 10);
	cout << w1;
	cout << w1.throwSomething() << endl;
	cout << p3.throwSomething();
	return 0;
}