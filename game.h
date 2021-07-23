
#ifndef MONSTERKAMPF_GAME_H
#define MONSTERKAMPF_GAME_H
#include "ConsoleWindow.h"
#include "player.h"
#include "enemy.h"
#include "tile.h"
#include "fight_mode.h"

class game : public ConsoleWindow {
private:
    player ash;
    leader rocko;
    std::vector<enemy*> enemies;
    std::vector<std::vector<char>> map;
    std::vector<power*> training;
    fight_mode current_fight;
    std::vector<position> used; //saves used objects like enemies or the muscle item so it wont get drawn a second time
    uint64_t ticker = 0; //ticker for keeping an eye on the time
    unsigned sec = 0; //variable for the 5seconds on power tile rule
    bool fight_menu = false; //if there is a confrontation with a wild monster/ a trainer the bool changes to true and the dialog starts
    bool fight = false; //if the fight starts bool is true
    bool wild_monster = false; //if player is on a grass tile and there is a appearance its true
    bool change_monster = false; //if player wants to change the first pokemon (press p) the dialog starts running
    bool init_enemies = false;
    bool major = false;
    bool quit = false;
public:
    game(); //init
    ~game() override; //deconstructor
    player get_player() const;
    std::vector<enemy*> get_enemies() const;
    std::vector<std::vector<char>> get_map() const;

    void onKeyPress() override;
    void onRefresh() override; //game-loop
    void draw_map(); //draws map and fills the vectors with the variables
    void clear_last(); //clears last tile from player symbol
    bool valid_move(const position &p); //checks if next move of player is valid
    bool check_enemy(const position &p); //checks if player is going into a fight!
    bool check_healing(const position &p); //checks if player is standing on healing tile
    bool check_used(const position &p);
    bool check_exit(const position &p);
    bool check_leader(const position &p);
    bool on_grass(const position &p); //checks if player is standing on grass tile
    bool on_training(); //checks if player stands on the muscle symbol
    void heal_team(); //fills the LP of the whole team
    power& find_power(const position &p); //searches in vector for the fitting power-tile at given position
    enemy& find_enemy(const position &p); //searches in vector for the enemy at given position
    int find_used(const position &p); //checks if positition is in used
    unsigned generate_probability(const unsigned &val); //generates random uint
    void wild_monster_appears(); //starts wild monster dialog
    void draw_interface();
    void change_first_monster(const unsigned &index);
    void change_monster_dialog();
    void fight_dialog();
    void leader_dialog();
    void fight_on();
    bool is_game_over();
    void game_over();
    void leave_game();
    void reset();


};


#endif //MONSTERKAMPF_GAME_H
