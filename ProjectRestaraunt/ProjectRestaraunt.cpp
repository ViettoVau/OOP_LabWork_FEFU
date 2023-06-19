#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
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

class Restaurant {
protected:
    std::string name;
    int rating;
    bool hasWebsite;
    int numGuests;
    int maxCapacity;

public:
    Restaurant(const std::string& name, int rating, bool hasWebsite, int maxCapacity)
        : name(name), rating(rating), hasWebsite(hasWebsite), numGuests(0), maxCapacity(maxCapacity) {}

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

    bool bookTable(int numPeople) {
        if (numGuests + numPeople <= maxCapacity) {
            numGuests += numPeople;
            return true;
        }

        return false;
    }

    void showInfo() const {
        std::cout << "Restaurant: " << name << std::endl;
        std::cout << "Rating: " << rating << std::endl;
        std::cout << "Website: " << (hasWebsite ? "Yes" : "No") << std::endl;
        std::cout << "Current Guests: " << numGuests << std::endl;
        std::cout << "Max Capacity: " << maxCapacity << std::endl;
    }

    std::string getName() const {
        return name;
    }

    int getRating() const {
        return rating;
    }
    auto operator<=>(const Restaurant& other) const
    {
        return rating <=> other.rating;
    }
};

class Employee {
protected:
    std::string name;
    std::string position;
    int experience;
    float salary;

public:
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
};


class Supra : public Restaurant {
private:
    std::string cuisineType;
    Container<Employee> employees;
    Container<Dish> menu;
   
    double totalProfit;

public:
    Supra(const std::string& name, int rating, bool hasWebsite, int maxCapacity, const std::string& cuisineType)
        : Restaurant(name, rating, hasWebsite, maxCapacity), cuisineType(cuisineType), totalProfit(0.0) {}

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

    double getBill(double amount) {
        totalProfit += amount;
        numGuests--;
        return amount;
    }

    void showInfo() const {
        Restaurant::showInfo();
        std::cout << "Cuisine Type: " << cuisineType << std::endl;

        std::cout << "Employees:" << std::endl;
        for (const auto& employee : employees) {
            std::cout << "- Name: " << employee.getName() << ", Position: " << employee.getPosition() << std::endl;
        }

        std::cout << "Menu:" << std::endl;
        auto compareByPrice = [](const Dish& dish1, const Dish& dish2) {
            return dish1.price < dish2.price;
        };
        std::sort(menu.begin(), menu.end(), compareByPrice);
        for (const auto& dish : menu) {
            std::cout << "- Name: " << dish.name << ", Prise: " << dish.price << std::endl;
        }

        std::cout << "Total Profit: $" << totalProfit << std::endl;
    }
};

class TokyoCity : public Restaurant {
private:
    std::string cuisineType;
    Container<Employee> employees;
    Container<Dish> menu;
    double totalProfit;

public:
    TokyoCity(const std::string& name, int rating, bool hasWebsite, int maxCapacity, const std::string& cuisineType)
        : Restaurant(name, rating, hasWebsite, maxCapacity), cuisineType(cuisineType), totalProfit(0.0) {}

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
    double getBill(double amount) {
        totalProfit += amount;
        numGuests--;
        return amount;
    }

    void showInfo() const {
        Restaurant::showInfo();
        std::cout << "Cuisine Type: " << cuisineType << std::endl;

        std::cout << "Employees:" << std::endl;
        for (const auto& employee : employees) {
            std::cout << "- Name: " << employee.getName() << ", Position: " << employee.getPosition() << std::endl;
        }

        std::cout << "Menu:" << std::endl;
        auto compareByPrice = [](const Dish& dish1, const Dish& dish2) {
            return dish1.price < dish2.price;
        };
        std::sort(menu.begin(), menu.end(), compareByPrice);
        for (const auto& dish : menu) {
            std::cout << "- Name: " << dish.name << ", Prise: " << dish.price << std::endl;
        }

        std::cout << "Total Profit: $" << totalProfit << std::endl;
    }
};

class Laffa : public Restaurant {
private:
    std::string cuisineType;
    Container<Employee> employees;
    Container<Dish> menu;
    double totalProfit;

public:
    Laffa(const std::string& name, int rating, bool hasWebsite, int maxCapacity, const std::string& cuisineType)
        : Restaurant(name, rating, hasWebsite, maxCapacity), cuisineType(cuisineType), totalProfit(0.0) {}

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

    double getBill(double amount) {
        totalProfit += amount;
        numGuests--;
        return amount;
    }

    void showInfo() const {
        Restaurant::showInfo();
        std::cout << "Cuisine Type: " << cuisineType << std::endl;

        std::cout << "Employees:" << std::endl;
        for (const auto& employee : employees) {
            std::cout << "- Name: " << employee.getName() << ", Position: " << employee.getPosition() << std::endl;
        }

        std::cout << "Menu:" << std::endl;
        auto compareByPrice = [](const Dish& dish1, const Dish& dish2) {
            return dish1.price < dish2.price;
        };
        std::sort(menu.begin(), menu.end(), compareByPrice);
        for (const auto& dish : menu) {
            std::cout << "- Name: " << dish.name << ", Prise: " << dish.price << std::endl;
        }

        std::cout << "Total Profit: $" << totalProfit << std::endl;
    }
};
class RestaurantFactory {
public:
    virtual std::unique_ptr<Restaurant> createRestaurant(const std::string& name, int rating, bool hasWebsite, int maxCapacity) = 0;
};

class SupraFactory : public RestaurantFactory {
public:
    std::unique_ptr<Restaurant> createRestaurant(const std::string& name, int rating, bool hasWebsite, int maxCapacity) override {
        return std::make_unique<Supra>(name, rating, hasWebsite, maxCapacity, "Georgian");
    }
};

class TokyoCityFactory : public RestaurantFactory {
public:
    std::unique_ptr<Restaurant> createRestaurant(const std::string& name, int rating, bool hasWebsite, int maxCapacity) override {
        return std::make_unique<TokyoCity>(name, rating, hasWebsite, maxCapacity, "Japanese");
    }
};

class LaffaFactory : public RestaurantFactory {
public:
    std::unique_ptr<Restaurant> createRestaurant(const std::string& name, int rating, bool hasWebsite, int maxCapacity) override {
        return std::make_unique<Laffa>(name, rating, hasWebsite, maxCapacity, "Middle Eastern");
    }
};



    int main() {
  
        SupraFactory supraFactory;
        TokyoCityFactory tokyoCityFactory;
        LaffaFactory laffaFactory;

 
        std::unique_ptr<Restaurant> supraRestaurant = supraFactory.createRestaurant("Supra Restaurant", 4, true, 100);
        std::unique_ptr<Restaurant> tokyoCityRestaurant = tokyoCityFactory.createRestaurant("Tokyo City Restaurant", 5, true, 150);
        std::unique_ptr<Restaurant> laffaRestaurant = laffaFactory.createRestaurant("Laffa Restaurant", 3, false, 80);

        
        supraRestaurant->open(Week::Monday);
        supraRestaurant->open(Week::Friday);
        tokyoCityRestaurant->open(Week::Tuesday);
        laffaRestaurant->open(Week::Sunday);

        supraRestaurant->bookTable(4);
        tokyoCityRestaurant->bookTable(6);
        laffaRestaurant->bookTable(3);

        supraRestaurant->showInfo();
        tokyoCityRestaurant->showInfo();
        laffaRestaurant->showInfo();

        supraRestaurant->close();
        tokyoCityRestaurant->close();
        laffaRestaurant->close();

        return 0;
    }



