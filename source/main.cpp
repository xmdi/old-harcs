#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "headers.h"
#include <shlobj.h>
#include "rlutil.h"
#include <chrono>
#include <algorithm>
using namespace std;

typedef std::chrono::high_resolution_clock Clock;

string cubeRevert(bool);
void applyMove2(char amove);
void showCube(void);
void unpruner(void);
string remove_last_word_if(string sentence);
//void algparser(int);
size_t countWords(std::string s);
string solutionreducer(string,int);
string scramble;
string inputWCA;
bool firstWordWCA=0;
bool isScramble2=0;
bool isSolver2=0;
bool isCheck=0;
bool isDepth=0;
bool isAnalyze=0;
bool isAlgSearch=0;
bool isSet=0;
bool isLoad=0;
bool isHacks=0;
int isSet2=0;
int number=3;
int oldnumber=0;
int tempnumber;
bool setOutput=1;
bool asetstate=0;
bool prunedyet=0;
int prunedmethod=99;
uint64_t EPo, EOo, CPo, COo, CNo;
bool dosomething(int, int, string, bool);
vector < string > orientations;
vector < string > rotations;
bool firstdo=1;
bool vis=0;
string usedrotation;
string usedorientation;
bool customparser(string);
bool executecommand(string comma, int nom, vector < string > oris, vector < string > rots);
void cubeSet(vector < uint64_t > setter);
vector <uint64_t> randomizer2();
vector < uint64_t > setter(5);
string moveReverse(string a);
vector < char > move2vec (string movesstring);
string vec2move ( vector < char >  movevec);
void solves12(int depth, int method, int step, int nom, vector < string > oris, vector < string > rots, int allowedmoves);
void analyze(int quantity, int prunedmethod, vector < string > orientations, vector < string > rotations, int NTHREADS);
void prunes12 (int depth, int method, int step, int allowedmoves);
string trim(const string& str);
int colorH=0;
int colorI=0;
int colorO=0;
int NTHREADS=0;
string cterm="";
bool isHisto=0;
void exportAnalysis();
void makeHistogram(string whichstep, int method);
void algSearch(int);
void fmc(int branchf, int prunedmethod, vector < string > orientations, vector < string > rotations);

void introWCA()
{
    cout << string(100, '\n') <<
         "      ooooo   ooooo       .o.       ooooooooo.     .oooooo.    .oooooo..o \n"
         "      `888'   `888'      .888.      `888   `Y88.  d8P'  `Y8b  d8P'    `Y8 \n"
         "       888     888      .88888.      888   .d88' 888          Y88bo.      \n"
         "       888ooooo888     .8' `888.     888ooo88P'  888           `\Y8888o.  \n"
         "       888     888    .88ooo8888.    888`88b.    888               `\Y88b \n"
         "       888     888   .8'     `888.   888  `88b.  `88b    ooo  oo     .d8P \n"
         "      o888o   o888o o88o     o8888o o888o  o888o  `Y8bood8P'  `8888888P' \n\n\n"
         "                       Here's A Replacement Cube Solver\n\n\n\n\n\n\n";
}
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

string ToString(size_t val)
{
    stringstream stream;
    stream << val;
    return stream.str();
}

string replaceStrChar(string str, const string& replace, char ch)
{

    size_t found = str.find_first_of(replace);

    while (found != string::npos)
    {
        str[found] = ch;
        found = str.find_first_of(replace, found+1);
    }

    return str; // return our new string.
}

