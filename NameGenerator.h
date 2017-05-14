#ifndef NAMEGENERATOR_H
#define NAMEGENERATOR_H
#include <random>
#include <time.h>
#include <string>

class NameGenerator
{
private:
    int letterCount[2] = {4,8};
    std::string vowels ="aeiou";
    std::string consonants ="bcdfghklmnprstv";
public:
    NameGenerator() {}
    void NameConstructor(std::string& _outName)
    {
        int kk = rand()%(letterCount[1]-letterCount[0] + 1) + letterCount[0];
        if((int)_outName.size() != kk)
        {
            _outName.resize(kk, 'a');
        }
        int k = 0;
        int p = _outName.length();
        int tempTracker[p];
        for(int i=0; i<p; ++i)
        {
            if(i==0)
            {
                if(std::rand()%2){
                    //pick vowel
                    k = 5;
                    _outName[i] = vowels[(std::rand()%k)];
                    tempTracker[i] = 1;
                }
                else
                {
                    //pick consonant
                    k = 15;
                    _outName[i] = consonants[(std::rand()%k)];
                    tempTracker[i] = 0;
                }
            }
            else
            {
                if(tempTracker[i-1] == 0) //previous is a consonant
                {
                    //pick vowel
                    k = 5;
                    int tmpMemb = std::rand()%k;
                    while(((char)_outName[i-1] == 'j' && (char)vowels[tmpMemb] == 'y') ||
                          ((char)_outName[i-1] == 'p' && (char)vowels[tmpMemb] == 'u') ||
                          ((char)_outName[i-1] == 'm' && (char)vowels[tmpMemb] == 'i') ||
                          ((char)_outName[i-1] == 'c' && (char)vowels[tmpMemb] == 'i') ||
                          ((char)_outName[i-1] == 'g' && (char)vowels[tmpMemb] == 'i')) //add rules
                    {
                        tmpMemb = std::rand()%k;
                    }
                    _outName[i] = vowels[tmpMemb];
                    tempTracker[i] = 1;
                }
                else //previous is a vowel
                {
                    //pick consonant
                    k = 15;
                    int tmpMemb = std::rand()%k;
                    while(((char)_outName[i-1] == 'y' && (char)consonants[tmpMemb] == 'j') ||
                          ((char)_outName[i-1] == 'u' && (char)consonants[tmpMemb] == 'h')) //add rules
                    {
                        tmpMemb = std::rand()%k;
                    }
                    _outName[i] = consonants[tmpMemb];
                    tempTracker[i] = 0;
                }
            }
        }
        _outName.at(0) = toupper(_outName.at(0));
    }
};

#endif // NAMEGENERATOR_H
