#include "pch.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() 
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// TODO implement proper input validation for if a word is a bull or cow
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram 
	{ 
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{ 
		return EGuessStatus::Not_Lowercase;
	} 
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{ 
		return EGuessStatus::Wrong_Length;
	} 
	else 
	{
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) 
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = GetHiddenWordLength(); // assuming same length as guess

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				} else {
					BullCowCount.Cows++; // increment cows
				}
			}
		}
	}
	
	if (BullCowCount.Bulls == WordLength) 
{
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

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
			if (LetterSeen[Letter]) { // if letter is in map
				return false; // we do NOT have an isogram
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
	// if word length is zero  false
	if (Word.length() == 0) return false;

	// TODO fix so if ANY uppercase letters pop up, return false
	for (auto Letter : Word) // loop through characters in word and check if lowercase
	{
		if (!islower(Letter))
		{
			return false;  // if char is lowercase or there's a space, we do NOT have a valid input
		}
		else { 
			return true;  // otherwise, we have a valid input
		}
	}
}

FBullCowGame::FBullCowGame() { Reset(); }
