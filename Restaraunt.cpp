#include <iostream>
enum Week { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
class Restaraunt
{
protected:
    std::string name;
    bool hasWebSite;
    double rating;

public:
    Restaraunt(std::string name, bool hasWebSite,  double rating)
    {
        this->name = name;
        this->hasWebSite = hasWebSite;  
        this->rating = rating;
   
    }
    friend bool operator==(Restaraunt& rest1, Restaraunt& rest2);
    friend bool operator>(Restaraunt& rest1, Restaraunt& rest2);
    friend bool operator<(Restaraunt& rest1, Restaraunt& rest2);
};

class Supra : public Restaraunt
{
protected:
    int profit;
    int fullLand;
    int guestcount; 
    int workercount;

public:
    Supra(std::string name, bool hasWebSite, double rating) : Restaraunt(name, hasWebSite, rating)
    {
        this->fullLand = 100;
        this->guestcount = 0;
    }

    bool freetable()
    {
        
        if (guestcount >= fullLand)
            return false;
        else
        
            guestcount += 1;
           
       
        return true;
    };
    void Open(Week day)
    {
        srand(time(0));
        if (day == Friday || day == Saturday || day == Sunday)
        guestcount += (60 + rand() % 51);
        else
        guestcount += (30 + rand() % 51);
  
    };
   
};
enum  class PostWorker {Cook, Chef, Waiter, Meneger, Cleaner};
class Worker
{   
protected:
    PostWorker post;
    int salary;
    int exp;
    friend Supra;
public:
    Worker(PostWorker post, int salary, int exp)
    {
        this->post = post;
        this->exp = exp;
        this->salary = salary;
    }
    
};

bool operator==(Restaraunt& rest1, Restaraunt& rest2)
{
    return rest1.rating == rest2.rating;
}
bool operator>(Restaraunt& rest1, Restaraunt& rest2)
{
    return rest1.rating > rest2.rating;
}

bool operator<(Restaraunt& rest1, Restaraunt& rest2)
{
    return rest1.rating < rest2.rating;
}
int main()
{   
    
    Restaraunt rest1("TokyoCity", true, 4.3);
    Supra centre("Supra-Centre", true, 4.8);
    std::cout << centre.freetable() << "\n";
    centre.Open(Friday);
    std::cout << centre.freetable() << "\n";
    std::cout << (rest1 < centre);
}
