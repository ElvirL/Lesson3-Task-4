/*
4. Пошаговая ролевая игра (дополнительное задание)
Что нужно сделать
Реализуйте упрощённую версию пошаговой ролевой игры.
Действие разворачивается на карте размером 20 на 20 клеток. По клеткам перемещаются игрок и его противники.
После каждого хода игрока карта показывается вновь со всеми противниками на ней:
• игрок помечается буквой P,
• противники — буквой E,
• пустые места — точкой.
Каждый персонаж игры представлен в виде структуры с полями:
• «Имя»,
• «Жизни»,
• «Броня»,
• «Урон».
Сначала создаётся пять противников в случайных клетках карты:
• Имена противникам задаются в формате Enemy #N, где N — порядковый номер.
• Уровень жизни противников задаётся случайно — от 50 до 150.
• Уровень брони варьируется от 0 до 50.
• Урон тоже выбирается случайно — от 15 до 30 единиц.
Игрок конструирует своего персонажа самостоятельно. Задаёт все его параметры, включая имя. Все персонажи появляются в случайных местах 
карты.
Игрок ходит с помощью команд: L, R, U, D (по первым буквам слов left, right, up, down). В зависимости от команды выбирается направление 
перемещения: влево, вправо, вверх, вниз.
Противники перемещаются в случайном направлении.
Если игрок перемещается в сторону, где уже кто-то находится, он наносит этому персонажу урон. Противники при этом никогда не бьют друг 
друга: они просто пропускают ход и остаются на своём месте. За пределы карты (20 на 20 клеток) ходить нельзя никому. Если кто-то выбрал 
направление за границами, ход пропускается.
Формула расчёта урона совпадает с той, что была в материале. Жизни уменьшаются на размер урона. При этом броня тоже сокращается на 
приведённый урон.
Игра заканчивается тогда, когда умирают либо все противники, либо игрок. В первом случае на экран выводится сообщение о победе, во 
втором — о поражении.
Если в начале хода игрок вводит команду save или load вместо направления перемещения, то игра либо сохраняет своё состояние в файл, 
либо загружает это состояние из файла.

Советы и рекомендации
• Для определения команды персонажа можно внутри структуры данных о нём завести флаг.
• Для отображения координат персонажей можно использовать структуру вектора из другой задачи, но заменить типы координат.
• Для сохранения параметров игры и их загрузки можно работать с текстовыми данными. Однако записать всё в двоичном формате проще, 
главное — соблюдать последовательность полей:

std::ofstream file("save.bin", std::ios::binary);
for (int i = 0; i < 6; ++i) {
file.write((char*)&(characters[i].position),
sizeof(characters[i].position));
…

• При загрузке используйте ifstream и ту же последовательность полей.

Задание необязательно сдавать на проверку. Но если хотите это сделать, куратор будет учитывать следующее:
• Корректно работает сохранение и загрузка в игре.
• После загрузки все атрибуты игрока, включая имя, восстанавливаются из файла.
• После загрузки количество противников на поле соответствует количеству противников при сохранении.
• Все игроки после загрузки появляются в местах, где они находились при сохранении.
• При ходе игрока не появляются новые противники.
• Перед загрузкой файла сохранения проверяется, есть ли он в операционной системе.

Что оценивается
• Программы запускаются и корректно работают, нет синтаксических ошибок.
• Имена переменных корректные, отражают суть хранимых данных.
• Создан текстовый интерфейс для всех программ.
• Во всех задачах корректно использованы структуры.
• Перед загрузкой файла в задачах проверяется его существование на диске.
• Выполнено минимум три задания.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct position{
    int x;
    int y;
};

struct character{
    string name;
    int health;
    int armor;
    int damage;
    position pos_on_map;
    bool is_alive = true;
};

void create_enemies(character enemies[5]){
    srand(time(0));
    for (int i=0; i<5; ++i){
        enemies[i].name = "Enemy № " + to_string(i+1);
        enemies[i].health = (rand() % 101) + 50;
        enemies[i].armor = rand() % 51;
        enemies[i].damage = (rand() % 16) + 15;
    }
}

void create_player_character(character& player_character){
    cout << "Введите имя вашего персонажа: ";
    cin >> player_character.name;
    cout << "Введите здоровье вашего персонажа: ";
    cin >> player_character.health;
    cout << "Введите броню вашего персонажа: ";
    cin >> player_character.armor;
    cout << "Введите урон вашего персонажа: ";
    cin >> player_character.damage;
}

void arrange_all_character_on_map(char map[20][20], character& player_character, character enemies[5]){
    srand(time(0));
    player_character.pos_on_map.x = rand() % 21;
    player_character.pos_on_map.y = rand() % 21;
    map[player_character.pos_on_map.y][player_character.pos_on_map.x] = 'P';

    for (int i=0; i<5; ++i){
        enemies[i].pos_on_map.x = rand() % 21;
        enemies[i].pos_on_map.y = rand() % 21;
        while (map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x] != '.'){
            enemies[i].pos_on_map.x = rand() % 21;
            enemies[i].pos_on_map.y = rand() % 21;
        }
        map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x] = 'E';
    }
}

void player_attack_enemy(character& player_character, character* enemy, char map[20][20]){
    if (enemy->armor >= player_character.damage){
        enemy->armor -= player_character.damage;
    }
    else {
        enemy->health -= player_character.damage - enemy->armor;
        enemy->armor = 0;
    }

    if (enemy->health < 0){
        enemy->health = 0;
    }

    if (enemy->health ==0){
        enemy->is_alive = false;
        map[enemy->pos_on_map.y][enemy->pos_on_map.x] = '.';
    }
}

void enemy_attack_player(character& enemy, character& player_character){
    if (player_character.armor >= enemy.damage){
        player_character.armor -= enemy.damage;
    }
    else {
        player_character.health -= enemy.damage - player_character.armor;
        player_character.armor = 0;
        if (player_character.health < 0){
            player_character.health = 0;
        }
    }
}

void print_map(char map[20][20]){
    cout << "Текущее состояние: " << endl;
    for (int i=0; i<20; ++i){
        for (int j=0; j<20; ++j){
            cout << map[i][j];
        }
        cout << endl;
    }
}

void move_enemies(char map[20][20], character enemies[5], character& player_character){
    srand(time(0));
    for (int i=0; i<5; ++i){
        int direction_move = rand() % 4;

        if (enemies[i].is_alive){
            if (direction_move == 0 && enemies[i].pos_on_map.x+1 < 20){
                if (map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x+1] == '.'){
                    map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x+1] = 'E';
                    map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x] = '.';
                    ++enemies[i].pos_on_map.x;
                }
                else if (map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x+1] == 'P'){
                    enemy_attack_player(enemies[i], player_character);
                } 
            }

            else if (direction_move == 1 && enemies[i].pos_on_map.x-1 >= 0){
                if (map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x-1] == '.'){
                    map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x-1] = 'E';
                    map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x] = '.';
                    --enemies[i].pos_on_map.x;
                }
                else if (map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x-1] == 'P'){
                    enemy_attack_player(enemies[i], player_character);
                }
            }
            else if (direction_move == 2 && enemies[i].pos_on_map.y+1 < 20){
                if (map[enemies[i].pos_on_map.y+1][enemies[i].pos_on_map.x] == '.'){
                    map[enemies[i].pos_on_map.y+1][enemies[i].pos_on_map.x] = 'E';
                    map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x] = '.';
                    ++enemies[i].pos_on_map.y;
                }
                else if (map[enemies[i].pos_on_map.y+1][enemies[i].pos_on_map.x] == 'P'){
                    enemy_attack_player(enemies[i], player_character);
                }
            }
            else if (direction_move == 3 && enemies[i].pos_on_map.y-1 >= 0){
                if (map[enemies[i].pos_on_map.y-1][enemies[i].pos_on_map.x] == '.'){
                    map[enemies[i].pos_on_map.y-1][enemies[i].pos_on_map.x] = 'E';
                    map[enemies[i].pos_on_map.y][enemies[i].pos_on_map.x] = '.';
                    --enemies[i].pos_on_map.y;
                }
                else if (map[enemies[i].pos_on_map.y-1][enemies[i].pos_on_map.x] == 'P'){
                    enemy_attack_player(enemies[i], player_character);
                }
            }
        }
    }
}

bool is_correct_command_to_move(string command, character& player_character){
    if (command == "L" && player_character.pos_on_map.x-1 <0){
        return false;
    }
    if (command == "R" && player_character.pos_on_map.x+1 > 20){
        return false;
    }
    if (command == "U" && player_character.pos_on_map.y-1 < 0){
        return false;
    }
    if (command == "D" && player_character.pos_on_map.y+1 > 20){
        return false;
    }
    return true;
}

character* find_ememy_by_position(int y, int x, character enemies[5]){
    for (int i=0; i<5; ++i){
        if (enemies[i].pos_on_map.x == x && enemies[i].pos_on_map.y == y){
            return &enemies[i];
        }
    }
}

void save_game(char map[20][20], character& player_character, character enemies[5]){
    ofstream file("save.bin", ios::binary);
    if (file.is_open()){
        file.write((char*) map, 400);
        file.write((char*) &player_character, sizeof(player_character));
        for (int i=0; i<5; ++i){
            file.write((char*) &enemies[i].armor, sizeof(enemies[i].armor));
            file.write((char*) &enemies[i].damage, sizeof(enemies[i].damage));
            file.write((char*) &enemies[i].health, sizeof(enemies[i].health));
            file.write((char*) &enemies[i].is_alive, sizeof(enemies[i].is_alive));
            size_t len = enemies[i].name.length()+1;
            file.write((char*) &len, sizeof(len));
            file.write((char*) enemies[i].name.c_str(), len);
            file.write((char*) &enemies[i].pos_on_map.x, sizeof(enemies[i].pos_on_map.x));
            file.write((char*) &enemies[i].pos_on_map.y, sizeof(enemies[i].pos_on_map.y));
        }
        file.close();
    }
    else {
        cout << "Файл не открыт" << endl;
    }
}

void load_game(char map[20][20], character& player_character, character enemies[5]){
    ifstream file("save.bin", ios::binary);
    if (file.is_open()){
        file.read((char*) map, 400);
        file.read((char*) &player_character, sizeof(player_character));
        for (int i=0; i<5; ++i){
            file.read((char*) &enemies[i].armor, sizeof(enemies[i].armor));
            file.read((char*) &enemies[i].damage, sizeof(enemies[i].damage));
            file.read((char*) &enemies[i].health, sizeof(enemies[i].health));
            file.read((char*) &enemies[i].is_alive, sizeof(enemies[i].is_alive));
            size_t len;
            file.read((char*) &len, sizeof(len));
            char* buf = new char[len];
            file.read(buf, len);
            enemies[i].name = buf;
            delete [] buf;
            file.read((char*) &enemies[i].pos_on_map.x, sizeof(enemies[i].pos_on_map.x));
            file.read((char*) &enemies[i].pos_on_map.y, sizeof(enemies[i].pos_on_map.y));
        }
        file.close();
    }
    else {
        cout << "Файл не открыт" << endl;
    }
}

void move_player_character(char map[20][20], character& player_character, character enemies[5]){
    cout << "Введите команду для движения персонажа L, R, U, D. (команда save для сохранения игры): ";
    string command;
    cin >> command;
    while (command != "L" && command != "R" && command != "U" && command != "D"){
        if (command == "save"){
            save_game(map, player_character, enemies);
            cout << "Игра сохранена!" << endl;
        }
        cout << "Введите команду для движения персонажа L, R, U, D. (команда save для сохранения игры): ";
        string command;
        cin >>  command;
    }

        while (!is_correct_command_to_move(command,player_character)){
            cout << "Персонаж выходит за границы карты. Введите другую команду: ";
            cin >> command;
        }

        if (command == "L"){
            if (map[player_character.pos_on_map.y][player_character.pos_on_map.x-1] == '.'){
                map[player_character.pos_on_map.y][player_character.pos_on_map.x-1] = 'P';
                map[player_character.pos_on_map.y][player_character.pos_on_map.x] = '.';
                --player_character.pos_on_map.x;
            }
            else {
                character* enemy = find_ememy_by_position(player_character.pos_on_map.y, (player_character.pos_on_map.x-1), enemies);
                player_attack_enemy(player_character, enemy, map);
            }
        }

        else if (command == "R"){
            if (map[player_character.pos_on_map.y][player_character.pos_on_map.x+1] == '.'){
                map[player_character.pos_on_map.y][player_character.pos_on_map.x+1] = 'P';
                map[player_character.pos_on_map.y][player_character.pos_on_map.x] = '.';
                ++player_character.pos_on_map.x;
            }
            else {
                character* enemy = find_ememy_by_position(player_character.pos_on_map.y, (player_character.pos_on_map.x+1), enemies);
                player_attack_enemy(player_character, enemy, map);
            }
        }

        else if (command == "U"){
            if (map[player_character.pos_on_map.y-1][player_character.pos_on_map.x] == '.'){
                map[player_character.pos_on_map.y-1][player_character.pos_on_map.x] = 'P';
                map[player_character.pos_on_map.y][player_character.pos_on_map.x] = '.';
                --player_character.pos_on_map.y;
            }
            else {
                character* enemy = find_ememy_by_position(player_character.pos_on_map.y-1, (player_character.pos_on_map.x), enemies);
                player_attack_enemy(player_character, enemy, map);
            }
        }

        else if (command == "D"){
            if (map[player_character.pos_on_map.y+1][player_character.pos_on_map.x] == '.'){
                map[player_character.pos_on_map.y+1][player_character.pos_on_map.x] = 'P';
                map[player_character.pos_on_map.y][player_character.pos_on_map.x] = '.';
                ++player_character.pos_on_map.y;
            }
            else {
                character* enemy = find_ememy_by_position(player_character.pos_on_map.y+1, (player_character.pos_on_map.x), enemies);
                player_attack_enemy(player_character, enemy, map);
            }
        }
}

int get_sum_health_enemies(character enemies[5]){
    int sum = 0;
    for (int i=0; i<5; ++i){
        sum += enemies[i].health;
    }
    return sum;
}

void print_armor_health(character& player_character, character enemies[5]){
    cout << "--------------------------------------" << endl;
    cout << "Показатели вашего персонажа: " << endl;
    cout  << "Здоровье: " << player_character.health << ". Броня: " << player_character.armor << endl;
    cout << "--------------------------------------" << endl;
    cout << "Показатели соперников: " << endl;
    for (int i=0; i<5; ++i){
        cout << enemies[i].name << ". Здоровье: " << enemies[i].health << ". Броня: " << enemies[i].armor << endl;
    }
    cout << "--------------------------------------" << endl;
}

int main(){
    setlocale(LC_ALL, "Russian");
    char map[20][20];
    for (int i=0; i<20; ++i){
        for (int j=0; j<20; ++j){
            map[i][j] = '.';
        }
    }

    character enemies[5];
    character player_character;
    cout << "Для загрузки сохраненной игры введите команду \"load\", или команду \"new\" для начала новой игры" << endl;
    string command;
    cin >> command;
    while (command != "load" && command != "new"){
        cout << "Для загрузки сохраненной игры введите команду \"load\", или команду \"new\" для начала новой игры" << endl;
        cin >> command;
    }
    
    if (command == "load"){
        load_game(map, player_character, enemies);
    }
    else {
        create_enemies(enemies);
        create_player_character(player_character);
        arrange_all_character_on_map(map, player_character, enemies);
    }
    
    print_map(map);
    print_armor_health(player_character,enemies);

    while (true){
        cout << "Ваш ход:" << endl;
        move_player_character(map,player_character,enemies);
        print_map(map);
        print_armor_health(player_character,enemies);

        if (get_sum_health_enemies(enemies) <= 0){
            cout << "Победил игрок!";
            break;
        }
        cout << "Ход соперников: " << endl;
        move_enemies(map,enemies,player_character);
        print_map(map);
        print_armor_health(player_character,enemies);

        if (player_character.health <=0){
            cout << "Победил соперник";
            break;
        }
    }

}
