/*
	This is the console executable, that makes use of the BullCow class
	This acts as the view in a MVC (Model-View-Controller) pattern, and
	is responsible for all user interaction. For game logic, see the
	FBullCowGame class
*/
#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game which we re-use across plays

// the entry point for the application
int main() 
{
	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintIntro() 
{
	std::cout << "\n\n\Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Copyright 2019 Anthony Collier\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

// plays a single game to completion
void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit vald guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until user gives valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		// get a guess from the playewr
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter your guess : ";
		getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "You won!\n";
	}
	else 
	{
		std::cout << "You lost... better luck next time.\n";
	}

	return;
}

bool AskToPlayAgain() 
{
	std::cout << "Do you want to play again with the same hidden word? (Y/y) / (N/n)";
	std::cout << std::endl;
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
