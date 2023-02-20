#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Cerinta:
Aplicatie pentru programarea activitatilor la o Sala de fitness oferite de un instructor.
Un instructor se identifica prin id, nume si dispune de un vector dinamic de programari.
O programare contine informatii despre participant, data programarii, durata in ore a sedintei.
*/

class Client
{
private:
	const int idClient;
	string nume;
	int nrOre; //numar ore petrecute la Sala
	float* pretOra; //pret per ora platit de client
	char nr_telefon[50];

public:
	//getteri
	int getidClient()
	{
		return this->idClient;
	}
	string getNume()
	{
		return this->nume;
	}

	int getnrOre()
	{
		return this->nrOre;
	}
	float* getpretOra()
	{
		return this->pretOra;
	}
	char* getNr_telefon()
	{
		return this->nr_telefon;
	}

	//setteri
	void setnume(string nume_)
	{
		this->nume = nume_;
	}

	void setpretOra(float* pretOra, int nrOre_)
	{
		if (nrOre_ != 0 && pretOra != NULL)
		{
			this->nrOre = nrOre_;
			delete[] this->pretOra;
			this->pretOra = new float[this->nrOre];
			for (int i = 0; i < this->nrOre; i++)
			{
				this->pretOra[i] = pretOra[i];
			}
		}
	}

	void setnr_telefon(const char* nr_telefon_)
	{
		if (nr_telefon_ != NULL)
		{
			strcpy(this->nr_telefon, nr_telefon_);
		}
	}

	// Metode

	float medie()
	{
		if (this->pretOra != NULL && this->nrOre != 0)
		{
			float medie = 0;
			for (int i = 0; i < this->nrOre; i++)
			{
				medie = medie + this->pretOra[i];
			}
			medie = medie / this->nrOre;
			return medie;
		}

	}

	float maxim()
	{
		if (this->pretOra != NULL && this->nrOre != 0)
		{


			float max;
			max = this->pretOra[0];
			for (int i = 1; i < this->nrOre; i++)
			{
				if (max < this->pretOra[i])
					max = pretOra[i];
			}
			return max;
		}
	}

	// Constructor
	Client() :idClient(0)
	{

	}

	// Constructor cu 2 parametri
	Client(string nume, char nr_telefon[50]) :idClient(0)
	{
		this->nume = nume;
		this->nrOre = 0;
		this->pretOra = NULL;
		strcpy(this->nr_telefon, nr_telefon);

	}

	// Constructor cu toti parametri
	Client(int idClient, string nume, int nrOre, float* pretOra, const char nr_telefon[50]) :idClient(idClient)
	{
		this->nume = nume;
		if (nrOre != 0 && pretOra != NULL)
		{
			this->nrOre = nrOre;
			this->pretOra = new float[this->nrOre];
			for (int i = 0; i < this->nrOre; i++) {
				this->pretOra[i] = pretOra[i];
			}

		}
		else
		{
			this->nrOre = 0;
			this->pretOra = NULL;
		}
		strcpy(this->nr_telefon, nr_telefon);
	}


	// Constructor de copiere
	Client(const Client& c) :idClient(c.idClient)
	{
		this->nume = c.nume;
		if (c.nrOre != 0 && c.pretOra != NULL)
		{
			this->nrOre = c.nrOre;
			this->pretOra = new float[this->nrOre];
			for (int i = 0; i < this->nrOre; i++) {
				this->pretOra[i] = c.pretOra[i];
			}

		}
		else
		{
			this->nrOre = 0;
			this->pretOra = NULL;
		}
		strcpy(this->nr_telefon, c.nr_telefon);
	}

	//operator =
	Client& operator=(const Client& c)
	{
		delete[] this->pretOra;
		this->nume = c.nume;
		if (c.nrOre != 0 && c.pretOra != NULL)
		{
			this->nrOre = c.nrOre;
			this->pretOra = new float[this->nrOre];
			for (int i = 0; i < this->nrOre; i++) {
				this->pretOra[i] = c.pretOra[i];
			}

		}
		else
		{
			this->nrOre = 0;
			this->pretOra = NULL;
		}
		strcpy(this->nr_telefon, c.nr_telefon);

		return *this;


	}

	friend istream& operator>>(istream& in, Client& c)
	{
		cout << "Clientul este: ";
		in >> c.nume;
		cout << "Nr de ore petrecute: ";
		in >> c.nrOre;
		delete[] c.pretOra;
		if (c.nrOre > 0)
		{
			cout << "Preturile pe ora sunt: ";
			c.pretOra = new float[c.nrOre];
			for (int i = 0; i < c.nrOre; i++)
			{
				in >> c.pretOra[i];
			}
		}
		else
		{
			c.pretOra = NULL;
		}
		cout << "Numarul de telefon este: ";
		char aux[50];
		in >> aux;
		strcpy(c.nr_telefon, aux);
		cout << endl;

		return in;


	}

	friend ostream& operator<<(ostream& out, const Client& v)
	{
		out << "ID-ul clientului este: " << v.idClient << " " << "Numele este: " << v.nume << " " << "Nr de ore petrecute: " << v.nrOre << " " << "Preturile pe ora: ";
		if (v.pretOra != NULL)
		{
			for (int i = 0; i < v.nrOre; i++)
			{
				out << v.pretOra[i] << " ";
			}
		}
		else
			out << "-";
		out << "Numarul de telefon este: " << v.nr_telefon;
		out << endl;

		return out;
	}

	float operator[](int pozitie)
	{
		if (pozitie >= 0 && pozitie < this->nrOre)
		{
			return this->pretOra[pozitie];
		}
		else
			throw exception("Nu este corecta valoarea");

	}


	Client operator--()
	{

		if (this->nrOre > 0 && this->pretOra != NULL)
		{
			Client copie = *this;
			float max = this->pretOra[0];
			int poz = 1;
			for (int i = 1; i < this->nrOre; i++)
			{
				if (max < this->pretOra[i])
				{
					max = this->pretOra[i];
					poz = 1;
				}
				else
				{
					if (this->pretOra[i] == max)
						poz++;
				}
			}

			delete[] this->pretOra;
			this->nrOre -= poz;
			if (this->nrOre > 0)
			{
				this->pretOra = new float[this->nrOre];
				int k = 0;
				for (int i = 0; i < copie.nrOre; i++)
				{
					if (copie.pretOra[i] != max)
						this->pretOra[k++] = copie.pretOra[i];
				}
			}
			else
			{
				this->pretOra = NULL;
			}
			return *this;
		}
	}

	Client operator--(int)
	{
		Client copie = *this;

		if (this->nrOre > 0 && this->pretOra != NULL)
		{
			float max = this->pretOra[0];
			int poz = 1;
			for (int i = 1; i < this->nrOre; i++)
			{
				if (max < this->pretOra[i])
				{
					max = this->pretOra[i];
					poz = 1;
				}
				else
				{
					if (this->pretOra[i] == max)
						poz++;
				}
			}

			delete[] this->pretOra;
			this->nrOre -= poz;
			if (this->nrOre > 0)
			{
				this->pretOra = new float[this->nrOre];
				int k = 0;
				for (int i = 0; i < copie.nrOre; i++)
				{
					if (copie.pretOra[i] != max)
						this->pretOra[k++] = copie.pretOra[i];
				}
			}
			else
			{
				this->pretOra = NULL;
			}
			return copie;
		}
	}

	operator int() // Operator cast care returneaza nr preturilor mai mari de 50
	{
		if (this->nrOre != 0 && this->pretOra != NULL)
		{
			int nr = 0;
			for (int i = 0; i < this->nrOre; i++)
			{
				if (this->pretOra[i] > 50)
				{
					nr = nr + 1;
				}
			}
			return nr;
		}
	}

	Client& operator!()
	{
		delete[] this->pretOra;
		this->pretOra = NULL;
		this->nrOre = 0;
		return *this;
	}

	bool operator>(Client& c)
	{
		if (this->nrOre > c.nrOre)
			return true;
		else
			return false;
	}

