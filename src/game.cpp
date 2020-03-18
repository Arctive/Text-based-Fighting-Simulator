#include "Entity.hpp"
#include "Character.hpp"
#include "Novice.hpp"
#include "Knight.hpp"
#include "Wizard.hpp"
#include "Enemy.hpp"
#include "Boss.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>

//*********Function prototypes**********//
//Character creation
void openingDialog();
void createTeam(std::vector<Character*>&, int);
int charMenu();
void newCharacter(std::vector<Character*>&, int);
//Main menu
void demoExplore(std::vector<Character*>, Enemy&, Boss&, int&, int&);
int exploreMenu();
void noFight(std::vector<Character*>);
void exploreWild(std::vector<Character*>, Enemy&, Boss&, int&);
void rest(std::vector<Character*>, int&);
void printTeamInfo(std::vector<Character*>);
//Fight enemies
Character* chooseCharacter(std::vector<Character*>);
int fightMenu();
void blockAttack(Character*, Enemy&);
void printFightInfo(Character*, Enemy);
void charAttack(Character*, Enemy&);
void enemAttack(Character*, Enemy&, int);
bool charFatality(Character*, Enemy);
void processEnemFight(Character*, Enemy&, int&);
//Fight boss
Boss createMiniBoss(std::vector<Character*>);
void printBossInfo(std::vector<Character*>, Boss); 
void processBossFight(std::vector<Character*>, Boss&);
//End game
bool teamFatality(std::vector<Character*>);
bool quitGame(std::vector<Character*>, Boss, int);

int main()
{
	//declare and initialize variables, vectors, and objects
	std::vector<Character*> team;
	Enemy badguy;
	Boss miniBoss, finalBoss = Boss("THANOS", "Infinity Gauntlet", 100, 1000);
	int exploreChoice, members = 3, addToEnemyAtk = 0, steps = 1000, demo = 0;
	char endChoice;
	srand(time(0)); //seed the random number generator
	openingDialog(); //opening dialog
	cout << "[BEGIN GAME]" << "\n\nCreate your team..." << endl;
	createTeam(team, members);
	cout << "\nLet's begin...\n" << "\n***Thanos is " << steps << " light years from Earth!***\n";
	//call exploreMenu to display the game menu
	exploreChoice = exploreMenu();
	//process game options
	while (exploreChoice != 5)
	{
		switch (exploreChoice)
		{
		case 1: //explore the wilderness
			demoExplore(team, badguy, miniBoss, addToEnemyAtk, demo);
			//exploreWild(team, badguy, miniBoss, addToEnemyAtk);
			break;
		case 2: rest(team, addToEnemyAtk); //call rest for live team members to heal
			cout << "\nYour team's hp has been restored,\n        but enemies have gained strength!" << endl;
			break;
		case 3: printTeamInfo(team); //call printTeam to display team info
			break;
		case 4: //fight the final boss
			printBossInfo(team, finalBoss); //display fight statistics
			//ask player to fight or flee
			cout << "\nDo you dare to engage? (y or n): ";
			cin >> endChoice;
			if (tolower(endChoice) == 'y')
				processBossFight(team, finalBoss); //fight boss
			else
				cout << "\n...Nope." << endl;
		}
		//decide to continue
		if (quitGame(team, finalBoss, steps))
			break;
		steps -= 10; //update counter
		cout << "\n***Thanos is " << steps << " light years from Earth!***\n";
		exploreChoice = exploreMenu(); //ask for next choice
	}//end of game menu
	cout << "\n[END GAME]";
	cout << "\nProgrammed by Erick Santos Jr" << endl;
	return 0;
}

//**********************************************************************************//
//**************************App Function Definitions********************************//
//**********************************************************************************//

//**************************Character creation**************************************//
void createTeam(std::vector<Character*>& list, int mem)
{
	//receives the team vector and its size
	//calls charMenu and newCharacter to create characters to be saved to vector
	int charChoice;
	while (list.size() < mem)
	{
		cout << "\nCharacter " << list.size() + 1 << "/" << mem << ":" << endl;
		//call charMenu to display character selection menu
		charChoice = charMenu();
		//call newCharacter to create new character
		cin.ignore(); //remove enter key
		newCharacter(list, charChoice);
	}
}

