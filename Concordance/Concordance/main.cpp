// This file contains starter code with stubs for student-designed portions.
// // Author: Nafis Ahmed Munim
// Date: 30 May 2022
// Using Maps to implement a concordance.

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <map>

using namespace std;

//define a FrequencyMap: Line1 --> 2, Line7 --> 1, etc.
//Line numbers are the keys, and the frequency of that line
//number is the data associated with a given key.
//Total frequency will be stored at key value of zero.
typedef map<int, int, less<int> > FrequencyMap;

//define a ConcordanceMap: "liberal" --> FrequencyMap
//Words themselves are keys, and the associated data is a FrequencyMap.
typedef map<string, FrequencyMap, less<string> > ConcordanceMap;

//utility method that expands isalpha() to account for a few extra characters
bool isalphaesque(char a)
{
    return isalpha(a) || (a == '-') || (a == '+') || (a == '\'');
}

int main()
{
    cout << "Now entering Concordance Builder" << endl;
    ConcordanceMap concord;            //declare a ConcordanceMap
    ConcordanceMap::iterator it;    //and an iterator for it
    FrequencyMap::iterator it2;        //and an iterator for a FrequencyMap

    string    fileIn, fileOut,    //fields to hold input and output file names
        word;                //and the current word in the document

    ifstream in;            //infile stream
    ofstream out;            //outfile stream

    bool running = true;

    while (running)
    {
        //refresh everything
        concord.clear();
        //it = NULL;
        //it2 = NULL;

        int line = 1;            //keeps track of what line the file is on

        //prompt user for input and output file names
        cout << "Please enter the name of the input file: ";
        cin >> fileIn;
        in.open(fileIn.c_str(), ios::in);

        cout << "Please enter the name of the output file: ";
        cin >> fileOut;
        out.open(fileOut.c_str(), ios::out);

        while (in >> word)
        {
            //make lower case
            string temp;
            for (unsigned i = 0; i < word.length(); i++)
                temp += (char)tolower(word[i]);
            word = temp;

            //trim off punctuation etc
            while (!isalphaesque(word[word.length() - 1]))
                word.erase(word.length() - 1);

            // print the word to console to be sure words read properly
            cout << "word is: " << word;

            
            if (word.length() < 7)
                cout << "\t";    //extra tab for short words
            cout << "\t(update maps with this word - not yet implemented)" << endl;

            // stub - for student to replace with logic for updating maps
            // --- STUDENT PUTS LOGIC HERE TO UPDATE MAPS FOR THIS WORD ---
            
            it = concord.find(word); //finding if the word is already been read once and pointing the iterator to that
            if(it != concord.end()){
                it2 = it->second.find(line); // if the word is found then update the frequency map and find the line it is right now
                if (it2 != it->second.end()){ //if the word is in current line then go next
                    it2->second = it2->second +1; //adding value to the frequency for current line
                    it->second[0] = it->second[0] +1; //updating the total number of frq
                }
                else{  //if not in the existing line then go next
                    it->second[0] = it->second[0] +1; //updating total frequency
                    it->second.insert(make_pair(line,1)); // creating map value for this line in the frequency map
                }
            }
            else{    //go here if the word is not in the concord map yet
                FrequencyMap wordfreq;
                wordfreq.insert(make_pair(line,1)); //creating frequency map for the word and adding line and value
                wordfreq.insert(make_pair(0,1)); // creatiiing the first 0 key for total freq
                concord.insert(make_pair(word,wordfreq)); //adding this word and freq map to concord map
            }
            //find the next character that is not a space
            //if it is an end of line character, increment the line number
            while (in.peek() == ' ')
                in.ignore();
            if (in.peek() == '\n' || in.peek() == '\r')
                line++;
        }

        //print everything to the output file all pretty using nested maps
        out << "Enhanced Concordance:" << endl << endl;
        //out << "(Printing the concordance is not yet implemented.)";

        
         
        
          for(it =concord.begin(); it != concord.end();++it){ //first print all the words of the concord
              out << it->first;
              if(it->first.length()<8){ //tabbing if the word is too long
                  out << "\t";
              }
              out << "\t[" << it->second[0] << "]\t"; // printing the total freq from the freq map of the word
           for(it2 = ++it->second.begin();it2 != it->second.end(); ++it2){ //looping through all elements in the freq map for the word
               if(it2->second > 1){ //prionting the value if the frequency is more than once in a line
               out << it2->first << " ("<< it2->second << ") "; //printing the value and the key from the freq map
               }
               else{
                   out << it2->first << " "; //just printing the line number for freq less than 2
               }
            }
              out << endl; //going to a new line and taking a new word after this line as for continues until concord map ends
        }
          

        
        cout << endl << "Enhanced Concordance has been written to " << fileOut << endl << endl;
        // close input and output file and ask if more files to process.
        in.close();
        out.close();

        bool answered = false;
        while (!answered)
        {
            char answer;
            cout << "Do you want to create a concordance for another file? (y/n): ";
            cin >> answer;
            switch (answer)
            {
            case 'y':
                answered = true;
                break;
            case 'n':
                answered = true;
                running = false;
                break;
            default:
                cout << "That is not a valid response." << endl;
            }
        }

        cout << endl;
    }

    return 0;
}

