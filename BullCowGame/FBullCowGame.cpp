/*
	This file handles all the logic regarding the FBullCowGame class. All getters and
	methods are found here and are able to be instantiated in the main file for the
	foundation of the application.
*/
#pragma once

#include "pch.h"
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 21} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() 
{
	const FString HIDDEN_WORD = "plane"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{
	if (!IsIsogram(Guess))
	{ 
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess))
	{ 
		return EGuessStatus::Not_Lowercase;
	} 
	else if (Guess.length() != GetHiddenWordLength())
	{ 
		return EGuessStatus::Wrong_Length;
	} 
	else 
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) 
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = GetHiddenWordLength();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	
	if (BullCowCount.Bulls == WordLength) 
{
		// potentially introduce logic here for the terminal window
		// to reset when the user wins the game 
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
			if (LetterSeen[Letter]) {
				return false;
			}
			else 
			{
				// add the letter to the map as seen
				LetterSeen[Letter] = true;
			}
	}
	return true; // for example, in cases where "/0" is entered
}

bool FBullCowGame::IsLowercase(FString Word) const 
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
