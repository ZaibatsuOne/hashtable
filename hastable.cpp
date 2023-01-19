#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class hashing
{
private:
		static const int size = 10;

		struct item {
			string show;
			item* next;
		}; 

		item* HashTable[size];

	public:
		hashing();
		int Hash(string key);
		void AddItem(string show);
		int NumbersItem(int index);
		void PrintTable();
		void PrintOnIndex(int index);
		void DeleteItem(string show);

	};
	hashing::hashing() {
		for (int i = 0; i < size; i++) {
			HashTable[i] = new item;
			HashTable[i]->show = "пусто";
			HashTable[i]->next = NULL;

		}
}

void hashing::AddItem(string show) {
	int index = Hash(show); 

	if (HashTable[index]->show == "пусто") {
		HashTable[index]->show = show;
	}
	else {
		item* ptr = HashTable[index];
		item* n = new item;
		n->show = show;
		n->next = NULL;

		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = n; 
	}
}
int hashing::NumbersItem(int index) {
	int count = 0;
	if (HashTable[index]->show == "пусто") {
		return count;
	}
	else {
		count++;
		item* ptr = HashTable[index];
		while (ptr->next != NULL) {
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}

int hashing::Hash(string key) {
	int hash = 0;
	int index;

	const int P = 263;
	int x = 1;
	for (int i = 0; i < key.length(); i++) {
		hash = (hash + (int)key[i] * (x));
		x = (x * P) % size;
		cout << "hash = " << hash << endl;
	}
	index = hash % size;
	return index;
}
void hashing::PrintOnIndex(int index) {
	item* ptr = HashTable[index];
	if (ptr->show == "пусто") {
		cout << "Индекс: " << index << " пустой" << endl;
	}
	else {
		cout << "=======================" << endl;
		cout << "Индекс: " << index << endl;
		while (ptr != NULL) {
			cout << "Содержимое: " <<  ptr->show << endl;
			ptr = ptr->next;
		}
	}
}
void hashing::PrintTable() {
	int counter;
	for (int i = 0; i < size; i++) {
		counter = NumbersItem(i);
		cout << "=======================" << endl;
		cout << "Индекс: " << i << endl;
		cout << "Содержимое: " << HashTable[i]->show << endl;
		cout << "Кол-во: " << counter << endl;
	}
}
void hashing::DeleteItem(string show) {
	int index = Hash(show);
	item* delPtr;
	item* Ptr1;
	item* Ptr2;

	// 1 - Если ячейки пустые
	if (HashTable[index]->show == "пусто") {
		cout << show << " не найден в таблице" << endl;
	}
	// 2 - Если ячейка есть, но там только 1 элемент
	else if (HashTable[index]->show == show) {
		cout << show << " был найден и удален" << endl;
		HashTable[index]->show = "пусто";
	}
	// 3 - Если элемент первый, но там ещё есть с совпадающим именем
	else if (HashTable[index]->show == show) {
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;

		cout << show << " был найден и удален" << endl;
	}
	// 4 - Если совпадения нет в первом элементе, но могут быть совпадения в других 
	else {
		Ptr1 = HashTable[index]->next;
		Ptr2 = HashTable[index];

		while (Ptr1 != NULL && Ptr1->show != show) {
			Ptr2 = Ptr1;
			Ptr1 = Ptr1->next;
		}
		// Нет совпадения
		if (Ptr1 == NULL) {
			cout << show << " не найден в таблице" << endl;
		}
		// Есть совпадение
		else {
			delPtr = Ptr1;
			Ptr1 = Ptr1->next;
			Ptr2->next = Ptr1;

			delete delPtr;
			cout << show << " был найден и удален" << endl;


		}
	}

}
int main() {
	setlocale(LC_ALL, "RUSSIAN");
	hashing Hashing; 
	FILE* out = nullptr;
	freopen_s(&out, "hash.txt", "w", stdout);
	Hashing.AddItem("AB");
	Hashing.AddItem("BA");
	Hashing.AddItem("AC");

	Hashing.AddItem("AAGTRGRGTRGTRGRTTRTRYTR");
	Hashing.AddItem("BDSFFSADhhFDDSAFDDGA");
	Hashing.AddItem("BGDSFGDSFGDSFSA");

	Hashing.AddItem("B3432SDFFDSDSFA");
	Hashing.AddItem("Bdfsfadsf324A");
	Hashing.AddItem("BSdSADsddsf23A");

	Hashing.PrintTable();
	int n = 263;
	for (int i = 2; i * i <= n; i++){
		if (n % i == 0)
			cout << i << endl;
	}

	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			cout << "Ne prostoe" << endl;
			return 0;
		}
	}
	cout << "Prostoe" << endl;
	return 0;
	
}