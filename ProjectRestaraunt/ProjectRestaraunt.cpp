#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include <functional>
#include "Container.h" 
enum class Week {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

class Employee {
protected:
    std::string name;
    std::string position;
    int experience;
    float salary;

public:
    friend bool operator== (const Employee& a, const Employee& b) {
        return (a.name == b.name) && (a.position == b.position) && (a.experience == b.experience)
            && (a.salary == b.salary);
    };

    Employee(const std::string& name, const std::string& position, int experience, float salary)
        : name(name), position(position), experience(experience), salary(salary) {}

    std::string getName() const {
        return name;
    }

    std::string getPosition() const {
        return position;
    }

    int getExperience() const {
        return experience;
    }

    float getSalary() const {
        return salary;
    }
};

class EmployeeBuilder {
protected:
    std::string name;
    std::string position;
    int experience;
    float salary;

public:
    EmployeeBuilder& setName(const std::string& name) {
        this->name = name;
        return *this;
    }

    EmployeeBuilder& setPosition(const std::string& position) {
        this->position = position;
        return *this;
    }

    EmployeeBuilder& setExperience(int experience) {
        this->experience = experience;
        return *this;
    }

    EmployeeBuilder& setSalary(float salary) {
        this->salary = salary;
        return *this;
    }

    Employee build() const {
        return Employee(name, position, experience, salary);
    }
};
struct Dish {
    std::string name;
    double price;

    friend bool operator== (const Dish& a, const Dish& b) {
        return (a.name == b.name) && (a.price == b.price);
    };
    friend bool operator< (const Dish& a, double b) {
        return a.price<b;
    };
    friend std::ostream& operator<<(std::ostream& os, const Dish& dish) {
        os << "- Название: " << dish.name << ", Цена: " << dish.price << "$";
        return os;
    }

};

class Restaurant {
protected:
    std::string name;
    double rating;
    bool hasWebsite;
    int numGuests;
    int maxCapacity;
    Container<Employee> employees;
    Container<Dish> menu;
    std::string cuisineType;
    double totalProfit;
public:
    Restaurant(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType)
        : name(name), rating(rating), hasWebsite(hasWebsite), numGuests(0), maxCapacity(maxCapacity), cuisineType(cuisineType), totalProfit(0) {}

    void open(Week dayOfWeek) {
        int extraGuests = 0;
        switch (dayOfWeek) {
        case Week::Saturday:
        case Week::Sunday:
            extraGuests += 50;
            break;
        case Week::Friday:
            extraGuests += 30;
            break;
        default:
            extraGuests += 10;
            break;
        }

        if (rating >= 4) {
            extraGuests += 20;
        }

        if (hasWebsite) {
            extraGuests += 10;
        }

        numGuests += extraGuests;
    }

    void close() {
        numGuests = 0;
    }
    void addEmployee(const Employee& employee) {
        employees.addElement(employee);
    }

    void deleteEmployee(const Employee& employee) {
        employees.deleteElement(employee);
    }

    void addDish(const Dish& dish) {
        menu.addElement(dish);
    }

    void deleteDish(const Dish& dish) {
        menu.deleteElement(dish);
    }

    bool bookTable(int numPeople) {
        if (numGuests + numPeople <= maxCapacity) {
            numGuests += numPeople;
            return true;
        }

        return false;
    }
    double getBill(double amount) {
        totalProfit += amount;
        numGuests--;
        return amount;
    }

    void showMenuwithMinPriceDish(double minprice)
    {
        menu.printMin(minprice);
    }

    void showInfo() const {
        std::cout << "=========================" << std::endl;
        std::cout << "Ресторан: " << name << std::endl;
        std::cout << "Рейтинг: " << rating << std::endl;
        std::cout << "Website: " << (hasWebsite ? "Yes" : "No") << std::endl;
        std::cout << "Кол-во гостей сейчас: " << numGuests << std::endl;
        std::cout << "Максимальная посадка: " << maxCapacity << std::endl;
        std::cout << "Тип кухни: " << cuisineType << std::endl;

        std::cout << "Сотрудники:" << std::endl;
        for (const auto& employee : employees) {
            std::cout << "- Имя: " << employee.getName() << ", Должность: " << employee.getPosition() << std::endl;
        }

        std::cout << "Меню:" << std::endl;
        for (const auto& dish : menu) {
            std::cout << "- Название: " << dish.name << ", Цена: " << dish.price << "$" << std::endl;
        }

        std::cout << "Прибыль за сегодня: $" << totalProfit << std::endl;
        std::cout << "=========================" << std::endl;
    }

