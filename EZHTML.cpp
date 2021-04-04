/*
    EZHTML : An easy static website generator, written entirely in C++
    Copyright (C) 2021 Aaron Lee

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <fstream>
#include <filesystem>
using namespace std;
string CSS[100], JS[100];
int CSScount = 0, JScount = 0;

void generateFinalFile(string fileName, string titleName)
{
    ofstream EachFile("output/" + fileName + ".html");
    EachFile << "<html>\n\n";
    EachFile << "<head>\n\t<title>" << titleName << "</title>\n";
    for (int i = 0; i < CSScount; i++)
        EachFile << "\t<link rel=\"stylesheet\" href=\"" << CSS[i] << "\">\n";
    EachFile << "</head>\n\n<body>\n";

    ifstream NAVread("NAV.html");
    string gotText;
    while (getline(NAVread, gotText))
        EachFile << "\t" << gotText << "\n";
    NAVread.close();

    EachFile << "\t<div class=\"container\">\n";

    ifstream PAGEread(fileName + ".html");
    while (getline(PAGEread, gotText))
        EachFile << "\t\t" << gotText << "\n";
    PAGEread.close();

    EachFile << "\t</div>\n";
    for (int i = 0; i < JScount; i++)
        EachFile << "\t<script src=\"" << JS[i] << "\"></script>\n";

    ifstream FOOTERread("FOOTER.html");
    while (getline(FOOTERread, gotText))
        EachFile << "\t" << gotText << "\n";
    FOOTERread.close();

    EachFile << "</body>\n\n</html>";
    EachFile.close();
}

int main()
{
    auto start = std::chrono::system_clock::now();
    int readSmthing = 0, tempCSScnt, tempJScnt;
    string myText, tempFileName;
    ifstream INFOread("info");
    while (getline(INFOread, myText))
    {
        if (readSmthing != 0)
        {
            if (readSmthing == 1)
            {
                CSS[tempCSScnt] = myText;
                tempCSScnt++;
                if (tempCSScnt == CSScount)
                    readSmthing = 0;
            }
            else if (readSmthing == 2)
            {
                JS[tempJScnt] = myText;
                tempJScnt++;
                if (tempJScnt == JScount)
                    readSmthing = 0;
            }
            else if (readSmthing == 3)
            {
                generateFinalFile(myText, tempFileName);
                readSmthing = 0;
            }
        }
        else if (myText[0] == '^')
        {
            if (myText.substr(1, 3) == "CSS")
            {
                CSScount = myText[4] - '0';
                tempCSScnt = 0;
                readSmthing = 1;
            }
            else if (myText.substr(1, 2) == "JS")
            {
                JScount = myText[3] - '0';
                tempJScnt = 0;
                readSmthing = 2;
            }
        }
        else if (myText[0] == '#')
        {
            readSmthing = 3;
            tempFileName = myText.substr(1);
        }
    }
    INFOread.close();
    std::filesystem::copy("./static", "./output/static", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    ofstream ResultsFile("output/results");
    ResultsFile << "/output/ was generated successfully at " << ctime(&end_time);
    ResultsFile << "\nelapsed time: " << elapsed_seconds.count() << "s";
    return 0;
}