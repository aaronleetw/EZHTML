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
string CSS[100], JS[100], LOCATION = "docs";
int CSScount = 0, JScount = 0;

void generateFinalFile(string fileName, string titleName)
{
    std::ofstream EachFile("./" + LOCATION + "/" + fileName + ".html");
    EachFile << "<!-- Website generated using EZHTML -->\n";
    EachFile << "<!-- View the project on Github: https://github.com/aaronleetw/EZHTML -->\n";
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

int getAllTheNumbers(string str)
{
    int N = 0;
    for (int i = 0; i < str.size(); i++)
        N = (N * 10) + ((int)(str[i]) - '0');
    return N;
}

void resetDir()
{
    std::filesystem::remove_all("./" + LOCATION + "/");
    std::filesystem::create_directories("./" + LOCATION + "/");
}

int main()
{
    auto start = std::chrono::system_clock::now();
    int readSmthing = 0, tempCSScnt, tempJScnt;
    string myText, tempTitleName;
    ifstream INFOread("INFO");
    while (getline(INFOread, myText))
    {
        if (readSmthing != 0)
        {
            if (readSmthing == 1) // READ CSS
            {
                CSS[tempCSScnt] = myText;
                tempCSScnt++;
                if (tempCSScnt == CSScount)
                    readSmthing = 0;
            }
            else if (readSmthing == 2) // READ JS
            {
                JS[tempJScnt] = myText;
                tempJScnt++;
                if (tempJScnt == JScount)
                    readSmthing = 0;
            }
            else if (readSmthing == 3) // READ PAGE TITLE
            {
                generateFinalFile(myText, tempTitleName);
                readSmthing = 0;
            }
            else if (readSmthing == 4) // READ LOCATION
            {
                LOCATION = myText;
                resetDir();
                readSmthing = 0;
            }
        }
        else if (myText[0] == '^')
        {
            if (myText.substr(1, 2) == "JS")
            {
                JScount = getAllTheNumbers(myText.substr(4));
                tempJScnt = 0;
                readSmthing = 2;
            }
            else if (myText.substr(1, 3) == "CSS")
            {
                CSScount = getAllTheNumbers(myText.substr(4));
                tempCSScnt = 0;
                readSmthing = 1;
            }
            else if (myText.substr(1, 8) == "LOCATION")
                readSmthing = 4;
        }
        else if (myText[0] == '#')
        {
            readSmthing = 3;
            tempTitleName = myText.substr(1);
        }
    }
    INFOread.close();
    std::filesystem::copy("./static", "./" + LOCATION + "/static", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::ofstream ResultsFile("./" + LOCATION + "/results");
    ResultsFile << "./" + LOCATION + "/ was generated successfully at " << ctime(&end_time);
    ResultsFile << "elapsed time: " << elapsed_seconds.count() << "s";
    return 0;
}