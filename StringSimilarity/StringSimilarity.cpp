#include <cstring>
#include <string.h>
#include <iostream>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

int stringSimilarity(string s) {
    int n;
    const char* c = s.c_str();
    n = strlen(c);

    char s1[255];
    strcpy(s1, c);

    s1[n] = '\0';

    char** sufix = new char* [n];
    for (int i = 0; i < n; i++)
    {
        sufix[i] = new char[n - i + 1];
        strcpy(sufix[i], s1 + i);
    }

    char s2[255];
    int* numberOfSimilarities = new int[n];

    for (int i = 0; i < n; i++)
    {
        numberOfSimilarities[i] = 0;

        for (int j = 1; j <= n - i; j++)
        {
            strncpy(s2, s1, j);
            s2[j] = '\0';

            char prefixSufix[255];
            strncpy(prefixSufix, sufix[i], j);
            prefixSufix[j] = '\0';

            if (strcmp(s2, prefixSufix) == 0)
                numberOfSimilarities[i] = j;
            else
                break;
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += numberOfSimilarities[i];

    for (int i = 0; i < n; i++)
        delete[] sufix[i];

    delete[] sufix;
    delete[] numberOfSimilarities;

    return sum;
}

int main()
{
    
    string s;
    cout << "String: ";
    cin >> s;

    int rez = stringSimilarity(s);

    cout << "Similarity = " << rez << endl;

    return 0;
}
