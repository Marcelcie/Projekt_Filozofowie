# Problem Ucztujących Filozofów (Dining Philosophers) 🍝

Symulacja klasycznego problemu synchronizacji w systemach operacyjnych, zaimplementowana w języku C++ z wykorzystaniem wątków (POSIX Threads) oraz wizualizacją w terminalu (biblioteka ncurses).

## 📋 Opis Projektu

Celem projektu było zbadanie problemów współbieżności, takich jak **zakleszczenie (deadlock)** oraz **głodzenie procesów**. Aplikacja symuluje zachowanie 5 filozofów siedzących przy okrągłym stole, którzy na przemian myślą i jedzą, rywalizując o ograniczoną liczbę zasobów (widelców).

W projekcie zaimplementowano **rozwiązanie asymetryczne (hierarchia zasobów)**, które skutecznie zapobiega powstawaniu zakleszczeń poprzez wymuszenie różnej kolejności pobierania widelców dla filozofów parzystych i nieparzystych.

### Główne funkcjonalności:
* ✅ **Wielowątkowość:** Każdy filozof działa jako niezależny wątek (`pthread`).
* ✅ **Synchronizacja:** Dostęp do widelców jest chroniony przez Mutexy.
* ✅ **Wizualizacja TUI:** Stan każdego filozofa (Myśli, Głodny, Je) jest wyświetlany na żywo w terminalu dzięki bibliotece `ncurses`.
* ✅ **Stabilność:** Zastosowany algorytm gwarantuje brak Deadlocka.

## 🛠️ Wymagania Techniczne

Projekt przeznaczony jest na systemy **Linux**. Do kompilacji i działania wymagane są biblioteki systemowe:

* `g++` (Kompilator C++)
* `libncurses` (Interfejs graficzny w terminalu)
* `pthread` (Obsługa wątków - standardowo w systemie),

  
* Jeśli nie masz ncurses, zainstaluj je komendą (Ubuntu/Debian):
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## 🚀 Kompilacja i Uruchomienie

Aby skompilować projekt, użyj poniższej komendy w terminalu (pamiętaj o linkowaniu bibliotek!):
1. Kompilacja (pamiętaj o linkowaniu bibliotek!):
```bash
g++ main.cpp -o filozofowie_gui -lsfml-graphics -lsfml-window -lsfml-system -lpthread
```

3. Uruchomienie symulacji:
```bash
./filozofowie
```

## ⚙️ Jak działa algorytm?

Aby uniknąć zakleszczenia, zastosowano **rozwiązanie asymetryczne**:

1.  **Filozofowie parzyści:** Najpierw podnoszą widelec **LEWY**, potem **PRAWY**.
2.  **Filozofowie nieparzyści:** Najpierw podnoszą widelec **PRAWY**, potem **LEWY**.

Dzięki temu zabiegowi matematycznie niemożliwe jest utworzenie cyklu oczekiwania (Circular Wait).
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```
## 👨‍💻 Autor
* **Marcel Cieśliński**
* Politechnika Wrocławska
