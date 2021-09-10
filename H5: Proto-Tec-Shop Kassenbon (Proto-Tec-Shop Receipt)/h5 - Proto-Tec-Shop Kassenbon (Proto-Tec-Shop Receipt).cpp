/*
Task: H5
Family Name: SARDAR NIBIR
Given Name: Ismam Hasin
Matriculation number: 3088266
Uni-Email: ismam.sardar-nibir@stud.uni-due.de
Course of Studies: ISE CE
*/

#include <iostream>
#include <iomanip>

using namespace std;

class Article
{
friend class ShoppingCart;
friend class Notebook;
friend class Accessory;
friend class Device;
friend class InCart;
private:
    string model;
    double netprice;
    double taxRate;

public:
    Article(string model, double netprice, double taxRate):
    //Article(string model1, double netprice1):
        model(model),
        netprice(netprice),
        taxRate(0.19)
        {}

        virtual ~Article() {cout << " ~Article()   " << setw(42) <<setfill(' ') <<left << get_model() << endl;}
        void set_model(string model1) {model = model1;}
        void set_netPrice(double netprice1) {netprice = netprice1;}
        string get_model () {return model;}
        double get_netPrice () {return netprice;}
        double get_grossPrice()
        {
            double grossPrice;
            grossPrice = netprice + (netprice)*(taxRate);
            return grossPrice;
        }
        //pure virtual method for the base abstract class
        virtual void print() = 0;
};

class Accessory : public Article
{
friend class ShoppingCart;
private:
    bool original;
public:
    Accessory(string model, double netprice, bool original=true): Article (model, netprice, taxRate),
    original(original)
    {}//original(original1) //taxRate1 shows errors

    virtual ~Accessory() {cout << "  ~Accessory() ";}
    virtual void print()
    {
        cout << get_model(); //<< " netprice " <<get_netPrice() << " grossprice " <<get_grossPrice() << " tax " <<(taxRate) << endl;
        if (original==true) {cout << " (original accessories)" << endl;}
    }

};

enum class OperatingSystem {unknown, android, iOS, macOS, linux, proprietary, unix, windows};

ostream& operator<<(ostream& out, const OperatingSystem &obj)
{
    //out << static_cast<std::underlying_type<OperatingSystem>::type>(obj);

    switch (obj)
    {
    case OperatingSystem::unknown:
        out << " unknown ";
        return out;
        break;
    case OperatingSystem::android:
        out << "Android OS ";
        return out;
        break;
    case OperatingSystem::iOS:
        out << " iOS ";
        return out;
        break;
    case OperatingSystem::macOS:
        out << " macOS ";
        return out;
        break;
    case OperatingSystem::linux:
        out << " linux ";
        return out;
        break;
    case OperatingSystem::proprietary:
        out << " proprietary ";
        return out;
        break;
    case OperatingSystem::unix:
        out << " unix ";
        return out;
        break;
    case OperatingSystem::windows:
        out << " MS Windows OS,";
        return out;
        break;
    }
    return out;
}

class Device : public Article
{
   // friend class Phone;
friend class Notebook;
private:
    int main_memory;
    OperatingSystem os;
public:
    Device(string model, double netprice, int main_memory, OperatingSystem o =OperatingSystem::unknown ) : Article (model, netprice, taxRate),
    main_memory(main_memory),os(o)
    //didn't initialize os, os not in parameter
    {}
    virtual ~Device() { cout << " ~Device()"; }
    OperatingSystem get_os () {return os;}
    virtual void print()
    {
        cout<< get_model() << " RAM " << main_memory << " GB," << os;
    }

};

class Notebook : public Device //5
{
friend class Phone;
private:
    string drive;
    bool convertible;
public:

    Notebook(string model, double netprice, int main_memory, string drive, OperatingSystem o = OperatingSystem::linux, bool convertible=false) : Device(model, netprice, main_memory, o),
    drive(drive),
    convertible(convertible)
    {}
    virtual ~Notebook() {cout << "  ~Notebook()";}
    bool is_a_convertible () {return convertible;}
    virtual void print()
    {
        Device::print();
        cout << " " << drive;
        if(convertible==true)
        {
            cout << "(convertible) " << drive  <<endl;
        }
    }
};

class Phone : public Device //6
{
    friend class ShoppingCart;
public:

    Phone(string model, double netprice, int main_memory, OperatingSystem os) : Device(model, netprice, main_memory,os)
     //no attribute to initialize
     {}
     virtual ~Phone() {cout << "  ~Phone()";}
     virtual void print()
     {
         Device::print();
         cout << "phone";
     }
};

class InCart //7
{
    friend class ShoppingCart;
private:
    Article *article;
    int amount;
    InCart *next;

public:
    InCart(Article *article, int amount=0,InCart *next=nullptr):
        article(article),
        amount(amount),
        next(next)
        {}
        virtual ~InCart() //or also delete article   //call article destructor
        {
        cout << "delete article: ~InCart() Amount: " <<amount;
        article->~Article(); //called article destructor
        }
        InCart* get_next() {return next;}