void addOris(string buf)
{
    if (buf=="UB")
    {
        orientations.push_back("UB");
        rotations.push_back("y2");
    }
    else if (buf=="UR")
    {
        orientations.push_back("UR");
        rotations.push_back("y'");
    }
    else if (buf=="UF")
    {
        orientations.push_back("UF");
        rotations.push_back(" ");
    }
    else if (buf=="UL")
    {
        orientations.push_back("UL");
        rotations.push_back("y");
    }
    else if (buf=="BL")
    {
        orientations.push_back("BL");
        rotations.push_back("z' y");
    }
    else if (buf=="BR")
    {
        orientations.push_back("BR");
        rotations.push_back("z y'");
    }
    else if (buf=="FR")
    {
        orientations.push_back("FR");
        rotations.push_back("z' y'");
    }
    else if (buf=="FL")
    {
        orientations.push_back("FL");
        rotations.push_back("z y");
    }
    else if (buf=="DB")
    {
        orientations.push_back("DB");
        rotations.push_back("x2");
    }
    else if (buf=="DR")
    {
        orientations.push_back("DR");
        rotations.push_back("y z2");
    }
    else if (buf=="DF")
    {
        orientations.push_back("DF");
        rotations.push_back("z2");
    }
    else if (buf=="DL")
    {
        orientations.push_back("DL");
        rotations.push_back("y' z2");
    }
    else if (buf=="BU")
    {
        orientations.push_back("BU");
        rotations.push_back("x");
    }
    else if (buf=="RU")
    {
        orientations.push_back("RU");
        rotations.push_back("x y");
    }
    else if (buf=="FU")
    {
        orientations.push_back("FU");
        rotations.push_back("x y2");
    }
    else if (buf=="LU")
    {
        orientations.push_back("LU");
        rotations.push_back("x y'");
    }
    else if (buf=="LB")
    {
        orientations.push_back("LB");
        rotations.push_back("z y2");
    }
    else if (buf=="RB")
    {
        orientations.push_back("RB");
        rotations.push_back("z' y2");
    }
    else if (buf=="RF")
    {
        orientations.push_back("RF");
        rotations.push_back("z");
    }
    else if (buf=="LF")
    {
        orientations.push_back("LF");
        rotations.push_back("z'");
    }
    else if (buf=="BD")
    {
        orientations.push_back("BD");
        rotations.push_back("x' y2");
    }
    else if (buf=="RD")
    {
        orientations.push_back("RD");
        rotations.push_back("x' y'");
    }
    else if (buf=="FD")
    {
        orientations.push_back("FD");
        rotations.push_back("x'");
    }
    else if (buf=="LD")
    {
        orientations.push_back("LD");
        rotations.push_back("x' y");
    }

    else if (buf=="DCN")
    {
        orientations.push_back("UB");
        rotations.push_back("y2");

        orientations.push_back("UR");
        rotations.push_back("y'");

        orientations.push_back("UF");
        rotations.push_back("");

        orientations.push_back("UL");
        rotations.push_back("y");

        orientations.push_back("DB");
        rotations.push_back("x2");

        orientations.push_back("DR");
        rotations.push_back("y z2");

        orientations.push_back("DF");
        rotations.push_back("z2");

        orientations.push_back("DL");
        rotations.push_back("y' z2");
    }

    else if (buf=="CN")
    {
        orientations.push_back("UB");
        rotations.push_back("y2");

        orientations.push_back("UR");
        rotations.push_back("y'");

        orientations.push_back("UF");
        rotations.push_back(" ");

        orientations.push_back("UL");
        rotations.push_back("y");

        orientations.push_back("BL");
        rotations.push_back("z' y");

        orientations.push_back("BR");
        rotations.push_back("z y'");

        orientations.push_back("FR");
        rotations.push_back("z' y'");

        orientations.push_back("FL");
        rotations.push_back("z y");

        orientations.push_back("DB");
        rotations.push_back("x2");

        orientations.push_back("DR");
        rotations.push_back("y z2");

        orientations.push_back("DF");
        rotations.push_back("z2");

        orientations.push_back("DL");
        rotations.push_back("y' z2");

        orientations.push_back("BU");
        rotations.push_back("x");

        orientations.push_back("RU");
        rotations.push_back("x y");

        orientations.push_back("FU");
        rotations.push_back("x y2");

        orientations.push_back("LU");
        rotations.push_back("x y'");

        orientations.push_back("LB");
        rotations.push_back("z y2");

        orientations.push_back("RB");
        rotations.push_back("z' y2");

        orientations.push_back("RF");
        rotations.push_back("z");

        orientations.push_back("LF");
        rotations.push_back("z'");

        orientations.push_back("BD");
        rotations.push_back("x' y2");

        orientations.push_back("RD");
        rotations.push_back("x' y'");

        orientations.push_back("FD");
        rotations.push_back("x'");

        orientations.push_back("LD");
        rotations.push_back("x' y");
    }

    else if (buf==cterm)
    {
        cout<<"\n   orientations set to: ";
        isCheck=0;
        for (int i=0; i<orientations.size(); i++)
        {
            cout<<orientations[i]<<" ";
        }
        cout<<"\n\n";
    }
    else
        cout << "\n   invalid orientation specified.\n\n";

}

string concatOris()
{
    string outstring="";
    for (int j=0;j<orientations.size();j++)
        outstring+=orientations[j]+" ";
    return trim(outstring);
}