int charMenu()
{
	//displays character selection, returns the validated choice
	int op;
	cout << "CHOOSE YOUR CHARACTER!" << endl;
	cout << "======================" << endl;
	cout << "     1 - Novice       " << endl;
	cout << "     2 - Knight       " << endl;
	cout << "     3 - Wizard       " << endl;
	cout << "Enter choice: ";
	cin >> op;
	//validate choice
	while (op < 1 || op > 3)
	{
		cout << "Invalid, re-enter: ";
		cin >> op;
	}
	return op;
}

void newCharacter(std::vector<Character*>& list, int op)
{
	//receives the team vector and the user choice
	//asks for new character info to be saved to vector
	string na, wna;
	char type;
	cout << "Enter character name: ";
	getline(cin, na);
	switch (op)
	{
	case 1: //novice
		list.push_back(new Novice(na));
		break;
	case 2: //knight
		cout << "Enter weapon name: ";
		getline(cin, wna);
		list.push_back(new Knight(na, wna));
		break;
	case 3: //wizard
		//different types????
		cout << "Arcane or Divine? (enter A or D): ";
		cin >> type;
		if (toupper(type) == 'A')
			list.push_back(new Wizard(na, "Arcane", 2));
		else
			list.push_back(new Wizard(na, "Divine", 5));
	}
	cout << "New character added!" << endl;
}

void openingDialog()
{
	//displays the opening dialog of the game
	cout << "\n                              Hello user\n\n";
	cout << "\n                 A mad titan approaches your planet.";
	cout << "\n              Fight battles to level up your characters,";
	cout << "\n        then attack the final boss when you feel you're ready\n";
	cout << "\n                      ...and before it's too late.\n";
	cout << "\n         Enemies and mini bosses may appear in the wilderness,";
	cout << "\n                       defeat them to level up!\n";
	cout << "\n          Resting will restore your team's health,";
	cout << "\n                     but enemies will come back even stronger.\n";
	cout << "\n              Best of luck user, you're going to need it.\n";
	cout << "\n\n                        Press enter to begin ";
	cin.ignore();
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

//*****************************Main Menu*******************************************//
int exploreMenu()
{
	//displays the game menu options, returns a validated choice
	int op;
	cout << "\n-------------------------------" << endl;
	cout << "|          GAME MENU          |" << endl;
	cout << "|-----------------------------|" << endl;
	cout << "|  1) Explore the Wilderness  |" << endl;
	cout << "|  2) Rest                    |" << endl;
	cout << "|  3) View character stats    |" << endl;
	cout << "|  4) Fight the [FINAL BOSS]  |" << endl;
	cout << "|  5) Quit                    |" << endl;
	cout << "-------------------------------" << endl;
	cout << "Enter choice: ";
	cin >> op;
	while (op < 1 || op > 5)
	{
		cout << "Invalid, re-enter: ";
		cin >> op;
	}
	return op;
}

void noFight(std::vector<Character*> list)
{
	//receives the team vector, adds 5 XP to all characters
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->getHP() != 0) //only update live characters
			list[i]->updateXP(5);
	}
	cout << "\nNo enemies around..." << endl;
	cout << " -Gained 5xp-" << endl;
}

void exploreWild(std::vector<Character*> team, Enemy& badguy, Boss& miniBoss, int& addToEnemyAtk)
{
	//receives the team vector, Enemy, and Boss objects
	//generates a random number, then decides on type of encounter
	Character* chosenOne;
	char engage;
	int chance = rand() % 101;
	if (chance < 50)
		noFight(team); //chance for no encounter, characters gain 5xp
	else if (chance < 90)
	{	//enemy approaches
		cout << "\n >>>>> A challenger approaches! <<<<<\n\n";
		chosenOne = chooseCharacter(team); //choose character
		badguy = Enemy(rand() % 9, chosenOne->getLevel(), chosenOne->getMaxHP()); //create enemy
		printFightInfo(chosenOne, badguy); //display fight statistics
		//ask player to fight or flee
		cout << "Do you wish to engage in combat? (y or n): ";
		cin >> engage;
		if (tolower(engage) == 'y')
			processEnemFight(chosenOne, badguy, addToEnemyAtk); //fight enemy
		else
			cout << "\nNot today..." << endl;
	}
	else
	{	//miniboss approaches
		cout << "\n        >>>>> A MINI BOSS approaches! <<<<<\n";
		miniBoss = createMiniBoss(team); //create miniboss
		printBossInfo(team, miniBoss); //display fight statistics
		//ask player to fight or flee
		cout << "\nWill you send your team into battle? (y or n): ";
		cin >> engage;
		if (tolower(engage) == 'y')
			processBossFight(team, miniBoss); //fight boss
		else
			cout << "\nNot today..." << endl;
	}
}

