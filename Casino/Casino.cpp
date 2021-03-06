// Casino.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include  <string>
#include <ctime>


using namespace std;

class Player {
private:
	string name;
	int cash;
	//jer mi u razgovoru sa casinom vrati adresu kad zelim procitati koliko chipova imam a prvi put sam usao u cash in, znaci chipovi su null
	int chips = 0;
	int highScore;
public:
	void SetPlayerName(string n) {
		name = n;
	}
	string GetPlayerName() {
		return name;
	}
	void SetPlayerCash(int& c) {
		cash = c;
	}
	int GetPlayerCash() {
		return cash;
	}
	void SetPlayerChips(int& c) {
		chips = c;
	}
	int GetPlayerChips() {
		return chips;
	}
	void DecrementCash(int& amount) {
		cash -= amount;
		chips += amount / 5;
	}
	void IncrementCash(int& amount) {
		//tu sam skinuo sa chipova vrijednost koju zelim zamijeniti za pare
		chips -= amount;
		cash += amount * 5;
	}
	void DecrementChips(int& amount) {
		chips -= amount;
	}
	void IncrementChips(int& amount) {
		chips += amount;
	}
};
class SmokinDices {
private:
	int dice_roll;
	int player_roll;
	bool winner;
public:
	int SetRng() {
		int random;
		random = rand() % 6 + 1;
		return random;
	}
	void SetPlayerDiceRoll() {
		player_roll = SetRng();
	}
	int GetPlayerDiceRoll() {
		return player_roll;
	}
	void SetDiceRoll() {
		dice_roll = SetRng();
	}
	int GetDiceRoll() {
		return dice_roll;
	}
	void Game() {
		//ova funkcija vraca chipove
		SetDiceRoll();
		SetPlayerDiceRoll();
		cout << "daj mi casino score " << GetDiceRoll() << endl;
		cout << "daj mi player score " << GetPlayerDiceRoll() << endl;
		if (GetPlayerDiceRoll() > GetDiceRoll()) {
			winner = true;
		}
		else if (GetDiceRoll() > GetPlayerDiceRoll()) {
			winner = false;
		}
		else {
			cout << "go agane" << endl;
		}
	}
	bool GetWinner() {
		return winner;
	}
	

};
////GLOBAL FUNCTIONS//////////
void MainMenu(Player& p);
void WelcomeToCasino(Player& p);
void CashIn(Player& p);
void CashOut(Player& p);
void GameSelectionScreen(Player& p);
void PlaySmokinDices(Player& p);


int main()
{
	Player p;
	Player* ptr;
	ptr = &p;
	// mi pokazuje adresu od objeka p
	//cout << ptr << endl;
	WelcomeToCasino(*ptr);
	MainMenu(*ptr);
}



void MainMenu(Player& p) {
	
	
	int selector = 0;
	cout << "Welcome to LightzOut casino" << endl;
	cout << "Choose what you wanna do here!" << endl;
	cout << "1. Cash in" << endl;
	cout << "2. Cash out" << endl;
	cout << "3. Game selection screen" << endl;
	cout << "4. High score" << endl;
	cout << "5. Exit the casino" << endl;
	cin >> selector;
	switch (selector)
	{
	case 1:
		CashIn(p);
		break;
	case 2:
		CashOut(p);
		break;
	case 3:
		GameSelectionScreen(p);
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
	

}

void WelcomeToCasino(Player& p) {
	string name;
	int cash;
	cout << "Well hello there! What's your name?" << endl;
	cin >> name;
	p.SetPlayerName(name);
	cout << "Hi there " << p.GetPlayerName() << " ! How much cash do you wanna deposit?" << endl;
	cin >> cash;
	p.SetPlayerCash(cash);
	cout << "You've deposited " << p.GetPlayerCash() << " dollars!" << endl;
}


void CashIn(Player& p) {
	int amount;
	cout << "So, you're here to put some money in gambling?" << endl;
	cout << "How much of your money you wanna change for chips?" << endl;
	cout << "You currently have " << p.GetPlayerCash() << " in dollars and " << p.GetPlayerChips() << " in chips!" << endl;
	cout << "Enter the amount of money you wanna exchange for chips" << endl;
	cin >> amount;
	while (amount > p.GetPlayerCash()) {
		cout << "You don't have that much cash Mr. " << p.GetPlayerName() << " Please try again" << endl;
		cin >> amount;
	}
	if (amount <= p.GetPlayerCash()) {
		p.DecrementCash(amount);
	}
	cout << "Your cash status is " << p.GetPlayerCash() << endl;
	cout << "Your chip status is " << p.GetPlayerChips() << endl;
	MainMenu(p);
}

void CashOut(Player& p) {
	int amount;
	cout << "How much of your chips you wanna exchange for dollars dude?" << endl;
	cout << "Please enter a valid value" << endl;
	cout << "Your cash status is " << p.GetPlayerCash() << endl;
	cout << "Your chip status is " << p.GetPlayerChips() << endl;
	cin >> amount;
	while (amount > p.GetPlayerChips()) {
		cout << "You don't have that many chips Mr. " << p.GetPlayerName() << endl;
		cout << "Please enter a valid number" << endl;
		cin >> amount;
	}
	if (amount <= p.GetPlayerChips()) {
		p.IncrementCash(amount);
	}
	MainMenu(p);
}


void GameSelectionScreen(Player& p) {
	cout << "1. Aparati" << endl;
	cout << "2. Go big or go home" << endl;
	cout << "3. Smokin' dices" << endl;
	int selector;
	cin >> selector;
	switch (selector)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		PlaySmokinDices(p);
		break;
	default:
		break;
	}
	
}


void PlaySmokinDices(Player& p) {
	srand(time(NULL));
	SmokinDices sd;
	int bet;
	cout << "Welcome to the game of smokin' dices! Are you feeling lucky punk?" << endl;
	cout << "How much of your chips you wanna bet per round?" << endl;
	cin >> bet;
	while (bet > p.GetPlayerChips()) {
		cout << "You don't have that many chips dude! Please enter a valid value." << endl;
		cin >> bet;
	}
	if (bet <= p.GetPlayerChips()) {
		p.DecrementChips(bet);
	}
	sd.Game();
	if (sd.GetWinner() == true) {
		bet = bet * 2;
		p.IncrementChips(bet);
	}
	cout << "chipovi su mi " << p.GetPlayerChips() << endl;
	GameSelectionScreen(p);
}










// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
