
#include "game.h"
#include <fstream>
#include <iostream>
#include <random>
#include <QSoundEffect>
#include <QSound>

void play_sound(const QString &file) { //source: Qt documentation, https://doc.qt.io/qt-5/qsound.html
    QSound::play(file);
}


std::vector<std::vector<char>> readfile(const std::string &filename) { //source EiS PacMan Klausur PDF (few changes made)
    std::vector<std::vector<char>> streetmap;

    std::ifstream file(filename);
    if (!file.is_open())
        std::cout << "FILE OPENING ERROR!!" << std::endl;
    else {

        std::ifstream myfile(filename);
        if (myfile.is_open()) {
            std::string s;
            std::getline(myfile, s);
            do {
                std::vector<char> line(s.begin(), s.end());
                streetmap.push_back(line);

            } while ((std::getline(myfile, s)));
        }
        file.close();
    }
    return streetmap;
}

bool game::check_used(const position &p) {
    for (int i = 0; i < used.size(); ++i) {
        if (used[i] == p) { return true; }
    }
    return false;
}

void game::draw_map() { //draws world-map
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            position temp = position(j, i);
            if (map[i][j] == '0') { //init player
                if (!check_used(temp)) {
                    ash.set_pos(temp);
                    setCharacter(j, i, QString::fromUtf8("\xF0\x9F\x98\x83"));
                    used.push_back(temp);
                } else { setCharacter(j, i, ' '); }
            } else if (map[i][j] == 'T') { //init enemies
                if (!check_used(temp)) { //if enemy is not beaten draw it
                    if (!init_enemies) {
                        enemy *trainer = new enemy();
                        trainer->set_pos(temp);
                        enemies.push_back(trainer);
                    }
                    setCharacter(j, i, QString::fromUtf8("\xF0\x9F\x98\x92"));
                } else {
                    if (temp == ash.get_pos()) {
                        setCharacter(ash.get_pos().get_x(), ash.get_pos().get_y(),
                                     QString::fromUtf8("\xF0\x9F\x98\x83"));
                    } else { setCharacter(temp.get_x(), temp.get_y(), ' '); }
                }
            } else if (map[i][j] == '#') { //wall
                setCharacter(j, i, QString::fromUtf8("\xE2\x96\x92"));
            } else if (map[i][j] == 'E') { //exit
                setCharacter(j, i, QString::fromUtf8("\xE2\x9E\xA5"));
            } else if (map[i][j] == 'G') { //grass
                if (temp != ash.get_pos()) {
                    setCharacter(j, i, QString::fromUtf8("\xF0\x9F\x8C\xB2"));
                }
            } else if (map[i][j] == 'Y') { //power+
                if (!check_used(temp)) {
                    power *p = new power();
                    p->set_pos(temp);
                    training.push_back(p);
                    setCharacter(j, i, QString::fromUtf8("\xF0\x9F\x92\xAA"));
                }
            } else if (map[i][j] == 'P') { //Healing
                setCharacter(j, i, QString::fromUtf8("\xF0\x9F\xA4\x8E"));
            } else setCharacter(j, i, map[i][j]);
        }
    }
    if (!init_enemies) { //if first draw -> enemies get thir monsters (randomly)
        unsigned p;
        for (int i = 0; i < enemies.size(); ++i) {
            p = generate_probability(3);
            if (p == 1) { enemies[i]->set_mons(monster("DonnerRatte")); }
            else if (p == 2) { enemies[i]->set_mons(monster("BaumBaum")); }
            else if (p == 3) { enemies[i]->set_mons(monster("WasserKroete")); }
        }
        init_enemies = true;
    }
    if (!used.empty()) {
        setCharacter(ash.get_pos().get_x(), ash.get_pos().get_y(), QString::fromUtf8("\xF0\x9F\x98\x83"));
    } //if it isnt the first draw
}

bool game::valid_move(const position &p) { //checks if move is valid, returns true if position isnt initialised as '#' on the map
    if (map[p.get_y()][p.get_x()] == ' ') { return true; }
    else if (map[p.get_y()][p.get_x()] == '#') { return false; }
}

bool game::check_enemy(const position &p) { //checks if players position equals a certain enemys position
    if (map[p.get_y()][p.get_x()] == 'T') {
        map[p.get_y()][p.get_x()] = ' ';
        return true;
    } else { return false; }
}