    std::string getName() {
        return name;
    }

    double getRating() {
        return rating;
    }
    auto operator<=>(Restaurant& other)
    {
        return rating <=> other.rating;
    }
 
};



class Supra : public Restaurant {
public:
    Supra(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType)
        : Restaurant(name, rating, hasWebsite, maxCapacity, cuisineType) {}

};

class TokyoCity : public Restaurant {
public:
    TokyoCity(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType)
        : Restaurant(name, rating, hasWebsite, maxCapacity, cuisineType) {}

  
};

class Laffa : public Restaurant {
public:
    Laffa(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType)
        : Restaurant(name, rating, hasWebsite, maxCapacity, cuisineType) {}

};

class RestaurantFactory {
public:
    virtual Restaurant* createRestaurant(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType) = 0;
};

class SupraFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType) override {
        return new Supra(name, rating, hasWebsite, maxCapacity, cuisineType);
    }
};

class TokyoCityFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType) override {
        return new TokyoCity(name, rating, hasWebsite, maxCapacity, cuisineType);
    }
};

class LaffaFactory : public RestaurantFactory {
public:
    Restaurant* createRestaurant(std::string name, double rating, bool hasWebsite, int maxCapacity, std::string cuisineType) override {
        return new Laffa(name, rating, hasWebsite, maxCapacity, cuisineType);
    }
};



int main() {
    setlocale(LC_ALL, "Russian");
    SupraFactory supraFactory;
    TokyoCityFactory tokyoCityFactory;
    LaffaFactory laffaFactory;


    Restaurant* supraRestaurant = supraFactory.createRestaurant("Супра", 4.7, true, 120, "Грузинская");
    Restaurant* tokyoCityRestaurant = tokyoCityFactory.createRestaurant("Токио-Сити", 3.9, true, 70, "Японская");
    Restaurant* laffaRestaurant = laffaFactory.createRestaurant("Лаффа", 4.3, false, 100, "Восточная");

    EmployeeBuilder employeeBuilder;
    Employee employee1 = employeeBuilder.setName("Виктор Петрович").setPosition("Chef").setExperience(25).setSalary(5000.0).build();
    Employee employee2 = employeeBuilder.setName("Максим").setPosition("Cook").setExperience(2).setSalary(2000.0).build();
    Employee employee3 = employeeBuilder.setName("Анстасия").setPosition("Waiter").setExperience(3).setSalary(500.0).build();
    Employee employee4 = employeeBuilder.setName("Виктория").setPosition("Manager").setExperience(15).setSalary(4500.0).build();
    Employee employee5 = employeeBuilder.setName("Люда").setPosition("Cleaner").setExperience(10).setSalary(350.0).build();

    supraRestaurant->addEmployee(employee1);
    supraRestaurant->addEmployee(employee2);
    tokyoCityRestaurant->addEmployee(employee4);
    tokyoCityRestaurant->addEmployee(employee3);
    laffaRestaurant->addEmployee(employee2);
    laffaRestaurant->addEmployee(employee5);

    Dish dish1 = { "Хачапури", 25.0 };
    Dish dish2 = { "Суши", 10.0 };
    Dish dish3 = { "Хинкали", 8.0 };
    Dish dish4 = { "Удон", 12.0 };
    Dish dish5 = { "Шашлык", 12.0 };
    Dish dish6 = { "Чизкейк", 12.0 };

    supraRestaurant->addDish(dish1);
    supraRestaurant->addDish(dish2);
    supraRestaurant->addDish(dish3);
    supraRestaurant->addDish(dish4);
    supraRestaurant->addDish(dish5);
    supraRestaurant->addDish(dish6);
    tokyoCityRestaurant->addDish(dish2);
    tokyoCityRestaurant->addDish(dish4);
    laffaRestaurant->addDish(dish5);
    laffaRestaurant->addDish(dish6);

    supraRestaurant->open(Week::Monday);
    tokyoCityRestaurant->open(Week::Tuesday);
    laffaRestaurant->open(Week::Sunday);

    supraRestaurant->showInfo();
    supraRestaurant->showMenuwithMinPriceDish(11);
    tokyoCityRestaurant->showInfo();
    laffaRestaurant->showInfo();
    
    supraRestaurant->close();
    tokyoCityRestaurant->close();
    laffaRestaurant->close();

    return 0;
}



