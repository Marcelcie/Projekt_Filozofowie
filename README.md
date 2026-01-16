# Problem Ucztujących Filozofów - Wizualizacja (C++ / SFML) 🍝

Projekt implementujący klasyczny problem synchronizacji w systemach operacyjnych, zrealizowany w języku C++ z wykorzystaniem wielowątkowości (POSIX Threads) oraz wizualizacji graficznej w czasie rzeczywistym (SFML).

## 📋 Opis Projektu

Celem projektu była analiza mechanizmów synchronizacji oraz identyfikacja zagrożeń takich jak **zakleszczenie (deadlock)** i **głodzenie procesów**. Aplikacja symuluje zachowanie 5 filozofów zasiadających przy okrągłym stole, którzy rywalizują o zasoby (widelce).

W projekcie zaimplementowano **rozwiązanie asymetryczne (hierarchia zasobów)**, które skutecznie zapobiega powstawaniu zakleszczeń poprzez wymuszenie różnej kolejności pobierania widelców dla filozofów parzystych i nieparzystych.

### Główne funkcjonalności:
* ✅ **Wielowątkowość:** Każdy filozof działa jako niezależny wątek (`pthread`).
* ✅ **Synchronizacja:** Dostęp do zasobów (widelców) chroniony jest przez Mutexy.
* ✅ **Wizualizacja GUI:** Zastąpiono interfejs tekstowy biblioteką graficzną **SFML**, co pozwala na obserwację stanów "na żywo".
* ✅ **Stabilność:** Zastosowany algorytm gwarantuje brak Deadlocka i sprawiedliwy przydział zasobów.

## 🖥️ Interfejs Graficzny i Legenda

Stan każdego filozofa jest reprezentowany kolorem w oknie aplikacji:
* 🔵 **Niebieski:** Myśli (praca własna wątku).
* 🔴 **Czerwony:** Głodny (oczekuje na mutexy widelców).
* 🟢 **Zielony:** Je (sekcja krytyczna - posiada oba zasoby).

**Analiza wydajności:**
* W scenariuszu naiwnym (Deadlock) interfejs ulega natychmiastowemu zamrożeniu (**Application Hang**).
* W zaimplementowanym rozwiązaniu asymetrycznym aplikacja utrzymuje pełną płynność (**60 FPS**).

## 🛠️ Wymagania Techniczne

Projekt przeznaczony jest na systemy **Linux**. Wymagane biblioteki:

* `g++` (Kompilator C++)
* `libsfml-dev` (Biblioteka graficzna SFML)
* `pthread` (Obsługa wątków - standard POSIX)

Instalacja zależności (Ubuntu/Debian):
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

🚀 Kompilacja i Uruchomienie
Kompilacja projektu:

```bash
g++ main.cpp -o filozofowie_gui -lsfml-graphics -lsfml-window -lsfml-system -lpthread
Uruchomienie symulacji:
```

```bash
./filozofowie_gui
```
⚙️ Jak działa algorytm?
Aby uniknąć zakleszczenia, zastosowano rozwiązanie asymetryczne:
Filozofowie parzyści: Najpierw podnoszą widelec LEWY, potem PRAWY.
Filozofowie nieparzyści: Najpierw podnoszą widelec PRAWY, potem LEWY.

👨‍💻 Autor
Marcel Cieśliński
Politechnika Wrocławska