void game::clear_last() { //sets character of last tile player was on recording to the information from the map, sets empty string if object is already used
    if (map[ash.get_last()[0].get_y()][ash.get_last()[0].get_x()] == 'P') {
        setCharacter(ash.get_last()[0].get_x(), ash.get_last()[0].get_y(), QString::fromUtf8("\xF0\x9F\xA4\x8E"));
    } else if (map[ash.get_last()[0].get_y()][ash.get_last()[0].get_x()] == 'G') {
        setCharacter(ash.get_last()[0].get_x(), ash.get_last()[0].get_y(), QString::fromUtf8("\xF0\x9F\x8C\xB2"));
    } else if (map[ash.get_last()[0].get_y()][ash.get_last()[0].get_x()] == 'Y') {
        if (check_used(ash.get_last()[0])) { setCharacter(ash.get_last()[0].get_x(), ash.get_last()[0].get_y(), ' '); }
        else {
            setCharacter(ash.get_last()[0].get_x(), ash.get_last()[0].get_y(), QString::fromUtf8("\xF0\x9F\x92\xAA"));
        }
    } else { setCharacter(ash.get_last()[0].get_x(), ash.get_last()[0].get_y(), ' '); }
    ash.clear_vec();
}

bool game::check_healing(const position &p) { //checks if player is on a healing tile ('P' on the map)
    if (map[p.get_y()][p.get_x()] == 'P') {
        return true;
    } else { return false; }
}

void game::heal_team() { //heals whole team
    for (int i = 0; i < ash.get_team().size(); ++i) {
        ash.get_team()[i]->heal_LP();
    }
}

bool game::on_training() { //checks if player is on training tile ('Y' on the map), if item was already used func returns false
    for (auto &i : training) {
        if (i->get_pos() == ash.get_pos()) { if (!i->is_used()) { return true; }}
    }
    return false;
}

bool game::on_grass(const position &p) { //checks if player is on gras tile ('G' on the map)
    if (map[p.get_y()][p.get_x()] == 'G') {
        return true;
    } else { return false; }
}

bool game::check_exit(const position &p) { //checks if player is on a exit tile ('E' on the map)
    if (map[p.get_y()][p.get_x()] == 'E') {
        return true;
    } else { return false; }
}

power &game::find_power(const position &p) { //returns power-tile
    for (int i = 0; i < training.size(); ++i) {
        if (training[i]->get_pos() == p) { return *training[i]; }
    }
}

enemy &game::find_enemy(const position &p) { //returns certain enemy for the fight_mode class
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->get_pos() == p) { return *enemies[i]; }
    }
}

int game::find_used(const position &p) { //returns -1 if object isnt in used-vector else returns index of the object in the vector
    for (int i = 0; i < used.size(); ++i) {
        if (used[i] == p) { return i; }
    }
    return -1;
}

bool game::is_game_over() { //checks if every monster has 0 LP
    for (auto i : ash.get_team()) {
        if (i->get_currentLP() != 0) { return false; }
    }
    return true;
}

unsigned int game::generate_probability(const unsigned int &val) { //generates random number from 1 to val, source:https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, val); // define the range

    return distr(gen);

}

void game::fight_on() { //starts fight
    clear();
    fight = true;
}

void game::change_first_monster(const unsigned &index) { //changes the active monster
    monster *temp = new monster();
    temp = ash.get_team()[0];
    ash.update_team(0, ash.get_team()[index]);
    ash.update_team(index, temp);

}

void game::change_monster_dialog() { //draws the interface if the player wants to change his active monster
    clear();
    if (ash.get_team()[0]->get_currentLP() == 0) { //player has to change if the active monster has 0 LP
        writeString(8, 13, "Dein aktives Monster wurde besiegt. Du musst es wechseln!");
    }
    writeString(8, 15, "Waehle das aktive Monster: ");
    for (int i = 0; i < ash.get_team().size(); ++i) {
        writeString(8, 17 + i, ash.get_team()[i]->get_name() + " " + "(" + std::to_string(i) + ")");
    }
}

void game::wild_monster_appears() { //draws the interface if there is a confrontation with a wild monster
    clear();
    play_sound("pokemon_battle_theme.wav"); //source: https://www.youtube.com/watch?v=hDpfyI8Ljvs
    wild_monster = true;
    fight = true;
    writeString(7, 15, "Ein wildes Monster erscheint (SuperTaube)! Was moechtest du tun?");
    if (ash.get_team().size() != 6) {
        writeString(7, 16, "Fangen (1) Flucht (2)");
    } else { //if team.size() == 6 player cant catch any more monsters (team is full)
        writeString(7, 16, "Dein Team ist voll. Du kannst nichts mehr fangen! Flucht (2)");
    }
}

