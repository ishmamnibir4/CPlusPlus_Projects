/*
Task: H2
Family Name: Sardar Nibir
Given Name: Ismam Hasin
Matriculation number: 3088266
Uni-Email: ismam.sardar-nibir@stud.uni-due.de
Course of Studies: ISE CE
*/
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>


using namespace std;


struct node_obst //1st Auf for creating structure
{
    string name_obstacles;
    double x, y, distance_origin;
    node_obst *next;
};
node_obst *head = nullptr;
node_obst *last = nullptr;

node_obst *storing_3_data(string name_obstacles, double x, double y);
double auf2_euclidcalc(node_obst a, node_obst b);
void auf6_stringdelete();
void auf5_displayfunc();
node_obst *auf3_nearest_dist(node_obst *obstacles, node_obst onepoint);
node_obst *auf4_thesorting(node_obst *obst_pointers, node_obst *point);




node_obst* storing_3_data(string name_obstacles, double x, double y) //separate function for storing the data that the user inputs in int main
{
    node_obst *forstoring = new node_obst;
    forstoring->x = x;
    forstoring->y = y;
    forstoring->name_obstacles = name_obstacles;
    forstoring->distance_origin = sqrt((forstoring->x) *(forstoring->x) + (forstoring->y)*(forstoring->y));

    return forstoring;
}

double auf2_euclidcalc(node_obst one, node_obst two)
{
double d;
d = sqrt(pow(one.x-two.x, 2) + pow(one.y-two.y, 2));
return d;
}

void auf6_stringdelete()
{
    node_obst *fordeletion;
    while (head != nullptr)
    {
        fordeletion = head;
        head = head->next;
        cout << " " << fordeletion->name_obstacles << " ";
        delete fordeletion;
    }
}




void auf5_displayfunc()
{
    node_obst *fordisplay = new node_obst;
    node_obst *ptr;
    string oneobstacle = "No other points or obstacles to make comparison";
    fordisplay = head;
    while(fordisplay != nullptr)
        {
            ptr = auf3_nearest_dist(fordisplay, *fordisplay);
            if(ptr != nullptr)
            {
                oneobstacle = ptr->name_obstacles;
            }
        cout << "obstacle " << fordisplay->name_obstacles << ": (" << fixed << setprecision(2) << fordisplay->x << ", " << setprecision(3) << fordisplay->y << "),  distance: " << fordisplay->distance_origin << "m,  nearest to this: " << oneobstacle << endl;
        fordisplay = fordisplay->next;
    }
}


node_obst *auf4_thesorting(node_obst *obst_pointers, node_obst *point)
{
    node_obst *t;
    obst_pointers = head;
    if(obst_pointers == nullptr){
        point->next = obst_pointers;
        obst_pointers = point;
        head = obst_pointers;
    }
    else
        {
        t = obst_pointers -> next;
        if(point->distance_origin < obst_pointers ->distance_origin){
            point->next = obst_pointers;
            obst_pointers = point;
            head = obst_pointers;
        }
        else if(obst_pointers->next == nullptr){
            obst_pointers->next = point;
            point->next = nullptr;
        }
        else
        {
            while(point->distance_origin > t->distance_origin)
            {
                obst_pointers = obst_pointers->next;
                t = obst_pointers->next;
                if(t == nullptr)
                {
                    break;
                }
            }
            if(obst_pointers->next == nullptr)
            {
                obst_pointers->next = point;
                point->next = nullptr;
            }
            else
            {
                point->next = obst_pointers->next;
                obst_pointers->next = point;
            }
        }
    }
    return head;
}

node_obst *auf3_nearest_dist(node_obst *diffptrs, node_obst thept)
{
    double closest, p;
    node_obst *ptr;
    diffptrs = head;
    if(diffptrs == nullptr || diffptrs -> next == nullptr)
    {
        return nullptr;
    }
    else
    {
        while(diffptrs != nullptr)
        {
        if(thept.name_obstacles != diffptrs->name_obstacles)
        {
            closest = auf2_euclidcalc(thept, *diffptrs);
            ptr = diffptrs;
            break;
        }
        diffptrs = diffptrs->next;
        }
        while(diffptrs!=nullptr){
            if(thept.name_obstacles != diffptrs->name_obstacles)
            {
                p = auf2_euclidcalc(thept, *diffptrs);
                if(p < closest)
                {
                    closest = p;
                    ptr = diffptrs;
                }
            }
            diffptrs = diffptrs->next;
        }
        return ptr;
    }
}


int main (void)
{
    string pointname;
    double x, y;
    node_obst *obs;
    node_obst *p;
    int vp = 1;
    cout << "string describing obstacle ('end' for end of input): ";
            cin >> pointname;
            cout << "x and y coordinate: ";
            cin >> x;
            cin >> y;
            p = storing_3_data(pointname, x, y);
            auf4_thesorting(obs, p);
        while(vp == 1)
        {
            cout << "string describing obstacle ('end' for end of input): ";
            cin >> pointname;
            if (pointname == "end" || pointname == "END")
            {
                break;
            }

            else
            {
                cout << "x and y coordinate:";
                cin >> x;
                cin >> y;
                p = storing_3_data(pointname, x, y);
                auf4_thesorting(obs, p);
            }
        }
    auf5_displayfunc();
    cout << "all strings deleted: ";
    auf6_stringdelete();
    return 0;
}