void putCursor()
{
    cout<<"HARCS>> ";
}
void showHelpWCA()
{
    cout <<"\n   info\t\tdisplay version information\n"
         "   apply * "<<cterm<<"\tapply a scramble/moves to current cube, ending with "<<cterm<<"\n\t\t   (ex: apply R U2 B' L ... "<<cterm<<")\n"
         "   set * * * * * "<<cterm<<" set a scrambled state via hex input; order EP EO CP CO CN\n"
         "   random\tset to random cubestate\n"
         "   revert\trevert cube to solved state\n"
         "   number *\tset desired count of substep solutions (current: "<<number<<")\n"
         "   state\tshow current hexadecimal cubestate representation\n"
         "   view\t\tview current cube in browser\n"
         "   print\tprint applied sequences on current cube\n"
         "   save\t\tappend applied sequences to solutions.txt\n"
         "   style * "<<cterm<<"\tset solution orientations, CN and DCN are options\n\t\t   (ex: style UF DB "<<cterm<<") (current: "<<concatOris()<<") \n"
         "\n   Type 'help2' for the rest of the commands.\n\n";
}
void showHelpWCA2()
{
    cout <<"\n   cfop\t\tprunes for cross (D) and xcross (D,DFR)\n"
         "   petrus\tprunes for 2x2x2 (DLB), 3x2x2 (DL), eo, f2l, and zbll\n"
         "   roux\t\tprunes for fs (DLB), fb (DL), sb (DR), cmll, and lse\n"
         "   zz\t\tprunes for eoline (D), eo3x2x2 (DL), lb, rb, and zbll\n"
         "   load *\tloads the method defined in text file (ex: load SSC.txt)\n"
         "   all\t\tsolves entire cube with set method in single orientation\n"
         "   analyze *\tanalyzes desired number of solves with set method\n"
         "   export\texports raw solve data from latest analysis\n"
         "   histogram *\tcreates a movecount histogram for *=step from analysis\n"
         "   hacks *\texecutes linear FMC with desired branch factor\n"
         "   algsearch *\tfinds * algs between steps defined in input file\n\n"
         "   To solve a substep for a pruned method, type the step, as written above.\n"
         "   To apply a generated substep solution, type the number next to it.\n\n"
         ;

}
int getInputWCA(bool CLI, string commands)
{

    while (1)
    {
        if (CLI)
        {
            inputWCA=commands;
        }
        else
        {
            firstWordWCA=0;
            cout<<"HARCS>> ";
            getline(cin, inputWCA);
        }
        string buf;
        stringstream ss(inputWCA);
        while (ss >> buf)
        {
            rlutil::setColor(colorO);
            bool notrecognized=1;
            if (buf=="test")
            {

                auto t1 = std::chrono::high_resolution_clock::now();
                for (int i=0; i<1e8; i++)
                    applyMove2(rand()%18);
                auto t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> diff=t2-t1;
                std::cout<<"   1e8 6gen: "<<diff.count()<<" s \n";

                t1 = std::chrono::high_resolution_clock::now();
                for (int i=0; i<1e8; i++)
                    applyMove2(rand()%6);
                t2 = std::chrono::high_resolution_clock::now();
                diff=t2-t1;
                std::cout<<"   1e8 easy: "<<diff.count()<<" s \n";

                int j=0;
                t1 = std::chrono::high_resolution_clock::now();
                for (int i=0; i<1e8; i++)
                    j=rand()%6;
                t2 = std::chrono::high_resolution_clock::now();
                diff=t2-t1;
                std::cout<<"   1e8 rand: "<<diff.count()<<" s \n";

             /*   std::cout<<"\n   5 candidate desktop backgrounds opened in default browser. You're welcome.\n\n";
                string url="http://wallpapersdsc.net/wp-content/uploads/2016/01/Alex-Morgan-Desktop.jpg";
                ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );
                url="http://images.performgroup.com/di/library/goal_es/96/b5/alex-morgan-usa_1s9ri4wgd2n111nscf2jkt1g1l.jpg";
                ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );
                url="http://www.espn.com/photo/2013/1210/ew_g_morgan_b1_800x450.jpg";
                ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );
                url="https://cdn-s3.si.com/s3fs-public/images/Alex-Morgan-X159570_TK1_0281.jpg";
                ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );
                url="http://mydotcomrade.com/wp-content/uploads/2013/11/Alex-Morgan_82.jpg";
                ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );*/
                firstWordWCA=1;
            }
            if (buf=="gullible")
            {
                std::cout<<"\n   3.141592653\n\n";
                firstWordWCA=1;
            }

            if (isLoad)
            {
                if (prunedyet)
                {
                    unpruner();
                    cout<<"\n   Clearing old tables.\n";
                }
                if (customparser(buf))
                {
                    prunedyet=1;
                    prunedmethod=4;
                }
                firstWordWCA=1;
                isLoad=0;
            }
            if (buf=="load")
            {
                firstWordWCA=1;
                isLoad=1;
            }
            if (buf=="petrus")
            {
                firstWordWCA=1;
                if (prunedmethod==1)
                {
                    cout<<"\n   petrus already loaded.\n\n";
                }
                else
                {
                    prunedmethod=1;
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    auto t1 = Clock::now();
                    auto t2 = t1;
                    int cum=0;
                    cout<<"\n      2x2x2";
                    prunes12(4,1,0,1);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      3x2x2";
                    prunes12(5,1,1,1);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      eo";
                    prunes12(4,1,2,6);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      f2l";
                    prunes12(7,1,3,4);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      zbll";
                    prunes12(1,1,4,8);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    cout<<"   Loaded petrus in "<< cum <<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=1;
                }

            }

            if (buf=="cfop")
            {

                firstWordWCA=1;
                if (prunedmethod==0)
                {
                    cout<<"\n   cfop already loaded.\n\n";
                }
                else
                {
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    auto t1 = Clock::now();
                    auto t2 = t1;
                    int cum=0;
                    cout<<"\n      cross";
                    prunes12(4,0,0,1);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      xcross";
                    prunes12(5,0,1,1);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    cout<<"   Loaded cfop in "<< cum <<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=0;
                }
            }

            if (buf=="zz")
            {
                auto t1 = Clock::now();
                firstWordWCA=1;
                if (prunedmethod==3)
                {
                    cout<<"\n   zz already loaded.\n\n";
                }
                else
                {
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    auto t1 = Clock::now();
                    auto t2 = t1;
                    int cum=0;
                    cout<<"\n      eoline";
                    prunes12(4,3,0,1);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      eo3x2x2";
                    prunes12(5,3,1,1);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      lb";
                    prunes12(6,3,2,5);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      rb";
                    prunes12(7,3,3,4);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      zbll";
                    prunes12(1,3,4,8);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    cout<<"   Loaded zz in "<< cum <<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=3;
                }

            }

            if (buf=="roux")
            {
                auto t1 = Clock::now();
                firstWordWCA=1;
                if (prunedmethod==2)
                {
                    cout<<"\n   roux already loaded.\n\n";
                }
                else
                {
                    if (prunedyet)
                    {
                        unpruner();
                        cout<<"\n   Clearing old tables.\n";
                    }
                    auto t1 = Clock::now();
                    auto t2 = t1;
                    int cum=0;
                    cout<<"\n      fs";
                    prunes12(4,2,3,2);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      fb";
                    prunes12(4,2,0,2);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      sb";
                    prunes12(7,2,1,3);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      cmll";
                    prunes12(1,2,4,8);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    t1 = Clock::now();
                    cout<<"      lse";
                    prunes12(10,2,5,7);
                    t2 = Clock::now();
                    cout<<" in "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n"<<std::endl;
                    cum+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    cout<<"   Loaded roux in "<< cum <<" ms \n"<<std::endl;
                    prunedyet=1;
                    prunedmethod=2;
                }
            }


            if (buf=="histogram")
            {
                firstWordWCA=1;
                isHisto=1;
            }
            else if (isHisto)
            {
                firstWordWCA=1;
                makeHistogram(buf,prunedmethod);
                isHisto=0;
                rlutil::setColor(colorI);
                break;
            }

            if (prunedmethod==4)
            {
                notrecognized=executecommand(buf,number,orientations,rotations);
            }
            else
            {
                if (buf=="all")
                {
                    oldnumber=number;
                    number=1;
                    firstWordWCA=1;
                    if (prunedmethod!=1&&prunedmethod!=2&&prunedmethod!=3)
                    {
                        cout<<"\n   must be pruned for petrus/roux/zz/custom\n\n";
                    }
                    else if (orientations.size()==1)
                    {
                        auto t1 = Clock::now();
                        if (prunedmethod==1) // petrus
                        {
                            solves12(6,1,1,number,orientations,rotations,1);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(5,1,2,number,orientations,rotations,6);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(7,1,3,number,orientations,rotations,4);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(1,1,4,number,orientations,rotations,8);
                            firstdo=dosomething(0,1," ",firstdo);
                            auto t2 = Clock::now();
                            cout<<"\n   stepwise-optimal petrus solution applied in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n\n";
                        }

                        if (prunedmethod==2) // roux
                        {
                            solves12(5,2,0,number,orientations,rotations,2);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(6,2,1,number,orientations,rotations,3);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(1,2,4,number,orientations,rotations,8);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(10,2,5,number,orientations,rotations,7);
                            firstdo=dosomething(0,1," ",firstdo);
                            auto t2 = Clock::now();
                            cout<<"\n   stepwise-optimal roux solution applied in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n\n";
                        }

                        if (prunedmethod==3) // zz
                        {
                            solves12(5,3,0,number,orientations,rotations,1);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(6,3,2,number,orientations,rotations,5);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(7,3,3,number,orientations,rotations,4);
                            firstdo=dosomething(0,1," ",firstdo);
                            solves12(1,3,4,number,orientations,rotations,8);
                            firstdo=dosomething(0,1," ",firstdo);
                            auto t2 = Clock::now();
                            cout<<"\n   stepwise-optimal zz solution applied in "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<" ms \n\n";
                        }

                    }
                    else
                    {
                        cout<<"\n   specify a single orientation\n\n";
                    }
                    number=oldnumber;
                }



                if (buf=="eoline")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,3,0,number,orientations,rotations,1);
                    }
                }

                if (buf=="eo3x2x2")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,3,1,number,orientations,rotations,1);
                    }
                }

                if (buf=="lb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,3,2,number,orientations,rotations,5);
                    }
                }

                if (buf=="rb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3)
                    {
                        cout<<"\n   zz is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(7,3,3,number,orientations,rotations,4);
                    }
                }

                if (buf=="zbll")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=3 && prunedmethod!=1)
                    {
                        cout<<"\n   neither zz nor petrus is currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(1,1,4,number,orientations,rotations,8);
                    }
                }

                if (buf=="fs")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(4,2,3,number,orientations,rotations,2);
                    }
                }


                if (buf=="fb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,2,0,number,orientations,rotations,2);
                    }
                }

                if (buf=="sb")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,2,1,number,orientations,rotations,3);
                    }
                }


                if (buf=="cmll")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(1,2,4,number,orientations,rotations,8);
                    }
                }


                if (buf=="lse")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=2)
                    {
                        cout<<"\n   roux is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(10,2,5,number,orientations,rotations,7);
                    }
                }


                if (buf=="cross")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=0)
                    {
                        cout<<"\n   cfop is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,0,0,number,orientations,rotations,1);
                    }
                }

                if (buf=="xcross")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=0)
                    {
                        cout<<"\n   cfop is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,0,1,number,orientations,rotations,1);
                    }
                }

                if (buf=="2x2x2")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,1,0,number,orientations,rotations,1);
                    }
                }

                if (buf=="3x2x2")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(6,1,1,number,orientations,rotations,1);
                    }
                }

                if (buf=="eo")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(5,1,2,number,orientations,rotations,6);
                    }
                }

                if (buf=="f2l")
                {
                    firstWordWCA=1;
                    if (prunedmethod!=1)
                    {
                        cout<<"\n   petrus is not currently loaded.\n\n";
                    }
                    else
                    {
                        solves12(7,1,3,number,orientations,rotations,4);
                    }
                }

            }
            if (buf=="illuminati")
            {
                firstWordWCA=1;
                cout<<"\n   Confirmed.\n\n";
            }
            if (buf=="help")
            {
                firstWordWCA=1;
                showHelpWCA();
            }
            if (buf=="help2")
            {
                firstWordWCA=1;
                showHelpWCA2();
            }
            else if (buf=="cls")
            {
                firstWordWCA=1;
                cout << string(400, '\n');
            }
            else if (buf=="info")
            {
                firstWordWCA=1;
                cout << "\n   HARCS v0.9e : 01-14-2019 : Matt DiPalma : USA\n\n";
            }
            else if (buf=="number")
            {
                firstWordWCA=1;
                isDepth=1;
            }
            else if (buf=="analyze")
            {
                firstWordWCA=1;
                isAnalyze=1;
            }
            else if (buf=="algsearch")
            {
                firstWordWCA=1;
                isAlgSearch=1;
            }
            else if (buf=="hacks")
            {
                firstWordWCA=1;
                isHacks=1;
            }
            else if (buf=="revert")
            {
                firstWordWCA=1;
                scramble=cubeRevert(1);
                usedrotation.clear();
                firstdo=1;
                asetstate=0;
                cout << "\n   Reset to solved.\n\n";
            }
            else if (buf=="state")
            {
                firstWordWCA=1;
                showCube();
            }
            else if (buf=="print")
            {
                firstWordWCA=1;
                if (!wherretf.empty())
                {
                    for (int j=0; j<wherretf.size(); j++)
                    {
                        if (asetstate && j==0)
                        {
                            cout<<std::hex<<"\n   init state:\n   EP: 0x"<<EPo<<"\n   EO: 0x"<<EOo<<"\n   CP: 0x"<<CPo<<"\n   CO: 0x"<<COo<<"\n   CN: 0x"<<CNo<<"\n";
                        }
                        cout <<std::dec<< "\n   "<<wherretf[j][0]<<" // "<<wherretf[j][1];
                        if (j>1 || (j>0 && asetstate))
                        {
                            cout<<" ("<<countWords(wherretf[j][0])<<")";
                        }
                        cout<<endl;
                    }
                    cout<<endl;
                }
                else
                {
                    cout<<"\n   no sequences applied yet\n\n";
                }
            }
            else if (buf=="save")
            {
                firstWordWCA=1;
                ofstream outfile;
                outfile.open("solutions.txt",ios_base::app);
                if (!wherretf.empty())
                {
                    //outfile<<endl;
                    for (int j=0; j<wherretf.size(); j++)
                    {
                        if (asetstate && j==0)
                        {
                            outfile<<std::hex<<"\ninit state: 0x"<<EPo<<" 0x"<<EOo<<" 0x"<<CPo<<" 0x"<<COo<<" 0x"<<CNo<<std::dec;
                        }
                        outfile << "\n"<<wherretf[j][0]<<" // "<<wherretf[j][1];
                        if (j>1 || (j>0 && asetstate))
                        {
                            outfile<<" ("<<countWords(wherretf[j][0])<<")";
                        }
                        // outfile<<endl;
                    }
                    outfile<<"\n---"<<endl;
                    cout<<"\n   sequences saved to solutions.txt\n\n";
                }
                else
                {
                    cout<<"\n   no sequences applied yet\n\n";
                }
                outfile.close();
            }
            else if (buf=="export")
            {
                firstWordWCA=1;
                exportAnalysis();
            }
            else if (buf=="view")
            {
                firstWordWCA=1;
                if (!wherretf.empty())
                {
                    string url;
                    if (vis==0)
                    {
                        url="https://alg.cubing.net?";
                        string useit;
                        if (!asetstate)
                        {
                            for (int j=0; j<wherretf.size(); j++)
                            {
                                useit=replaceStrChar(wherretf[j][0], "'", '-');
                                useit=replaceStrChar(useit, " ", '_');
                                if (j==0)
                                {
                                    url+=("setup="+useit);
                                }
                                else if (j==1)
                                {
                                    url+=("&alg="+useit+"_%2F%2F_"+wherretf[j][1]);
                                }
                                else if (j>1)
                                {
                                    url+=("%0A"+useit+"_%2F%2F_"+wherretf[j][1]+"_("+ToString(countWords(wherretf[j][0]))+")");
                                }
                            }
                        }
                        else if (asetstate)
                        {
                            for (int j=0; j<wherretf.size(); j++)
                            {
                                if (j==0)
                                {
                                    useit="";
                                    for (int k=0; k<wherretf.size(); k++)
                                    {
                                        useit+=(wherretf[k][0]+" ");
                                    }
                                    useit=moveReverse(useit);
                                    useit=replaceStrChar(useit, "'", '-');
                                    useit=replaceStrChar(useit, " ", '_');
                                    url+=("setup="+useit);
                                    useit=replaceStrChar(wherretf[j][0], "'", '-');
                                    useit=replaceStrChar(useit, " ", '_');
                                    url+=("&alg="+useit+"_%2F%2F_"+wherretf[j][1]);
                                }
                                else if (j>0)
                                {
                                    useit=replaceStrChar(wherretf[j][0], "'", '-');
                                    useit=replaceStrChar(useit, " ", '_');
                                    url+=("%0A"+useit+"_%2F%2F_"+wherretf[j][1]+"_("+ToString(countWords(wherretf[j][0]))+")");
                                }
                            }
                        }
                    }
                    else if (vis==1)
                        {
                        url="https://xmdi.github.io?";
                        string useit;
                        if (!asetstate)
                        {
                            for (int j=0; j<wherretf.size(); j++)
                            {
                                useit=replaceStrChar(wherretf[j][0], " ", '_');
                                if (j==0)
                                {
                                    url+=("sc="+useit);
                                }
                                else if (j==1)
                                {
                                    url+=("&so="+useit+"_%2F%2F_"+wherretf[j][1]);
                                }
                                else if (j>1)
                                {
                                    url+=("_^n_"+useit+"_%2F%2F_"+wherretf[j][1]);
                                }
                            }
                        }
                        else if (asetstate)
                        {
                            for (int j=0; j<wherretf.size(); j++)
                            {
                                if (j==0)
                                {
                                    useit="";
                                    for (int k=0; k<wherretf.size(); k++)
                                    {
                                        useit+=(wherretf[k][0]+" ");
                                    }
                                    useit=moveReverse(useit);
                                    useit=replaceStrChar(useit, "'", '-');
                                    useit=replaceStrChar(useit, " ", '_');
                                    url+=("sc="+useit);
                                    useit=replaceStrChar(wherretf[j][0], "'", '-');
                                    useit=replaceStrChar(useit, " ", '_');
                                    url+=("&so="+useit+"_%2F%2F_"+wherretf[j][1]);
                                }
                                else if (j>0)
                                {
                                    useit=replaceStrChar(wherretf[j][0], "'", '-');
                                    useit=replaceStrChar(useit, " ", '_');
                                    url+=("_^n_"+useit+"_%2F%2F_"+wherretf[j][1]);
                                }
                            }
                        }
                    }



                    cout<<"\n   opening visualization in default browser\n\n";
                    ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );

                }

                else
                {
                    cout<<"\n   no sequences applied yet\n\n";
                }
            }


            else if (buf == "style")
            {
                firstWordWCA=1;
                isCheck=1;
                orientations.clear();
                rotations.clear();

            }
            else if (isCheck)
            {
                addOris(buf);
            }

            else if (buf=="set")
            {
                isSet=1;
                cout << "\n   state set\n\n";
            }

            else if (buf=="random")
            {
                    scramble=cubeRevert(1);
                    vector <uint64_t> sss = randomizer2();
                    cubeSet(sss);
                    asetstate=1;
                    EPo=sss[0];
                    EOo=sss[1];
                    CPo=sss[2];
                    COo=sss[3];
                    CNo=sss[4];
                    firstWordWCA=1;
                    usedrotation.clear();
                    firstdo=1;
                    cout << "\n   Random state applied.\n\n";
            }
            else if (buf=="apply")
            {
                isScramble2=1;
                cout << "\n   sequence applied\n\n";
            }
            else if (isDepth==1)
            {
                istringstream convert(buf);
                if ( (convert >> tempnumber) )
                {
                    number=tempnumber;
                    cout << "\n   max count set to: " << number << "\n\n";
                    isDepth=0;
                }
                else
                {
                    cout << "\n   invalid count specified; count remains: "<<number<<"\n\n";
                    isDepth=0;
                }

            }
            else if (isAnalyze==1)
            {
                istringstream convert(buf);
                if ( (convert >> tempnumber) )
                {
                    if (orientations.size()>1)
                    {
                        cout<<"\n   specify a single orientation\n\n";
                    }
                    else
                    {
                        analyze(tempnumber, prunedmethod, orientations, rotations, NTHREADS);
                    }
                    isAnalyze=0;
                }
                else
                {
                    cout << "\n   invalid quantity for analysis\n\n";
                    isAnalyze=0;
                }
            }
            else if (isAlgSearch==1)
            {

                istringstream convert(buf);
                if ( (convert >> tempnumber) )
                {
                    if (prunedmethod!=4)
                    {
                        cout<<"\n   invalid method loaded\n\n";
                    }
                    else
                    {
                        algSearch(tempnumber);
                    }
                    isAlgSearch=0;
                }
                else
                {
                    cout << "\n   invalid quantity for algsearch\n\n";
                    isAlgSearch=0;
                }
            }
            else if (isHacks==1)
            {
                istringstream convert(buf);
                if ( (convert >> tempnumber) )
                {
                    if (prunedmethod==0)
                    {
                        cout<<"\n   invalid method loaded\n\n";
                    }
                    else
                    {
                        fmc(tempnumber, prunedmethod, orientations, rotations);
                    }
                    isHacks=0;
                }
                else
                {
                    cout << "\n   invalid quantity for hacks\n\n";
                    isHacks=0;
                }
            }
        else if (isSet==1)
        {
            if (buf==cterm)
            {
                if (isSet)
                {
                    isSet=0;
                    isSet2=0;
                    cubeSet(setter);
                    scramble="";
                    asetstate=1;
                    EPo=setter[0];
                    EOo=setter[1];
                    CPo=setter[2];
                    COo=setter[3];
                    CNo=setter[4];
                }
            }
            else
            {
                istringstream buffer(buf);
                uint64_t value;
                buffer >> std::hex >> value;
                setter[isSet2]=value;
                isSet2++;
            }
        }

        else if (isScramble2==1)
        {
            if (buf==cterm)
            {
                if (isScramble2)
                {
                    isScramble2=0;
                    dosomething(1,0,scramble,firstdo);
                    scramble="";
                }

            }
            else
            {
                //applyMove(buf);
                vector < char > tempmove=move2vec(buf);
                for (int i=0; i<tempmove.size(); i++)
                {
                    applyMove2(tempmove[i]);
                }
                scramble.append(buf);
                scramble.append(" ");
            }
        }
        else if (buf==cterm)
        {

            if (isCheck)
            {
                cout<<"\n   orientations set to: ";
                isCheck=0;
                for (int i=0; i<orientations.size(); i++)
                {
                    cout<<orientations[i]<<" ";
                }
                cout<<"\n\n";
            }
        }
        else if (firstWordWCA==1)
        {
            firstWordWCA=0;
        }

        else if (is_number(buf))
        {
            firstdo=dosomething(0,atoi(buf.c_str())," ",firstdo);
        }


        else
        {
            if (notrecognized)
            {
                cout << "\n   command not recognized\n\n";
                rlutil::setColor(colorI);
                break;
            }
        }
    rlutil::setColor(colorI);
    }
    if (CLI)
    {
        break;
    }
}
return 0;
}

