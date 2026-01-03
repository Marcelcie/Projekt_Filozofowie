#include <iostream> 
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>

const int ilosc_filozofow = 5;
pthread_mutex_t widelec[ilosc_filozofow];
enum Stan { MYSLI, GLODNY, JE_CARBONARE };
Stan stan[ilosc_filozofow];
const char* nazwa_stanu[] = { "MYSLI", "GLODNY", "JE_CARBONARE" };
bool dziala = true;

void* filozof(void* arg) {
    int id = *(int*)arg; 
    int prawy_widelec = (id + 1) % ilosc_filozofow;
    while (dziala) {
        stan[id] = MYSLI;                 
        usleep(500000 + rand() % 500000); 
        stan[id] = GLODNY;
        pthread_mutex_lock(&widelec[prawy_widelec]);
        stan[id] = JE_CARBONARE;
        usleep(800000 + rand() % 500000);
        pthread_mutex_unlock(&widelec[prawy_widelec]);
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
    }
    pthread_t watki[ilosc_filozofow]; 
    int id[ilosc_filozofow];          

    for (int i = 0; i < ilosc_filozofow; i++) {
        id[i] = i; 
        pthread_create(&watki[i], NULL, filozof, &id[i]);
    }
    while (dziala) {
        clear();
        mvprintw(0, 0, "=== Uczta Filozofow: jeden widelec (Tylko prawy) ===");
        mvprintw(1, 0, "Nacisnij 'q' zeby zakonczyc.");

        for (int i = 0; i < ilosc_filozofow; i++) {
            mvprintw(i + 3, 0, "Filozof %d: %s", i, nazwa_stanu[stan[i]]);
        }
        
        refresh();
        usleep(50000);

        int klawisz = getch();
        if (klawisz == 'q'){
            dziala = false;
        }
    }

    for (int i = 0; i < ilosc_filozofow; i++) {
        pthread_join(watki[i], NULL);
        pthread_mutex_destroy(&widelec[i]);
    }
    
    endwin();
    return 0;
}