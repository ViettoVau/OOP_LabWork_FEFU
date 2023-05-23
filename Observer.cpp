#include <iostream>
#include <vector>

class Observer {
public:
	virtual void update(const std::string& message) = 0;
};

class Video {
	std::string title;
	int likes = 0;
	int dislikes = 0;

public:
	Video(const std::string& title) : title(title) {}

	const std::string& getTitle() const {
		return title;
	}
	void like() {
		likes++;
	}

	void dislike() {
		dislikes++;
	}

	void printStats() const {
		std::cout  << "Статистика видео \"" << title << "\":" << std::endl;
		std::cout << "Лайки: " << likes << std::endl;
		std::cout << "Дизлайки: " << dislikes << std::endl;
	}
};

// Класс Блогер
class Blogger {
	std::string name;
	std::vector<Observer*> observers;
	std::vector<Video> videos;

public:
	Blogger(const std::string& name) : name(name) {}

	void addObserver(Observer* observer) {
		observers.push_back(observer);
	}

	void removeObserver(Observer* observer) {
		auto it = std::find(observers.begin(), observers.end(), observer);
		if (it != observers.end()) {
			observers.erase(it);
		}
	}

	void notifyAll(const std::string& message) {
		for (auto observer : observers) {
			observer->update(message);
		}
	}

	void publishPost(const std::string& message) {
		std::cout << name << " опубликовал новую запись: " << message << std::endl;
		notifyAll(message);
	}

	void loadVideo(const Video& video) {
		videos.push_back(video);
		std::string message = "Новое видео: " + video.getTitle();
		std::cout << name << " загрузил новое видео: " << video.getTitle() << std::endl;
		notifyAll(message);
	}
};

class Subscriber : public Observer
{
	std::string name;

public:
	Subscriber(const std::string& name) : name(name) {}

	void update(const std::string& message) 
	{
		std::cout << name << " получил уведомление: " << message << std::endl;
	}
	void likeVideo(Video& video) {
		video.like();
		video.printStats();
	}

	void dislikeVideo(Video& video) {
		video.dislike();
		video.printStats();
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	Blogger blogger("Юлия Высоцкая");
	Subscriber subscriber1("ТУтуту");
	Subscriber subscriber2("Трутрутурутр");

	blogger.addObserver(&subscriber1);
	blogger.addObserver(&subscriber2);
	blogger.publishPost("Новый рецептик вышел!");

	Video video("Рецепт прекрысных помидорчиков<3");

	blogger.loadVideo(video);
	subscriber1.likeVideo(video);
	subscriber2.dislikeVideo(video);
	blogger.removeObserver(&subscriber2);
	
	blogger.publishPost("Еще один рецептик!");

	return 0;
}