void rest(std::vector<Character*> list, int& up)
{
	//receives the team vector and enemy attack modifier, restores health to live team members
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->getHP() != 0)
			list[i]->heal();
	}
	up++; //increment to increase enemy attacks
}

void printTeamInfo(std::vector<Character*> list)
{
	//receives the team vector, prints each character's info
	cout << "\n**************************" << endl;
	cout << "       TEAM STATS        " << endl;
	cout << "**************************\n" << endl;
	for (int i = 0; i < list.size(); i++)
	{
		cout << "       Character " << i + 1 << endl;
		cout << "--------------------------" << endl;
		list[i]->print();
		cout << endl;
	}
}

//********************************Fight enemies************************************//
Character* chooseCharacter(std::vector<Character*> list)
{
	//receives the team vector, prints the list of names, returns validated user choice
	int ch;
	cout << "Who will you send into battle?" << endl;
	for (int i = 0; i < list.size(); i++)
	{
		cout << "   " << i + 1 << " - " << list[i]->getName() << " (" << list[i]->getType() << ") ";
		if (list[i]->getHP() == 0)
			cout << "[DECEASED]"; //print this if character is dead
		cout << endl;
	}
	cout << "Enter choice: ";
	cin >> ch;
	while ((ch < 1) || (ch > list.size()))
	{
		cout << "Invalid, re-enter: ";
		cin >> ch;
	}
	//check if character is dead
	while (list[ch - 1]->getHP() == 0)
	{
		cout << list[ch - 1]->getName() << " is in a better place, pick again: ";
		cin >> ch;
		//validate choice again
		while ((ch < 1) || (ch > list.size()))
		{
			cout << "Invalid, re-enter: ";
			cin >> ch;
		}
	}
	return list[ch - 1];
}

int fightMenu()
{
	//displays the fighting options, returns a validated choice
	int op;
	cout << "Options" << endl;
	cout << " 1 - Attack" << endl;
	cout << " 2 - Block" << endl;
	cout << " 3 - Flee!" << endl;
	cout << "Choose your move: ";
	cin >> op;
	while (op < 1 || op > 3)
	{
		cout << "Invalid, re-enter: ";
		cin >> op;
	}
	return op;
}

void blockAttack(Character* chosenOne, Enemy& badguy)
{
	//receives the chosenOne and enemy, displays dialog, chance to regain hp
	int regain = 1 + rand() % 10;
	cout << endl << chosenOne->getName() << " successfully blocked " << badguy.getName() << "'s attack!" << endl;
	cout << "No damage taken!" << endl;
	chosenOne->addHP(regain);
	cout << " -Regenerated " << regain << "hp-" << endl;
}

void printFightInfo(Character* chosen, Enemy bad)
{
	//receives the user's chosen character and an enemy
	//displays the fight info, including names, level, and health
	cout << endl << endl << "  " << left << setw(12) << chosen->getName() << "            " << setw(12) << bad.getName() << endl;
	cout << " Level: " << left << setw(2) << chosen->getLevel() << "      vs       Level: " << setw(2) << bad.getLevel() << endl;
	cout << "HP: ";
	chosen->printHealth();
	cout << "             HP: ";
	bad.printHealth();
	cout << endl << endl << endl;
}

void charAttack(Character* chosen, Enemy& bad)
{
	//receives the user choice and the enemy object
	//call the attack, adjusts stats as necessary, 20% chance for miss, 5% chance for crit
	int atkPoints, miss, crit;
	crit = rand() % 101;
	miss = rand() % 101;
	if (miss > 20)
	{
		//character attacks enemy
		chosen->printAtkMsg();
		atkPoints = chosen->getAttack();
		if (crit < 5)
		{
			//crit does an extra 50% damage
			cout << "[CRITICAL HIT!]" << endl;
			atkPoints += 0.5 * atkPoints;
		}
		cout << ">>> Damage dealt: " << atkPoints << " pts" << endl;
		//subtract atkPoints from the enemy health
		bad.updateHP(atkPoints);
	}
	else
	{
		//the attack missed, display dialog
		cout << endl << chosen->getName() << "'s attack MISSED!" << endl;
		cout << bad.getName() << " took no damage" << endl;
	}
}