void game::draw_interface() { //draws the interface of the monster-world with useful information about the players team
    writeString(0, 31, "Naechster Dialog: Press (n)");
    writeString(0, 32, "Wechsle aktives Monster: Press (p)");
    for (int i = 0; i < ash.get_team().size(); ++i) {
        writeString(0, 34 + i, "Monster: " + ash.get_team()[i]->get_name() +
                               " | LP: " + std::to_string((ash.get_team()[i]->get_currentLP())) + " /"
                               + std::to_string(ash.get_team()[i]->get_maxLP()) + " " + " AP: " +
                               std::to_string(ash.get_team()[i]->get_AP()) + " ");
    }

}

void game::fight_dialog() { //draws fight dialog
    clear();
    play_sound("pokemon_battle_theme2s.wav"); //source: https://www.youtube.com/watch?v=hDpfyI8Ljvs
    fight_menu = true;
    current_fight.set_heal(false);
    writeString(7, 15, "Der Trainer moechte kaempfen! Was moechtest du tun?");
    writeString(0, 25, "Dialog fortsetzen: (n)");
    writeString(0, 26, "Dein aktives Monster: " + ash.get_team()[0]->get_name() +
                       " |" + " LP: " + std::to_string(ash.get_team()[0]->get_currentLP()) + " /" +
                       std::to_string(ash.get_team()[0]->get_maxLP()) + " " + " AP: " +
                       std::to_string(ash.get_team()[0]->get_AP()) + " ");
    writeString(0, 28, "Gegnerisches Monster: " + current_fight.get_opponent().get_mons().get_name() +
                       " |" + " LP: " + std::to_string(current_fight.get_opponent().get_mons().get_currentLP()) + " /" +
                       std::to_string(current_fight.get_opponent().get_mons().get_maxLP()) + " " + " AP: " +
                       std::to_string(current_fight.get_opponent().get_mons().get_AP()) + " ");
}

void game::game_over() { //draws GAME OVER dialog
    clear();
    fight_menu = false;
    quit = true;
    clear();
    writeString(7, 15, "Alle Monster wurden besiegt. Ash faellt in Ohnmacht.");
    writeString(7, 17, "Moechtest du das Spiel  verlassen?   Ja: (j)   Neues Spiel: (g)");
}

void game::leave_game() {
    clear();
    quit = true;
    writeString(7, 15, "Moechtest du das Spiel  verlassen? Ja: (j)   Nein: (n)   Neues Spiel: (g)");
}

void game::reset() {
    ash.clear_team();
    enemies.clear();
    map.clear();
    training.clear();
    used.clear();
    ticker = 0;
    sec = 0;
    fight_menu = false;
    fight = false;
    wild_monster = false;
    change_monster = false;
    init_enemies = false;
    quit = false;
    map = readfile("map_advanced.txt");
}

