#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

enum class Week { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

class Restaurant
{
protected:
    std::string name;
    bool hasWebSite;
    double rating;

public:
    Restaurant(std::string name, bool hasWebSite, double rating)
        : name(name), hasWebSite(hasWebSite), rating(rating)
    {
    }
    std::string getName() const
    {
        return name;
    }
    double getRating() const
    {
        return rating;
    }
    auto operator<=>(const Restaurant& other) const
    {
        return rating <=> other.rating;
    }
};

class Supra : public Restaurant
{
protected:
    int fullLand;
    int guestCount;

public:
    Supra(std::string name, bool hasWebSite, double rating)
        : Restaurant(name, hasWebSite, rating), fullLand(100), guestCount(0)
    {
    }

    bool isTableAvailable()
    {
        return guestCount < fullLand;
    }

    void open(Week day)
    {
        srand(time(0));
        int minGuestCount = (day == Week::Friday || day == Week::Saturday || day == Week::Sunday) ? 60 : 30;
        int maxGuestCount = minGuestCount + 51;
        guestCount += (minGuestCount + rand() % (maxGuestCount - minGuestCount + 1));
    }
};

enum class PostWorker { Cook, Chef, Waiter, Manager, Cleaner };

class Worker
{
public:
    std::string name;
    int age;
    PostWorker post;
    int salary;
    int exp;
    std::string experienceLevel;

    Worker(const std::string& name, int age, PostWorker post, int salary, int exp, std::string experienceLevel)
        : name(name), age(age), post(post), salary(salary), exp(exp), experienceLevel(experienceLevel)
    {
    }

    void print() const
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Post: " << static_cast<int>(post) << std::endl;
        std::cout << "Salary: " << salary << std::endl;
        std::cout << "Experience: " << exp << std::endl;
        std::cout << "Experience Level: " << experienceLevel << std::endl;
    }
};
class WorkerBuilder
{
private:
    std::string name;
    int age;
    PostWorker post;
    int salary;
    int exp;

public:
    WorkerBuilder& setName(const std::string& name)
    {
        this->name = name;
        return *this;
    }

    WorkerBuilder& setAge(int age)
    {
        this->age = age;
        return *this;
    }

    WorkerBuilder& setPost(PostWorker post)
    {
        this->post = post;
        return *this;
    }

    WorkerBuilder& setSalary(int salary)
    {
        this->salary = salary;
        return *this;
    }

    WorkerBuilder& setExp(int exp)
    {
        this->exp = exp;
        return *this;
    }

    Worker build() const
    {
        std::string expLevel;
        if (exp < 12)
        {
            expLevel = "Начинающий";
        }
        else if (exp < 60)
        {
            expLevel = "Опытный";
        }
        else
        {
            expLevel = "Профессионал";
        }

        return Worker(name, age, post, salary, exp, expLevel);
    }
};

struct Node
{
    Node* next;
    Node* prev;
    std::pair<std::string, double> value;
};

class MenuIterator
{
private:
    Node* current;

public:
    MenuIterator(Node* node) : current(node) {}//

    std::pair<std::string, double>& operator*()
    {
        return current->value;
    }

    MenuIterator& operator++()
    {
        current = current->next;
        return *this;
    }

    MenuIterator operator++(int)
    {
        MenuIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    MenuIterator& operator--()
    {
        current = current->prev;
        return *this;
    }

    MenuIterator operator--(int)
    {
        MenuIterator iterator = *this;
        --(*this);
        return iterator;
    }

    bool operator==(const MenuIterator& other) const
    {
        return current == other.current;
    }

    bool operator!=(const MenuIterator& other) const
    {
        return !(*this == other);
    }
};

class Menu
{
private:
    Node* head;
    Node* tail;

public:
    Menu() : head(nullptr), tail(nullptr) {}

    MenuIterator begin()
    {
        return MenuIterator(head);
    }

    MenuIterator end()
    {
        return MenuIterator(tail->next);
    }

    void addElement(const std::string& dishName, double price)
    {
        if (head == nullptr)
        {
            head = new Node;
            tail = head;
            head->next = nullptr;
            head->prev = nullptr;
            head->value = std::make_pair(dishName, price);
        }
        else
        {
            if (!findElement(dishName))
            {
                Node* new_node = new Node;
                new_node->value = std::make_pair(dishName, price);
                new_node->prev = nullptr;
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            }
        }
    }

    bool findElement(const std::string& dishName)
    {
        Node* curr = head;
        while (curr != nullptr)
        {
            if (curr->value.first == dishName)
                return true;
            curr = curr->next;
        }
        return false;
    }

    void deleteElement(const std::string& dishName)
    {
        Node* curr = head;

        while (curr != nullptr)
        {
            if (curr->value.first == dishName)
            {
                if (curr == head && curr == tail)
                {
                    delete curr;
                    head = nullptr;
                    tail = nullptr;
                }
                else if (curr == head)
                {
                    Node* d = head;
                    head = head->next;
                    head->prev = nullptr;
                    delete d;
                }
                else if (curr == tail)
                {
                    Node* d = tail;
                    tail = tail->prev;
                    tail->next = nullptr;
                    delete d;
                }
                else
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    delete curr;
                }
                curr = nullptr;
            }
            else
                curr = curr->next;
        }
    }

    ~Menu()
    {
        clearList();
    }

    void clearList()
    {
        Node* curr = head;
        while (curr != nullptr)
        {
            Node* last_curr = curr;
            curr = curr->next;
            delete last_curr;
        }
        head = nullptr;
        tail = nullptr;
    }
};
int main()
{
    setlocale(LC_ALL, "Russian");
    Restaurant r1("Tokyo City", true, 4.2);
    Restaurant r2("Laffa", true, 4.8);
    auto result1 = r1 <=> r2;

    if (result1 < 0)
        std::cout << "Рейтинг ресторана " << r1.getName() << " (" << r1.getRating() << ") меньше, чем рейтинг ресторана " << r2.getName() << " (" << r2.getRating() << ")" << std::endl;
    else if (result1 > 0)
std::cout << "Рейтинг ресторана " << r1.getName() << " (" << r1.getRating() << ") больше, чем рейтинг ресторана" << r2.getName() << " (" << r2.getRating() << ")" << std::endl;
    else
        std::cout << "Рейтинг ресторана " << r1.getName() << " (" << r1.getRating() << ") равен рейтингу ресторана" << r2.getName() << " (" << r2.getRating() << ")" << std::endl;
   
    Supra s("Supra", true, 4.5);
    if (s.isTableAvailable())
    {
        s.open(Week::Monday);
        s.open(Week::Friday);
        s.open(Week::Sunday);
    }

    Worker w = WorkerBuilder()
        .setName("Юлия Высоцкая")
        .setAge(49)
        .setPost(PostWorker::Chef)
        .setSalary(1000)
        .setExp(120)
        .build();

    w.print();

    Menu m;

    m.addElement("Хинкали с бараниной", 150.0);
    m.addElement("Хачапури по-аджарски", 120.0);
    m.addElement("Цезаридзе с курицей", 180.0);
    m.addElement("Прекраснейшее гранатовое вино", 300.0);
    m.addElement("Чача", 200.0);

    for (MenuIterator it = m.begin(); it != m.end(); ++it)
    {
        std::cout << (*it).first << " - " << (*it).second << " рублей" << std::endl;
    }


    return 0;
}
