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
	std::cout << "[BEGIN GAME]" << "\n\nCreate your team..." << std::endl;
	createTeam(team, members);
	std::cout << "\nLet's begin...\n" << "\n***Thanos is " << steps << " light years from Earth!***\n";
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
			std::cout << "\nYour team's hp has been restored,\n        but enemies have gained strength!" << std::endl;
			break;
		case 3: printTeamInfo(team); //call printTeam to display team info
			break;
		case 4: //fight the final boss
			printBossInfo(team, finalBoss); //display fight statistics
			//ask player to fight or flee
			std::cout << "\nDo you dare to engage? (y or n): ";
			std::cin >> endChoice;
			if (tolower(endChoice) == 'y')
				processBossFight(team, finalBoss); //fight boss
			else
				std::cout << "\n...Nope." << std::endl;
		}
		//decide to continue
		if (quitGame(team, finalBoss, steps))
			break;
		steps -= 10; //update counter
		std::cout << "\n***Thanos is " << steps << " light years from Earth!***\n";
		exploreChoice = exploreMenu(); //ask for next choice
	}//end of game menu
	std::cout << "\n[END GAME]";
	std::cout << "\nProgrammed by Erick Santos Jr" << std::endl;
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
		std::cout << "\nCharacter " << list.size() + 1 << "/" << mem << ":" << std::endl;
		//call charMenu to display character selection menu
		charChoice = charMenu();
		//call newCharacter to create new character
		std::cin.ignore(); //remove enter key
		newCharacter(list, charChoice);
	}
}

int charMenu()
{
	//displays character selection, returns the validated choice
	int op;
	std::cout << "CHOOSE YOUR CHARACTER!" << std::endl;
	std::cout << "======================" << std::endl;
	std::cout << "     1 - Novice       " << std::endl;
	std::cout << "     2 - Knight       " << std::endl;
	std::cout << "     3 - Wizard       " << std::endl;
	std::cout << "Enter choice: ";
	std::cin >> op;
	//validate choice
	while (op < 1 || op > 3)
	{
		std::cout << "Invalid, re-enter: ";
		std::cin >> op;
	}
	return op;
}

void newCharacter(std::vector<Character*>& list, int op)
{
	//receives the team vector and the user choice
	//asks for new character info to be saved to vector
	std::string na, wna;
	char type;
	std::cout << "Enter character name: ";
	getline(std::cin, na);
	switch (op)
	{
	case 1: //novice
		list.push_back(new Novice(na));
		break;
	case 2: //knight
		std::cout << "Enter weapon name: ";
		getline(std::cin, wna);
		list.push_back(new Knight(na, wna));
		break;
	case 3: //wizard
		//different types????
		std::cout << "Arcane or Divine? (enter A or D): ";
		std::cin >> type;
		if (toupper(type) == 'A')
			list.push_back(new Wizard(na, "Arcane", 2));
		else
			list.push_back(new Wizard(na, "Divine", 5));
	}
	std::cout << "New character added!" << std::endl;
}

