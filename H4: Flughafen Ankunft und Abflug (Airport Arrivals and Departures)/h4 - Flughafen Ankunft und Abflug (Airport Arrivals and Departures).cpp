/*
Task: H4
Family Name: SARDAR NIBIR
Given Name: Ismam Hasin
Matriculation number: 3088266
Uni-Email: ismam.sardar-nibir@stud.uni-due.de
Course of Studies: ISE CE
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


enum timezones : unsigned //A1
{
    ACT, CET, CST, EST, GMT, MSK, PST, UTC
};

enum arrive_depart //A2
{
    arrival, departure
};

class LocalTime //A3
{
friend class Airport; //for schedule A7 (when mins = mins)

private:
    int minutes; //1
    enum timezones zones; //2

public:
    LocalTime(): //3
        minutes(-1),
        zones(CET)
        {}


    LocalTime(int hours, int minss, unsigned zones=CET) : //4
        minutes(minss),
        zones(CET)  //this line is optional
        {set_time(hours, minss);}


    void set_time(int hours, int minss) //5
    {
         if (is_valid()==false)
        {
            cout<< "Whatever/error" ;
            minutes= -1;
        }

         if(is_valid()==true)
        {
                minutes = minss; //minss
                hours = get_hour();
        }
    }

    int get_hour() //6
    {
        return minutes/60;
    }

    int get_minute() //6
    {
        return minutes;
    }
    bool is_valid() //7
    {
        bool check_T_F = true; //initialized to be true initially

        if(minutes < 0)
        {
            return check_T_F = false;
        }
        else
        {
            return check_T_F = true;
        }

        return check_T_F;

    }

friend ostream &operator<<(ostream &output, const LocalTime &object);
};

ostream &operator<<(ostream &output, const LocalTime &object)
{
  output << setw(2) << setfill('0') << (object.minutes)/60 << ":" << setw(2) << setfill('0') << (object.minutes)%60;
  return output;
}



   class Flight //A5
    {
        friend class Airport;
        friend class LocalTime;

    private:
        enum arrive_depart arrivalorDeparture;
        string code, destination, gate, checkIn, comment; //all of type string as said in the question
        LocalTime expectedd; //flight consists of object localtime

    public:
        Flight(enum arrive_depart, string code2, string destination2, string gate2, string checkIn2);
        ~Flight(); //destructor

        string get_code();
        string get_destination();
        string get_gate();
        string get_checkIn();
        string get_comment();

        LocalTime get_scheduled();

        void set_comment(string comment2);
        void set_expected(LocalTime exp);


        bool is_arrival()
        {
            return true;
        }
        bool is_departure()
        {
            return true;
        }

        void print(LocalTime);

    };

    //A6  outside the class

   Flight::Flight(enum arrive_depart arrivalorDeparture, string code2, string destination2, string gate2, string checkIn2="") : //initializing checkIn="" inside parameter doesn't work

        arrivalorDeparture(arrivalorDeparture),
        code(code2),
        destination(destination2),
        gate(gate2),
        checkIn(checkIn2),
        comment("")
    {}

    Flight::~Flight()
    {
        cout << "\t\t\t\tThe flight " <<get_code() << " has been deleted (Flight destructor)" << endl;
    }


    string Flight::get_code()  //Getters
    {
        return code;
    }
    string Flight::get_destination()
    {
            return destination;
    }
    string Flight::get_gate()
    {
            return gate;
    }
    string Flight::get_checkIn()
    {
            return checkIn;
    }
    string Flight::get_comment()
    {
            return comment;
    }

    LocalTime Flight::get_scheduled() //LocalTime treated as type in Flight class
    {
        return expectedd;
    }


    void Flight::set_comment(string comment2) //Setters
    {
        comment = comment2;
    }
    void Flight::set_expected(LocalTime exp)
    {
        expectedd = exp;
    }

    void Flight::print(LocalTime locall)
    {
        cout << get_code() << "\t" << setw(12) << setfill(' ') << get_destination() << "\t\t\t" << locall << "\t\t" << get_scheduled() << "\t\t" << get_gate() << "\t" <<get_checkIn() << "\t\t" << get_comment() <<endl;
    }

    //A7

    class Airport
    {

        friend class Flight;
        //friend class LocalTime;
    private:
        string name;
        Flight *slot[24][60] = {{0},{0}}; //in class Airport

    public:
        Airport(string namee1):
            name(namee1)
            {}

            ~Airport() //destructor
            {
               cout << "\n\tWith the destructor called Airport, deleting the whole pointer array with all flight objects on the heap. " <<endl;
            }


            void schedule(LocalTime the_time, Flight *pointt)
            {
                int hourrr = the_time.get_hour();
                int minuteee = the_time.get_minute();

               slot[hourrr][minuteee]= pointt;
            }

            void comment(LocalTime the_time, string comm)
            {
                int hourrr = the_time.get_hour();
                int minuteee = the_time.get_minute();
                slot[hourrr][minuteee]->set_comment(comm);
            }
            void delay(LocalTime as_scheduled, LocalTime as_expectedd) //NO instruction for objects of class
            {
                slot[as_scheduled.get_hour()][as_scheduled.get_minute()]->set_expected(as_expectedd);
            }

            void print(enum arrive_depart arrivalorDeparture)
            {
                LocalTime timee;

                switch(arrivalorDeparture)
                {
            case arrival:
            {
                break;
            }

            case departure:
            {
                break;
            }
                }

            }
    };



int main() //A8
{
Airport airpt ("DUSSELDORF AIRPORT");

cout << "\t\tDUSSELDORF AIRPORT ARRIVAL" << endl;
cout << "\t\t==========================" <<endl;
cout << "flight\t\t" << "from\t\t" << "\tscheduled" << "\texpected" << "\tgate" <<"\tcheck-in" <<"\tcomment" <<endl;

LocalTime local_sch(0, 760, 0);
LocalTime local_expp(0, 785, 0);
Flight *flightt1 = new Flight (arrive_depart::arrival, "LH 2010", "Munich", "A04", ""); //still works
airpt.schedule(local_sch, flightt1);
airpt.delay(local_sch, local_expp);
airpt.comment(local_sch, "");
airpt.print(arrive_depart::arrival);
flightt1->print(local_sch);

LocalTime local_sch1(0, 890, 0);
Flight *flightt2 = new Flight (arrive_depart::arrival, "EW 9347", "Manchester", "B04", "");
airpt.schedule(local_sch1, flightt2);
airpt.delay(local_sch1, local_sch1);
airpt.comment(local_sch1, "");
airpt.print(arrive_depart::arrival);
flightt2->print(local_sch1);

cout << "\n\n\t\tDUSSELDORF AIRPORT DEPARTURE" << endl;
cout << "\t\t============================" <<endl;
cout << "flight\t\t" << "to\t\t" << "\tscheduled" << "\texpected" << "\tgate" <<"\tcheck-in" <<"\tcomment" <<endl;

LocalTime local_sch2(0, 550, 0);
Flight *flightt3 = new Flight (arrive_depart::departure, "AF 1307", "Paris", "B51", "192-194");
airpt.schedule(local_sch2, flightt3);
airpt.delay(local_sch2, local_sch2);
airpt.comment(local_sch2, "departed");
airpt.print(arrive_depart::departure);
flightt3->print(local_sch2);


LocalTime local_sch3(0, 640, 0);
Flight *flightt4 = new Flight (arrive_depart::departure, "SU 2537", "Moscow", "C31", "252-255");
airpt.schedule(local_sch3, flightt4);
airpt.delay(local_sch3, local_sch3);
airpt.comment(local_sch3, "boarding");
airpt.print(arrive_depart::departure);
flightt4->print(local_sch3);

LocalTime local_sch4(0, 675, 0);
Flight *flightt5 = new Flight (arrive_depart::departure, "EW 9466", "London_Heathrow", "B35", "151-170");
airpt.schedule(local_sch4, flightt5);
airpt.delay(local_sch4, local_sch4);
airpt.comment(local_sch4, "");
airpt.print(arrive_depart::departure);
flightt5->print(local_sch4);

LocalTime local_sch5(0, 805, 0);
Flight *flightt6 = new Flight (arrive_depart::departure, "LH 2011", "Munich", "A40", "115-120");
airpt.schedule(local_sch5, flightt6);
airpt.delay(local_sch5, local_sch5);
airpt.comment(local_sch5, "Code Sharing");
airpt.print(arrive_depart::departure);
flightt6->print(local_sch5);


LocalTime local_sch6(0, 895, 0);
LocalTime local_expp1(0, 920, 0);
Flight *flightt7 = new Flight (arrive_depart::arrival, "XQ 959", "Izmir", "C45", "240-242");
airpt.schedule(local_sch6, flightt7);
airpt.delay(local_sch6, local_expp1);
airpt.comment(local_sch6, "");
airpt.print(arrive_depart::arrival);
flightt7->print(local_sch6);



cout << endl <<endl;

flightt3->~Flight();
flightt4->~Flight();
flightt5->~Flight();
flightt1->~Flight();
flightt6->~Flight();
flightt2->~Flight();
flightt7->~Flight();
//The Airport destructor is called automatically

return 0;
}