	Client operator+(int x)
	{
		if (this->nrOre != 0 && this->pretOra != NULL)
		{
			Client copie = *this;
			for (int i = 0; i < this->nrOre; i++)
			{
				copie.pretOra[i] = this->pretOra[i] + x;
			}

			return copie;
		}

	}

	bool operator==(const Client& c)
	{

		bool ok = 0;
		if (this->idClient == c.idClient && this->nume == c.nume && this->nrOre == c.nrOre && strcmp(this->nr_telefon, c.nr_telefon) == 0)
		{
			int ok = 1;
			if (ok == 1)
			{
				for (int i = 0; i < this->nrOre; i++)

				{
					for (int i = 0; i < c.nrOre; i++)
						if (this->pretOra[i] != c.pretOra[i])
							ok = 0;
				}

			}
			else
				ok = 0;
			return ok;
		}
	}

	~Client()
	{
		delete[] this->pretOra;
	}


	friend ofstream& operator<<(ofstream& out, Client& c)
	{

		out << c.nume << endl;
		out << c.nrOre << endl;
		for (int i = 0; i < c.nrOre; i++)
		{
			out << c.pretOra[i] << " ";

		}
		out << endl;
		out << c.nr_telefon << endl;
		return out;

	}

	friend ifstream& operator>>(ifstream& in, Client& c)
	{
		delete[] c.pretOra;
		in >> c.nume;
		in >> c.nrOre;
		c.pretOra = new float[c.nrOre];
		for (int i = 0; i < c.nrOre; i++)
		{
			in >> c.pretOra[i];
		}
		in >> c.nr_telefon;
		return in;

	}

	void scriereBinar(fstream& file)
	{
		int lg = this->nume.length() + 1;

		file.write((char*)&lg, sizeof(int));
		file.write(this->nume.data(), lg);

		file.write((char*)&this->nrOre, sizeof(int));

		for (int i = 0; i < this->nrOre; i++)
		{
			file.write((char*)&this->pretOra[i], sizeof(float));


		}

		int lg1 = strlen(this->nr_telefon);
		file.write((char*)&lg1, sizeof(int));
		for (int i = 0; i < lg1; i++)
		{
			file.write((char*)&this->nr_telefon[i], sizeof(char));

		}

	}


	void citireBinar(fstream& file)

	{
		delete[] this->pretOra;
		char* buffer;
		int lg = 0;
		file.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		file.read(buffer, lg);
		this->nume = buffer;


		file.read((char*)&this->nrOre, sizeof(int));

		this->pretOra = new float[this->nrOre];
		for (int i = 0; i < this->nrOre; i++)
		{
			file.read((char*)&this->pretOra[i], sizeof(float));

		}

		int lg1;
		file.read((char*)&lg1, sizeof(int));
		for (int i = 0; i < lg1; i++)
		{
			file.read((char*)&this->nr_telefon[i], sizeof(char));

		}
		this->nr_telefon[lg1] = '\0';

	}

};

class Programare
{
protected:
	static int nrProgramari; //atributul static care imi numara nr obiectelor(Programarile)
	bool Premium;
	string numeClient;
	int nrOre; //pentru cat timp fac programarea
	float* garantie;
	char* data_programarii;

public:

	//get si set 
	string getNumeClient()
	{
		return this->numeClient;
	}

	bool getPremium()
	{
		return this->Premium;
	}

	int getnrOre()
	{
		return this->nrOre;

	}

	float* getgarantie()
	{
		return this->garantie;
	}


	char* getdata_programarii()
	{
		return this->data_programarii;
	}

	void setNumeClient(string numeClient)
	{
		this->numeClient = numeClient;
	}

	void setPremium(bool Premium)
	{
		this->Premium = Premium;
	}

	void setgarantie(int nrOre, float* garantie)
	{
		if (garantie != NULL && nrOre != 0)
		{
			delete[] this->garantie;
			this->nrOre = nrOre;
			this->garantie = new float[this->nrOre];
			for (int i = 0; i < this->nrOre; i++)
			{
				this->garantie[i] = garantie[i];
			}

		}
	}


	void setdata_programarii(const char* data_programarii)
	{
		if (data_programarii != NULL)
		{
			this->data_programarii = new char[strlen(data_programarii) + 1];
			strcpy(this->data_programarii, data_programarii);
		}
	}

	Programare()
	{
		this->Premium = 0;
		this->nrOre = 0;
		this->garantie = NULL;

		this->data_programarii = new char[strlen("Data neintrodusa") + 1];
		strcpy(this->data_programarii, "Data neintrodusa");
	}


	//constructor cu 2 parametri
	Programare(const char* data_programarii, bool Premium)
	{
		this->Premium = Premium;
		this->nrOre = 0;
		this->garantie = NULL;
		if (data_programarii != NULL)
		{
			this->data_programarii = new char[strlen(data_programarii) + 1];
			strcpy(this->data_programarii, data_programarii);
		}
		else
		{
			this->data_programarii = NULL;
		}

		nrProgramari++;

	}

	//constructor cu toti parametri
	Programare(bool Premium, int nrOre, float* garantie, const char* data_programarii)
	{
		this->Premium = Premium;
		if (nrOre != 0 && garantie != NULL)
		{
			this->nrOre = nrOre;
			this->garantie = new float[this->nrOre];
			for (int i = 0; i < this->nrOre; i++)
			{
				this->garantie[i] = garantie[i];
			}
		}
		else
		{
			this->garantie = NULL;
			this->nrOre = 0;
		}
		if (data_programarii != NULL)
		{
			this->data_programarii = new char[strlen(data_programarii) + 1];
			strcpy(this->data_programarii, data_programarii);

		}
		else
		{
			this->data_programarii = NULL;
		}
		nrProgramari++;
	}


	//constr de copiere
	Programare(const Programare& p)
	{
		this->Premium = p.Premium;
		if (p.nrOre != 0 && p.garantie != NULL)
		{
			this->nrOre = p.nrOre;
			this->garantie = new float[this->nrOre];
			for (int i = 0; i < this->nrOre; i++)
			{
				this->garantie[i] = p.garantie[i];
			}
		}
		else
		{
			this->garantie = NULL;
			this->nrOre = 0;
		}
		if (p.data_programarii != NULL)
		{
			this->data_programarii = new char[strlen(p.data_programarii) + 1];
			strcpy(this->data_programarii, p.data_programarii);

		}
		else
		{
			this->data_programarii = NULL;

		}
		nrProgramari++;


	}

	//operator=
	Programare& operator=(const Programare& p)
	{
		if (this != &p) {
			delete[] this->garantie;
			delete[] this->data_programarii;
			this->Premium = p.Premium;
			if (p.nrOre != 0 && p.garantie != NULL)
			{
				this->nrOre = p.nrOre;
				this->garantie = new float[this->nrOre];
				for (int i = 0; i < this->nrOre; i++)
				{
					this->garantie[i] = p.garantie[i];
				}
			}
			else
			{
				this->garantie = NULL;
				this->nrOre = 0;
			}
			if (p.data_programarii != NULL)
			{
				this->data_programarii = new char[strlen(p.data_programarii) + 1];
				strcpy(this->data_programarii, p.data_programarii);

			}
			else
			{
				this->data_programarii = new char[strlen("Data neintrodusa") + 1];
				strcpy(this->data_programarii, "Data neintrodusa");;
			}
		}

		return *this;
	}

	// Metoda virtuala care numara garantiile mai mari de 50 de RON
	virtual int numarGarantii()
	{
		if (this->garantie != NULL)
		{
			int nr = 0;
			for (int i = 0; i < this->nrOre; i++)
				if (this->garantie[i] > 50)
					nr++;
			return nr;
		}
	}
	// Metoda virtuala care calculeaza suma garantiilor
	virtual float sumaGarantii()
	{
		if (this->garantie != NULL)
		{
			float suma = 0;
			for (int i = 0; i < this->nrOre; i++)
			{
				suma = suma + this->garantie[i];
			}
			return suma;
		}
	}

