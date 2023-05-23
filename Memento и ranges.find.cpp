#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class Memento {
public:
    virtual std::string GetName() const = 0;
    virtual std::string GetDate() const = 0;
};

class ConcreteMemento : public Memento {
private:
    std::string state_;
    std::string date_;

public:
    ConcreteMemento(std::string state) : state_(state) {
        std::time_t now = std::time(0);
        this->date_ = now;
    }

    std::string GetState() const {
        return state_;
    }

    std::string GetName() const override {
        return this->state_;
    }

    std::string GetDate() const override {
        return this->date_;
    }
};

class Math {
private:
    std::string state_;

    int printGeometricProgression(int a, int r, int n) {
        for (int i = 0; i < n; i++) {
            std::cout << a << " ";
            a *= r;
        }
        return a;
    }

public:
    Math(std::string state) : state_(state) {
        std::cout  << this->state_ << "\n";
    }

    void DoSomething(int a, int r, int n) {
        std::cout << "Doing...  \n";
        this->state_ = std::to_string(this->printGeometricProgression(a, r, n));
        std::cout << "Result:  " << this->state_ << "\n";
    }

    Memento* Save() {
        return new ConcreteMemento(this->state_);
    }

    void Restore(Memento* memento) {
        this->state_ = dynamic_cast<ConcreteMemento*>(memento)->GetState();
        std::cout << "Return state: " << this->state_ << "\n";
    }
};

class Caretaker {
private:
    std::vector<Memento*> mementos_;
    Math* math_;

public:
    Caretaker(Math* math) : math_(math) {}

    void Backup() {
        std::cout << "\nSaving Math's state...\n";
        this->mementos_.push_back(this->math_->Save());
    }

    void Undo(const std::string& name) {
        std::vector<Memento*>::iterator iter = FindMemento(name);
        if (iter != mementos_.end()) {
            Memento* memento = *iter;
            std::cout << "Restoring state to: " << memento->GetName() << "\n";
            try {
                math_->Restore(memento);
                mementos_.erase(iter);
            }
            catch (...) {
                Undo(name);
            }
        }
    }

    void ShowHistory() const {
        std::cout << "The list of mementos:\n";
        for (Memento* memento : this->mementos_) {
            std::cout << memento->GetName() << "\n";
        }
    }

    std::vector<Memento*>::iterator FindMemento(const std::string& name) {
        return std::ranges::find_if(this->mementos_, [&name](Memento* m) { return m->GetName() == name; });
    }
    const std::vector<Memento*>& GetMementos() const {
        return this->mementos_;
    }
};

int main() {
    Math* math = new Math("State 1");
    Caretaker* caretaker = new Caretaker(math);

    caretaker->Backup();
    math->DoSomething(2, 3, 5);
    caretaker->Backup();
    math->DoSomething(1, 2, 7);
    caretaker->Backup();
    math->DoSomething(5, 2, 4);

    std::cout << "\n";
    caretaker->ShowHistory();

    std::cout << "\n";
    caretaker->Undo("State 1");
    return 0;
}

