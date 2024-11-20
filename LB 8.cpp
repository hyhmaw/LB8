/*ЛР8

Створити програму на C++ для управління даними про футбольну команду 
з використанням структур.
Програма повинна дозволяти зберігати, оновлювати та аналізувати інформацію 
про гравців і статистику команди. 

Структура Player:
Кожен гравець включає: 
 1. Ім'я; 
 2. Позицію (наприклад, "нападник", "захисник"); 
 3. Кількість голів;
 4. Кількість матчів;
 5. Середній рейтинг.

Функціонал:
 6. Робота з даними гравців:
 • Додавання та виведення інформації про гравців.
 • Пошук гравців за позицією або іншими критеріями.
 7. Аналіз статистики:
 • Підрахунок загальної кількості голів команди.
 • Визначення найкращого бомбардира та гравця з найвищим рейтингом.
 8. Формування складу:
 • Вибір оптимального складу команди на основі рейтингу.
 9. Оновлення даних:
 • Можливість змінювати статистику гравців.
 
Програма повинна бути зручною для аналізу та динамічного оновлення даних.*/

#include <iostream>
#include <string>

using namespace std;

struct Player {
    string name;
    string position;
    int goals;
    int matches;
    double rating;
};


const int MAX_PLAYERS = 100;


void addPlayer(Player team[], int& playerCount) {
    if (playerCount >= MAX_PLAYERS) {
        cout << "Досягнуто максимальну кількість гравців!\n";
        return;
    }
    Player player;
    cout << "Введіть ім'я гравця: ";
    cin.ignore();
    getline(cin, player.name);
    cout << "Введіть позицію (наприклад, нападник, захисник): ";
    getline(cin, player.position);
    cout << "Введіть кількість голів: ";
    cin >> player.goals;
    cout << "Введіть кількість матчів: ";
    cin >> player.matches;
    cout << "Введіть середній рейтинг: ";
    cin >> player.rating;

    team[playerCount++] = player;
    cout << "Гравця успішно додано!\n";
}


void displayPlayers(const Player team[], int playerCount) {
    for (int i = 0; i < playerCount; ++i) {
        cout << "Ім'я: " << team[i].name
            << ", Позиція: " << team[i].position
            << ", Голи: " << team[i].goals
            << ", Матчі: " << team[i].matches
            << ", Рейтинг: " << team[i].rating << "\n";
    }
}

void searchByPosition(const Player team[], int playerCount, const string& position) {
    for (int i = 0; i < playerCount; ++i) {
        if (team[i].position == position) {
            cout << "Ім'я: " << team[i].name
                << ", Голи: " << team[i].goals
                << ", Матчі: " << team[i].matches
                << ", Рейтинг: " << team[i].rating << "\n";
        }
    }
}


int TotalGoals(const Player team[], int playerCount) {
    int goals = 0;
    for (int i = 0; i < playerCount; ++i) {
        goals += team[i].goals;
    }
    return goals;
}

Player findTopScorer(const Player team[], int playerCount) {
    Player topScorer = team[0];
    for (int i = 1; i < playerCount; ++i) {
        if (team[i].goals > topScorer.goals) {
            topScorer = team[i];
        }
    }
    return topScorer;
}


Player findTopRatedPlayer(const Player team[], int playerCount) {
    Player topRated = team[0];
    for (int i = 1; i < playerCount; ++i) {
        if (team[i].rating > topRated.rating) {
            topRated = team[i];
        }
    }
    return topRated;
}


void updatePlayerData(Player team[], int playerCount, const string& name) {
    for (int i = 0; i < playerCount; ++i) {
        if (team[i].name == name) {
            cout << "Введіть нову кількість голів: ";
            cin >> team[i].goals;
            cout << "Введіть нову кількість матчів: ";
            cin >> team[i].matches;
            cout << "Введіть новий середній рейтинг: ";
            cin >> team[i].rating;
            cout << "Дані успішно оновлено!\n";
            return;
        }
    }
    cout << "Гравця з таким ім'ям не знайдено.\n";
}


void getOptimalLineup(Player team[], int playerCount) {
    
    for (int i = 0; i < playerCount - 1; ++i) {
        for (int j = 0; j < playerCount - i - 1; ++j) {
            if (team[j].rating < team[j + 1].rating) {
                swap(team[j], team[j + 1]);
            }
        }
    }

    cout << "Оптимальний склад за рейтингом:\n";
    for (int i = 0; i < playerCount; ++i) {
        cout << "Ім'я: " << team[i].name
            << ", Рейтинг: " << team[i].rating << "\n";
    }
}

int main() {
    setlocale(0, ".1251"); 
    Player team[MAX_PLAYERS];
    int playerCount = 0;
    int choice;

    do {
        cout << "\nМеню:\n"
            << "1. Додати гравця\n"
            << "2. Вивести інформацію про всіх гравців\n"
            << "3. Пошук гравців за позицією\n"
            << "4. Підрахувати загальну кількість голів команди\n"
            << "5. Знайти найкращого бомбардира\n"
            << "6. Знайти гравця з найвищим рейтингом\n"
            << "7. Оновити статистику гравця\n"
            << "8. Вивести оптимальний склад за рейтингом\n"
            << "0. Вийти\n"
            << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPlayer(team, playerCount);
            break;
        case 2:
            displayPlayers(team, playerCount);
            break;
        case 3: {
            string position;
            cout << "Введіть позицію: ";
            cin.ignore();
            getline(cin, position);
            searchByPosition(team, playerCount, position);
            break;
        }
        case 4:
            cout << "Загальна кількість голів: " << TotalGoals(team, playerCount) << "\n";
            break;
        case 5: {
            Player topScorer = findTopScorer(team, playerCount);
            cout << "Найкращий бомбардир: " << topScorer.name
                << " (Голи: " << topScorer.goals << ")\n";
            break;
        }
        case 6: {
            Player topRated = findTopRatedPlayer(team, playerCount);
            cout << "Гравець з найвищим рейтингом: " << topRated.name
                << " (Рейтинг: " << topRated.rating << ")\n";
            break;
        }
        case 7: {
            string name;
            cout << "Введіть ім'я гравця: ";
            cin.ignore();
            getline(cin, name);
            updatePlayerData(team, playerCount, name);
            break;
        }
        case 8:
            getOptimalLineup(team, playerCount);
            break;
        case 0:
            cout << "Вихід з програми.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}
