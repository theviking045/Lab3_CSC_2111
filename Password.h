#if !defined PASSWORD_H
#define PASSWORD_H

//complete the includes
#include "ListArray.h"
#include "String.h"
using namespace CSC2110;

class Password
{
   private:
		ListArray<String>* viable_words;  //the list of words that can still be the password
		ListArray<String>* all_words;  //the original list of words
		int len;  //the length of the first word entered is stored to check that all subsequent words have the same length

      //a private helper method to report the number of character matches between two Strings
		int getNumMatches(String* curr_word, String* word_guess);

   public:
		String* curr_word;
		String* word_guess;
		String* word;
		int try_passwords;
		int num_matches;
		Password();
		~Password();
		void addWord(String* word);
		void guess(int try_password, int num_matches);
		
};

#endif