void enemAttack(Character* chosen, Enemy& bad, int up)
{
	//receives the chosen character, enemy, and the amount to increment enemy attack
	//call the attack, adjusts stats as necessary, chance for miss
	int atkPoints, miss;
	miss = rand() % 101;
	if (miss > 10)
	{
		//enemy attack character
		atkPoints = bad.getAttack() + up;
		cout << endl << bad.getName() << " attacks!" << endl;
		cout << ">>> Damage dealt: " << atkPoints << " pts" << endl;
		//update character health
		chosen->updateHP(atkPoints);
	}
	else
	{
		//the attack missed, display dialog
		cout << endl << bad.getName() << "'s attack MISSED!" << endl;
		cout << chosen->getName() << " received no damage" << endl;
	}
}

bool charFatality(Character* chosen, Enemy bad)
{
	//receives the chosenOne and the enemy
	//determines if either has fainted, displays death messages
	if (chosen->getHP() == 0)
	{
		//death message if hp <= 0
		cout << "FATALITY!" << endl;
		cout << chosen->getName() << " has fainted!" << endl;
		cout << "You have lost" << endl;
		return true;
	}
	else if (bad.getHP() == 0)
	{
		//death message if hp <= 0
		cout << "FATALITY!" << endl;
		cout << bad.getName() << " has fainted!" << endl;
		cout << "You have won!" << endl << "Gained xp" << endl;
		//update xp
		chosen->updateXP(bad.getLevel());
		return true;
	}
	else
		return false;
}

void processEnemFight(Character* chosenOne, Enemy& badguy, int& addToEnemyAtk)
{
	//receives the chosen character, and an Enemy object, and enemy attack modifier
	//this function processes the entire fight, calls fight functions and updates values accordingly
	int yourMove;
	//call fightMenu to display fight options
	yourMove = fightMenu();
	while (yourMove != 3)
	{
		switch (yourMove)
		{
		case 1: charAttack(chosenOne, badguy); //character attacks
			if (badguy.getHP() != 0) //if character kills enemy, then don't call enemAttack
				enemAttack(chosenOne, badguy, addToEnemyAtk); //enemy attacks
			break;
		case 2: //block
			blockAttack(chosenOne, badguy);
		}
		//print new fight info
		printFightInfo(chosenOne, badguy);
		//decide to continue
		if (charFatality(chosenOne, badguy)) //if either are dead, leave the loop
			break;
		else
		{
			//ask for next move
			cout << "Your move..." << endl;
			yourMove = fightMenu();
		}
	} //end of loop for turns
	if (yourMove == 3) //if fled, display dialog
		cout << endl << chosenOne->getName() << " has fled, like a true coward..." << endl;
	cout << "END OF FIGHT" << endl;
}

//***********************************Fight boss************************************//
Boss createMiniBoss(std::vector<Character*> list)
{
	//receives the team vector, creates a miniboss based on the team stats
	int totlevel = 0, totHP = 0;
	for (int i = 0; i < list.size(); i++)
	{
		totlevel += list[i]->getLevel();
		totHP += list[i]->getMaxHP();
	}
	return Boss(rand() % 9, totlevel, totHP);
}

void printBossInfo(std::vector<Character*> list, Boss bad)
{
	//receives the team vector and the boss
	//displays the fight info, including names, level, and health
	cout << "\n\n                   " << bad.getName() << endl;
	cout << "                   Level: " << bad.getLevel() << endl;
	cout << "                   HP: ";
	bad.printHealth();
	cout << endl << endl << "                       VS." << endl << endl;	
	for (int i = 0; i < list.size(); i++)
	{	//print name on same line
		string na = list[i]->getName();
		if (list[i]->getHP() == 0)
			na += " [DEAD]"; //add indication that character is dead
		//cout << "  " << left << setw(12) << na << "     ";                           *****edit
		cout << left << setw(12) << na << "       ";
	}
	cout << endl;
	for (int i = 0; i < list.size(); i++)
	{	//print level on same line
		cout << "Level: " << left << setw(2) << list[i]->getLevel() << "          ";
		//cout << " Level: " << left << setw(2) << list[i]->getLevel() << "         "; *****edit
	}
	cout << endl;
	for (int i = 0; i < list.size(); i++)
	{	//print health on same line
		cout << "HP: ";
		list[i]->printHealth();
		cout << "        ";
	}
	cout << endl << endl;
}

