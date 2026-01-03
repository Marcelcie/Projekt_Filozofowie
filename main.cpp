#include <iostream> 
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>

const int ilosc_filozofow = 5;
pthread_mutex_t widelec[ilosc_filozofow];
pthread_mutex_t mutex_stan = PTHREAD_MUTEX_INITIALIZER; 
enum Stan { MYSLI, GLODNY, Je_salatke_grecka };
Stan stan[ilosc_filozofow];
const char* nazwa_stanu[] = { "MYSLI", "GLODNY", "Je_salatke_grecka" };
volatile bool dziala = true;

void* filozof(void* arg) {
    int id = *(int*)arg; 
    delete (int*)arg;
    int lewy_widelec = id;
    int prawy_widelec = (id + 1) % ilosc_filozofow;
    while (dziala) {
        pthread_mutex_lock(&mutex_stan);
        stan[id] = MYSLI;    
        pthread_mutex_unlock(&mutex_stan);         
        usleep(500000 + rand() % 500000); 
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
        stan[id] = Je_salatke_grecka;    
        pthread_mutex_unlock(&mutex_stan); 
        usleep(800000 + rand() % 500000);
        pthread_mutex_unlock(&widelec[prawy_widelec]);
        pthread_mutex_unlock(&widelec[lewy_widelec]);
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    for (int i = 0; i < ilosc_filozofow; i++) {
        pthread_mutex_init(&widelec[i], NULL);
        stan[i] = MYSLI;
    }
    pthread_t watki[ilosc_filozofow];       

    for (int i = 0; i < ilosc_filozofow; i++) {
        int* id_pwt = new int(i);
        pthread_create(&watki[i], NULL, filozof, id_pwt);
    }
    while (dziala) {
        clear();
        mvprintw(0, 0, "=== Uczta Filozofow ===");
        mvprintw(1, 0, "Nacisnij 'q' zeby zakonczyc.");

        pthread_mutex_lock(&mutex_stan);
        for (int i = 0; i < ilosc_filozofow; i++) {
            mvprintw(i + 3, 0, "Filozof %d: %s", i, nazwa_stanu[stan[i]]);
        }
        pthread_mutex_unlock(&mutex_stan);
        refresh();
        usleep(100000);

        int klawisz = getch();
        if (klawisz == 'q'){
            dziala = false;
        }
    }

    for (int i = 0; i < ilosc_filozofow; i++) {
        pthread_join(watki[i], NULL);
        pthread_mutex_destroy(&widelec[i]);
    }
    pthread_mutex_destroy(&mutex_stan);
    
    endwin();
    return 0;
}