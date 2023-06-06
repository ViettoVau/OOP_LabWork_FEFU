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
    std::string experienceLevel;

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
        int yearsOfExperience = exp / 12;
        std::string expLevel;

        if (yearsOfExperience < 1)
        {
            expLevel = "Начинающий";
        }
        else if (yearsOfExperience < 5)
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

template<typename T>
class MenuContainer
{
private:
    std::vector<T> items;

public:
    class Iterator
    {
    private:
        typename std::vector<T>::const_iterator iter;

    public:
        Iterator(typename std::vector<T>::const_iterator iter)
            : iter(iter)
        {
        }

        const T& operator*() const
        {
            return *iter;
        }

        Iterator& operator++()
        {
            ++iter;
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return iter != other.iter;
        }
    };

    MenuContainer(std::vector<T> items)
        : items(items)
    {
    }

    Iterator begin() const
    {
        return Iterator(items.begin());
    }

    Iterator end() const
    {
        return Iterator(items.end());
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

    std::vector<std::pair<std::string, double>> dishes = {
        {"Хинкали с бараниной", 150.0},
        {"Хачапури по-аджарски", 120.0},
        {"Цезаридзе с курицей", 180.0},
        {"Прекраснейшее гранатовое вино", 300.0},
        {"Чача", 200.0}
    };

    MenuContainer<std::pair<std::string, double>> m(dishes);

    std::for_each(m.begin(), m.end(), [](const auto& dish) {
        std::cout << dish.first << " - " << dish.second << " рублей" << std::endl;
        });

    return 0;
}