void game::onKeyPress() {
    if (quit) { //if game over or on exit file
        if (getPressedKey() == 'j') {
            close();
        } else if (getPressedKey() == 'n') {
            ash.set_pos(position(ash.get_pos().get_x() - 1, ash.get_pos().get_y()));
            quit = false;
            draw_map();
        } else if (getPressedKey() == 'g') {
            reset();
            draw_map();
        }
    }
    if (change_monster) { //if player wants to change his active monster
        unsigned num = ash.get_team().size();
        if (getPressedKey() == '0') {
            if (fight) {
                change_monster = false;
                clear();
            } else {
                draw_map();
                change_monster = false;
            }
        } else if ((getPressedKey() == '1') && (num >= 1)) {
            if (fight) { //if player is in a fight!

                change_first_monster(1);
                ash.get_team()[0]->subtract_currentLP(current_fight.get_opponent().get_mons().get_AP());
                change_monster = false;
                clear();
                writeString(7, 18, "Gegnerisches " + current_fight.get_opponent().get_mons().get_name() +
                                   " greift an! Es richtet " +
                                   std::to_string(current_fight.get_opponent().get_mons().get_AP()) + " Schaden an.");
                play_sound("LowKick.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17240/

            } else {
                change_first_monster(1);
                draw_map();
                change_monster = false;
            }
        } else if ((getPressedKey() == '2') && (num >= 2)) {
            if (fight) { //if changing happens during a fight the active monster will get hit by the enemy
                change_first_monster(2);
                ash.get_team()[0]->subtract_currentLP(current_fight.get_opponent().get_mons().get_AP());
                change_monster = false;
                clear();
                writeString(7, 18, "Gegnerisches " + current_fight.get_opponent().get_mons().get_name() +
                                   " greift an! Es richtet " +
                                   std::to_string(current_fight.get_opponent().get_mons().get_AP()) + " Schaden an.");
                play_sound("LowKick.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17240/
            } else {
                change_first_monster(2);
                draw_map();
                change_monster = false;
            }
        } else if ((getPressedKey() == '3') && (num >= 3)) {
            if (fight) {
                change_first_monster(3);
                ash.get_team()[0]->subtract_currentLP(current_fight.get_opponent().get_mons().get_AP());
                change_monster = false;
                clear();
                writeString(7, 18, "Gegnerisches " + current_fight.get_opponent().get_mons().get_name() +
                                   " greift an! Es richtet " +
                                   std::to_string(current_fight.get_opponent().get_mons().get_AP()) + " Schaden an.");
                play_sound("LowKick.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17240/
            } else {
                change_first_monster(3);
                draw_map();
                change_monster = false;
            }
        } else if ((getPressedKey() == '4') && (num >= 4)) {
            if (fight) {
                change_first_monster(4);
                ash.get_team()[0]->subtract_currentLP(current_fight.get_opponent().get_mons().get_AP());
                change_monster = false;
                clear();
                writeString(7, 18, "Gegnerisches " + current_fight.get_opponent().get_mons().get_name() +
                                   " greift an! Es richtet " +
                                   std::to_string(current_fight.get_opponent().get_mons().get_AP()) + " Schaden an.");
                play_sound("LowKick.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17240/
            } else {
                change_first_monster(4);
                draw_map();
                change_monster = false;
            }
        } else if ((getPressedKey() == '5') && (num >= 5)) {
            if (fight) {
                change_first_monster(5);
                ash.get_team()[0]->subtract_currentLP(current_fight.get_opponent().get_mons().get_AP());
                change_monster = false;
                clear();
            } else {
                change_first_monster(5);
                draw_map();
                change_monster = false;
            }
        }


    }
    if (fight_menu || fight) {
        if (wild_monster) { //if there is a confrontation with a wild monster the player can catch it if he wants (he will always catch SuperTaube)
            if (getPressedKey() == '1') {
                if (ash.get_team().size() != 6) {
                    play_sound("capture_pokemon.wav"); //source: https://www.youtube.com/watch?v=8q41tKajv3A
                    fight = false;
                    wild_monster = false;
                    ash.append_team(new monster("SuperTaube"));
                    draw_map();
                } else { //if team is full nothing happens
                    fight = false;
                    wild_monster = false;
                    draw_map();
                }
            } else if (getPressedKey() == '2') { //run away option
                fight = false;
                wild_monster = false;
                play_sound("SFX_FLY.wav"); // source:  https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                draw_map();
            }
        } else {
            if (fight) {
                if (!change_monster) {
                    if (getPressedKey() == 'a') { //attack option
                        writeString(7, 18,
                                    "                                                                                                                                              "); //long empty string for clearing reasons
                        current_fight.opponent_mons_got_hit(ash.get_team()[0]->get_AP()); //opponents monster gets hit
                        if (current_fight.get_opponent().get_mons().get_currentLP() !=
                            0) { //if enemys monster hasnt died
                            writeString(7, 18, "Gegnerisches " + current_fight.get_opponent().get_mons().get_name() +
                                               " greift an! Es richtet " +
                                               std::to_string(current_fight.get_opponent().get_mons().get_AP()) +
                                               " Schaden an.");
                            ash.get_team()[0]->subtract_currentLP(
                                    current_fight.get_opponent().get_mons().get_AP());//players active monsters LP -= AP of active enemys monster
                        } else {
                            if (ash.get_team()[0]->get_currentLP() != 0) { //if ash has beaten the trainer

                            }
                        }
                        play_sound("LowKick.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17240/
                    } else if (getPressedKey() == 'h') { //healing option
                        if (!current_fight.is_healed()) {
                            play_sound("SFX_HEAL_UP.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                            writeString(7, 18,"                                                                                                                                          "); //long empty string for clearing reasons
                            ash.heal_active_monster();
                            current_fight.set_heal(true);
                            writeString(7, 18, "Gegnerisches " + current_fight.get_opponent().get_mons().get_name() +
                                               " greift an! Es richtet " +
                                               std::to_string(current_fight.get_opponent().get_mons().get_AP()) +
                                               " Schaden an.");
                            play_sound("LowKick.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17240/
                            ash.get_team()[0]->subtract_currentLP(current_fight.get_opponent().get_mons().get_AP());
                        }
                    } else if (getPressedKey() == 'c') { //change monster option
                        writeString(7, 18,
                                    "                                                                                                                            ");
                        change_monster = true;
                    } else if (getPressedKey() == 'f') { //run away option
                        int p = generate_probability(5); //generates probability of succesfull escape (80%)
                        if (p == 5) {
                            writeString(7, 18, "Flucht gescheitert! Gegnerisches " +
                                               current_fight.get_opponent().get_mons().get_name() +
                                               " greift an! Es richtet " +
                                               std::to_string(current_fight.get_opponent().get_mons().get_AP()) +
                                               " Schaden an.");
                            play_sound("SFX_DENIED.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                            ash.get_team()[0]->subtract_currentLP(current_fight.get_opponent().get_mons().get_AP());
                            play_sound("LowKick.wav"); // source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17240/
                        } else if (p != 5) { //if player succesfully escaped world-map appears again
                            play_sound("SFX_FLY.wav"); // source:  https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                            fight = false;
                            fight_menu = false;
                            clear();
                            draw_map();
                        }

                    }
                }
            }
            if (getPressedKey() == 'n') { fight_on(); } //starts fight dialog
        }
    } else { //sets movement direction of the player
        if (!wild_monster) {
            if (getPressedKey() == 1) {
                ash.set_direction(1);
            } else if (getPressedKey() == 2) {
                ash.set_direction(2);
            } else if (getPressedKey() == 3) {
                ash.set_direction(3);
            } else if (getPressedKey() == 4) {
                ash.set_direction(4);
            } else if (getPressedKey() == 'p') {
                change_monster = true;
            }
        }
    }
}


void game::onRefresh() { //game-loop
    if (quit) { return; }
    quit = false;
    if (change_monster) { //if player wants to change his active monster
        change_monster_dialog();
        return;
    }
    if (wild_monster) { return; } //if there is a wild monster confrontation do nothing until monster is captured or player decides to run away
    if (fight) { //draws interface for fight and updates if something happens
        if (is_game_over()) { //checks if game is over
            game_over();
            return;
        }
        if (ash.get_team()[0]->get_currentLP() ==0) { //if players active pokemon has 0 LP the player needs to change it if he can
            change_monster = true;
        }
        //next lines update the dialog with the current stats of the active monsters
        writeString(7, 15, "Angriff (a)   Heilen (h)   Wechsle aktives Monster(c)   Flucht (f)");
        writeString(0, 26, "Dein aktives Monster: " + ash.get_team()[0]->get_name() +
                           " |" + " LP: " + std::to_string(ash.get_team()[0]->get_currentLP()) + " /" +
                           std::to_string(ash.get_team()[0]->get_maxLP()) + " " + " AP: " +
                           std::to_string(ash.get_team()[0]->get_AP()) + " ");
        writeString(0, 28, "Gegnerisches Monster: " + current_fight.get_opponent().get_mons().get_name() +
                           " |" + " LP: " + std::to_string(current_fight.get_opponent().get_mons().get_currentLP()) +
                           " " + "/ " + std::to_string(current_fight.get_opponent().get_mons().get_maxLP()) + " " +
                           " AP: " +
                           std::to_string(current_fight.get_opponent().get_mons().get_AP()) + " ");
        if (current_fight.get_opponent().get_mons().get_currentLP() <=0) { //if enemys monser has 0 LP the player wins the fight
            writeString(7, 15, "Du hast gewonnen! Druecke (n) zum weiterspielen.                                 ");
            if (getPressedKey() == 'n') { //go back to world map
                ash.add_active_mons_AP(); //active monsters AP getting +1 if its a win
                clear();
                fight = false;
                fight_menu = false;
                draw_map();
            }
        }
    }
    ++ticker;
    if (!fight_menu) {  //game is over if every players monster has 0 LP
        if (check_exit(ash.get_pos())) {
            leave_game();
            return;
        }
        draw_interface(); //draws interface while world map is running
        if (getPressedKey() != 0 && //player only moves if a cursor button is pressed
            (getPressedKey() == 1 || getPressedKey() == 2 || getPressedKey() == 3 || getPressedKey() == 4)) {
            if (ticker % 2 == 0) { //decreasing speed
                if (ash.get_direction() == 1) { //movement to left
                    position temp = position(ash.get_pos().get_x() - 1, ash.get_pos().get_y());
                    if (valid_move(temp)) {
                        ash.move(temp);
                        setCharacter(temp.get_x(), temp.get_y(), ash.get_sym());
                        clear_last(); //clears last tile from players symbol
                        if (on_grass(ash.get_pos())) { //if player isnt standing checks if players on a grass tile
                            unsigned k = generate_probability(5);
                            if (k == 4) { wild_monster_appears(); }
                        }
                    }
                    else{ play_sound("SFX_COLLISION.wav");} //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                } else if (ash.get_direction() == 2) { //movement to right
                    position temp = position(ash.get_pos().get_x() + 1, ash.get_pos().get_y());
                    if (valid_move(temp)) {
                        ash.move(temp);
                        setCharacter(temp.get_x(), temp.get_y(), ash.get_sym());
                        clear_last();
                        if (on_grass(ash.get_pos())) { //if player isnt standing checks if players on a grass tile
                            unsigned k = generate_probability(5);
                            if (k == 4) { wild_monster_appears(); }
                        }
                    }
                    else{ play_sound("SFX_COLLISION.wav");} //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                } else if (ash.get_direction() == 3) { //movement up
                    position temp = position(ash.get_pos().get_x(), ash.get_pos().get_y() - 1);
                    if (valid_move(temp)) {
                        ash.move(temp);
                        setCharacter(temp.get_x(), temp.get_y(), ash.get_sym());
                        clear_last();
                        if (on_grass(ash.get_pos())) { //if player isnt standing checks if players on a grass tile
                            unsigned k = generate_probability(5);
                            if (k == 4) { wild_monster_appears(); }
                        }
                    }
                    else{ play_sound("SFX_COLLISION.wav");} //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                } else if (ash.get_direction() == 4) { //movement down
                    position temp = position(ash.get_pos().get_x(), ash.get_pos().get_y() + 1);
                    if (valid_move(temp)) {
                        ash.move(temp);
                        setCharacter(temp.get_x(), temp.get_y(), ash.get_sym());
                        clear_last();
                        if (on_grass(ash.get_pos())) { //if player isnt standing checks if players on a grass tile
                            unsigned k = generate_probability(5);
                            if (k == 4) { wild_monster_appears(); }
                        }
                    }
                    else{ play_sound("SFX_COLLISION.wav");} //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                }
                if (check_enemy(ash.get_pos())) { //if players position equals a certain enemys position the fight starts
                    used.push_back(
                            ash.get_pos());  //vector of already used enemies or items so they wont appear again on the world-map
                    current_fight.set_opponent(
                            find_enemy(ash.get_pos())); //gives the fight_mode class the current enemy (opponent)
                    fight_dialog();
                }
                if (check_healing(ash.get_pos())) {//if player is standing on healing tile the team will get full LP
                    play_sound("pokemon_healing_soundeffect.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                    heal_team();
                }

            }

        }
        if (on_training()) { //if player is on training field, player needs to wait ~5 seconds until the active monster gets +5 Max LP
            if (ticker >= 17) {
                ++sec;
                if(find_used(ash.get_pos()) == -1) {
                    if (sec == 5) {
                        if (find_used(ash.get_pos()) == -1) {
                            ash.get_team()[0]->add_max_LP();
                            find_power(ash.get_pos()).set_used(true);
                            sec = 0;
                            used.push_back(ash.get_pos());
                            play_sound(
                                    "SFX_LEVEL_UP.wav"); //source: https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/
                        } else { sec = 0; }
                    }
                }
            }

        } else { sec = 0; }
        if (ticker >= 20) { ticker = 0; } //reset ticker
    }

}

game::game() {
    map = readfile("map_advanced.txt");
    draw_map();

}

game::~game() noexcept { //deconstructor
    for (int i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
    for (int i = 0; i < training.size(); ++i) {
        delete training[i];
    }

}