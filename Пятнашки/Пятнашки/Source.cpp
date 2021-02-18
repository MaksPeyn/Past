#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Kletka
{
	short num;
	Kletka* pov[4];
	void Add (Kletka *add, short first)
	{
		(pov[first] = add)->pov[first + 1] = this;
	}
};

struct Dop
{
	short num;
	Dop* pov[2];
	void Add (Dop *add)
	{
		(*pov = add)->pov[1] = this;
	}
};

struct Smesh
{
	short num;
	operator short() { return abs(num); }
	short operator - (int a)
	{
		return abs(((num - a) < -4 ? num + 8 : num) - a);
	}
	short operator + (int a)
	{
		return abs(((num + a) > 4 ? num - 8: num) + a);
	}
	Smesh operator ++()
	{
		if (num == 4) num = -3;
		else ++num;
		return *this;
	}
	Smesh operator --()
	{
		if (num == -4) num = 3;
		else --num;
		return *this;
	}
};

ofstream fout("Путь.txt");

void print (short *k)
{
	fout << "\n\n " << k[-4] << ' ' << k[-3] << ' ' << k[-2];
	fout << "\n " << k[3] << ' ' << k[4] << ' ' << k[-1];
	fout << "\n " << k[2] << ' ' << k[1] << ' ' << *k;
}

short per (Smesh *smesh, short &m, bool &f)
{
	short voz = 0, vyb[8], *k = (short*)smesh - 5;
	Smesh temp;
	++++smesh;
	vyb[0] = (smesh[-2] - 1) + (smesh[-1] + 2) + (smesh[5] - 1) - smesh[-2] - smesh[-1] - smesh[5];
	vyb[1] = (smesh[-2] + 1) + (smesh[-1] + 1) + (smesh[5] - 2) - smesh[-2] - smesh[-1] - smesh[5];
	vyb[2] = (*smesh - 1) + (smesh[1] + 2) + (smesh[-1] - 1) - *smesh - smesh[1] - smesh[-1];
	vyb[3] = (*smesh + 1) + (smesh[1] + 1) + (smesh[-1] - 2) - *smesh - smesh[1] - smesh[-1];
	++++smesh;
	vyb[4] = (*smesh - 1) + (smesh[1] + 2) + (smesh[-1] - 1) - *smesh - smesh[1] - smesh[-1];
	vyb[5] = (*smesh + 1) + (smesh[1] + 1) + (smesh[-1] - 2) - *smesh - smesh[1] - smesh[-1];
	++++smesh;
	vyb[6] = (*smesh - 1) + (smesh[1] + 2) + (smesh[-1] - 1) - *smesh - smesh[1] - smesh[-1];
	vyb[7] = (*smesh + 1) + (smesh[1] + 1) + (smesh[-1] - 2) - *smesh - smesh[1] - smesh[-1];
	----smesh;
	if ((f = !f)) { for (int i = 7; i; --i) if (vyb[i] < vyb[voz] && i != m) voz = i; }
	else { for (int i = 1; i != 8; ++i) if (vyb[i] < vyb[voz] && i != m) voz = i; }
	m = voz + voz % 2 ? -1 : 1;
	cout << endl << smesh[-4] << ' ' << smesh[-3] << ' ' << smesh[-2] << ' ' << smesh[-1] << ' '
		 << *smesh << ' ' << smesh[1] << ' ' << smesh[2] << ' ' << smesh[3] << ' ' << vyb[voz];
	switch (voz)
	{
		case 0:
		{
			temp = ++++smesh[-3];
			smesh[-3] = --smesh[-4];
			smesh[-4] = --smesh[3];
			smesh[3] = temp;
			k[4] = k[-3];
			k[-3] = 8;
			print(k);
			k[-3] = k[-4];
			k[-4] = 8;
			print(k);
			k[-4] = k[3];
			k[3] = 8;
			print(k);
			k[3] = k[4];
			break;
		}
		case 1:
		{
			temp = ----smesh[3];
			smesh[3] = ++smesh[-4];
			smesh[-4] = ++smesh[-3];
			smesh[-3] = temp;
			k[4] = k[3];
			k[3] = 8;
			print(k);
			k[3] = k[-4];
			k[-4] = 8;
			print(k);
			k[-4] = k[-3];
			k[-3] = 8;
			print(k);
			k[-3] = k[4];
			break;
		}
		case 2:
		{
			temp = ++++smesh[-1];
			smesh[-1] = --smesh[-2];
			smesh[-2] = --smesh[-3];
			smesh[-3] = temp;
			k[4] = k[-1];
			k[-1] = 8;
			print(k);
			k[-1] = k[-2];
			k[-2] = 8;
			print(k);
			k[-2] = k[-3];
			k[-3] = 8;
			print(k);
			k[-3] = k[4];
			break;
		}
		case 3:
		{
			temp = ----smesh[-3];
			smesh[-3] = ++smesh[-2];
			smesh[-2] = ++smesh[-1];
			smesh[-1] = temp;
			k[4] = k[-3];
			k[-3] = 8;
			print(k);
			k[-3] = k[-2];
			k[-2] = 8;
			print(k);
			k[-2] = k[-1];
			k[-1] = 8;
			print(k);
			k[-1] = k[4];
			break;
		}
		case 4:
		{
			temp = ++++smesh[1];
			smesh[1] = --*smesh;
			*smesh = --smesh[-1];
			smesh[-1] = temp;
			k[4] = k[1];
			k[1] = 8;
			print(k);
			k[1] = *k;
			*k = 8;
			print(k);
			*k = k[-1];
			k[-1] = 8;
			print(k);
			k[-1] = k[4];
			break;
		}
		case 5:
		{
			temp = ----smesh[-1];
			smesh[-1] = ++*smesh;
			*smesh = ++smesh[1];
			smesh[1] = temp;
			k[4] = k[-1];
			k[-1] = 8;
			print(k);
			k[-1] = *k;
			*k = 8;
			print(k);
			*k = k[1];
			k[1] = 8;
			print(k);
			k[1] = k[4];
			break;
		}
		case 6:
		{
			temp = ++++smesh[3];
			smesh[3] = --smesh[2];
			smesh[2] = --smesh[1];
			smesh[1] = temp;
			k[4] = k[3];
			k[3] = 8;
			print(k);
			k[3] = k[2];
			k[2] = 8;
			print(k);
			k[2] = k[1];
			k[1] = 8;
			print(k);
			k[1] = k[4];
			break;
		}
		default:
		{
			temp = ----smesh[1];
			smesh[1] = ++smesh[2];
			smesh[2] = ++smesh[3];
			smesh[3] = temp;
			k[4] = k[1];
			k[1] = 8;
			print(k);
			k[1] = k[2];
			k[2] = 8;
			print(k);
			k[2] = k[3];
			k[3] = 8;
			print(k);
			k[3] = k[4];
			break;
		}
	}
	k[4] = 8;
	print(k);
	return short(smesh[-4]) + smesh[-3] + smesh[-2] + smesh[-1] + *smesh + smesh[1] + smesh[2] + smesh[3];
}

