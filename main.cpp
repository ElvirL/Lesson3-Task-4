/*
4. ��������� ������� ���� (�������������� �������)
��� ����� �������
���������� ���������� ������ ��������� ������� ����.
�������� ��������������� �� ����� �������� 20 �� 20 ������. �� ������� ������������ ����� � ��� ����������.
����� ������� ���� ������ ����� ������������ ����� �� ����� ������������ �� ���:
� ����� ���������� ������ P,
� ���������� � ������ E,
� ������ ����� � ������.
������ �������� ���� ����������� � ���� ��������� � ������:
� �����,
� ������,
� �������,
� �����.
������� �������� ���� ����������� � ��������� ������� �����:
� ����� ����������� �������� � ������� Enemy #N, ��� N � ���������� �����.
� ������� ����� ����������� ������� �������� � �� 50 �� 150.
� ������� ����� ����������� �� 0 �� 50.
� ���� ���� ���������� �������� � �� 15 �� 30 ������.
����� ������������ ������ ��������� ��������������. ����� ��� ��� ���������, ������� ���. ��� ��������� ���������� � ��������� ������ 
�����.
����� ����� � ������� ������: L, R, U, D (�� ������ ������ ���� left, right, up, down). � ����������� �� ������� ���������� ����������� 
�����������: �����, ������, �����, ����.
���������� ������������ � ��������� �����������.
���� ����� ������������ � �������, ��� ��� ���-�� ���������, �� ������� ����� ��������� ����. ���������� ��� ���� ������� �� ���� ���� 
�����: ��� ������ ���������� ��� � �������� �� ���� �����. �� ������� ����� (20 �� 20 ������) ������ ������ ������. ���� ���-�� ������ 
����������� �� ���������, ��� ������������.
������� ������� ����� ��������� � ���, ��� ���� � ���������. ����� ����������� �� ������ �����. ��� ���� ����� ���� ����������� �� 
���������� ����.
���� ������������� �����, ����� ������� ���� ��� ����������, ���� �����. � ������ ������ �� ����� ��������� ��������� � ������, �� 
������ � � ���������.
���� � ������ ���� ����� ������ ������� save ��� load ������ ����������� �����������, �� ���� ���� ��������� ��� ��������� � ����, 
���� ��������� ��� ��������� �� �����.

������ � ������������
� ��� ����������� ������� ��������� ����� ������ ��������� ������ � �� ������� ����.
� ��� ����������� ��������� ���������� ����� ������������ ��������� ������� �� ������ ������, �� �������� ���� ���������.
� ��� ���������� ���������� ���� � �� �������� ����� �������� � ���������� �������. ������ �������� �� � �������� ������� �����, 
������� � ��������� ������������������ �����:

std::ofstream file("save.bin", std::ios::binary);
for (int i = 0; i < 6; ++i) {
file.write((char*)&(characters[i].position),
sizeof(characters[i].position));
�

� ��� �������� ����������� ifstream � �� �� ������������������ �����.

������� ������������� ������� �� ��������. �� ���� ������ ��� �������, ������� ����� ��������� ���������:
� ��������� �������� ���������� � �������� � ����.
� ����� �������� ��� �������� ������, ������� ���, ����������������� �� �����.
� ����� �������� ���������� ����������� �� ���� ������������� ���������� ����������� ��� ����������.
� ��� ������ ����� �������� ���������� � ������, ��� ��� ���������� ��� ����������.
� ��� ���� ������ �� ���������� ����� ����������.
� ����� ��������� ����� ���������� �����������, ���� �� �� � ������������ �������.

��� �����������
� ��������� ����������� � ��������� ��������, ��� �������������� ������.
� ����� ���������� ����������, �������� ���� �������� ������.
� ������ ��������� ��������� ��� ���� ��������.
� �� ���� ������� ��������� ������������ ���������.
� ����� ��������� ����� � ������� ����������� ��� ������������� �� �����.
� ��������� ������� ��� �������.
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
        enemies[i].name = "Enemy � " + to_string(i+1);
        enemies[i].health = (rand() % 101) + 50;
        enemies[i].armor = rand() % 51;
        enemies[i].damage = (rand() % 16) + 15;
    }
}

void create_player_character(character& player_character){
    cout << "������� ��� ������ ���������: ";
    cin >> player_character.name;
    cout << "������� �������� ������ ���������: ";
    cin >> player_character.health;
    cout << "������� ����� ������ ���������: ";
    cin >> player_character.armor;
    cout << "������� ���� ������ ���������: ";
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
    cout << "������� ���������: " << endl;
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
        cout << "���� �� ������" << endl;
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
        cout << "���� �� ������" << endl;
    }
}

void move_player_character(char map[20][20], character& player_character, character enemies[5]){
    cout << "������� ������� ��� �������� ��������� L, R, U, D. (������� save ��� ���������� ����): ";
    string command;
    cin >> command;
    while (command != "L" && command != "R" && command != "U" && command != "D"){
        if (command == "save"){
            save_game(map, player_character, enemies);
            cout << "���� ���������!" << endl;
        }
        cout << "������� ������� ��� �������� ��������� L, R, U, D. (������� save ��� ���������� ����): ";
        string command;
        cin >>  command;
    }

        while (!is_correct_command_to_move(command,player_character)){
            cout << "�������� ������� �� ������� �����. ������� ������ �������: ";
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
    cout << "���������� ������ ���������: " << endl;
    cout  << "��������: " << player_character.health << ". �����: " << player_character.armor << endl;
    cout << "--------------------------------------" << endl;
    cout << "���������� ����������: " << endl;
    for (int i=0; i<5; ++i){
        cout << enemies[i].name << ". ��������: " << enemies[i].health << ". �����: " << enemies[i].armor << endl;
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
    cout << "��� �������� ����������� ���� ������� ������� \"load\", ��� ������� \"new\" ��� ������ ����� ����" << endl;
    string command;
    cin >> command;
    while (command != "load" && command != "new"){
        cout << "��� �������� ����������� ���� ������� ������� \"load\", ��� ������� \"new\" ��� ������ ����� ����" << endl;
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
        cout << "��� ���:" << endl;
        move_player_character(map,player_character,enemies);
        print_map(map);
        print_armor_health(player_character,enemies);

        if (get_sum_health_enemies(enemies) <= 0){
            cout << "������� �����!";
            break;
        }
        cout << "��� ����������: " << endl;
        move_enemies(map,enemies,player_character);
        print_map(map);
        print_armor_health(player_character,enemies);

        if (player_character.health <=0){
            cout << "������� ��������";
            break;
        }
    }

}