void openingDialog()
{
	//displays the opening dialog of the game
	std::cout << "\n                              Hello user\n\n";
	std::cout << "\n                 A mad titan approaches your planet.";
	std::cout << "\n              Fight battles to level up your characters,";
	std::cout << "\n        then attack the final boss when you feel you're ready\n";
	std::cout << "\n                      ...and before it's too late.\n";
	std::cout << "\n         Enemies and mini bosses may appear in the wilderness,";
	std::cout << "\n                       defeat them to level up!\n";
	std::cout << "\n          Resting will restore your team's health,";
	std::cout << "\n                     but enemies will come back even stronger.\n";
	std::cout << "\n              Best of luck user, you're going to need it.\n";
	std::cout << "\n\n                        Press enter to begin ";
	std::cin.ignore();
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

//*****************************Main Menu*******************************************//
int exploreMenu()
{
	//displays the game menu options, returns a validated choice
	int op;
	std::cout << "\n-------------------------------" << std::endl;
	std::cout << "|          GAME MENU          |" << std::endl;
	std::cout << "|-----------------------------|" << std::endl;
	std::cout << "|  1) Explore the Wilderness  |" << std::endl;
	std::cout << "|  2) Rest                    |" << std::endl;
	std::cout << "|  3) View character stats    |" << std::endl;
	std::cout << "|  4) Fight the [FINAL BOSS]  |" << std::endl;
	std::cout << "|  5) Quit                    |" << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << "Enter choice: ";
	std::cin >> op;
	while (op < 1 || op > 5)
	{
		std::cout << "Invalid, re-enter: ";
		std::cin >> op;
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
	std::cout << "\nNo enemies around..." << std::endl;
	std::cout << " -Gained 5xp-" << std::endl;
}

void exploreWild(std::vector<Character*> team, Enemy& badguy, Boss& miniBoss, int& addToEnemyAtk)
{
	//receives the team vector, Enemy, and Boss objects
	//generates a random number, then decides on type of encounter
	Character* chosenOne;
	char engage;
	int chance = std::rand() % 101;
	if (chance < 50)
		noFight(team); //chance for no encounter, characters gain 5xp
	else if (chance < 90)
	{	//enemy approaches
		std::cout << "\n >>>>> A challenger approaches! <<<<<\n\n";
		chosenOne = chooseCharacter(team); //choose character
		badguy = Enemy(std::rand() % 9, chosenOne->getLevel(), chosenOne->getMaxHP()); //create enemy
		printFightInfo(chosenOne, badguy); //display fight statistics
		//ask player to fight or flee
		std::cout << "Do you wish to engage in combat? (y or n): ";
		std::cin >> engage;
		if (tolower(engage) == 'y')
			processEnemFight(chosenOne, badguy, addToEnemyAtk); //fight enemy
		else
			std::cout << "\nNot today..." << std::endl;
	}
	else
	{	//miniboss approaches
		std::cout << "\n        >>>>> A MINI BOSS approaches! <<<<<\n";
		miniBoss = createMiniBoss(team); //create miniboss
		printBossInfo(team, miniBoss); //display fight statistics
		//ask player to fight or flee
		std::cout << "\nWill you send your team into battle? (y or n): ";
		std::cin >> engage;
		if (tolower(engage) == 'y')
			processBossFight(team, miniBoss); //fight boss
		else
			std::cout << "\nNot today..." << std::endl;
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
	std::cout << "\n**************************" << std::endl;
	std::cout << "       TEAM STATS        " << std::endl;
	std::cout << "**************************\n" << std::endl;
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << "       Character " << i + 1 << std::endl;
		std::cout << "--------------------------" << std::endl;
		list[i]->print();
		std::cout << std::endl;
	}
}

//********************************Fight enemies************************************//
Character* chooseCharacter(std::vector<Character*> list)
{
	//receives the team vector, prints the list of names, returns validated user choice
	int ch;
	std::cout << "Who will you send into battle?" << std::endl;
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << "   " << i + 1 << " - " << list[i]->getName() << " (" << list[i]->getType() << ") ";
		if (list[i]->getHP() == 0)
			std::cout << "[DECEASED]"; //print this if character is dead
		std::cout << std::endl;
	}
	std::cout << "Enter choice: ";
	std::cin >> ch;
	while ((ch < 1) || (ch > list.size()))
	{
		std::cout << "Invalid, re-enter: ";
		std::cin >> ch;
	}
	//check if character is dead
	while (list[ch - 1]->getHP() == 0)
	{
		std::cout << list[ch - 1]->getName() << " is in a better place, pick again: ";
		std::cin >> ch;
		//validate choice again
		while ((ch < 1) || (ch > list.size()))
		{
			std::cout << "Invalid, re-enter: ";
			std::cin >> ch;
		}
	}
	return list[ch - 1];
}

int fightMenu()
{
	//displays the fighting options, returns a validated choice
	int op;
	std::cout << "Options" << std::endl;
	std::cout << " 1 - Attack" << std::endl;
	std::cout << " 2 - Block" << std::endl;
	std::cout << " 3 - Flee!" << std::endl;
	std::cout << "Choose your move: ";
	std::cin >> op;
	while (op < 1 || op > 3)
	{
		std::cout << "Invalid, re-enter: ";
		std::cin >> op;
	}
	return op;
}

void blockAttack(Character* chosenOne, Enemy& badguy)
{
	//receives the chosenOne and enemy, displays dialog, chance to regain hp
	int regain = 1 + std::rand() % 10;
	std::cout << std::endl << chosenOne->getName() << " successfully blocked " << badguy.getName() << "'s attack!" << std::endl;
	std::cout << "No damage taken!" << std::endl;
	chosenOne->addHP(regain);
	std::cout << " -Regenerated " << regain << "hp-" << std::endl;
}

void printFightInfo(Character* chosen, Enemy bad)
{
	//receives the user's chosen character and an enemy
	//displays the fight info, including names, level, and health
	std::cout << std::endl << std::endl << "  " << std::left << std::setw(12) << chosen->getName() << "            " << std::setw(12) << bad.getName() << std::endl;
	std::cout << " Level: " << std::left << std::setw(2) << chosen->getLevel() << "      vs       Level: " << std::setw(2) << bad.getLevel() << std::endl;
	std::cout << "HP: ";
	chosen->printHealth();
	std::cout << "             HP: ";
	bad.printHealth();
	std::cout << std::endl << std::endl << std::endl;
}

void charAttack(Character* chosen, Enemy& bad)
{
	//receives the user choice and the enemy object
	//call the attack, adjusts stats as necessary, 20% chance for miss, 5% chance for crit
	int atkPoints, miss, crit;
	crit = std::rand() % 101;
	miss = std::rand() % 101;
	if (miss > 20)
	{
		//character attacks enemy
		chosen->printAtkMsg();
		atkPoints = chosen->getAttack();
		if (crit < 5)
		{
			//crit does an extra 50% damage
			std::cout << "[CRITICAL HIT!]" << std::endl;
			atkPoints += 0.5 * atkPoints;
		}
		std::cout << ">>> Damage dealt: " << atkPoints << " pts" << std::endl;
		//subtract atkPoints from the enemy health
		bad.updateHP(atkPoints);
	}
	else
	{
		//the attack missed, display dialog
		std::cout << std::endl << chosen->getName() << "'s attack MISSED!" << std::endl;
		std::cout << bad.getName() << " took no damage" << std::endl;
	}
}

void enemAttack(Character* chosen, Enemy& bad, int up)
{
	//receives the chosen character, enemy, and the amount to increment enemy attack
	//call the attack, adjusts stats as necessary, chance for miss
	int atkPoints, miss;
	miss = std::rand() % 101;
	if (miss > 10)
	{
		//enemy attack character
		atkPoints = bad.getAttack() + up;
		std::cout << std::endl << bad.getName() << " attacks!" << std::endl;
		std::cout << ">>> Damage dealt: " << atkPoints << " pts" << std::endl;
		//update character health
		chosen->updateHP(atkPoints);
	}
	else
	{
		//the attack missed, display dialog
		std::cout << std::endl << bad.getName() << "'s attack MISSED!" << std::endl;
		std::cout << chosen->getName() << " received no damage" << std::endl;
	}
}

bool charFatality(Character* chosen, Enemy bad)
{
	//receives the chosenOne and the enemy
	//determines if either has fainted, displays death messages
	if (chosen->getHP() == 0)
	{
		//death message if hp <= 0
		std::cout << "FATALITY!" << std::endl;
		std::cout << chosen->getName() << " has fainted!" << std::endl;
		std::cout << "You have lost" << std::endl;
		return true;
	}
	else if (bad.getHP() == 0)
	{
		//death message if hp <= 0
		std::cout << "FATALITY!" << std::endl;
		std::cout << bad.getName() << " has fainted!" << std::endl;
		std::cout << "You have won!" << std::endl << "Gained xp" << std::endl;
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
			std::cout << "Your move..." << std::endl;
			yourMove = fightMenu();
		}
	} //end of loop for turns
	if (yourMove == 3) //if fled, display dialog
		std::cout << std::endl << chosenOne->getName() << " has fled, like a true coward..." << std::endl;
	std::cout << "END OF FIGHT" << std::endl;
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
	return Boss(std::rand() % 9, totlevel, totHP);
}

