/*
Task: H3
Family Name: Sardar Nibir
Given Name: Ismam Hasin
Matriculation number: 3088266
Uni-Email: ismam.sardar-nibir@stud.uni-due.de
Course of Studies: ISE CE
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include<fstream>

using namespace std;


struct Entry
{
    string key, value;

    void auf4_searching_the_bucket(string key, struct Entry assoc_arr[]);
    void auf3_insertintotable(string key, string value, struct Entry assoc_arr[]);
    void auf5_get_data_from_file(string filetitle, struct Entry assoc_arr[]);
    int auf2_hashCode (string key, int p);

};  int p;

int main()
{
    string filetitle = "tiere_animals.txt";
    string key, value;
    cout << "please input value for (prime) number p. <Ensure that you input a very large prime number>: ";
    cin >> p;

    Entry *Hash_tab = new Entry[p];
    Hash_tab->auf5_get_data_from_file(filetitle, Hash_tab);
    int keeplooping = 1;
        while(keeplooping == 1)
        {
            cout << "\n\nTranslate from German-to-English. \nWrite a german name of an animal (from the options above) to see the corresponding meaning in English.\nPlease enter the first letter as capital letter and use correct spelling. Tap '0' to exit" <<endl;
            cin >> key;
            if (key == "0")
            {
                break;
            }
            else
            {
                cout << "\n\t\t\t" <<key << " {in German} ->  ";
                Hash_tab->auf4_searching_the_bucket(key, Hash_tab);
            }
        }
    return 0;
}

void Entry::auf4_searching_the_bucket(string key, struct Entry assoc_arr[])
{
    int searchbucket = assoc_arr->auf2_hashCode(key, p);
    while((searchbucket<p) && (assoc_arr[searchbucket]).key!=key)
    {
        searchbucket++;
    }
    if(assoc_arr[searchbucket].key == key)
    {
        cout << assoc_arr[searchbucket].value << " {in English}";
    }
    else
    {
        cout << "\n\n\tNo German word known as '" << key << "' exist in the directory. Check if your first letter is capital\n\tand input the words above (with correct spelling). Try again or press '0' to abort." << endl;
    }
}

void Entry::auf3_insertintotable(string key, string value, struct Entry assoc_arr[])
{
	int bucket = auf2_hashCode(key, p);
	if (assoc_arr[bucket].key == "")
    {
        assoc_arr[bucket].key = key;
		assoc_arr[bucket].value = value;
		cout << "insert: '" << key << "' " <<" at bucket/index " << bucket << endl;
		bucket++;
    }
	else
    {
        cout << "insert: '" << key << "' " <<" at bucket/index " << bucket << endl;
        while(assoc_arr[bucket].key != "")
        {
        cout << "\tcollision at bucket/index " << bucket << endl;
        ++bucket;
        bucket = bucket % p; //the linear collision

        }

        assoc_arr[bucket].key = key;
		assoc_arr[bucket].value = value;
        cout<< "\tLinear collision strategy applied to ''" << key << "''. Index number: " <<bucket <<endl;
    }
}



int Entry::auf2_hashCode(string key, int p)
{

    int calculator = (int(key[0])*128 + int(key[1])) % p; //innermost part of the hash function
    for(int w = 2; w < key.length(); w++)
    {
    calculator = (calculator * 128 + int(key[w])) % p; //updates the equation depending on the length of string
    }
return calculator;
}



void Entry::auf5_get_data_from_file(string filetitle, struct Entry assoc_arr[])
{
    char c;
    char dividerr = ';';
    string key, value;
    struct Entry *tocallinsert;
    ifstream inFile;
    inFile.open(filetitle);
    if (!inFile.is_open())
        cout << "there is problem in opening the file\"" << filetitle << '\"' << endl;
    else
    {
        while ((c = inFile.get()) != EOF)
        {
            key = "";
            while (c != dividerr)
            {
            key = key + c;
            c = inFile.get();
            }
            c = inFile.get();
            value = "";
            while ((c != EOF) && (c != '\n') && (c != dividerr))
            {
               value = value + c;
               c = inFile.get();
            }
            tocallinsert->auf3_insertintotable(key, value, assoc_arr);
        }
        inFile.close();
    }
}



