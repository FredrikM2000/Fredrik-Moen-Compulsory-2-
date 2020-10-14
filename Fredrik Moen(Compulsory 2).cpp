#include <iostream>
#include <ctime>
#include <conio.h>

int pCard;//Player current card
int aCard;//AI current card
int pSum;//Player sum
int aSum;//AI sum
int pMoney = 100;//Players money
int aMoney = 100;//AI's money



void pPickCard() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	pCard = rand() % 13 + 1;
	if (pCard >= 10) {
		pSum += 10;
	}
	else {
		pSum += pCard;
	}
}

void aPickCard() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	aCard = rand() % 13 + 1;
	if (aCard >= 10) {
		aSum += 10;
	}
	else {
		aSum += aCard;
	}
}

void info() {
	std::cout << "Information : \n\n";
	std::cout << "-Press p to pick new card\n";
	std::cout << "-Press s to stand\n";
	std::cout << "-Press i to recieve info again\n\n";
	std::cout << "-You and the dealer will start with 100$ each, the minimum fee for starting a game is 10$\n";
	std::cout << "-The highest value you can gain is 10, so if you pick a knight, queen or king it will count as 10\n";
	std::cout << "-The game will continue until either one of you don't have enough money to continue\n";
}

void ifAce() {
	int ace;
	bool valid = true;
	do {
		if (pCard == 1) {
			pSum -= 1;

			std::cout << "Sum : " << pSum << "\n";
			std::cout << "You picked an ace, do you want it to count as 1 or 11? ";
			std::cin >> ace;
			system("cls");
			if (ace == 1) {
				valid = true;
				pCard = 1;
				pSum += 1;
			}
			else if (ace == 11) {
				pSum += 11;
				pCard = 11;
				valid = true;
			}
			else {
				std::cout << "Not valid, try again\n";
				valid = false;
				system("pause");
			}
		}
	} while (valid == false);
}

int main() {
	bool roundDone = false;
	char input;
	int bet;

	info();
	std::cout << "\n";
	system("pause");
	system("cls");

	bool game_over = false;
	bool pPickNewCard = false;
	bool aPickNewCard = true;
	do {
		pPickCard();
		pPickNewCard = false;
		if (pCard >= 10) {
			pCard = 10;
		}
		std::cout << "You picked a " << pCard << "\n";
		system("pause");
		aPickCard();
		if (aCard >= 10) {
			aCard = 10;
		}
		aPickNewCard = true;
		std::cout << "The dealer picked a : " << aCard << "\n\n";

		bool highbet = true;
		do {//Betting
			std::cout << "You have " << pMoney << "$\n";
			std::cout << "How much do you want to bet? ";
			std::cin >> bet;

			if (bet > pMoney) {
				std::cout << "You don't have that much money, try again\n\n";
				highbet = true;
			}
			else if (bet > aMoney) {
				std::cout << "Dealer does not have that much money, try again\n\n";
				highbet = true;
			}
			else if (bet < 10) {
				std::cout << "Minimum fee is 10$, try again\n\n";
			}
			else {
				pMoney -= bet;
				aMoney -= bet;
				highbet = false;
			}
		} while (bet < 10 || highbet == true);
		system("cls");
		std::cout << "You bet " << bet << "$ \n\n";
		std::cout << "Start game...\n";
		system("pause");

		do {
			//Doesn't pick a new card if it is the first card
			if (pPickNewCard == false) {

			}
			else {
				pPickCard();
			}
			pPickNewCard = true;
			roundDone = false;
			system("cls");
			std::cout << "\t\t BLACKJACK\n\n";

			ifAce();

			std::cout << "You picked a " << pCard << "\n";
			std::cout << "Sum : " << pSum << "\n";

			if (pSum > 21) {
				std::cout << "Your sum is over 21, dealer wins\n\n";
				roundDone = true;
				aMoney += bet + bet;
			}
			else if (pSum <= 21) {
				input = _getch();
				//player choices
				if (input == 'p') {

				}
				else if (input == 's') {
					bool aRoundDone = false;
					system("cls");
					do {
						if (aPickNewCard == true) {

						}
						else {
							aPickCard();
						}
						aPickNewCard = false;

						if (aCard == 1) {
							std::cout << "Dealer picked an ace";

							if (aSum <= 10) {
								aSum += 10;
								std::cout << ", the dealer chooses it to count as 11\n";
							}
							else if (aSum >= 11) {
								std::cout << ", the dealer chooses it to count as 1\n";
							}
							std::cout << "Sum : " << aSum << "\n";
						}
						else {
							std::cout << "Dealer picked " << aCard << "\n";
							std::cout << "Sum : " << aSum << "\n";
						}

						if (aSum > pSum && aSum < 21) {
							std::cout << "Dealer wins!\n\n";
							aRoundDone = true;
							roundDone = true;
							aMoney += bet + bet;
						}
						else if (aSum == 21) {
							if (pSum == 21) {
								std::cout << "You both got 21, so you drew";
								aRoundDone = true;
								roundDone = true;
								aMoney += bet;
								pMoney += bet;
							}
							else {
								std::cout << "Dealer wins!\n\n";
								aRoundDone = true;
								roundDone = true;
								aMoney += bet + bet;
							}
						}
						else if (aSum > 21) {
							std::cout << "You win!\n\n";
							aRoundDone = true;
							roundDone = true;
							pMoney += bet + bet;
						}
						else {
							system("pause");
							system("cls");
						}
					} while (aRoundDone == false);
				}
				else if (input == 'i') {
					info();
					system("pause");
				}
				else {
					pPickNewCard = false;
				}
			}

		} while (roundDone == false);
		system("pause");
		system("cls");

		//Resets scores after a round is finished
		aSum = 0;
		pSum = 0;
		if (pMoney < 10) {
			game_over = true;
			std::cout << "You do not have enough money to continue, dealer wins\n";
		}
		if (aMoney < 10) {
			game_over = true;
			std::cout << "Dealer does not have enough money to continue, you win!\n";
		}
	} while (game_over == false);
}