/*Aufgabe: H1
Nachname: SARDAR NIBIR
Vorname: Ismam Hasin
Matrikelnummer: 3088266
Uni-Email: ismam.sardar-nibir@stud.uni-due.de
Studiengang: ISE CE*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct theTeams {
  string teamnames;
  int points;
  int donematches;
};

void inputsofstructt (struct theTeams Teamnames[], int nofTeams);
void outputsofstructt (struct theTeams Teamnames[], int nofTeams);
int selectionofteamm (struct theTeams Teamnames[], int nofTeams);
void updatingthenumbers (struct theTeams Teamnames[], int nofTeams, int indexing, int nofpts);
void resetpointstonull (struct theTeams Teamnames[], int nofTeams);


int main()

{
    int n;
    cout<<"Enter the number of teams (input integers only):" <<endl;
    cin>>n;
    cout<< "Number of teams you inputted:  "<< n<<endl;
    struct theTeams arrr[n+1];
    inputsofstructt (arrr, n);
    outputsofstructt (arrr, n);
    char insertionuser;
    do
    {
    cout<< "\nInsert your choice (using only the corresponding digits below)" <<endl<<endl;
    cout<< "0.  end program"<< endl;
    cout<< "1.  add result of a match"<< endl;
    cout<< "2.  show ranking"<< endl;
    cout<< "9.  reset points"<< endl;
    cin>> insertionuser;
    cout<< "You chose option: " << insertionuser << endl;
    switch (insertionuser)
    {
case '0':
        cout<< "You have chosen to terminate the program"<< endl;
        break;
case '1':
    {
        int index1;
        int index2;
        int pt1, pt2;
        cout<< "\nMake your first choice of team (input one of the numbers given below):" <<endl;
        index1 = selectionofteamm (arrr, n);
        cout<< "\nNow choose the opposition team (make a selection from one of the digits given below):" <<endl;
        index2 = selectionofteamm (arrr, n);
        if ((index1 == index2))
        {
        cout<< "\n\nError: Same team chosen twice <invalid>. \nChoose different teams now (input only the corresponding numbers):" <<endl;
        break;
        }
        if  ((index1!=index2))
            {
        cout<< "Add the result for the first team you chose: " <<endl;
        cin >> pt1;
        cout<< "Add the desired result for the opposition team of the first team" <<endl;
        cin >> pt2;
        updatingthenumbers (arrr, n, index1, pt1);
        updatingthenumbers (arrr, n, index2, pt2);
        cout<< "\n\n\nThe points have been successfully updated and sorted in descending order. Please see the points below." << endl;
            }

}

case '2':
    outputsofstructt (arrr, n);
    break;

case '9':
    resetpointstonull (arrr, n);
    cout<< "\nThe points have been reset. Press \"2\" to view" <<endl;
    break;
default:
    cout<< "\n\nInvalid input. Choose from options \"1,2 or 9\". Otherwise press \"0\" to terminate the program."<< endl;
    }
    }
while(insertionuser != '0');
 return 0;
 }
void inputsofstructt (struct theTeams Teamnames[], int nofTeams)
{
    cout<< "\nInput of the names of individual teams"<<endl;
    cout<< "======================================"<<endl;
    for(int i=1; i<nofTeams+1; i++)
    {
        cout<< "Enter name for Team  " << i << endl;
        cin>> Teamnames[i].teamnames;
        Teamnames[i].points = 0;
        Teamnames[i].donematches = 0;
    }


}

void outputsofstructt (struct theTeams Teamnames[], int nofTeams)
{

cout<< "\n\nThe current standing of teams (with respect to points earned)"<<endl;
cout<< "============================================================="<< endl;
cout<< "\npoints\t\tdonematches\t\tnames"<<endl;

for(int i=1; i<nofTeams+1; i++)
{
   cout<< Teamnames[i].points << "\t\t" << Teamnames[i].donematches << "\t\t\t" << Teamnames[i].teamnames <<endl;

}

}

int selectionofteamm (struct theTeams Teamnames[], int nofTeams)
{
    int i;
    cout<< "\nThe teams are as follows:" <<endl;
    cout<< "\n";
    cout<< "Ranking\t\tNames of the teams" <<endl;
for(i=1; i<nofTeams+1; i++)
{
    cout  << i << "\t\t" << Teamnames[i].teamnames <<endl;
}

cin>> i;
cout<< "Your chosen team is Team  " << i << " : " << Teamnames[i].teamnames << endl;
return i;

}
bool rankingaftersort (theTeams teamOne, theTeams teamTwo)
{
    return (teamOne.points > teamTwo.points);
}

void updatingthenumbers (struct theTeams Teamnames[], int nofTeams, int indexing, int nofpts)
{

Teamnames[indexing].points+=nofpts;
Teamnames[indexing].donematches++;
std::sort(Teamnames, Teamnames+ nofTeams+1, rankingaftersort);



}

void resetpointstonull (struct theTeams Teamnames[], int nofTeams)
{

    for(int i=1; i<nofTeams+1; i++)
{
    Teamnames[i].points=0;
    Teamnames[i].donematches=0;


}


}
