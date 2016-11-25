// AutoAppRelease.cpp: определяет точку входа для консольного приложения.
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <map>
#include <conio.h>
#include <windows.h>
#undef max  //Разрешение конфликтов std:: и windows.h
using namespace std;
using std::cout;
struct Fuel{ //Топливо
public:
	int id_fuel; //Номер топлива, 2
	string name; //Вид топлива, 3
	double cost; //Цена, 4
	double amount; //Количество топлива, галлоны, 5
};
struct Selling{ //Учет продаж
public:
	int id_order; //Номер заказа, 2
	int id_fuel; //Номер вида топлива, 3
	int id_vendor; //Номер продавца, 4
	double amount; //Количество топлива,5
};
struct Vendor{ //Продавец
public:
	int id_vendor; //Номер продавца, 2
	string name_vendor; //Имя продавца, 3
};
struct Purchase{ //Закупки топлива
public:
	int id_purchase; //Номер закупки топлива, 2
	int id_agent; //Номер контрагента, 3
	int id_fuel; //Номер вида топлива, 4
	double amount; //Количество топлива, 5
};
struct Agent{ //Контрагент
public:
	int id_agent; //Номер контрагента, 2
	string name_agent; //Имя контрагента, 3
};
class AutoClass{
public:
	const string* Fuels = new string[6]{"fuel.txt","Count map: ","Fuel: ","Cost: ","Name: ","Amount: "};
	const string* Sellings = new string[6]{"selling.txt","Count map: ","Selling: ","id Fuel: ","id Vendor: ","Amount: "};
	const string* Vendors = new string[4]{"vendor.txt","Count map: ","Vendor: ","Name: "};
	const string* Purchases = new string[6]{"purchase.txt","Count map: ","Purchase: ","id Agent: ","id Fuel: ","Amount: "};
	const string* Agents = new string[4]{"agent.txt","Count map: ","Agent: ","Name: "};
	map <int, Fuel> fuels; //не зависимые
	map <int, Selling> sellings; //зависимые
	map <int, Vendor> vendors; //не зависимые
	map <int, Purchase> purchases; //зависимые
	map <int, Agent> agents; //не зависимые
	bool dirExists(string dirName_in);
	void report1();
	void report2();
	void inputFuel(Fuel fuel);//Ввод в map одного элемента
	void inputSelling(Selling selling);	void inputVendor(Vendor vendor);void inputPurchase(Purchase purchase);void inputAgent(Agent agent);
	void addFuel(Fuel fuel);//Добавление в map одного элемента
	void addSelling(Selling selling);void addVendor(Vendor vendor);void addPurchase(Purchase Purchase);void addAgent(Agent agent);
	void updateFuel(Fuel fuel);//Обновление в map одного элемента
	void updateSelling(Selling selling);void updateVendor(Vendor vendor);void updatePurchase(Purchase Purchase);void updateAgent(Agent agent);
	void deleteFuel(Fuel fuel);//Удаление из map одного элемента
	void deleteSelling(Selling selling);void deleteVendor(Vendor vendor);void deletePurchase(Purchase Purchase);void deleteAgent(Agent agent);
	void outputFuel(Fuel fuel);//Вывод на экран одного элемента
	void outputSelling(Selling selling);void outputVendor(Vendor vendor);void outputPurchase(Purchase Purchase);void outputAgent(Agent agent);
	void outputAllFuel();//Вывод map на экран
	void outputAllSelling();void outputAllVendor();void outputAllPurchase();void outputAllAgent();
	void readFromFuels(string path);//Чтение из файла в список по указанному пути
	void readFromSelling(string path);void readFromVendors(string path);void readFromPurchases(string path);void readFromAgents(string path);void readFromAll(string path);
	void writeFuels(string path);//Запись из списка в файл по указанному пути
	void writeSelling(string path);void writeVendors(string path);void writePurchases(string path);void writeAgents(string path);void writeAll(string path);
};
//Исправляет ввод-вывод русских букв в консоли
void russianWordFix(){
	setlocale(LC_ALL, "Russian");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 18;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251
}
//Точка входа в программу
int main(){
	russianWordFix();
	const int countObjs = 5;
	AutoClass *autoObjs = new AutoClass[countObjs];
	AutoClass currAutoObj;
	currAutoObj = autoObjs[0];
	//Заготовка меню для пункта 8 из общего задания
	//Вывод меню
	int choose = 0;
	do
	{
		cout << "---------------------------------------------------------------\n";
		cout << "1 - Выбор элемента из массива, с которым планируется работать.\n";
		cout << "2 - Cписок действий\n";
		cout << "0 - Завершение программы\n";
		cout << "---------------------------------------------------------------\n";
		cout << "Введите число, для выбора действия!\n";
		cout << "---------------------------------------------------------------\n";
		cin >> choose;
		if (!std::cin)
		{
			cout << "Введена не целое число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (choose == 1)
		{
			cout << "Выберите один из 5(1-5) элемент с которым планируете работать\n";
			int elem;
			cin >> elem;
			if (!std::cin)
			{
				cout << "Введено не целое число\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (elem < 1 || elem > countObjs) cout << "Вы ввели не верный элемент\n";
			else{
				cout << "Вы выбрали элемент с номером: " << elem << endl;
				currAutoObj = autoObjs[elem - 1];
			}
		}
		if (choose == 2){
			do
			{
				cout << "---------------------------------------------------------------\n";
				cout << "1 - Загрузить из файла\n";
				cout << "2 - Топливо - Сущность 1\n";
				cout << "3 - Учет продаж - Сущность 2\n";
				cout << "4 - Продавец - Сущность 3\n";
				cout << "5 - Закупки топлива - Сущность 4\n";
				cout << "6 - Контрагент - Сущность 5\n";
				cout << "7 - Сформировать отчет 1 - отчет по Учёту продаж\n";
				cout << "8 - Сформировать отчет 2 - отчет по Топливу\n";
				cout << "9 - Сохранить в файл\n";
				cout << "10 - Перейти к другому элементу(вернутся к первому уровню).\n";
				cout << "---------------------------------------------------------------\n";
				cout << "Введите число, для выбора действия!\n";
				cout << "---------------------------------------------------------------\n";
				cin >> choose;
				if (!std::cin){
					cout << "Введено не целое число\n";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else if (choose == 1){
					cout << "---------------------------------------------------------------\n";
					cout << "1 - Ввести путь к файлам для загрузки\n";
					cout << "2 - Не вводить вручную, выбрать путь по умолчанию\n";
					cout << "---------------------------------------------------------------\n";
					cout << "Введите число, для выбора действия!\n";
					cout << "---------------------------------------------------------------\n";
					cin >> choose;
					if (!std::cin){
						cout << "Введено не целое число\n";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					if (choose == 1){
						string path = "";
						cout << "Введите существующий путь к файлам, например: C:\\\\Program Files\\\\Microsoft\\\\" << endl;
						std::cin >> path;
						if (currAutoObj.dirExists(path)) {currAutoObj.readFromAll(path);}
						else{cout << "Введеный путь не существует\n";}
					}
					if (choose == 2) currAutoObj.readFromAll("");
				}
				else if (choose == 2 || choose == 3 || choose == 4 || choose == 5 || choose == 6) {
					int chooseEntity = choose;
					do {
						cout << "---------------------------------------------------------------\n";
						cout << "1 - добавить\n";
						cout << "2 - изменить\n";
						cout << "3 - удалить\n";
						cout << "4 - вывести на экран\n";
						cout << "5 - вернутся к списку действий\n";
						cout << "---------------------------------------------------------------\n";
						cout << "Введите число, для выбора действия!\n";
						cout << "---------------------------------------------------------------\n";
						cin >> choose;
						if (!std::cin){
							cout << "Введено не целое число\n";
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
						else if (choose == 1){
							if (chooseEntity == 2){currAutoObj.addFuel(Fuel{});}
							if (chooseEntity == 3){currAutoObj.addSelling(Selling{});}
							if (chooseEntity == 4){currAutoObj.addVendor(Vendor{});}
							if (chooseEntity == 5){currAutoObj.addPurchase(Purchase{});}
							if (chooseEntity == 6){currAutoObj.addAgent(Agent{});}
						}
						else if (choose == 2){
							int id;
							cout << "Введите номер обновляемой сущности" << endl;
							std::cin >> id;
							if (!std::cin){
								cout << "Введено не целое число\n";
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
							if (chooseEntity == 2) {currAutoObj.updateFuel(Fuel{ id = id });}
							if (chooseEntity == 3) {currAutoObj.updateSelling(Selling{ id = id });}
							if (chooseEntity == 4) {currAutoObj.updateVendor(Vendor{ id = id });}
							if (chooseEntity == 5) {currAutoObj.updatePurchase(Purchase{ id = id });}
							if (chooseEntity == 6) {currAutoObj.updateAgent(Agent{ id = id });}
						}
						else if (choose == 3){
							int id;
							cout << "Введите номер удаляемой сущности" << endl;
							std::cin >> id;
							if (!std::cin){
								cout << "Введено не целое число\n";
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
							if (chooseEntity == 2){currAutoObj.deleteFuel(Fuel{ id = id });}
							if (chooseEntity == 3){currAutoObj.deleteSelling(Selling{ id = id });}
							if (chooseEntity == 4){currAutoObj.deleteVendor(Vendor{ id = id });}
							if (chooseEntity == 5){currAutoObj.deletePurchase(Purchase{ id = id });}
							if (chooseEntity == 6){currAutoObj.deleteAgent(Agent{ id = id });}
						}
						else if (choose == 4){
							if (chooseEntity == 2){currAutoObj.outputAllFuel();}
							if (chooseEntity == 3){currAutoObj.outputAllSelling();}
							if (chooseEntity == 4){currAutoObj.outputAllVendor();}
							if (chooseEntity == 5){currAutoObj.outputAllPurchase();}
							if (chooseEntity == 6){currAutoObj.outputAllAgent();}
						}
					} while (choose != 5);
				}
				else if (choose == 7){currAutoObj.report1();}
				else if (choose == 8){currAutoObj.report2();}
				else if (choose == 9){
					cout << "---------------------------------------------------------------\n";
					cout << "1 - Ввести путь к файлам для сохранения\n";
					cout << "2 - Не вводить вручную, выбрать путь по умолчанию\n";
					cout << "---------------------------------------------------------------\n";
					cout << "Введите число, для выбора действия!\n";
					cout << "---------------------------------------------------------------\n";
					cin >> choose;
					if (!std::cin){
						cout << "Введено не целое число\n";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					if (choose == 1){
						string path = "";
						cout << "Введите существующий путь к файлам, например: C:\\\\Program Files\\\\Microsoft\\\\" << endl;
						std::cin >> path;
						if (currAutoObj.dirExists(path)) {currAutoObj.writeAll(path);}
						else{cout << "Введеный путь не существует\n";}
					}
					if (choose == 2){currAutoObj.writeAll("");}
				}
			} while (choose != 10);
		}
	} while (choose != 0);
	system("pause");
	return 0;
}
bool AutoClass::dirExists(string dirName_in){
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //что-то не верно с путём
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // директория существует
	return false;    // директория не существует!
}
//Разрез видов топлива и разрез продавцов
void AutoClass::report1(){
	cout << "--------------------------Отчет-№-1----------------------\n";
	for (std::map<int, Selling>::iterator selling = sellings.begin(); selling != sellings.end(); ++selling){
		cout << Sellings[2] << selling->second.id_order << endl;
		std::map<int, Fuel>::iterator fuelIter = fuels.find(selling->second.id_fuel);
		if (fuelIter != fuels.end()){
			cout << Fuels[2] << selling->second.id_fuel << endl;
			cout << "Название топлива" << fuelIter->second.name << endl;
			cout << "Цена топлива за 1 единицу Amount: " << fuelIter->second.cost << endl;
			cout << "Полученно денег за заказ: " << selling->second.amount*fuelIter->second.cost << endl;
		}
		std::map<int, Vendor>::iterator vendorIter = vendors.find(selling->second.id_vendor);
		if (vendorIter != vendors.end()){
			cout << Vendors[2] << selling->second.id_fuel << endl;
			cout << "Имя продавца: " << vendorIter->second.name_vendor << endl;
		}
		cout << Sellings[5] << selling->second.amount << endl;
	}
	cout << "-------------окончание-Отчета-№-1----------------------\n";
}
//Сумма полученных дененг по видам топлива
void AutoClass::report2(){
	cout << "--------------------------Отчет-№-2----------------------\n";
	std::map<int, double> summaFuel;
	for (std::map<int, Selling>::iterator selling = sellings.begin(); selling != sellings.end(); ++selling)
	{
		std::map<int, Fuel>::iterator fuelIter = fuels.find(selling->second.id_fuel);
		if (fuelIter != fuels.end())
		{
			if (summaFuel.find(selling->second.id_fuel) != summaFuel.end())
				summaFuel[selling->second.id_fuel] += fuelIter->second.cost * selling->second.amount;
			else
				summaFuel[selling->second.id_fuel] = fuelIter->second.cost * selling->second.amount;
		}
	}
	for (std::map<int, double>::iterator summaFuelIter = summaFuel.begin(); summaFuelIter != summaFuel.end(); ++summaFuelIter){
		std::map<int, Fuel>::iterator fuelIter = fuels.find(summaFuelIter->first);
		if (fuelIter != fuels.end()){
			cout << Fuels[2] << fuelIter->second.id_fuel << endl;
			cout << Fuels[2] << Fuels[3] << fuelIter->second.name << endl;
			cout << Fuels[2] << Fuels[4] << fuelIter->second.cost << endl;
			cout << "Всего получено денег со всех заказов по указанному выше виду топлива: " << summaFuelIter->second << endl;
		}
	}
	cout << "-------------окончание-Отчета-№-2----------------------\n";
}
void AutoClass::inputFuel(Fuel fuel){fuels[fuel.id_fuel] = fuel;}
void AutoClass::inputSelling(Selling selling){	sellings[selling.id_fuel] = selling;}
void AutoClass::inputVendor(Vendor vendor){	vendors[vendor.id_vendor] = vendor;}
void AutoClass::inputPurchase(Purchase purchase){purchases[purchase.id_purchase] = purchase;}
void AutoClass::inputAgent(Agent agent){agents[agent.id_agent] = agent;}
void AutoClass::addFuel(Fuel fuel)
{
	fuel.id_fuel = 1;
	for (std::map<int, Fuel>::iterator i = fuels.begin(); i != fuels.end(); ++i){
		if (i->second.id_fuel == fuel.id_fuel)	{fuel.id_fuel++;}
	}
	bool verify = true;
	cout << "Введите Название вида топлива\n";
	std::cin >> fuel.name;
	cout << "Введите цену топлива\n";
	std::cin >> fuel.cost;
	if (!std::cin){
		verify = false;
		cout << "Введено не вещественное число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	cout << "Введите количество вида топлива\n";
	std::cin >> fuel.amount;
	if (!std::cin){
		verify = false;
		cout << "Введено не вещественное число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (verify) {
		inputFuel(fuel);
		cout << "Добавлено\n";
	}
	else{cout << "Введены неверные данные, сущность не добавлена!\n";}
}
void AutoClass::addSelling(Selling selling){
	selling.id_order = 1;
	for (std::map<int, Selling>::iterator i = sellings.begin(); i != sellings.end(); ++i){
		if (i->second.id_order == selling.id_order){selling.id_order++;	}
	}
	bool verify = true;
	string verifyString = "";
	cout << "Введите Номер вида топлива\n";
	std::cin >> selling.id_fuel;
	if (!std::cin){
		verify = false;
		cout << "Введено не целое число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}else if (fuels.find(selling.id_fuel) != fuels.end()) {
		verify = false;
		cout << "Номер не существует\n";
	}
	cout << "Введите номер продавца\n";
	std::cin >> selling.id_vendor;
	if (!std::cin){
		verify = false;
		cout << "Введено не целое число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (vendors.find(selling.id_vendor) != vendors.end()) {
		verify = false;
		cout << "Номер не существует\n";
	}
	cout << "Введите количество топлива\n";
	std::cin >> selling.amount;
	if (!std::cin)
	{
		verify = false;
		cout << "Введено не вещественное число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (verify){inputSelling(selling);cout << "Добавлено\n";}
	else{cout << "Введены неверные данные, сущность не добавлена!\n";}
}

void AutoClass::addVendor(Vendor vendor){
	vendor.id_vendor = 1;
	for (std::map<int, Vendor>::iterator i = vendors.begin(); i != vendors.end(); ++i)	{
		if (i->second.id_vendor == vendor.id_vendor){vendor.id_vendor++;}
	}
	cout << "Введите Имя продавца\n";
	std::cin >> vendor.name_vendor;
	inputVendor(vendor);
	cout << "Добавлено\n";
}
void AutoClass::addPurchase(Purchase purchase){
	purchase.id_purchase = 1;
	for (std::map<int, Purchase>::iterator i = purchases.begin(); i != purchases.end(); ++i){
		if (i->second.id_purchase == purchase.id_purchase){purchase.id_purchase++;}
	}
	bool verify = true;
	cout << "Введите Номер агента\n";
	std::cin >> purchase.id_agent;
	if (!std::cin){
		verify = false;
		cout << "Введено не целое число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else{
		verify = false;
		for (std::map<int, Agent>::iterator i = agents.begin(); i != agents.end(); ++i){
			if (i->second.id_agent == purchase.id_agent){verify = true;}
		}
		if (!verify){cout << "Сущности с данным номером не существует\n";}
	}
	cout << "Введите номер вида топлива\n";
	std::cin >> purchase.id_fuel;
	if (!std::cin){
		verify = false;
		cout << "Введено не целое число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}else{
		verify = false;
		for (std::map<int, Fuel>::iterator i = fuels.begin(); i != fuels.end(); ++i){
			if (i->second.id_fuel == purchase.id_fuel){verify = true;}
		}
		if (!verify){cout << "Сущности с данным номером не существует\n";}
	}
	cout << "Введите количество топлива\n";
	std::cin >> purchase.amount;
	if (!std::cin){
		verify = false;
		cout << "Введено не вещественное число\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (purchase.amount < 0){verify = false;cout << "Введено отрицательное число\n";}
	if (verify){inputPurchase(purchase);cout << "Добавлено\n";}
	else{cout << "Введены неверные данные, сущность не добавлена!\n";}
}

void AutoClass::addAgent(Agent agent){
	agent.id_agent = 1;
	for (std::map<int, Agent>::iterator i = agents.begin(); i != agents.end(); ++i){
		if (i->second.id_agent == agent.id_agent){agent.id_agent++;}
	}
	cout << "Введите Имя агента\n";
	std::cin >> agent.name_agent;
	inputAgent(agent);
	cout << "Добавлено\n";
}
void AutoClass::updateFuel(Fuel fuel){
	if (fuels.find(fuel.id_fuel) != fuels.end()){
		bool verify = true;
		cout << "Введите Название вида топлива\n";
		std::cin >> fuel.name;
		cout << "Введите цену топлива\n";
		std::cin >> fuel.cost;
		if (!std::cin){
			verify = false;
			cout << "Введено не вещественное число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		cout << "Введите количество вида топлива\n";
		std::cin >> fuel.amount;
		if (!std::cin){
			verify = false;
			cout << "Введено не вещественное число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (verify) {
			inputFuel(fuel);
			cout << "Обновлено\n";
		}
		else{cout << "Введены неверные данные, сущность не обновлена!\n";}
	}
	else{cout << "Номер не существует, не обновлено!\n";}
}

void AutoClass::updateSelling(Selling selling)
{
	if (sellings.find(selling.id_fuel) != sellings.end()){
		bool verify = true;
		string verifyString = "";
		cout << "Введите Номер вида топлива\n";
		std::cin >> selling.id_fuel;
		if (!std::cin){
			verify = false;
			cout << "Введено не целое число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}else if (fuels.find(selling.id_fuel) != fuels.end()) {
			verify = false;
			cout << "Номер не существует\n";
		}
		cout << "Введите номер продавца\n";
		std::cin >> selling.id_vendor;
		if (!std::cin){
			verify = false;
			cout << "Введено не целое число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (vendors.find(selling.id_vendor) != vendors.end()) {
			verify = false;
			cout << "Номер не существует\n";
		}
		cout << "Введите количество топлива\n";
		std::cin >> selling.amount;
		if (!std::cin){
			verify = false;
			cout << "Введено не вещественное число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (verify){
			inputSelling(selling);
			cout << "Обновлено\n";
		}
		else{cout << "Введены неверные данные, сущность не обновлена!\n";}
	}
	else{cout << "Номер не существует, не обновлено!\n";}
}

void AutoClass::updateVendor(Vendor vendor)
{
	if (vendors.find(vendor.id_vendor) != vendors.end()){
		cout << "Введите Имя продавца\n";
		std::cin >> vendor.name_vendor;
		inputVendor(vendor);
		cout << "Добавлено\n";
	}
	else{cout << "Номер не существует, не обновлено!\n";}
}


void AutoClass::updatePurchase(Purchase purchase)
{
	if (purchases.find(purchase.id_purchase) != purchases.end())
	{
		bool verify = true;
		cout << "Введите Номер агента\n";
		std::cin >> purchase.id_agent;
		if (!std::cin){
			verify = false;
			cout << "Введено не целое число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}else{
			verify = false;
			for (std::map<int, Agent>::iterator i = agents.begin(); i != agents.end(); ++i){
				if (i->second.id_agent == purchase.id_agent){verify = true;}
			}
			if (!verify)
				cout << "Сущности с данным номером не существует\n";
		}
		cout << "Введите номер вида топлива\n";
		std::cin >> purchase.id_fuel;
		if (!std::cin){
			verify = false;
			cout << "Введено не целое число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}else{
			verify = false;
			for (std::map<int, Fuel>::iterator i = fuels.begin(); i != fuels.end(); ++i){
				if (i->second.id_fuel == purchase.id_fuel){verify = true;}
			}
			if (!verify){cout << "Номер не существует\n";}
		}
		cout << "Введите количество топлива\n";
		std::cin >> purchase.amount;
		if (!std::cin){
			verify = false;
			cout << "Введено не вещественное число\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (purchase.amount < 0){
			verify = false;
			cout << "Введено отрицательное число\n";
		}
		if (verify){
			inputPurchase(purchase);
			cout << "Обновлено\n";
		}
		else{cout << "Введены неверные данные, сущность не обновлена!\n";}
	}
	else{cout << "Номер не существует, не обновлено!\n";}
}

void AutoClass::updateAgent(Agent agent){
	if (agents.find(agent.id_agent) != agents.end()){
		cout << "Введите Имя агента\n";
		std::cin >> agent.name_agent;
		inputAgent(agent);
		cout << "Обновлено\n";
	}
	else{cout << "Номер не существует, не обновлено!\n";}
}
void AutoClass::deleteFuel(Fuel fuel){
	if (fuels.find(fuel.id_fuel) != fuels.end())
	{
		bool exist = false;
		for (std::map<int, Selling>::iterator selling = sellings.begin(); selling != sellings.end(); ++selling){
			if (selling->second.id_fuel == fuel.id_fuel){exist = true;	}
		}
		for (std::map<int, Purchase>::iterator purchase = purchases.begin(); purchase != purchases.end(); ++purchase){
			if (purchase->second.id_fuel == fuel.id_fuel){exist = true;}
		}
		if (!exist){
			fuels.erase(fuel.id_fuel);
			cout << "Успешно удалено!\n";
		}
		else{cout << "Удалите номер из зависимых сущностей!\n";}
	}
	else{cout << "Номер не существует\n";}
}
void AutoClass::deleteSelling(Selling selling){
	if (sellings.find(selling.id_order) != sellings.end()){
		sellings.erase(selling.id_order);
		cout << "Успешно удалено!\n";
	}
	else{cout << "Номер не существует\n";}
}
void AutoClass::deleteVendor(Vendor vendor){
	if (vendors.find(vendor.id_vendor) != vendors.end()){
		bool exist = false;
		for (std::map<int, Selling>::iterator selling = sellings.begin(); selling != sellings.end(); ++selling){
			if (selling->second.id_vendor == vendor.id_vendor){exist = true;}
		}
		if (!exist){
			vendors.erase(vendor.id_vendor);
			cout << "Успешно удалено!\n";
		}
		else{cout << "Удалите номер из зависимой сущности, Учет продаж!\n";}
	}
	else{cout << "Номер не существует\n";}
}

void AutoClass::deletePurchase(Purchase purchase){
	if (purchases.find(purchase.id_purchase) != purchases.end()){
		purchases.erase(purchase.id_purchase);
		cout << "Успешно удалено!\n";
	}
	else{cout << "Номер не существует\n";}
}

void AutoClass::deleteAgent(Agent agent){
	if (agents.find(agent.id_agent) != agents.end()){
		bool exist = false;
		for (std::map<int, Purchase>::iterator purchase = purchases.begin(); purchase != purchases.end(); ++purchase){
			if (purchase->second.id_agent == agent.id_agent){exist = true;}
		}
		if (!exist){
			agents.erase(agent.id_agent);
			cout << "Успешно удалено!\n";
		}
		else {cout << "Удалите номер из зависимой сущности, Закупки топлива!\n";}
	}
	else{cout << "Номер не существует\n";}
}
void AutoClass::outputFuel(Fuel fuel){
	std::map<int, Fuel>::iterator fuelIter = fuels.find(fuel.id_fuel);
	if (fuelIter == fuels.end())	{
		cout << "Номер не существует\n";
		return;
	}
	cout << Fuels[2] << fuelIter->second.id_fuel << endl;
	cout << Fuels[3] << fuelIter->second.cost << endl;
	cout << Fuels[4] << fuelIter->second.name << endl;
	cout << Fuels[5] << fuelIter->second.amount << endl;
}
void AutoClass::outputSelling(Selling selling){
	std::map<int, Selling>::iterator sellingIter = sellings.find(selling.id_order);
	if (sellingIter == sellings.end()) {
		cout << "Номера не существует";
		return;
	}
	cout << Sellings[2] << sellingIter->second.id_order << endl;
	cout << Sellings[3] << sellingIter->second.id_fuel << endl;
	cout << Sellings[4] << sellingIter->second.id_vendor << endl;
	cout << Sellings[5] << sellingIter->second.amount << endl;
}
void AutoClass::outputVendor(Vendor vendor)
{
	std::map<int, Vendor>::iterator vendorIter = vendors.find(vendor.id_vendor);
	if (vendorIter == vendors.end()) {
		cout << "Номера не существует";
		return;
	}
	cout << Vendors[2] << vendorIter->second.id_vendor << endl;
	cout << Vendors[3] << vendorIter->second.name_vendor << endl;
}

void AutoClass::outputPurchase(Purchase purchase){
	std::map<int, Purchase>::iterator purchaseIter = purchases.find(purchase.id_purchase);
	if (purchaseIter == purchases.end()) {
		cout << "Номера не существует";
		return;
	}
	cout << Purchases[2] << purchaseIter->second.id_purchase << endl;
	cout << Purchases[3] << purchaseIter->second.id_agent << endl;
	cout << Purchases[4] << purchaseIter->second.id_fuel << endl;
	cout << Purchases[5] << purchaseIter->second.amount << endl;
}

void AutoClass::outputAgent(Agent agent){
	std::map<int, Agent>::iterator agentIter = agents.find(agent.id_agent);
	if (agentIter == agents.end()) {
		cout << "Номера не существует\n";
		return;
	}
	cout << Agents[2] << agentIter->second.id_agent << endl;
	cout << Agents[3] << agentIter->second.name_agent << endl;
}
void AutoClass::outputAllFuel(){
	for (std::map<int, Fuel>::iterator fuel = fuels.begin(); fuel != fuels.end(); ++fuel)	{
		cout << Fuels[2] << fuel->second.id_fuel << endl;
		cout << Fuels[3] << fuel->second.cost << endl;
		cout << Fuels[4] << fuel->second.name << endl;
		cout << Fuels[5] << fuel->second.amount << endl;
	}
}
void AutoClass::outputAllSelling(){
	for (std::map<int, Selling>::iterator selling = sellings.begin(); selling != sellings.end(); ++selling)	{
		cout << Sellings[2] << selling->second.id_order << endl;
		cout << Sellings[3] << selling->second.id_fuel << endl;
		cout << Sellings[4] << selling->second.id_vendor << endl;
		cout << Sellings[5] << selling->second.amount << endl;
	}
}
void AutoClass::outputAllVendor(){
	for (std::map<int, Vendor>::iterator vendor = vendors.begin(); vendor != vendors.end(); ++vendor)	{
		cout << Vendors[2] << vendor->second.id_vendor << endl;
		cout << Vendors[3] << vendor->second.name_vendor << endl;
	}
}
void AutoClass::outputAllPurchase(){
	for (std::map<int, Purchase>::iterator purchase = purchases.begin(); purchase != purchases.end(); ++purchase){
		cout << Purchases[2] << purchase->second.id_purchase << endl;
		cout << Purchases[3] << purchase->second.id_agent << endl;
		cout << Purchases[4] << purchase->second.id_fuel << endl;
		cout << Purchases[5] << purchase->second.amount << endl;
	}
}
void AutoClass::outputAllAgent(){
	for (std::map<int, Agent>::iterator agent = agents.begin(); agent != agents.end(); ++agent)
	{
		cout << Agents[2] << agent->second.id_agent << endl;
		cout << Agents[3] << agent->second.name_agent << endl;
	}
}
void AutoClass::writeFuels(string path){
	ofstream fout(path + Fuels[0]);
	fout << Fuels[1] << fuels.size() << endl;
	for (std::map<int, Fuel>::iterator fuel = fuels.begin(); fuel != fuels.end(); ++fuel){
		fout << Fuels[2] << fuel->second.id_fuel << endl;
		fout << Fuels[3] << fuel->second.cost << endl;
		fout << Fuels[4] << fuel->second.name << endl;
		fout << Fuels[5] << fuel->second.amount << endl;
	}

}
void AutoClass::writeSelling(string path){
	ofstream fout(path + Sellings[0]);
	fout << Sellings[1] << sellings.size() << endl;
	for (std::map<int, Selling>::iterator selling = sellings.begin(); selling != sellings.end(); ++selling){
		fout << Sellings[2] << selling->second.id_order << endl;
		fout << Sellings[3] << selling->second.id_fuel << endl;
		fout << Sellings[4] << selling->second.id_vendor << endl;
		fout << Sellings[5] << selling->second.amount << endl;
	}
}
void AutoClass::writeVendors(string path){
	ofstream fout(path + Vendors[0]);
	fout << Vendors[1] << vendors.size() << endl;
	for (std::map<int, Vendor>::iterator vendor = vendors.begin(); vendor != vendors.end(); ++vendor)	{
		fout << Vendors[2] << vendor->second.id_vendor << endl;
		fout << Vendors[3] << vendor->second.name_vendor << endl;
	}
}
void AutoClass::writePurchases(string path){
	ofstream fout(path + Purchases[0]);
	fout << Purchases[1] << purchases.size() << endl;
	for (std::map<int, Purchase>::iterator purchase = purchases.begin(); purchase != purchases.end(); ++purchase)	{
		fout << Purchases[2] << purchase->second.id_purchase << endl;
		fout << Purchases[3] << purchase->second.id_agent << endl;
		fout << Purchases[4] << purchase->second.id_fuel << endl;
		fout << Purchases[5] << purchase->second.amount << endl;
	}
}
void AutoClass::writeAgents(string path){
	ofstream fout(path + Agents[0]);
	fout << Agents[1] << agents.size() << endl;
	for (std::map<int, Agent>::iterator agent = agents.begin(); agent != agents.end(); ++agent)	{
		fout << Agents[2] << agent->second.id_agent << endl;
		fout << Agents[3] << agent->second.name_agent << endl;
	}
}
void AutoClass::writeAll(string path){
	writeFuels(path);
	writeSelling(path);
	writeVendors(path);
	writePurchases(path);
	writeAgents(path);
	cout << "Сущности сохранены\n";
}
void AutoClass::readFromAll(string path){
	readFromFuels(path);
	readFromVendors(path);
	readFromAgents(path);
	readFromSelling(path);
	readFromPurchases(path);
}
void AutoClass::readFromFuels(string path){
	Fuel fuel;
	int count_map = 0;
	ifstream fin(path + Fuels[0]);
	if (fin.is_open()){
		fin.ignore(Fuels[1].size());
		fin >> count_map; if (count_map == 0 || count_map == -1) cout << "Не добавлено Топливо" << endl;
		fin.ignore(strlen("\n"));
		for (int i = 0; i < count_map; i++){
			bool verify = true;
			fin.ignore(Fuels[2].size());
			fin >> fuel.id_fuel;
			if (fuels.find(fuel.id_fuel) != fuels.end()){
				cout << "Номер уже существует" << endl;
				verify = false;
			}
			else{cout << Fuels[2] << fuel.id_fuel << endl;}
			fin.ignore(strlen("\n"));
			fin.ignore(Fuels[3].size());
			fin >> fuel.cost;
			if (fuel.cost < 0)
			{
				cout << "Значение отрицательно, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Fuels[3] << fuel.cost << endl;}
			fin.ignore(strlen("\n"));
			fin.ignore(Fuels[4].size());
			fin >> fuel.name;
			cout << Fuels[4] << fuel.name << endl;
			fin.ignore(strlen("\n"));
			fin.ignore(Fuels[5].size());
			fin >> fuel.amount;
			if (fuel.amount < 0){
				cout << "Значение отрицательно, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Fuels[5] << fuel.amount << endl;}
			fin.ignore(strlen("\n"));
			if (verify){
				fuels[fuel.id_fuel] = fuel;
				cout << " - Добавлено Топливо\n";
			}
			else{cout << " - Топливо не добавлено\n";}

		}
	}
	else{cout << "Файл не был создан" << endl;}
}

void AutoClass::readFromSelling(string path){
	Selling selling;
	int count_map = 0;
	ifstream fin(path + Sellings[0]);
	if (fin.is_open()){
		fin.ignore(Sellings[1].size());
		fin >> count_map; if (count_map == 0 || count_map == -1) cout << "Не добавлено Учет продаж" << endl;
		fin.ignore(strlen("\n"));
		for (int i = 0; i < count_map; i++)
		{
			bool verify = true;
			fin.ignore(Sellings[2].size());
			fin >> selling.id_order;
			fin.ignore(strlen("\n"));
			if (sellings.find(selling.id_order) != sellings.end()){
				cout << "Номер уже существует" << endl;
				verify = false;;
			}
			else{cout << Sellings[2] << selling.id_order << endl;}
			fin.ignore(Sellings[3].size());
			fin >> selling.id_fuel;
			fin.ignore(strlen("\n"));
			if (fuels.find(selling.id_fuel) == fuels.end()){
				cout << "Номера не существует, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Sellings[3] << selling.id_fuel << endl;}
			fin.ignore(Sellings[4].size());
			fin >> selling.id_vendor;
			fin.ignore(strlen("\n"));
			if (vendors.find(selling.id_vendor) == vendors.end()){
				cout << "Номера не существует, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Sellings[4] << selling.id_vendor << endl;}
			fin.ignore(Sellings[5].size());
			fin >> selling.amount;
			if (selling.amount < 0){
				cout << "Значение отрицательно, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Sellings[5] << selling.amount << endl;}
			fin.ignore(strlen("\n"));
			if (verify) {
				sellings[selling.id_order] = selling;
				cout << " - Добавлен Учет продаж\n";
			}
			else{cout << " - Учет продаж не добавлен\n";}
		}
	}
	else{cout << "Файл не был создан" << endl;}
}

void AutoClass::readFromVendors(string path){
	Vendor vendor;
	int count_map = 0;
	ifstream fin(path + Vendors[0]);
	if (fin.is_open()){
		fin.ignore(Vendors[1].size());
		fin >> count_map; if (count_map == 0 || count_map == -1) cout << "Не добавлен Торговец" << endl;
		fin.ignore(strlen("\n"));
		for (int i = 0; i < count_map; i++){
			bool verify = true;
			fin.ignore(Vendors[2].size());
			fin >> vendor.id_vendor;
			fin.ignore(strlen("\n"));
			if (vendors.find(vendor.id_vendor) != vendors.end()){
				cout << "Номер уже существует" << endl;
				verify = false;
			}
			else{cout << Vendors[2] << vendor.id_vendor << endl;}
			fin.ignore(Vendors[3].size());
			fin >> vendor.name_vendor;
			fin.ignore(strlen("\n"));
			cout << Vendors[3] << vendor.name_vendor << endl;
			if (verify){
				inputVendor(vendor);
				cout << " - Добавлен Торговец\n";
			}
			else{cout << " - Торговец не добавлен\n";}
		}
	}
	else{cout << "Файл не существует, не загружено" << endl;}
}

void AutoClass::readFromPurchases(string path){
	Purchase purchase;
	int count_map = 0;
	ifstream fin(path + Purchases[0]);
	if (fin.is_open()){
		fin.ignore(Purchases[1].size());
		fin >> count_map; if (count_map == 0 || count_map == -1) cout << "Не добавлено Закупки топлива" << endl;
		fin.ignore(strlen("\n"));
		for (int i = 0; i < count_map; i++){
			bool verify = true;
			fin.ignore(Purchases[2].size());
			fin >> purchase.id_purchase;
			fin.ignore(strlen("\n"));
			if (purchases.find(purchase.id_purchase) != purchases.end()){
				cout << "Номер уже существует" << endl;
				verify = false;
			}
			else{cout << Purchases[2] << purchase.id_purchase << endl;}
			fin.ignore(Purchases[3].size());
			fin >> purchase.id_agent;
			fin.ignore(strlen("\n"));
			if (agents.find(purchase.id_agent) == agents.end()){
				cout << "Номера не существует, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Purchases[3] << purchase.id_agent << endl;}
			fin.ignore(Purchases[4].size());
			fin >> purchase.id_fuel;
			fin.ignore(strlen("\n"));
			if (fuels.find(purchase.id_fuel) == fuels.end()){
				cout << "Номера не существует, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Purchases[4] << purchase.id_fuel << endl;}
			fin.ignore(Purchases[5].size());
			fin >> purchase.amount;
			fin.ignore(strlen("\n"));
			if (purchase.amount < 0){
				cout << "Значение отрицательно, запись не будет считана" << endl;
				verify = false;
			}
			else{cout << Purchases[5] << purchase.amount << endl;}
			if (verify){
				purchases[purchase.id_purchase] = purchase;
				cout << " - Добавлено Закупки топлива\n";
			}
			else{cout << " - Закупки топлива не добавлено\n";}
		}
	}
	else{
		cout << "Файл не загружен" << endl;
	}
}
void AutoClass::readFromAgents(string path){
	Agent agent;
	int count_map = 0;
	ifstream fin(path + Agents[0]);
	if (fin.is_open()){
		fin.ignore(Agents[1].size());
		fin >> count_map; if (count_map == 0 || count_map == -1) cout << "Не добавлен Контрагент" << endl;
		fin.ignore(strlen("\n"));
		for (int i = 0; i < count_map; i++){
			bool verify = true;
			fin.ignore(Agents[2].size());
			fin >> agent.id_agent;
			if (agents.find(agent.id_agent) != agents.end()){
				cout << "Номер уже существует" << endl;
				verify = false;
			}
			else{cout << Agents[2] << agent.id_agent << endl;}
			fin.ignore(strlen("\n"));
			fin.ignore(Agents[3].size());
			fin >> agent.name_agent;
			fin.ignore(strlen("\n"));
			cout << Agents[3] << agent.name_agent << endl;
			if (verify){
				inputAgent(agent);
				cout << " - Добавлен Контрагент\n";
			}
			else{cout << " - Контрагент не добавлен\n";}
		}
	}
	else{cout << "Файл не загружен" << endl;}
}