        virtual void print()
        {
        cout << "\nAmount: " << amount << "   " ; //to be completed
        article->print();
        cout << "\n\t\t\t\t\t\t   " <<fixed <<setprecision(2)  <<article->get_grossPrice() << " EUR" ;
        cout <<"\t   " <<setw(7) <<right << (article->get_grossPrice())*(amount) << " EUR";
          //cout<< "\n\t\t\t---------------" <<endl;
        }

};

class ShoppingCart //: public Accessory
{
    friend class Phone;
private:

   InCart *articles=nullptr;
      double minFreeShipping, sumNetPrice, sumGrossPrice;
public:
    ShoppingCart():
        minFreeShipping(1000), sumNetPrice(0), sumGrossPrice (0)
        {}

        ~ShoppingCart() {
            cout << "\n\n~ShoppingCart()" << endl;
            InCart *ptr_for_removal;
            while (articles != nullptr)
            {
            ptr_for_removal = articles;
            articles = articles->get_next();
            delete ptr_for_removal;
            //no memory leak, new keyword and delete
            }
}

        void set_minFreeShipping (int minFreeShipping1) {minFreeShipping = minFreeShipping1;}
        void add_article (int amount, Article *article)
        {
            InCart *incartt = new InCart(article, amount, nullptr);
            if (articles==nullptr)
            {
                articles= incartt;
            }
            else
            {
                InCart *tempo_ptr=articles;
                while(tempo_ptr->get_next()!=nullptr)
                {
                    //tempo_ptr= articles;
                   tempo_ptr = tempo_ptr->get_next();
                }
                tempo_ptr->next = incartt;
            }
            sumGrossPrice+=(article->get_grossPrice())*(amount); //article pointer accessible from here as this class is made a friend of the class InCart, which has the article pointer
            sumNetPrice+=(article->get_netPrice())*(amount);
        }
        virtual void print()
        {
            InCart *print_ptr=articles;
        while (print_ptr != nullptr)
        {
            print_ptr->print();
            print_ptr=print_ptr->get_next();
        }
cout << "\n\t\t\t\t\t\t\t          ------------";
if (sumNetPrice>=2220)
{
cout  << "\n\t\t\t\t\t\tSum Net Price: \t   " <<sumNetPrice << " EUR";
}
if (sumNetPrice<2220)
{
    cout  << "\n\t\t\t\t\t\tSum Net Price: \t     " <<sumNetPrice << " EUR";
}
            cout << "\n\t\t\t\t\t\t\t  Tax:     " <<setw(7) <<right << sumGrossPrice - sumNetPrice << " EUR"; //((articles->article->get_grossPrice())*(articles->amount)) - ((articles->article->get_netPrice())*(articles->amount));
            cout<< "\n\t\t\t                      Sum Gross Price:     " <<setw(7) <<right <<sumGrossPrice << " EUR"; //((articles->article->get_grossPrice())*(articles->amount));
            cout << "\n\t\t\t\t\t\t\t          ------------";

            if(this->minFreeShipping>sumGrossPrice)
            {
                cout << "\n\t\t\t\t\t\tShipping Cost:        " << 5.9 << " EUR";
                cout << "\n\t\t\t\t\t\t\t          ------------";
                cout << "\n\t\t\t\t\t\t\tTotal:      " << sumGrossPrice + 5.9 << " EUR";
                cout << "\n\t\t\t\t\t\t\t          ============";
            }
            //else
                if(this->minFreeShipping<sumGrossPrice)
            {
                cout << "\n\t\t\t\t\t\tShipping Cost:        " << 0.00 << " EUR";
                cout << "\n\t\t\t\t\t\t\t          ------------";
                cout << "\n\t\t\t\t\t\t\tTotal:     " << sumGrossPrice + 0 << " EUR";
                cout << "\n\t\t\t\t\t\t\t          ============";
            }
        }
};


int main()
{

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+                        P R O T O - T E C - S H O P                         +";
    cout << "\n+                     Y O U R   S H O P P I N G C A R T                      +";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


    ShoppingCart shoppingg_obj;
    shoppingg_obj.set_minFreeShipping(500);

    Accessory *accessory_ptr= new Accessory ("\nYOOLOX 10k Wireless Powerbank Qi", 31.08, false);
    shoppingg_obj.add_article(3, accessory_ptr);
    shoppingg_obj.print();

    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+                        P R O T O - T E C - S H O P                         +" << endl;
    cout << "+                     Y O U R   S H O P P I N G C A R T                      +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    Notebook *notebook_ptr = new Notebook ( "\nASUS ROG Strix Scar III G731" , 1586.55, 16, "512 GB SSD + 1TB SSHD", OperatingSystem::windows , false); //7
    shoppingg_obj.add_article(1, notebook_ptr);

    Phone *phone_ptr = new Phone ("\nApple iPhone 11 Pro 256GB", 1097.47, 4, OperatingSystem::iOS); //2
    shoppingg_obj.add_article(2, phone_ptr);

    Phone *phone_ptr_1 = new Phone ("\nSamsung Galaxy S10+ SM-G975F/DS Dual SIM", 661.67, 8, OperatingSystem::android); //1
    shoppingg_obj.add_article(1, phone_ptr_1);

    shoppingg_obj.print();

    cout << "\n\n\t      The individual destructors to be utilized \"automatically\" below:";
    cout << "\n\t      Exiting out of the scope of the int main() function.......";

    return 0;
}