vector<short> pytno(Kletka beg[9], short end[9], short X)
{
	Dop dop[4];
	short O = 0;
	vector<short> smena;
	while (beg[++O].num != end[6]);
	if (O != 7)
	{
		if (O == 1)
		{
			if (X != 3 && X != 4)
				for (Kletka *b = beg + X; beg + 8 != b;
					smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
			else for (Kletka *b = beg + X; beg + 8 != b;
					smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
			for (Kletka *b = beg + 8; beg + 5 != b;
				smena.push_back((b = b->pov[2]) - beg)) b->num = b->pov[2]->num;
			for (Kletka *b = beg + 5; beg + 8 != b;
				smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
			beg[8].num = 8;
			X = 8;
		}
		else if (O == 2)
		{
			if (X != 4 && X != 5)
				for (Kletka *b = beg + X; beg + 3 != b;
					smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
			else for (Kletka *b = beg + X; beg + 3 != b;
				smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
			for (Kletka *b = beg + 3; beg + 8 != b;
				smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
			beg[8].num = end[6];
			smena.push_back(3);
			for (Kletka *b = beg + 3; beg + 8 != b;
				smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
			beg[8].num = 8;
			X = 8;
		}
		else if (O != 5 && O != 6)
		{
			for (Kletka *b = beg + X, *b7 = beg + 7; b7->num != end[6];
				smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
			beg[8].num = 8;
			X = 8;
		}
		else
		{
			for (Kletka *b = beg + X, *b7 = beg + 7; b7->num != end[6];
				smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
			beg[6].num = beg[5].num;
			smena.push_back(5);
			beg[5].num = 8;
			X = 5;
		}
	}
	O = 0;
	while (beg[++O].num != end[7]);
	if (O != 6)
	{
		if (O > 2)
			for (Kletka *b = beg + X, *b8 = beg + 8; b8->num != end[7];
				smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
		else
		{
			for (Kletka *b = beg + X, *b8 = beg + 8; b8->num != end[7];
				smena.push_back((b = b->pov[2]) - beg)) b->num = b->pov[2]->num;
			for (Kletka *b = beg + 1; beg + 5 != b;
				smena.push_back((b = b->pov[2]) - beg)) b->num = b->pov[2]->num;
		}
		if (O != 8)
		{
			beg[5].num = beg[6].num;
			smena.push_back(6);
		}
		else smena.pop_back();
		beg[6].num = beg[7].num;
		smena.push_back(7);
		beg[7].num = beg[8].num;
		smena.push_back(8);
		beg[8].num = 8;
		X = 8;
	}
	else if (X != 5)
	{
		for (Kletka *b = beg + 8; beg + 3 != b;
			smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
		beg[3].num = beg[8].num;
		smena.push_back(8);
		beg[8].num = beg[5].num;
		smena.push_back(5);
		for (Kletka *b = beg + 5; beg + 8 != b;
			smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
		beg[8].num = beg[5].num;
		smena.push_back(5);
		for (Kletka *b = beg + 5; beg + 8 != b;
			smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
		for (Kletka *b = beg + 8; beg + 3 != b;
			smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
		for (Kletka *b = beg + 3; beg + 5 != b;
			smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
		beg[5].num = 8;
		X = 5;
	}
	else
	{
		for (Kletka *b = beg + 5; beg + 4 != b;
			smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
		beg[4].num = beg[5].num;
		smena.push_back(5);
		beg[5].num = beg[8].num;
		smena.push_back(8);
		for (Kletka *b = beg + 8; beg + 5 != b;
			smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
		beg[5].num = beg[8].num;
		smena.push_back(8);
		for (Kletka *b = beg + 8; beg + 5 != b;
			smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
		beg[5].num = beg[8].num;
		smena.push_back(8);
		beg[8].num = beg[3].num;
		smena.push_back(3);
		for (Kletka *b = beg + 3; beg + 8 != b;
			smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
		beg[8].num = 8;
		X = 8;
	}
	O = 0;
	while (beg[++O].num != end[2]);
	if (O != 1)
	{
		if (O < 5)
		{
			for (Kletka *b = beg + X, *b1 = beg + 1; b1->num != end[2];
				smena.push_back((b = b->pov[2]) - beg)) b->num = b->pov[2]->num;
			beg[2].num = 8;
			X = 2;
		}
		else
		{
			for (Kletka *b = beg + X, *b1 = beg + 1; b1->num != end[2];
				smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
			beg[8].num = 8;
			X = 8;
		}
	}
	O = 1;
	while (beg[++O].num != end[1]);
	if (O != 2)
	{
		if (O != 8)
		{
			if (O != 5)
			{
				if (O != 3)
				{
					beg[X].num = beg[3].num;
					smena.push_back(3);
					for (Kletka *b = beg + 3; beg + 8 != b;
						smena.push_back((b = b->pov[2]) - beg)) b->num = b->pov[2]->num;
					beg[8].num = end[1];
					smena.push_back(3);
					for (Kletka *b = beg + 3; beg + 8 != b;
						smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
				}
				else if (X != 2)
				{
					beg[8].num = end[1];
					smena.push_back(3);
					for (Kletka *b = beg + 3; beg + 8 != b;
						smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
				}
				else
				{
					beg[2].num = beg[3].num;
					smena.push_back(3);
					beg[3].num = beg[8].num;
					smena.push_back(8);
					beg[8].num = beg[5].num;
					smena.push_back(5);
					for (Kletka *b = beg + 5; beg + 8 != b;
						smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
					for (Kletka *b = beg + 8; beg + 1 != b;
						smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
					beg[1].num = beg[8].num;
					smena.push_back(8);
				}
			}
			else
			{
				if (X == 2)
				{
					beg[2].num = beg[3].num;
					smena.push_back(3);
					beg[3].num = beg[8].num;
					smena.push_back(8);
				}
				beg[8].num = end[1];
				smena.push_back(5);
				for (Kletka *b = beg + 5; beg + 8 != b;
					smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
			}
		}
		else for (Kletka *b = beg + 2; beg + 8 != b;
				smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
	}
	else
	{
		for (Kletka *b = beg + 8; beg + 5 != b;
			smena.push_back((b = b->pov[2]) - beg)) b->num = b->pov[2]->num;
		beg[5].num = beg[8].num;
		smena.push_back(8);
		beg[8].num = beg[3].num;
		smena.push_back(3);
		for (Kletka *b = beg + 3; beg + 8 != b;
			smena.push_back((b = b->pov[3]) - beg)) b->num = b->pov[3]->num;
		for (Kletka *b = beg + 8; beg + 5 != b;
			smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
		beg[5].num = beg[8].num;
		smena.push_back(8);
		for (Kletka *b = beg + 8; beg + 5 != b;
			smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
		for (Kletka *b = beg + 5; beg + 3 != b;
			smena.push_back((b = b->pov[2]) - beg)) b->num = b->pov[2]->num;
		beg[3].num = beg[8].num;
		smena.push_back(8);
	}
	dop[1].num = beg[3].num;
	dop[2].num = beg[4].num;
	dop[3].num = beg[5].num;
	dop->Add(dop + 1);
	dop[1].Add(dop + 2);
	dop[2].Add(dop + 3);
	dop[3].Add(dop);
	X = 0;
	O = end[3] != 8 ? 1 : 2;
	Dop *db = dop;
	for (short Y = O + 2; dop[O].num != end[Y]; ++X)
	{
		db->num = db->pov[0]->num;
		db = db->pov[0];
	}
	if (X)
	{
		O = 2;
		while (end[++O] != 8);
		for (Dop *dend = O != 8 ? dop + O - 2: dop; db != dend; ++X)
		{
			db->num = db->pov[0]->num;
			db = db->pov[0];
		}
		db->num = 8;
		if (dop[2].num != end[4] || dop[3].num != end[5]
								 || dop->num != end[8]) smena.push_back(9);
		else
		{
			beg[5].Add(beg + 8, 0);
			db = (Dop*)(beg + 8);
			if (X > 6)
				do
				{
					db->num = db->pov[1]->num;
					smena.push_back((Kletka*)(db = db->pov[1]) - beg);
				}
				while (++X != 12);
			else
			{
				if (db->num == beg[3].num)
				{
					db = (Dop*)(beg + 3);
					smena.pop_back();
					--X;
				}
				do
				{
					db->num = db->pov[0]->num;
					smena.push_back((Kletka*)(db = db->pov[0]) - beg);
				} while (--X);
			}
		}
	}
	else
	{
		if (O != 1) smena.push_back(dop[1].num != end[8] ? 9 : 3);
		else if (end[4] != 8)
		{
			if (end[5] != 8)
			{
				if (dop[2].num != end[4]) smena.push_back(9);
			}
			else smena.push_back(dop[3].num != end[8] ? 9 : 5);
		}
		else if (dop[2].num != end[5]) smena.push_back(9);
		else
		{
			smena.push_back(5);
			smena.push_back(4);
		}
	}
	return smena;
}

void perest(short beg[9])
{
	ifstream fin("Путь.txt");
	short temp[2];
	fin >> temp[0];
	do
	{
		fin >> temp[1];
		if (temp[1] == 9) break;
		beg[temp[0]] = beg[temp[1]];
		temp[0] = temp[1];
	} while (true);
	beg[temp[0]] = 8;
	fout << endl << beg[0] << ' ' << beg[1] << ' ' << beg[2]
		 << endl << beg[7] << ' ' << beg[8] << ' ' << beg[3]
		 << endl << beg[6] << ' ' << beg[5] << ' ' << beg[4];
}

void main()
{
	/*Здесь осуществляется игра в пятнашки 3*3. В файл "Путь.txt" записываются перестановки до конца или тупика,
	потому что попытка перейти от одной расстановки к другой возможна лишь в половине случаев.
	Затем записываются сами состояния и расстановка после выполнения вышеперечисленных перестановок.*/
	setlocale(0, "");
	/*bool f;
	short m = 8, *k = (short*)new Smesh[17], *smesh = k + 8, *kend, *end = new short[10];
	Smesh *sm = (Smesh*)smesh+1;
	cout << "Напишите поля начала и конца, при этом отсчёт идёт по спирали с числами от 0 до 8(Х):\n";
	for (short *kbeg = k; kbeg != smesh; ++kbeg) cin >> *kbeg;
	cin >> *smesh;
	for (short *beg = end, *tend = end + 9; beg != tend; ++beg) cin >> *beg;
	if (end[8] != 8)
	{
		kend = end - 1;
		while (*++kend != 8);
		if ((kend - end) % 2) end[9] = 9;
		else if (kend != end)
		{
			*kend = kend[-1];
			--kend;
			end[9] = 1;
		}
		else
		{
			*kend = kend[1];
			++kend;
			end[9] = -1;
		}
		*kend = end[8];
		end[8] = kend - end;
	}
	if (*smesh != 8)
	{
		kend = smesh;
		while (*--kend != 8);
		if (!((smesh - kend) % 2))
		{
			print(k + 4);
			if (kend != k)
			{
				*kend = kend[-1];
				*--kend = 8;
			}
			else
			{
				*kend = kend[1];
				*++kend = 8;
			}
		}
		print(k + 4);
		*kend = *smesh;
		*smesh = 8;
	}
	print(k+4);
	for (short i = 0, j; i != 8; ++i)
	{
		j = -1;
		while (end[++j] != k[i]);
		if ((k[i + 9] = j - i) > 4)
			k[i + 9] -= 8;
		else if (k[i + 9] < -4)
			k[i + 9] += 8;
	}
	while (per(sm, m, f));
	++++++++end;
	if (end[4] != 8)
	{
		end[4] = *(kend = end + end[4] - 4);
		*kend = 8;
		print(end);
		if (end[5] != 9)
		{
			*kend = kend[end[5]];
			kend[end[5]] = 8;
			print(end);
		}
	}
	delete[] (end-4);
	delete[] k;*/
	Kletka beg[9];
	short end[9], dbeg[9], endsm[3], j = -1, O = -1;
	vector<short> smena, dop;
	cout << "Напишите поля начала и конца, при этом отсчёт идет по спирали от 0 до 8(Х):\n";
	for (short i = 0; i != 9; ++i)
	{
		cin >> dbeg[i];
		beg[i].num = dbeg[i];
	}
	for (short *e = end, *ed = end + 9; e != ed; ++e) cin >> *e;
	beg[1].Add(beg + 2, 2);
	beg[2].Add(beg + 3, 2);
	beg[3].Add(beg + 4, 2);
	beg[4].Add(beg + 5, 2);
	beg[5].Add(beg + 8, 2);
	beg[8].Add(beg + 1, 2);
	beg[3].Add(beg + 4, 0);
	beg[4].Add(beg + 5, 0);
	beg[5].Add(beg + 6, 0);
	beg[6].Add(beg + 7, 0);
	beg[7].Add(beg + 8, 0);
	beg[8].Add(beg + 3, 0);
	while (end[++j] != 8);
	switch (j)
	{
	case 1: { endsm[0] = 1; endsm[1] = 8; end[1] = end[8]; end[8] = 8; break; }
	case 7: { endsm[0] = 7; endsm[1] = 8; end[7] = end[8]; end[8] = 8; break; }
	case 0: { endsm[0] = 0; endsm[1] = 1; endsm[2] = 8;
		end[0] = end[1]; end[1] = end[8]; end[8] = 8; break; }
	case 2: { endsm[0] = 2; endsm[1] = 3; end[2] = end[3]; end[3] = 8; break; }
	case 6: { endsm[0] = 6; endsm[1] = 5; end[6] = end[5]; end[5] = 8; break; }
	default: { endsm[0] = 9; break; }
	}
	while (beg[++O].num != end[0]);
	j = -1;
	while (beg[++j].num != 8);
	smena.push_back(j);
	if (O)
	{
		if (O < 3 && j < 3)
		{
			if (O != 1)
			{
				if (!j) smena.push_back(1);
				smena.push_back(2);
				beg[2].num = beg[3].num;
				smena.push_back(3);
				beg[3].num = beg[8].num;
				smena.push_back(8);
				beg[8].num = beg[7].num;
				smena.push_back(7);
				beg[7].num = beg[1].num;
				smena.push_back(0);
			}
			else if (j)
			{
				beg[2].num = beg[3].num;
				smena.push_back(3);
				beg[3].num = beg[8].num;
				smena.push_back(8);
				beg[8].num = beg[7].num;
				smena.push_back(7);
				beg[7].num = beg->num;
				smena.push_back(0);
			}
			beg->num = end[0];
			smena.push_back(1);
			beg[1].num = beg[8].num;
			smena.push_back(8);
			beg[8].num = 8;
			j = 8;
		}
		else if (j < 2)
		{
			beg[j].num = beg[7 + j].num;
			++++++++++++++j;
			beg[j].num = 8;
			smena.push_back(j);
			if (O == j) O = j - 7;
		}
		else if (j == 2)
		{
			beg[2].num = beg[3].num;
			beg[3].num = 8;
			smena.push_back(3);
			if (O == 3) O = 2;
			j = 3;
		}
		else if (O == 2)
		{
			if (j != 3 && j != 4)
				for (Kletka *b = beg + j; beg + 8 != b;
					smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
			else for (Kletka *b = beg + j; beg + 8 != b;
					smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
			smena.push_back(1);
			smena.push_back(2);
			beg[2].num = beg[3].num;
			smena.push_back(3);
			beg[3].num = beg[1].num;
			smena.push_back(8);
			beg[8].num = beg[7].num;
			smena.push_back(7);
			beg[7].num = beg->num;
			smena.push_back(0);
			beg->num = end[0];
			smena.push_back(1);
			beg[1].num = beg[8].num;
			smena.push_back(8);
			beg[8].num = 8;
			j = 8;
		}
		else if (O == 1)
		{
			if (j != 3 && j != 8)
				for (Kletka *b = beg + j; beg + 7 != b;
					smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
			else for (Kletka *b = beg + j; beg + 7 != b;
					smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
			beg[7].num = beg->num;
			smena.push_back(0);
			beg->num = end[0];
			smena.push_back(1);
			beg[1].num = beg[8].num;
			smena.push_back(8);
			beg[8].num = 8;
			j = 8;
		}
		if (beg[0].num != end[0])
		{
			if (O != 3 && O != 8)
			{
				if (O != 7)
					for (Kletka *b = beg + j, *b7 = beg + 7; b7->num != end[0];
						smena.push_back((b = b->pov[0]) - beg)) b->num = b->pov[0]->num;
				else for (Kletka *b = beg + j; beg + 8 != b;
						smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
			}
			else
			{
				for (Kletka *b = beg + j, *b7 = beg + 7; b7->num != end[0];
					smena.push_back((b = b->pov[1]) - beg)) b->num = b->pov[1]->num;
				beg[6].num = beg[5].num;
				smena.push_back(5);
				beg[5].num = beg[8].num;
				smena.push_back(8);
			}
			beg[8].num = beg[1].num;
			smena.push_back(1);
			beg[1].num = beg->num;
			smena.push_back(0);
			beg->num = end[0];
			smena.push_back(7);
			beg[7].num = 8;
			j = 7;
		}
	}
	else if (j == 1)
	{
		beg[1].num = beg[8].num;
		smena.push_back(8);
		beg[8].num = 8;
		j = 8;
	}
	else if (j == 2)
	{
		beg[2].num = beg[3].num;
		smena.push_back(3);
		beg[3].num = 8;
		j = 3;
	}
	dop = pytno(beg, end, j);
	for (auto beg = smena.begin(), end = smena.end(); beg != end; ++beg) fout << ' ' << *beg;
	for (auto beg = dop.begin(), end = dop.end(); beg != end; ++beg) fout << ' ' << *beg;
	if (dop.end()[-1] != 9)
	{
		O = -1;
		if (endsm[0] != 9)
		{
			if (!endsm[0])
			{
				fout << ' ' << endsm[1];
				++O;
				end[endsm[2]] = end[endsm[1]];
			}
			fout << ' ' << endsm[0];
			++O;
			end[endsm[1]] = end[endsm[0]];
			end[endsm[0]] = 8;
		}
		fout << " 9\nВсего " << smena.size() + dop.size() + O << " ходов, а до шахмат ещё далеко.";
	}
	fout << endl << end[0] << ' ' << end[1] << ' ' << end[2] << '\t'
		<< dbeg[0] << ' ' << dbeg[1] << ' ' << dbeg[2]
		<< endl << end[7] << ' ' << end[8] << ' ' << end[3] << '\t'
		<< dbeg[7] << ' ' << dbeg[8] << ' ' << dbeg[3]
		<< endl << end[6] << ' ' << end[5] << ' ' << end[4] << '\t'
		<< dbeg[6] << ' ' << dbeg[5] << ' ' << dbeg[4] << endl;
	perest(dbeg);
	system("pause");
}