void printBossInfo(std::vector<Character*> list, Boss bad)
{
	//receives the team vector and the boss
	//displays the fight info, including names, level, and health
	std::cout << "\n\n                   " << bad.getName() << std::endl;
	std::cout << "                   Level: " << bad.getLevel() << std::endl;
	std::cout << "                   HP: ";
	bad.printHealth();
	std::cout << std::endl << std::endl << "                       VS." << std::endl << std::endl;	
	for (int i = 0; i < list.size(); i++)
	{	//print name on same line
		std::string na = list[i]->getName();
		if (list[i]->getHP() == 0)
			na += " [DEAD]"; //add indication that character is dead
		//std::cout << "  " << std::left << std::setw(12) << na << "     ";                           *****edit
		std::cout << std::left << std::setw(12) << na << "       ";
	}
	std::cout << std::endl;
	for (int i = 0; i < list.size(); i++)
	{	//print level on same line
		std::cout << "Level: " << std::left << std::setw(2) << list[i]->getLevel() << "          ";
		//std::cout << " Level: " << std::left << std::setw(2) << list[i]->getLevel() << "         "; *****edit
	}
	std::cout << std::endl;
	for (int i = 0; i < list.size(); i++)
	{	//print health on same line
		std::cout << "HP: ";
		list[i]->printHealth();
		std::cout << "        ";
	}
	std::cout << std::endl << std::endl;
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
		Character* rando = list[std::rand() % 3];
		while (rando->getHP() == 0)
		{	//don't attack dead players
			rando = list[std::rand() % 3];
		}
		switch (yourMove)
		{
		case 1: //get total attack
			std::cout << std::endl << "TEAM ATTACK" << std::endl;
			totAtk = 0; //reset attack points
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i]->getHP() != 0) //don't include dead teammates
					totAtk += list[i]->getAttack();
			}
			std::cout << ">>> Damage done: " << totAtk << std::endl;
			boss.updateHP(totAtk); //subtract from boss health
			if (boss.getHP() != 0)
			{	//boss attacks random character if still alive
				std::cout << std::endl << boss.getName() << " turns to attack " << rando->getName() << "!" << std::endl;
				bossAtk = boss.getAttack() + 10;
				boss.printAtkMsg();
				std::cout << ">>> Damage dealt: " << bossAtk << " pts" << std::endl;
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
			std::cout << "\nYour move..." << std::endl;
			yourMove = fightMenu();
		}
	} //end of loop for turns
	if (yourMove == 3) //if fled, display dialog
		std::cout << std::endl << "You have gotten away, for now..." << std::endl;
	if (boss.getHP() == 0)
	{
		std::cout << "\nYou have ended " << boss.getName() << "!" << std::endl;
		for (int i = 0; i < list.size(); i++) //update xp
			list[i]->updateXP(boss.getLevel());
	}
	std::cout << "\nEND BOSS FIGHT" << std::endl;
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
		std::cout << std::endl << "Your team has failed to stop the inevitable." << std::endl;
		std::cout << std::endl << "GAME OVER" << std::endl;
		return true;
	}
	else if (fin.getHP() == 0)
	{
		//print win dialog if final boss is killed
		std::cout << std::endl << "CONGRATULATIONS";
		std::cout << std::endl << "You saved the universe!" << std::endl;
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
		std::cout << "\n >>>>> A challenger approaches! <<<<<\n\n";
		chosenOne = chooseCharacter(team); //choose character
		badguy = Enemy(std::rand() % 9, chosenOne->getLevel(), chosenOne->getMaxHP()); //create enemy
		printFightInfo(chosenOne, badguy); //display fight statistics
		//ask player to fight or flee
		std::cout << "Do you wish to engage in combat? (y or n): ";
		std::cin >> engage;
		if (tolower(engage) == 'y')
			processEnemFight(chosenOne, badguy, addToEnemyAtk); //fight enemy
		else
			std::cout << "\nNot today..." << std::endl;
	}
	else if (demo == 2)
	{	//miniboss approaches
		std::cout << "\n        >>>>> A MINI BOSS approaches! <<<<<\n";
		miniBoss = createMiniBoss(team); //create miniboss
		printBossInfo(team, miniBoss); //display fight statistics
		//ask player to fight or flee
		std::cout << "\nWill you send your team into battle? (y or n): ";
		std::cin >> engage;
		if (tolower(engage) == 'y')
			processBossFight(team, miniBoss); //fight boss
		else
			std::cout << "\nNot today..." << std::endl;
	}
	else
		exploreWild(team, badguy, miniBoss, addToEnemyAtk);
	demo++;
}