	friend ostream& operator<<(ostream& out, Programare& p)
	{
		out << "Este facuta de un client Premium: " << p.Premium << " " << "Nr de ore: " << p.nrOre << " " << "Garantie trimisa: ";
		if (p.garantie != NULL)
		{
			for (int i = 0; i < p.nrOre; i++)
				out << p.garantie[i] << "  ";
		}
		else
		{
			out << "-";
		}
		if (p.data_programarii != NULL)
		{
			out << "Data Programarii: " << p.data_programarii;
		}
		else
			out << "-";

		out << endl;
		return out;
	}

	//operator >>
	friend istream& operator>>(istream& in, Programare& p)
	{
		cout << "Este un client Premium (1 pentru da, 0 pentru nu): ";
		in >> p.Premium;
		cout << "Numar de ore programate: ";
		in >> p.nrOre;
		delete[] p.garantie;
		if (p.nrOre > 0)
		{
			cout << "Garantiile trimise pentru fiecare ora: ";
			p.garantie = new float[p.nrOre];
			for (int i = 0; i < p.nrOre; i++)
			{
				in >> p.garantie[i];
			}
		}
		else
		{
			p.garantie = NULL;
		}
		cout << "Data Programarii: ";
		char aux[50];
		in >> aux;
		delete[] p.data_programarii;
		p.data_programarii = new char[strlen(aux) + 1];
		strcpy(p.data_programarii, aux);

		cout << endl;
		return in;

	}

	int lungimesir()
	{
		if (this->data_programarii != NULL)
		{
			int lungime = 0;
			lungime = strlen(this->data_programarii);
			return lungime;
		}
		else
			return 0;
	}

	float minim()
	{
		if (this->nrOre != 0 && this->garantie != NULL)
		{
			float min = this->garantie[0];
			for (int i = 0; i < this->nrOre; i++)
			{
				if (min > this->garantie[i])
					min = garantie[i];
			}
			return min;
		}
	}


	//operatorul indexare cu posibilitatea de a fi modificat
	float& operator[](int poz)
	{
		if (poz >= 0 && poz < this->nrOre)
		{
			return this->garantie[poz];
		}
		else
			throw exception("Valorea este incorecta");
	}

	Programare operator-(float x)
	{
		if (this->nrOre != 0 && this->garantie != NULL)
		{
			Programare copie = *this;
			for (int i = 0; i < this->nrOre; i++)
			{
				copie.garantie[i] = this->garantie[i] - (x / 100 * this->garantie[i]);
			}

			return copie;
		}

	}

	operator float()
	{
		if (this->nrOre != 0 && this->garantie != NULL)
		{
			float suma = 0;
			for (int i = 0; i < this->nrOre; i++)
			{
				suma = suma + this->garantie[i];
			}
			return suma;


		}
	}

	friend void operator!(Programare& p)
	{

		if (p.Premium == 1)
		{
			p.Premium = 0;
		}
		else
		{
			p.Premium = 1;
		}
	}

	//Operator comparatie - imi compara doua obiecte dupa suma garantiilor
	bool operator>(const Programare& p)
	{
		float suma1 = 0;
		float suma2 = 0;
		for (int i = 0; i < this->nrOre; i++)
		{
			suma1 = suma1 + this->garantie[i];
		}
		for (int i = 0; i < p.nrOre; i++)
		{
			suma2 = suma2 + p.garantie[i];
		}
		if (suma1 > suma2)
			return true;
		else
			return false;

	}



	//operatorul == pentru a testa daca 2 obiecte sunt egale
	bool operator==(const Programare& p)
	{
		bool ok = 1;
		if (this->Premium == p.Premium && this->nrOre == p.nrOre && strcmp(this->data_programarii, p.data_programarii) == 0)
			ok = 1;
		else
			ok = 0;
		if (ok == 1)
		{
			for (int i = 0; i < this->nrOre; i++)
			{
				for (int i = 0; i < p.nrOre; i++)
					if (this->garantie[i] != p.garantie[i])
						ok = 0;
			}
		}
		else
			ok = 0;
		return ok;

	}



	~Programare()
	{
		delete[] this->garantie;
		delete[] this->data_programarii;

	}

	friend ofstream& operator<<(ofstream& out, Programare& p)
	{
		out << p.Premium << endl;
		out << p.nrOre << endl;
		for (int i = 0; i < p.nrOre; i++)
		{
			out << p.garantie[i] << " ";

		}
		out << endl;
		out << p.data_programarii << endl;
		return out;

	}

	friend ifstream& operator>>(ifstream& in, Programare& p)
	{
		delete[] p.garantie;
		delete[] p.data_programarii;
		in >> p.Premium;
		in >> p.nrOre;
		p.garantie = new float[p.nrOre];
		for (int i = 0; i < p.nrOre; i++)
		{
			in >> p.garantie[i];
		}

		char plata[50];
		in >> plata;
		p.data_programarii = new char[strlen(plata) + 1];
		strcpy(p.data_programarii, plata);
		return in;

	}


	//Fisiere Binare
	void scriereBinar(fstream& file)
	{
		file.write((char*)&this->Premium, sizeof(bool));
		file.write((char*)&this->nrOre, sizeof(int));
		for (int i = 0; i < this->nrOre; i++)
		{
			file.write((char*)&this->garantie[i], sizeof(float));


		}
		int lg = strlen(this->data_programarii);
		file.write((char*)&lg, sizeof(int));
		for (int i = 0; i < lg; i++)
		{
			file.write((char*)&this->data_programarii[i], sizeof(char));

		}


	}

	void citireBinar(fstream& file)
	{
		delete[] this->garantie;
		delete[] this->data_programarii;

		file.read((char*)&this->Premium, sizeof(bool));
		file.read((char*)&this->nrOre, sizeof(int));

		this->garantie = new float[this->nrOre];
		for (int i = 0; i < this->nrOre; i++)
		{
			file.read((char*)&this->garantie[i], sizeof(float));

		}
		int lg;
		file.read((char*)&lg, sizeof(int));
		this->data_programarii = new char[lg + 1];
		for (int i = 0; i < lg; i++)
		{
			file.read((char*)&this->data_programarii[i], sizeof(char));

		}
		this->data_programarii[lg] = '\0';

	}

};
int Programare::nrProgramari = 0;

class Sala
{
private:
	int nrLocuri;
	int* nrAparate;
	float suprafata;
	char* numeSala;

public:

	//get si set

	int getnrLocuri()
	{
		return this->nrLocuri;
	}

	int* getnrAparate()
	{
		return this->nrAparate;
	}
	float getSuprafata()
	{
		return this->suprafata;
	}
	char* getnumeSala()
	{
		return this->numeSala;
	}

