#ifndef NAMEGENERATOR_H
#define NAMEGENERATOR_H
#include <random>
#include <time.h>
#include <string>

/// \brief A module for generating random names
/// \author Renats Bikmajevs

/// \class NameGenerator
/// \brief Generates random names based on a set of rules

class NameGenerator
{
public:
    /// \brief default ctor
    NameGenerator() {}
    /// \brief method for name generation
    /// \param[io] _outName the name variable wich will be edited
    void NameConstructor(std::string& _outName)
    {
        //make random size of the word in range {minSize, maxSize}
        int kk = rand()%(m_letterCount[1]-m_letterCount[0] + 1) + m_letterCount[0];
        if((int)_outName.size() != kk) //maybe we don't need to resize
        {
            _outName.resize(kk, 'a');
        }
        int k = 0; //k will be either the size of the vowel array (5)
        //or the size of the consonant array (15)
        int p = _outName.length(); //p is symbol count
        int tempTracker[p];//array to track symbol types at corresponding positions
        for(int i=0; i<p; ++i)
        {
            if(i==0) //first symbol
            {
                if(std::rand()%2){
                    //pick vowel
                    k = 5;
                    _outName[i] = m_vowels[(std::rand()%k)];
                    tempTracker[i] = 1;
                }
                else
                {
                    //pick consonant
                    k = 15;
                    _outName[i] = m_consonants[(std::rand()%k)];
                    tempTracker[i] = 0;
                }
            }
            else //all other symbols
            {
                if(tempTracker[i-1] == 0) //previous is a consonant
                {
                    //pick vowel
                    k = 5;
                    int tmpMemb = std::rand()%k;
                    while(((char)_outName[i-1] == 'j' && (char)m_vowels[tmpMemb] == 'y') ||
                          ((char)_outName[i-1] == 'p' && (char)m_vowels[tmpMemb] == 'u') ||
                          ((char)_outName[i-1] == 'm' && (char)m_vowels[tmpMemb] == 'i') ||
                          ((char)_outName[i-1] == 'c' && (char)m_vowels[tmpMemb] == 'i') ||
                          ((char)_outName[i-1] == 'g' && (char)m_vowels[tmpMemb] == 'i')) //add rules
                    {
                        tmpMemb = std::rand()%k;
                    }
                    _outName[i] = m_vowels[tmpMemb];
                    tempTracker[i] = 1;
                }
                else //previous is a vowel
                {
                    //pick consonant
                    k = 15;
                    int tmpMemb = std::rand()%k;
                    while(((char)_outName[i-1] == 'y' && (char)m_consonants[tmpMemb] == 'j') ||
                          ((char)_outName[i-1] == 'u' && (char)m_consonants[tmpMemb] == 'h')) //add rules
                    {
                        tmpMemb = std::rand()%k;
                    }
                    _outName[i] = m_consonants[tmpMemb];
                    tempTracker[i] = 0;
                }
            }
        }
        _outName.at(0) = toupper(_outName.at(0)); //first symbol should be capital
    }
private:
    /// \brief min and max symbol count of the word
    int m_letterCount[2] = {4,8};
    /// \brief an array of vovels (y is not here intentionally)
    std::string m_vowels ="aeiou";
    /// \brief an array of consonants (some are not included)
    std::string m_consonants ="bcdfghklmnprstv";
}; //end of class

#endif // NAMEGENERATOR_H
