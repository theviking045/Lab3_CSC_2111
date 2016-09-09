#include "Password.h"
using namespace CSC2110;

#include <iostream>
using namespace std;

Password::Password()
{
	String* word = new String;
	String* curr_word = new String;
	String* word_guess = new String;
    ListArray<String>* all_words = new ListArray<String>();
	ListArray<String>* viable_words = new ListArray<String>();
}

int Password::getNumMatches(String* curr_word, String* word_guess)
{
	int counter = 0;
	for (int i = 0; i < len; i++)
	{
		if (curr_word->text[i] == word_guess->text[i])
			++counter;
	}
	return counter;
}

Password::~Password()
{
	ListArrayIterator<String>* iterate = all_words->iterator();
	while(iterate->hasNext())
	{
		String* temp = iterate->next();
		delete temp;
	}
    delete iterate;
	
	ListArrayIterator<String>* iterate = viable_words->iterator();
	while(iterate->hasNext())
	{
		String* temp = iterate->next();
		delete temp;
	}
    delete iterate;
	
	delete word;
	delete curr_word;
	delete word_guess;
}

void Password::addWord(String* word)
{
	if (all_words->sz == 0)
	{
		len = word->length();
	}
	else
	{
		if (len != word->length())
			return NULL;
	}
	all_words->ListArray<String>::add(<String>* word);
}

void Password::guess(int try_password, int num_matches)
{
	int num_match = 0;
	word_guess->Password::getOriginalWord(try_password);
	
	if (viable_words->ListArray<String>::size() == 0)
		ListArrayIterator<String>* iterate = all_words->iterator();
	else
		ListArrayIterator<String>* iterate = viable_words->iterator();
	while(iterate->hasNext())
	{
		String* temp = iterate->next();
		num_match->Password::getNumMatches(temp,word_guess);
		if (num_matches == num_match)
		{
			viable_words->ListArray<String>::add(temp);	
		}
	}
	
	delete temp;
    delete iterate;
}

int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}