void loadSettings()
{
        ifstream infile;
        string pullin;
        int grabnext=0;
        infile.open("settings.txt");
        while(getline(infile,pullin))
        {
            if (trim(pullin)=="default orientations (space-separated):")
            {
                grabnext=1;
            }
            else if (trim(pullin)=="default number of results:")
            {
                grabnext=2;
            }
            else if (trim(pullin)=="default HARCS color (WIN-COLORS 0-15):")
            {
                grabnext=3;
            }
            else if (trim(pullin)=="default input color (WIN-COLORS 0-15):")
            {
                grabnext=4;
            }
            else if (trim(pullin)=="default output color (WIN-COLORS 0-15):")
            {
                grabnext=5;
            }
            else if (trim(pullin)=="default command terminator:")
            {
                grabnext=6;
            }
            else if (trim(pullin)=="visualization (ACN/XMDI):")
            {
                grabnext=7;
            }
            else if (grabnext==1)
            {
                string tuf;
                stringstream ss(pullin);
                while (ss >> tuf)
                {
                    addOris(tuf);
                }
                grabnext=0;
            }
            else if (grabnext==2)
            {
                stringstream todec;
                todec<<std::dec<<trim(pullin);
                todec>>number;
                grabnext=0;
            }
            else if (grabnext==3)
            {
                stringstream todec;
                todec<<std::dec<<trim(pullin);
                todec>>colorH;
                grabnext=0;
            }
            else if (grabnext==4)
            {
                stringstream todec;
                todec<<std::dec<<trim(pullin);
                todec>>colorI;
                grabnext=0;
            }
            else if (grabnext==5)
            {
                stringstream todec;
                todec<<std::dec<<trim(pullin);
                todec>>colorO;
                grabnext=0;
            }
            else if (grabnext==6)
            {
                cterm = trim(pullin);
                grabnext=0;
            }
            else if (grabnext==7)
            {
                if (trim(pullin)=="ACN")
                    vis=0;
                if (trim(pullin)=="XMDI")
                    vis=1;
                grabnext=0;
            }
        }

}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    loadSettings();
    if (argc > 1)
    {
        string asmb="";
        for (int j=1; j<argc; j++)
        {
            asmb=asmb+argv[j]+" ";
        }
        getInputWCA(1,asmb);
    }
    else
    {
        rlutil::setColor(colorH);
        introWCA();
        rlutil::setColor(colorI);
        while (1)
        {
            getInputWCA(0,"");
        }
    }
    return 0;
}