void processBossFight(std::vector<Character*> list, Boss& boss)
{
	//receives the team vector and the boss
	//this function processes the boss fight, calls fight functions and updates values accordingly
	int yourMove, totAtk, bossAtk;
	//call fightMenu to display fight options
	yourMove = fightMenu();
	while (yourMove != 3)
	{
		Character* rando = list[rand() % 3];
		while (rando->getHP() == 0)
		{	//don't attack dead players
			rando = list[rand() % 3];
		}
		switch (yourMove)
		{
		case 1: //get total attack
			cout << endl << "TEAM ATTACK" << endl;
			totAtk = 0; //reset attack points
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i]->getHP() != 0) //don't include dead teammates
					totAtk += list[i]->getAttack();
			}
			cout << ">>> Damage done: " << totAtk << endl;
			boss.updateHP(totAtk); //subtract from boss health
			if (boss.getHP() != 0)
			{	//boss attacks random character if still alive
				cout << endl << boss.getName() << " turns to attack " << rando->getName() << "!" << endl;
				bossAtk = boss.getAttack() + 10;
				boss.printAtkMsg();
				cout << ">>> Damage dealt: " << bossAtk << " pts" << endl;
				rando->updateHP(bossAtk); //update character health
			}
			break;
		case 2: //block
			blockAttack(rando, boss);
		}
		//print new fight info
		printBossInfo(list, boss);
		//decide to continue
		if (teamFatality(list) || boss.getHP() == 0) //if team or boss is dead, leave the loop
			break;
		else
		{	//ask for next move
			cout << "\nYour move..." << endl;
			yourMove = fightMenu();
		}
	} //end of loop for turns
	if (yourMove == 3) //if fled, display dialog
		cout << endl << "You have gotten away, for now..." << endl;
	if (boss.getHP() == 0)
	{
		cout << "\nYou have ended " << boss.getName() << "!" << endl;
		for (int i = 0; i < list.size(); i++) //update xp
			list[i]->updateXP(boss.getLevel());
	}
	cout << "\nEND BOSS FIGHT" << endl;
}

//*************************************End Game************************************//
bool teamFatality(std::vector<Character*> list)
{
	//receives the team vector, determines if all team members have fainted
	int totHP = 0;
	for (int i = 0; i < list.size(); i++)
		totHP += list[i]->getHP();
	if (totHP == 0)
		return true;
	else
		return false;
}

bool quitGame(std::vector<Character*> list, Boss fin, int steps)
{
	//receives the team vector and the steps from defeat
	//returns true if team is dead, final boss is dead, or if final boss reached the planet
	if (teamFatality(list) || steps == 0)
	{
		//print lose dialog if team is dead
		cout << endl << "Your team has failed to stop the inevitable." << endl;
		cout << endl << "GAME OVER" << endl;
		return true;
	}
	else if (fin.getHP() == 0)
	{
		//print win dialog if final boss is killed
		cout << endl << "CONGRATULATIONS";
		cout << endl << "You saved the universe!" << endl;
		return true;
	}
	else
		return false;
}

//*********************DEMO***********************//
void demoExplore(std::vector<Character*> team, Enemy& badguy, Boss& miniBoss, int& addToEnemyAtk, int& demo)
{
	//demo explore features
	Character* chosenOne;
	char engage;
	if (demo == 0)
		noFight(team); //chance for no encounter, characters gain 5xp
	else if (demo == 1)
	{	//enemy approaches
		cout << "\n >>>>> A challenger approaches! <<<<<\n\n";
		chosenOne = chooseCharacter(team); //choose character
		badguy = Enemy(rand() % 9, chosenOne->getLevel(), chosenOne->getMaxHP()); //create enemy
		printFightInfo(chosenOne, badguy); //display fight statistics
		//ask player to fight or flee
		cout << "Do you wish to engage in combat? (y or n): ";
		cin >> engage;
		if (tolower(engage) == 'y')
			processEnemFight(chosenOne, badguy, addToEnemyAtk); //fight enemy
		else
			cout << "\nNot today..." << endl;
	}
	else if (demo == 2)
	{	//miniboss approaches
		cout << "\n        >>>>> A MINI BOSS approaches! <<<<<\n";
		miniBoss = createMiniBoss(team); //create miniboss
		printBossInfo(team, miniBoss); //display fight statistics
		//ask player to fight or flee
		cout << "\nWill you send your team into battle? (y or n): ";
		cin >> engage;
		if (tolower(engage) == 'y')
			processBossFight(team, miniBoss); //fight boss
		else
			cout << "\nNot today..." << endl;
	}
	else
		exploreWild(team, badguy, miniBoss, addToEnemyAtk);
	demo++;
}