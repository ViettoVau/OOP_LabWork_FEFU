#include <iostream>
#include <string>
class restarauntSupra //класс ресторана "Супра"
{
public: 
    std::string additionalTitle; //Дополнительное название "Супры"
    std::string address; //адрес ресторана
    int operatingmode[2][30]; //график работы
    double rating; //рейтинг ресторана
    struct Menu { //меню
        struct Dishes //меню еды
        {
            unsigned price = 0; //цена блюда 
            std::string name; // название блюда

        };
        struct Alcohol //алкогольная карта
        {
            unsigned price; //цена алкоголя
            std::string name; //название алкоголя
        };
    };
    class Hall //класс зала ресторана
    {
    public:
        int fullLand; //максимальная вместимость при полной посадке
        struct Guest //гость
        {
            unsigned bill = 0; //счёт гостя
            restarauntSupra::Menu position[5]; //заказ
            unsigned timeReservation; //время брони столика
            bool selebrate; //есть ли у гостя праздник

        };   
        bool freeTable(int IndexGuest) //функция, определяющая есть ли свободный столик в ресторане
        {
            if (IndexGuest >= fullLand)
                return false;
            else return true;

        };
        bool Reservation(Guest* guest, int IndexGuest, int time) // функция бронирования столика
        {
            for (int i = 0; i < IndexGuest; i++)
            {
                if (guest[i].timeReservation =  time)
                {
                  
                    return false;
                }
            };
            guest[IndexGuest].timeReservation = time;
            return true;
        };
        
        class Waiter // класс официанта
        {
        public:
            struct listOrders //список заказов
            {
                int guestNumber; //номер гостя
                std::string order[]; //заказ гостя
            };
        private:
            int workschedule[16]; //рабочий график
            unsigned salary; //зарплата
            unsigned experience; // стаж
        };

        class Manager : public Waiter //класс менеджера
        {
        public:
            std::string complaintBook[100]; //книга жалоб и предложений
        private:
            std::string reportReprimands[]; //отчёт о выговорах

        };
    };

private:
    unsigned workersCount; //кол-во сотрудников
    class Kitchen // класс кухни
    {
        enum Post {Cook, SousChef, Chef};
        class Cook //класс повара
        { 
        public:
            bool free; //свободен ли повар для следущего заказа
            Post post; //должность

            int salary; //зарплата
        };
        
    };
    
};

class Delivery //класс доставки
{
public:
    std::string WebSite; //сайт доставки
    std::string PhoneNumber; //номер телефона доставки
    class Taxi //класс такси
    {
        std::string address; //адрес, куда нужно доставить заказ
        std::string order[]; //заказ
    };
};

bool operator>(const restarauntSupra::Menu::Alcohol& alcohol1, const restarauntSupra::Menu::Alcohol& alcohol2) //оператор сравнения цены на алкоголь
{
    return alcohol1.price > alcohol2.price;
};
bool operator>(const restarauntSupra::Menu::Dishes& dishes1, const restarauntSupra::Menu::Dishes& dishes2) //оператор сравнения цены на блюда
{
    return dishes1.price > dishes2.price;
};

bool operator<(const restarauntSupra& rest1, const restarauntSupra& rest2) //оператор сравнения рейтинг двух разных ресторанов "Супра"
{
    return rest1.rating < rest2.rating;
};

int main()
{
    std::cout << "Hello World!\n";
}