	void setLocuriSala(int nrLocuri, int* nrAparateCamera)
	{
		if (nrLocuri != 0 && nrAparateCamera != NULL)

		{
			delete[] this->nrAparate;
			this->nrLocuri = nrLocuri;
			this->nrAparate = new int[this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
			{
				this->nrAparate[i] = nrAparateCamera[i];
			}
		}
	}

	void setSuprafata(float suprafataNoua)
	{
		this->suprafata = suprafataNoua;
	}

	void setNumeSala(const char* numeSala)
	{
		if (numeSala != NULL)
		{

			this->numeSala = new char[strlen(numeSala) + 1];
			strcpy(this->numeSala, numeSala);
		}
	}

	Sala()
	{

		this->nrLocuri = 0;
		this->nrAparate = NULL;


		this->suprafata = 0;
		this->numeSala = new char[strlen("Necunoscut") + 1];
		strcpy(this->numeSala, "Necunoscut");

	}
	//constructor cu 3 parametri
	Sala(int nrLocuri, int* nrAparate, float suprafata)
	{
		if (nrLocuri != 0 && nrAparate != NULL)
		{
			this->nrLocuri = nrLocuri;
			this->nrAparate = new int[this->nrLocuri];

			for (int i = 0; i < this->nrLocuri; i++)
			{
				this->nrAparate[i] = nrAparate[i];
			}
		}
		else
		{
			this->nrLocuri = 0;
			this->nrAparate = NULL;


		}

		this->suprafata = suprafata;
		this->numeSala = NULL;

	}

	//constructor cu toti parametri
	Sala(int nrLocuri, int* nrAparate, float suprafata, const char* numeSala)
	{
		if (nrLocuri != 0 && nrAparate != NULL)
		{
			this->nrLocuri = nrLocuri;
			this->nrAparate = new int[this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
			{
				this->nrAparate[i] = nrAparate[i];
			}
		}
		else
		{
			this->nrLocuri = 0;
			this->nrAparate = NULL;
		}
		this->suprafata = suprafata;
		if (numeSala != NULL)
		{
			this->numeSala = new char[strlen(numeSala) + 1];
			strcpy(this->numeSala, numeSala);

		}
		else
		{
			this->numeSala = NULL;
		}
	}

	//constructor de copiere

	Sala(const Sala& s)
	{
		if (s.nrLocuri != 0 && s.nrAparate != NULL)
		{
			this->nrLocuri = s.nrLocuri;
			this->nrAparate = new int[this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
			{
				this->nrAparate[i] = s.nrAparate[i];
			}
		}
		else
		{
			this->nrLocuri = 0;
			this->nrAparate = NULL;
		}
		this->suprafata = s.suprafata;
		if (s.numeSala != NULL)
		{
			this->numeSala = new char[strlen(s.numeSala) + 1];
			strcpy(this->numeSala, s.numeSala);

		}
		else
		{
			this->numeSala = NULL;
		}
	}

	//operatorul=
	Sala& operator=(const Sala& s)
	{
		delete[] this->numeSala;
		delete[] this->nrAparate;
		if (s.nrLocuri != 0 && s.nrAparate != NULL)
		{
			this->nrLocuri = s.nrLocuri;
			this->nrAparate = new int[this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
			{
				this->nrAparate[i] = s.nrAparate[i];
			}
		}
		else
		{
			this->nrLocuri = 0;
			this->nrAparate = NULL;
		}
		this->suprafata = s.suprafata;
		if (s.numeSala != NULL)
		{
			this->numeSala = new char[strlen(s.numeSala) + 1];
			strcpy(this->numeSala, s.numeSala);

		}
		else
		{
			this->numeSala = new char[strlen("Anonim") + 1];
			strcpy(this->numeSala, "Anonim");
		}
		return *this;

	}

	friend ostream& operator<<(ostream& out, Sala& s)
	{
		out << "Nr de locuri este: " << s.nrLocuri << " " << "Nr aparate disponibile: ";
		if (s.nrAparate != NULL)
		{
			for (int i = 0; i < s.nrLocuri; i++)
				out << s.nrAparate[i] << " ";
		}
		else
			out << "-";
		out << "Suprafata salii: " << s.suprafata << " " << "Numele salii: ";
		if (s.numeSala != NULL)
		{
			out << s.numeSala << " ";
		}
		else
		{
			out << "-";
		}
		out << endl;
		return out;
	}

	//operator>>

	friend istream& operator>>(istream& in, Sala& s)
	{
		cout << "Numarul de locuri: ";
		in >> s.nrLocuri;
		cout << "Nr aparate disponibile/persoana: ";
		delete[] s.nrAparate;
		if (s.nrLocuri > 0)
		{
			s.nrAparate = new int[s.nrLocuri];
			for (int i = 0; i < s.nrLocuri; i++)
			{
				in >> s.nrAparate[i];
			}
		}
		else
			s.nrAparate = NULL;
		cout << "Suprafata salii: ";
		in >> s.suprafata;
		cout << "Numele salii: ";
		char aux[50];
		in >> aux;
		if (aux != NULL)
		{
			s.numeSala = new char[strlen(aux) + 1];
			strcpy(s.numeSala, aux);
		}
		else
		{
			s.numeSala = NULL;
		}
		cout << endl;
		return in;
	}

	// Metoda care calculeaza diferenta de suprafata intre 2 sali
	float diferentaSuprafata(Sala& s)
	{
		if (this->suprafata > 0 && s.suprafata > 0)
		{
			float diferenta = 0;
			diferenta = abs(this->suprafata - s.suprafata); //imi calculeaza modulul
			return diferenta;
		}
	}

	// Operator indexare - returneaza nr de aparate corespunzator salii data ca parametru
	int operator[](int sala)
	{
		if (sala >= 0 && sala < this->nrLocuri)
		{
			return this->nrAparate[sala];
		}
		else
			throw exception("Valoarea este incorecta: ");
	}


	//operator+
	Sala operator+(const Sala& s)
	{
		Sala rez = *this;
		delete[] rez.nrAparate;
		rez.nrLocuri = this->nrLocuri + s.nrLocuri;
		rez.nrAparate = new int[rez.nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++)
		{
			rez.nrAparate[i] = this->nrAparate[i];
		}
		for (int i = this->nrLocuri; i < rez.nrLocuri; i++)
		{
			rez.nrAparate[i] = s.nrAparate[i - this->nrLocuri];

		}
		return rez;

	}

	~Sala()
	{
		delete[] this->nrAparate;
		delete[] this->numeSala;
	}

	//operator++
	Sala& operator++()
	{
		this->suprafata++;
		return *this;

	}

	Sala operator++(int)
	{
		Sala copie = *this;
		this->suprafata++;
		return copie;

	}

	//operator CAST- MEDIA NR DE APARATE 
	operator float()
	{
		if (this->nrLocuri != 0 && this->nrAparate != NULL)
		{
			float medie = 0;
			for (int i = 0; i < this->nrLocuri; i++)
			{
				medie = medie + this->nrAparate[i];
			}
			medie = medie / this->nrLocuri;
			return medie;
		}
	}

	//operatorul negatie-anuleaza numeSala
	Sala& operator!()
	{
		delete[] this->numeSala;
		this->numeSala = NULL;
		return *this;
	}


	//operatorul de comparatie-compara nr de camere a doua Sali(obiecte)
	bool operator>=(const Sala& s)
	{
		if (this->nrLocuri >= s.nrLocuri)
			return true;
		else
			return false;
	}

	//operatorul == - testam egalitatea a doua obiecte

	bool egalitate(const  Sala& s)
	{
		bool ok = 1;
		if (this->nrLocuri == s.nrLocuri && this->suprafata == s.suprafata && strcmp(this->numeSala, s.numeSala) == 0)
			ok = 1;
		else
			ok = 0;
		if (ok == 1)
		{
			for (int i = 0; i < this->nrLocuri; i++)
			{
				for (int i = 0; i < s.nrLocuri; i++)
					if (this->nrAparate != s.nrAparate)
						ok = 0;

			}
		}
		return ok;
	}

	// Fisiere Text
	friend ofstream& operator<<(ofstream& out, Sala& s)
	{
		out << s.nrLocuri << endl;
		for (int i = 0; i < s.nrLocuri; i++)
		{
			out << s.nrAparate[i] << " ";

		}
		out << endl;
		out << s.suprafata << endl;
		out << s.numeSala << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Sala& s)
	{

		delete[] s.nrAparate;
		delete[] s.numeSala;
		in >> s.nrLocuri;
		s.nrAparate = new int[s.nrLocuri];
		for (int i = 0; i < s.nrLocuri; i++)
		{
			in >> s.nrAparate[i];

		}
		in >> s.suprafata;
		char nume[50];
		in >> nume;
		s.numeSala = new char[strlen(nume) + 1];
		strcpy(s.numeSala, nume);
		return in;
	}



	//Fisiere binare

	void scriereBinar(fstream& file)
	{
		file.write((char*)&this->nrLocuri, sizeof(int));
		for (int i = 0; i < this->nrLocuri; i++)
		{
			file.write((char*)&this->nrAparate[i], sizeof(int));

		}
		file.write((char*)&this->suprafata, sizeof(float));
		int lg = strlen(this->numeSala);
		file.write((char*)&lg, sizeof(int));
		for (int i = 0; i < lg; i++)
		{
			file.write((char*)&this->numeSala[i], sizeof(char));

		}


	}

	void citireBinar(fstream& file)
	{
		delete[] this->nrAparate;
		delete[] this->numeSala;
		file.read((char*)&this->nrLocuri, sizeof(int));
		this->nrAparate = new int[this->nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++)
		{
			file.read((char*)&this->nrAparate[i], sizeof(float));
		}

		file.read((char*)&this->suprafata, sizeof(float));
		int lg;
		file.read((char*)&lg, sizeof(int));
		this->numeSala = new char[lg + 1];
		for (int i = 0; i < lg; i++)
		{
			file.read((char*)&this->numeSala[i], sizeof(char));

		}
		this->numeSala[lg] = '\0';


	}


};



class Interfata
{
public:
	//metode virtual pura
	virtual void writeToFile(fstream& file) = 0;
};

class Angajat :public Interfata
{
	int aniExperienta;
	string nume;
	int nrLuni;
	int Salariu;
	int* nrClientiAntrenati;

public:
	Angajat()
	{}

	Angajat(int aniExperienta, string nume, int nrLuni, int* nrClientiAntrenati)
	{
		this->aniExperienta = aniExperienta;
		this->nume = nume;
		if (nrLuni > 0 && nrClientiAntrenati != NULL)
		{
			this->nrLuni = nrLuni;
			this->nrClientiAntrenati = new int[this->nrLuni];
			for (int i = 0; i < this->nrLuni; i++)
			{
				this->nrClientiAntrenati[i] = nrClientiAntrenati[i];
			}
		}
		else
		{
			this->nrLuni = 0;
			this->nrClientiAntrenati = NULL;
		}

	}

	Angajat(const Angajat& ang)
	{
		this->aniExperienta = ang.aniExperienta;
		this->nume = nume;
		if (ang.nrLuni > 0 && ang.nrClientiAntrenati != NULL)
		{
			this->nrLuni = ang.nrLuni;
			this->nrClientiAntrenati = new int[this->nrLuni];
			for (int i = 0; i < this->nrLuni; i++)
			{
				this->nrClientiAntrenati[i] = ang.nrClientiAntrenati[i];
			}
		}
		else
		{
			this->nrLuni = 0;
			this->nrClientiAntrenati = NULL;
		}
	}

	Angajat& operator=(const Angajat& ang)
	{
		delete[] this->nrClientiAntrenati;
		this->aniExperienta = ang.aniExperienta;
		this->nume = nume;
		if (ang.nrLuni > 0 && ang.nrClientiAntrenati != NULL)
		{
			this->nrLuni = ang.nrLuni;
			this->nrClientiAntrenati = new int[this->nrLuni];
			for (int i = 0; i < this->nrLuni; i++)
			{
				this->nrClientiAntrenati[i] = ang.nrClientiAntrenati[i];
			}
		}
		else
		{
			this->nrLuni = 0;
			this->nrClientiAntrenati = NULL;
		}
		return *this;

	}

	friend ostream& operator <<(ostream& out, Angajat& ang)
	{
		out << "Ani experienta: " << ang.aniExperienta << endl;
		out << "Nume angajat: " << ang.nume << endl;
		out << "Nr luni de cand este angajat: " << ang.nrLuni << endl;
		out << "Nr Clienti Antrenati pentru fiecare luna: " << endl;
		if (ang.nrClientiAntrenati != NULL)
		{
			for (int i = 0; i < ang.nrLuni; i++)
				out << i + 1 << ": " << ang.nrClientiAntrenati[i] << endl;

		}
		else
			out << "-";
		out << endl;
		return out;


	}

	void writeToFile(fstream& file)
	{
		file.write((char*)&this->aniExperienta, sizeof(int));
		int lg = this->nume.length() + 1;
		file.write((char*)&lg, sizeof(int));
		file.write(this->nume.data(), lg);
		file.write((char*)&this->nrLuni, sizeof(int));

		for (int i = 0; i < this->nrLuni; i++)
		{
			file.write((char*)&this->nrClientiAntrenati[i], sizeof(int));
		}
	}

};

class Instructor : public Angajat
{
private:

	const int idInstructor;
	char numeInstructor[50];
	int nrProgramari = 0;
	Programare** listaProgramari = NULL;
	int varsta;
	int nrAntrenamenteAnterioare;
	int* recenzii;

public:

	//get si set

	int getIdInstructor()
	{
		return this->idInstructor;
	}

	char* getNumeInstructor()
	{
		return this->numeInstructor;

	}
	int getnrProgramari()
	{
		return this->nrProgramari;
	}
	Programare** getProgramare()
	{
		return this->listaProgramari;
	}
	int getVarsta()
	{
		return this->varsta;

	}
	int getnrAntrenamenteAnterioare()
	{
		return this->nrAntrenamenteAnterioare;
	}
	int* getRecenzii()
	{
		return this->recenzii;
	}

	void setNumeInstructor(const char* nume)
	{
		if (nume != NULL)
		{
			strcpy(this->numeInstructor, nume);
		}
	}
	void setProgramari(int nrProgramari, Programare** listaProgramari)
	{
		delete[] this->listaProgramari;
		if (nrProgramari > 0 && listaProgramari != NULL)
		{
			this->nrProgramari = nrProgramari;
			this->listaProgramari = new Programare*[this->nrProgramari];
			for (int i = 0; i < this->nrProgramari; i++)
			{
				this->listaProgramari[i] = new Programare(*listaProgramari[i]);

			}

		}
	}
	void setVarsta(int varsta)
	{
		if (varsta > 0)
		{
			this->varsta = varsta;
		}
	}
	void setRecenzii(int nrAntrenamenteAnterioare, int* recenzii)
	{
		if (nrAntrenamenteAnterioare > 0 && recenzii != NULL)
		{
			delete[] this->recenzii;
			this->nrAntrenamenteAnterioare = nrAntrenamenteAnterioare;
			this->recenzii = new int[this->nrAntrenamenteAnterioare];
			for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
			{
				this->recenzii[i] = recenzii[i];
			}

		}
	}
	Instructor() :idInstructor(0)
	{

	}
	//constructor cu 2 parametri
	Instructor(int id, int varsta) :idInstructor(id)
	{
		strcpy(this->numeInstructor, "Anonim");
		this->nrProgramari = 0;
		this->listaProgramari = NULL;
		this->varsta = varsta;
		this->nrAntrenamenteAnterioare = 0;
		this->recenzii = NULL;
		this->varsta = varsta;
	}

	//constructor cu toti parametri

	Instructor(int id, char numeInstructor[50], int nrAntrenamenteAnterioare, int* recenzii, int varsta, int nrProgramari, Programare** listaProgramari) :idInstructor(id)
	{
		if (numeInstructor != NULL)
		{
			strcpy(this->numeInstructor, numeInstructor);
		}
		else
			strcpy(this->numeInstructor, " ");

		if (nrProgramari > 0 && listaProgramari != NULL)
		{
			this->nrProgramari = nrProgramari;
			this->listaProgramari = new Programare*[nrProgramari];
			for (int i = 0; i < nrProgramari; i++)
			{
				this->listaProgramari[i] = new Programare(*listaProgramari[i]);

			}
		}

		this->varsta = varsta;
		if (nrAntrenamenteAnterioare != 0 && recenzii != NULL)
		{
			this->nrAntrenamenteAnterioare = nrAntrenamenteAnterioare;
			this->recenzii = new int[this->nrAntrenamenteAnterioare];
			for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
			{
				if (recenzii[i] >= 0 && recenzii[i] <= 10) //deoarece recenziile pot fi date de la 1 pana la 10
				{
					this->recenzii[i] = recenzii[i];
				}
			}

		}
		else
		{
			this->nrAntrenamenteAnterioare = 0;
			this->recenzii = NULL;
		}
	}

	//metode generice de prelucrare/afisare a atributelor

	int InstructorRecenzieMaxima()
	{

		if (this->nrAntrenamenteAnterioare != 0 && this->recenzii != NULL)
		{
			int max = 0;
			int indice = 0;
			for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
			{
				if (max < this->recenzii[i])
				{
					max = this->recenzii[i];
					indice = i;
				}

			}
			return indice;
		}
		else
			throw exception("Nu sunt inregistrari");
	}

	//constructor de copiere
	Instructor(const Instructor& C) :idInstructor(C.idInstructor)
	{
		if (C.numeInstructor != NULL)
		{


			strcpy(this->numeInstructor, C.numeInstructor);
		}
		else
			strcpy(this->numeInstructor, " ");
		if (C.nrProgramari > 0 && C.listaProgramari != NULL)
		{
			this->nrProgramari = C.nrProgramari;
			this->listaProgramari = new Programare * [this->nrProgramari];
			for (int i = 0; i < this->nrProgramari; i++)
			{
				this->listaProgramari[i] = new Programare(*C.listaProgramari[i]);

			}
		}
		this->varsta = C.varsta;
		if (C.nrAntrenamenteAnterioare != 0 && C.recenzii != NULL)
		{
			this->nrAntrenamenteAnterioare = C.nrAntrenamenteAnterioare;
			this->recenzii = new int[this->nrAntrenamenteAnterioare];
			for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
			{
				if (C.recenzii[i] >= 0 && C.recenzii[i] <= 10) //deoarece recenziile pot fi date de la 1 pana la 10
				{
					this->recenzii[i] = C.recenzii[i];
				}
			}

		}
		else
		{
			this->nrAntrenamenteAnterioare = 0;
			this->recenzii = NULL;
		}
	}
	//operator=
	Instructor& operator=(const Instructor& C)
	{

		for (int i = 0; i < this->nrProgramari; i++)
			delete this->listaProgramari[i];  // dezaloc obiectul
		delete[] this->listaProgramari;  // dezaloc vector
		if (C.numeInstructor != NULL)
		{
			strcpy(this->numeInstructor, C.numeInstructor);
		}

		else
			strcpy(this->numeInstructor, " ");
		if (C.nrProgramari > 0 && C.listaProgramari != NULL)
		{
			this->nrProgramari = C.nrProgramari;
			this->listaProgramari = new Programare * [this->nrProgramari];
			for (int i = 0; i < this->nrProgramari; i++)
			{
				this->listaProgramari[i] = new Programare(*C.listaProgramari[i]);

			}
		}
		this->varsta = C.varsta;
		if (C.nrAntrenamenteAnterioare != 0 && C.recenzii != NULL)
		{
			this->nrAntrenamenteAnterioare = C.nrAntrenamenteAnterioare;
			this->recenzii = new int[this->nrAntrenamenteAnterioare];
			for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
			{
				if (C.recenzii[i] >= 0 && C.recenzii[i] <= 10) //deoarece recenziile pot fi date de la 1 pana la 10
				{
					this->recenzii[i] = C.recenzii[i];
				}
			}
		}
		else
		{
			this->nrAntrenamenteAnterioare = 0;
			this->recenzii = NULL;
		}
		return *this;
	}

	//operator<<
	friend ostream& operator<<(ostream& out, Instructor& C)
	{
		out << (Angajat&)C;
		cout << "Id Instructor: " << C.idInstructor << " " << "Nume Instructor: " << C.numeInstructor << " " << "Nr de Programari facute: " << C.nrProgramari << " " << "Programarile facute sunt: ";
		if (C.listaProgramari != NULL)
		{
			for (int i = 0; i < C.nrProgramari; i++)
			{
				out << *C.listaProgramari[i] << " ";
			}
		}

		cout << "Varsta Instructor: " << C.varsta << "Nr de antrenamente anterioare" << C.nrAntrenamenteAnterioare << " " << "Recenzii antrenamente anteriaore: ";
		if (C.recenzii != NULL)
		{
			for (int i = 0; i < C.nrAntrenamenteAnterioare; i++)
			{
				out << C.recenzii[i] << " ";
			}
		}
		else
			out << "-";
		out << endl << endl;
		return out;

	}

	//operator>>
	friend istream& operator>>(istream& in, Instructor& C)
	{
		cout << "Nume Instructor: ";
		char aux[50];
		in >> aux;
		strcpy(C.numeInstructor, aux);
		cout << "Nr Programari: ";
		in >> C.nrProgramari;
		for (int i = 0; i < C.nrProgramari; i++)
			//delete C.listaProgramari[i];
			delete[] C.listaProgramari;
		if (C.nrProgramari > 0)
		{
			C.listaProgramari = new Programare * [C.nrProgramari];
			for (int i = 0; i < C.nrProgramari; i++)
			{
				Programare r;
				in >> r;
				C.listaProgramari[i] = new Programare(r);


			}

		}
		else
		{
			C.listaProgramari = NULL;
			C.nrProgramari = 0;

		}
		cout << "Varsta Instructorului: ";
		in >> C.varsta;
		cout << "Nr de antrenamente anterioare: ";
		in >> C.nrAntrenamenteAnterioare;
		delete[] C.recenzii;
		if (C.nrAntrenamenteAnterioare > 0)
		{
			cout << "Recenzii antrenamente: ";
			C.recenzii = new int[C.nrAntrenamenteAnterioare];
			for (int i = 0; i < C.nrAntrenamenteAnterioare; i++)
			{
				in >> C.recenzii[i];

			}
		}
		else
		{
			C.nrAntrenamenteAnterioare = 0;
			C.recenzii = NULL;
		}
		return in;



	}

	~Instructor()
	{
		delete[] this->recenzii;
		// ordine distrugere de jos in sus
		for (int i = 0; i < this->nrProgramari; i++)
			delete this->listaProgramari[i];  // dezaloc obiectul
		delete[] this->listaProgramari;  // dezaloc vector
	}

	//operatorul +
	Instructor operator+(int x)
	{
		Instructor copie = *this;
		copie.varsta = copie.varsta + x;
		return copie;
	}

	//operatorul -- care elimina PRIMA recenzie din vectorul de recenzii

	//PREINCREMENTARE
	Instructor& operator--()
	{
		Instructor copie = *this;
		delete[] this->recenzii;
		this->nrAntrenamenteAnterioare--;
		this->recenzii = new int[this->nrAntrenamenteAnterioare];
		for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
			this->recenzii[i] = copie.recenzii[i + 1];
		return *this;
	}

	//POSTINCREMENTARE
	Instructor operator--(int)
	{
		Instructor copie = *this;
		delete[] this->recenzii;
		this->nrAntrenamenteAnterioare--;
		this->recenzii = new int[this->nrAntrenamenteAnterioare];
		for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
			this->recenzii[i] = copie.recenzii[i + 1];
		return copie;
	}

	//OPERATOR CAST-face conversie la nr de recenzii cu nota maxima

	operator int()
	{
		if (this->nrAntrenamenteAnterioare != 0 && this->recenzii != NULL)
		{
			int nr = 0;
			for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
				if (this->recenzii[i] == 10)
					nr++;
			return nr;

		}
	}

	//operator negatie-anuleaza vectorul de recenzii
	Instructor& operator!()
	{
		delete[] this->recenzii;
		this->recenzii = NULL;
		this->nrAntrenamenteAnterioare = 0;
		return *this;
	}

	//oprator de comparatie- compara varstele a doi Instructori
	bool operator>(const Instructor& C)
	{
		if (this->varsta > C.varsta)
			return 1;
		else
			return 0;

	}

	bool operator==(const Instructor* C)
	{
		bool ok = 1;
		if (this->idInstructor == C->idInstructor && strcmp(this->numeInstructor, C->numeInstructor) == 0 && this->nrProgramari == C->nrProgramari && this->varsta == C->varsta && this->nrAntrenamenteAnterioare == C->nrAntrenamenteAnterioare)
			ok == 1;
		else
			ok == 0;
		if (ok == 1)
		{
			for (int i = 0; i < this->nrProgramari; i++)
				if (this->listaProgramari[i] == C->listaProgramari[i])
					ok == 1;
				else
					ok == 0;
			if (ok == 1)
				for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
					if (this->recenzii[i] = C->recenzii[i])
						ok == 1;
					else
						ok == 0;
		}
		else
			ok == 0;
	}


	//fisiere text
	friend ofstream& operator<<(ofstream& out, Instructor& c)
	{
		out << c.numeInstructor << endl;
		out << c.nrProgramari << endl;
		for (int i = 0; i < c.nrProgramari; i++)
		{

			out << *c.listaProgramari[i] << " ";

		}
		out << endl;
		out << c.varsta << endl;
		out << c.nrAntrenamenteAnterioare << endl;
		for (int i = 0; i < c.nrAntrenamenteAnterioare; i++)
		{
			out << c.recenzii[i] << " ";
		}
		out << endl;
		return out;

	}

	friend ifstream& operator>>(ifstream& in, Instructor& c)
	{
		delete[] c.listaProgramari;
		delete[] c.recenzii;
		in >> c.numeInstructor;
		in >> c.nrProgramari;
		c.listaProgramari = new Programare * [c.nrProgramari];
		for (int i = 0; i < c.nrProgramari; i++)
		{
			Programare r;
			in >> r;
			c.listaProgramari[i] = new Programare(r);


		}
		in >> c.varsta;
		in >> c.nrAntrenamenteAnterioare;
		c.recenzii = new int[c.nrAntrenamenteAnterioare];
		for (int i = 0; i < c.nrAntrenamenteAnterioare; i++)
		{
			in >> c.recenzii[i];

		}
		return in;
	}

	//fisiere binare

	void scriereBinar(fstream& file)
	{
		int lg = strlen(this->numeInstructor);
		file.write((char*)&lg, sizeof(int));
		for (int i = 0; i < lg; i++)
		{
			file.write((char*)&this->numeInstructor[i], sizeof(char));


		}

		file.write((char*)&this->nrProgramari, sizeof(int));
		file.write((char*)&this->varsta, sizeof(int));
		file.write((char*)&this->nrAntrenamenteAnterioare, sizeof(int));
		for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
		{
			file.write((char*)&this->recenzii[i], sizeof(int));

		}
	}

	void citireBinar(fstream& file)
	{
		delete[] this->recenzii;
		delete[] this->listaProgramari;
		int lg1;
		file.read((char*)&lg1, sizeof(int));
		for (int i = 0; i < lg1; i++)
		{
			file.read((char*)&this->numeInstructor[i], sizeof(char));
		}
		file.read((char*)&this->nrProgramari, sizeof(int));
		file.read((char*)&this->varsta, sizeof(int));
		file.read((char*)&this->nrAntrenamenteAnterioare, sizeof(int));
		this->recenzii = new int[this->nrAntrenamenteAnterioare];
		for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
		{
			file.read((char*)&this->recenzii[i], sizeof(int));

		}

	}

	//Redefinim functia virtuala

	void writeToFile(fstream& file)
	{
		int lg = strlen(this->numeInstructor);
		file.write((char*)&lg, sizeof(int));
		for (int i = 0; i < lg; i++)
		{
			file.write((char*)&this->numeInstructor[i], sizeof(char));
		}

		file.write((char*)&this->nrProgramari, sizeof(int));
		file.write((char*)&this->varsta, sizeof(int));
		file.write((char*)&this->nrAntrenamenteAnterioare, sizeof(int));
		for (int i = 0; i < this->nrAntrenamenteAnterioare; i++)
		{
			file.write((char*)&this->recenzii[i], sizeof(int));

		}
	}

};

//void raportClienti(Client* clienti, int nrClienti)
//{
//	ofstream file("ProgramariClienti.txt", ios::out);
//	for (int i = 0; i < nrClienti; i++) {
//		file << clienti[i];
//	}
//	file.close();
//}

void raportProgramari(Programare* programari, int nrProgramari)
{
	ofstream file("programariTotale.txt", ios::out);
	for (int i = 0; i < nrProgramari; i++) {
		file << programari[i];
	}
	file.close();
}

void raportSali(Sala* sali, int nrSali)
{
	ofstream file("ProgramariSali.txt", ios::out);
	for (int i = 0; i < nrSali; i++) {
		file << sali[i];
	}
	file.close();
}

void meniuRapoarte() {
	cout << "- 1. Creare raport text cu toate programarile\t\t\t-" << endl;
	cout << "- 2. Creare raport text cu toate salile\t\t\t-" << endl;
}

int main()
{
	cout << "-----------------CLASA CLIENT------------------------";
	cout << endl;

	char nr_telefon1[50] = "0724768523";
	Client c1("Georgescu Oana", nr_telefon1);

	cout << "ID: " << c1.getidClient() << endl;

	c1.setnume("Georgescu Ioana");
	cout << "Nume: " << c1.getNume() << endl;

	float pretOra[] = { 15,20 };
	c1.setpretOra(pretOra, 2);
	cout << "Numar de ore petrecute la Sala: " << c1.getnrOre() << endl;
	cout << "Pret pe ora:";
	for (int i = 0; i < c1.getnrOre(); i++)
	{
		cout << c1.getpretOra()[i] << " ";
	}
	cout << endl;
	c1.setnr_telefon("0724768523");
	cout << "Nr Telefon: " << c1.getNr_telefon() << endl;

	float pretOra2[] = { 15,20,20,25 };
	char nr_telefon2[50] = "0745632789";
	Client c2(2, "Popescu Matei", 4, pretOra2, nr_telefon2);

	cout << endl;
	cout << "Egalitatea a doua obiecte: ";
	if (c1 == c2)
		cout << "Sunt egale";
	else
		cout << "Nu sunt egale";
	cout << endl << endl;

	//Constructor copiere
	Client c3 = c1;
	cout << "C3 in urma constructorului de copiere: " << c3;
	cout << endl << endl;

	//operator=
	c1 = c2;
	cout << "C1 in urma operatorului =: " << c1;
	cout << endl << endl;

	//Media preturilor pe ore ale clientului
	cout << "Media preturilor pe ore ale clientului C1 este: " << c1.medie();
	cout << endl;

	//Calcularea pretului maxim
	cout << "Pretul maxim: " << c2.maxim();
	cout << endl;

	//operator>>;
	char nr_telefon4[50] = "0747932789";
	Client c4("Stancu Ramon", nr_telefon4);
	cout << c4;
	cin >> c4;
	cout << endl;
	cout << c4;
	cout << endl << endl;

	//operator indexare
	try {
		cout << c1[2];
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	cout << endl << endl;

	//operator +
	char nr_telefon5[] = "0745532789";
	float pretOra5[] = { 10,20,30 };
	Client c5(5, "Zamfir Roxana", 3, pretOra5, nr_telefon5);
	cout << c5;

	cout << endl << endl;

	//operator-- pre si post
	c4 = --c5;
	cout << c4;
	cout << c5; //imi modifica si this si c5;

	c4 = c5--;
	cout << c4;
	cout << c5; //imi modifica doar c5 si c4 ia forma initiala a lui c5

	cout << endl << endl << endl;

	//operator cast 
	char nr_telefon6[] = "0745632724";
	float pretOra6[] = { 200,1 };
	Client c6(6, "Dumitru Leonard", 2, pretOra6, nr_telefon6);

	//operator cast - nr preturilor mai mari decat 100;
	cout << "Operator cast: " << (int)c6;

	cout << endl << endl;

	//operator negatie
	c6 = !c4;
	cout << c4;
	cout << c6;

	//operator de comparatie
	if (c1 > c2)
		cout << "c1 are mai multe ore decat c2";
	else
		cout << "Invers";
	cout << endl << endl;


	char nr_telefon7[] = "0745632721";
	float pretOra7[] = { 230, 45, 67 };
	Client c7(7, "Trandafir Alexandru", 3, pretOra7, nr_telefon7);

	char nr_telefon8[] = "0745642789";
	float pretOra8[] = { 34,78 };
	Client c8(8, "Paltin Victor", 2, pretOra8, nr_telefon8);

	//operator+ (adauga o valoare la preturile vectorului de preturi/ora)
	c7 = c8 + 10;
	cout << endl << endl << "Operator +: " << endl;
	cout << c7; // Preia preturile lui c8 adunate cu valoarea 10 fiecare
	cout << c8;

	cout << (c7 == c8) << endl;
	cout << (c7 == c1);

	cout << endl << endl;
	cout << "-----------------CLASA PROGRAMARE------------------------";
	cout << endl;

	Programare p("10 dec 2022", 0);
	p.setPremium(1);
	cout << "Este premium? " << p.getPremium() << endl;
	float garantie[] = { 100,20 };
	p.setgarantie(2, garantie);
	cout << "Nr ore: " << p.getnrOre() << endl;
	cout << "Garantie: ";
	for (int i = 0; i < p.getnrOre(); i++)
	{
		cout << p.getgarantie()[i] << " ";
	}
	cout << endl;
	char data[] = "11 dec 2022";
	p.setdata_programarii(data);
	cout << "Data programarii: " << p.getdata_programarii() << endl;

	float garantie1[] = { 23,67,89 };
	Programare p1(1, 3, garantie1, "11 dec 2022");

	float garantie2[] = { 20,21 };
	Programare p2(0, 2, garantie2, "12 dec 2022");

	p1 = p2;
	cout << p1;

	cout << endl;

	Programare p3 = p2;
	cout << p3;

	cout << endl;

	Programare p4("13 dec 2022", 1);
	cin >> p4;
	cout << endl;
	cout << p4;

	//imi afiseaza lungimea atributului de tip char*(metoda plata);
	cout << p4.lungimesir() << endl;

	cout << p1.minim() << endl;

	//indexare cu posibilitate de modificare
	float garantie5[] = { 60,20,40 };
	Programare p5(0, 3, garantie5, "14 dec 2022");
	cout << p5[2];
	cout << endl;
	p5[0] = 100;
	cout << p5;

	cout << endl;

	//Operatorul - 
	p1 = p2 - 5.0f; // imi pune in p1 p2,  unde vectorul de garantie s a redus cu 5% pt fiecare pozitie
	cout << p1;


	//CAST
	cout << "Suma totala a garantiilor pentru programarea p2: ";
	cout << (int)p2;
	cout << endl;

	//operatorul negatie;
	!p5;
	cout << p5;


	float garantie6[] = { 10,20,15,10,10 };
	Programare p6(1, 5, garantie6, "16 dec 2022");

	float garantie7[] = { 20,10 };
	Programare p7(0, 2, garantie7, "17 dec 2022");

	//operator de comparatie
	if (p6 > p7)
		cout << "Programarea 6 are suma mai mare decat Programarea 7";
	else
		cout << "Invers";

	//operator == testarea egalitatii a 2 obiecte
	if ((p7 == p1) == 1)
		cout << "Obiectele sunt egale";
	else
		cout << "Obiectele nu sunt egale";
	cout << endl;


	cout << endl << endl << endl;
	cout << "---------------CLASA SALA-------------------";
	cout << endl << endl;


	int nrAparate[] = { 4,2,6 };
	Sala s(3, nrAparate, 100.5);

	int aparatex[] = { 1,2,3,4,5 };
	s.setLocuriSala(5, aparatex);
	cout << "Nr locuri: " << s.getnrLocuri() << endl;
	cout << "Nr aparate pe camere: ";
	for (int i = 0; i < s.getnrLocuri(); i++)
	{
		cout << s.getnrAparate()[i] << " ";
	}
	cout << endl;
	cout << "Suprafata hotelului: ";
	cout << s.getSuprafata() << endl;
	cout << "Numele salii: ";
	s.setNumeSala("World Gym");
	cout << s.getnumeSala() << endl;

	int aparate1[] = { 2,5,6,7,4 };
	Sala s1(5, aparate1, 200.5, "Future Train");

	int aparate2[] = { 2,2,3,7,4 };
	Sala s2(5, aparate2, 1000, "Perfect Body");

	Sala s3 = s2;
	cout << s3;


	s = s1;
	cout << s;

	int aparate4[] = { 3,4,5 };
	Sala s4(3, aparate4, 200.89);
	cout << endl;
	cout << s4;
	cout << endl << endl;

	cout << "Diferenta de suprafata dintre s2 si s1 este";
	cout << "Diferenta dintre doua suprafate: " << s1.diferentaSuprafata(s2);
	cout << endl;


	//operator indexare
	try {
		cout << "Nr de locuri pentru Sala de pe pozitia  2 este: " << s2[2];
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	int locuri5[] = { 3,4 };
	Sala s5(2, locuri5, 340.7);

	s5 = s4 + s2;
	cout << s5;

	cout << endl << endl;


	s5 = ++s4;
	cout << s5;
	cout << s4;

	s5 = s4++;
	cout << s5;
	cout << s4;


	int aparate6[] = { 1,2,3,4,5,6 };
	Sala s6(6, aparate6, 1000, "MaxFit");

	//operator negatie
	s6 = !s5;
	cout << s6;


	//operator de comparatie
	if (s5 >= s6)
		cout << "S5 are mai multe aparate decat S6";
	else
		cout << "Invers";

	cout << endl << endl << endl << endl;

	//operator == pentru testarea egalitatii dintre 2 obiecte
	if ((s5 == s1) == 1)
		cout << "Obiectele sunt egale";
	else
		cout << "Nu sunt egale";

	cout << endl << endl << endl;

	cout << endl << endl;
	cout << "-----------------IERARHIE + CLASA ABSTRACTA-----------------";
	cout << endl;

	cout << "------------ClASA ANGAJAT-----------------";

	int clientiAntrenati1[] = { 1,3 };
	Angajat ag1(1, "Varna Adrian", 2, clientiAntrenati1);
	cout << ag1;

	// Metoda Virtuala
	fstream f1Out("FisierAngajat.bin", ios::out || ios::binary);
	ag1.writeToFile(f1Out);
	f1Out.close();
	cout << endl << endl;

	cout << "------------CLASA INSTRUCTOR-----------------";

	Programare* listaProgramari1[] = { &p1,&p2 };
	char nume1[] = "Tanasescu Matei";
	int recenzii1[] = { 10,10,9,10 };
	Instructor i1(1, nume1, 30, recenzii1, 34, 2, listaProgramari1);
	cout << i1;
	cout << endl << endl;

	// Metoda Virtuala
	fstream f2Out("FisierInstructor.bin", ios::out || ios::binary);
	i1.writeToFile(f2Out);
	f2Out.close();
	cout << endl << endl;

	/*
	cout << endl << endl;
	cout << "-----------------GENERARE RAPOARTE------------------------";
	cout << endl;

	cout << "Rapoarte" << endl;

	Programare* vectProgramari = new Programare[3];
	vectProgramari[0] = p5;
	vectProgramari[1] = p6;
	vectProgramari[2] = p7;

	Sala* vectSali = new Sala[3];
	vectSali[0] = s1;
	vectSali[1] = s6;
	vectSali[2] = s2;

	meniuRapoarte();
	cout << "Introduceti codul pentru a genera rapoartele dorite: " << endl;
	int valoareRaport = 0;
	cin >> valoareRaport;

	if (valoareRaport == 1) {
		raportProgramari(vectProgramari, 3);
	}
	if (valoareRaport == 2) {
		raportSali(vectSali, 3);
	}
	cout << endl << endl << endl;
	*/

	cout << endl << endl;
	cout << "-----------------SCRIERE IN FISIERE TEXT------------------------";
	cout << endl;

	ofstream file1("Client.txt", ios::out);
	file1 << c1;
	file1.close();

	//ifstream file2("Client.txt", ios::in);
	//file2 >> c2;
	//file2.close();
	//cout << c2;

	cout << endl << endl;
	cout << "-----------------SCRIERE IN FISIERE BINARE------------------------";
	cout << endl;

	fstream file11("ClientBinar.bin", ios::binary | ios::out);
	c1.scriereBinar(file11);
	file11.close();

	//fstream file12("ClientBinar.bin", ios::binary | ios::in);
	//c2.citireBinar(file12);
	//file12.close();

	cout << endl << endl;
	cout << "-----------------SCRIERE IN FISIERE CSV------------------------";
	cout << endl;

	ofstream filef1("Programare.csv", ios::out);
	filef1 << p1;
	filef1.close();

	//ifstream filef2("Programare.csv", ios::in);
	//filef2 >> p;
	//filef2.close();
}