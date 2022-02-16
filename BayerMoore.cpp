#include <iostream>
#include<sstream>
#include<fstream>
#include<chrono>
using namespace std;
# define CHARS 256

void BM_Shift(string str, int size,
    int badcharacter[CHARS])
{
    int i;
    for (i = 0; i < CHARS; i++)
        badcharacter[i] = -1;
    for (i = 0; i < size; i++)
        badcharacter[(int)str[i]] = i;
}
void search(string text, string pattern)
{
    int m = pattern.size();
    int n = text.size();

    int badcharacter[CHARS];

    BM_Shift(pattern, m, badcharacter);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0)
        {
            cout << "The pattern found @ " << s << endl;

            s += (s + m < n) ? m - badcharacter[text[s + m]] : 1;

        }

        else
            s += max(1, j - badcharacter[text[s + j]]);
    }
}

string FileToString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

int main()
{
    
    string filename("Sample.txt");
    //string file_contents;

    string text = FileToString(filename);
    string pattern;// = "agt tactcgtgcgtattacct";
    START:std::getline(std::cin, pattern);
    auto start = std::chrono::steady_clock::now();
    search(text, pattern);
    auto end = std::chrono::steady_clock::now();
    cout << "\nPattern : " << pattern;
    cout << "\n\nElapsed time in micro seconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " micro seconds\n";
    goto START;
    return 0;
}