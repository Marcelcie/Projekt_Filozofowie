#include <iostream> 
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

const int ilosc_filozofow = 5;
volatile bool dziala = true;


enum Stan { MYSLI, GLODNY, JE_SALATKE };
Stan stan[ilosc_filozofow];

pthread_mutex_t widelec[ilosc_filozofow];
pthread_mutex_t mutex_stan = PTHREAD_MUTEX_INITIALIZER;

void* filozof(void* arg) {
    int id = *(int*)arg; 
    delete (int*)arg;
    int lewy_widelec = id;
    int prawy_widelec = (id + 1) % ilosc_filozofow;

    while (dziala) {
        pthread_mutex_lock(&mutex_stan);
        stan[id] = MYSLI;    
        pthread_mutex_unlock(&mutex_stan);         
        usleep(1000000 + rand() % 2000000);

        pthread_mutex_lock(&mutex_stan);
        stan[id] = GLODNY;    
        pthread_mutex_unlock(&mutex_stan); 

        if (id % 2 == 0) {
            pthread_mutex_lock(&widelec[lewy_widelec]);
            pthread_mutex_lock(&widelec[prawy_widelec]);
        } else {
            pthread_mutex_lock(&widelec[prawy_widelec]);
            pthread_mutex_lock(&widelec[lewy_widelec]);
        }

        pthread_mutex_lock(&mutex_stan);
        stan[id] = JE_SALATKE;    
        pthread_mutex_unlock(&mutex_stan); 
        usleep(1500000 + rand() % 1000000);

        pthread_mutex_unlock(&widelec[prawy_widelec]);
        pthread_mutex_unlock(&widelec[lewy_widelec]);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < ilosc_filozofow; i++) {
        pthread_mutex_init(&widelec[i], NULL);
        stan[i] = MYSLI;
    }

    pthread_t watki[ilosc_filozofow];       
    for (int i = 0; i < ilosc_filozofow; i++) {
        int* id_pwt = new int(i);
        pthread_create(&watki[i], NULL, filozof, id_pwt);
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Problem Ucztujacych Filozofow - GUI", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::CircleShape stol(150.f);
    stol.setFillColor(sf::Color(60, 60, 60));
    stol.setOutlineThickness(5);
    stol.setOutlineColor(sf::Color::White);
    stol.setOrigin(150.f, 150.f);
    stol.setPosition(400.f, 300.f);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
    std::cout << "Błąd ładowania czcionki!" << std::endl;
}
    while (window.isOpen() && dziala) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                dziala = false;
                window.close();
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(stol);

        for (int i = 0; i < ilosc_filozofow; i++) {
            float angle = i * 2 * M_PI / ilosc_filozofow;
            float x = 400.f + 230.f * cos(angle);
            float y = 300.f + 230.f * sin(angle);

            sf::Color kolorTulowia;
            pthread_mutex_lock(&mutex_stan);
            if (stan[i] == JE_SALATKE) kolorTulowia = sf::Color::Green;
            else if (stan[i] == MYSLI) kolorTulowia = sf::Color::Blue;
            else kolorTulowia = sf::Color::Red;
            pthread_mutex_unlock(&mutex_stan);

            sf::RectangleShape tulow(sf::Vector2f(50.f, 50.f));
            tulow.setFillColor(kolorTulowia);
            tulow.setOutlineThickness(2);
            tulow.setOutlineColor(sf::Color::White);
            tulow.setOrigin(25.f, 25.f);
            tulow.setPosition(x, y);
            tulow.setRotation(angle * 180 / M_PI + 90);

            sf::CircleShape glowa(15.f);
            glowa.setFillColor(sf::Color(255, 239, 213));
            glowa.setOutlineThickness(2);
            glowa.setOutlineColor(sf::Color::Black);
            glowa.setOrigin(15.f, 15.f);
            glowa.setPosition(x, y);

            window.draw(tulow);
            window.draw(glowa);
        }
        // --- LEGENDA ---
            std::vector<std::pair<sf::Color, std::string>> legenda = {
                {sf::Color::Blue, "Mysli"},
                {sf::Color::Red, "Glodny (czeka)"},
                {sf::Color::Green, "Je salatke"}
            };

            for (int i = 0; i < legenda.size(); i++) {
                sf::CircleShape colCircle(10.f);
                colCircle.setFillColor(legenda[i].first);
                colCircle.setPosition(20.f, 20.f + (i * 30.f));
                window.draw(colCircle);

                sf::Text text;
                text.setFont(font);
                text.setString(legenda[i].second);
                text.setCharacterSize(15);
                text.setFillColor(sf::Color::White);
                text.setPosition(50.f, 18.f + (i * 30.f));
                window.draw(text);
            }
            // --- KONIEC LEGENDY ---

        window.display();
    }
    dziala = false;
    for (int i = 0; i < ilosc_filozofow; i++) {
        pthread_join(watki[i], NULL);
        pthread_mutex_destroy(&widelec[i]);
    }
    pthread_mutex_destroy(&mutex_stan);

    return 0;
}