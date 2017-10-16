#include <Arduboy2.h>

#include "Enums.h"

#include "Images_Arrows.h"
#include "Images_Dance.h"
#include "Images_Main_Menu.h"
#include "Images_Game_Over.h"

using namespace std;

// make an instance of arduboy used for many functions
Arduboy2 arduboy;

uint8_t game_scene = MAIN_MENU;
uint8_t frame = 0;

// Main menu global variables
uint8_t main_menu_animation_key_frame = 0;
uint8_t main_menu_index = 0;
uint8_t select_frame_rate = DEFAULT_FRAME_RATE;

// Dance scene global variables
uint8_t current_level = 1;
uint8_t current_play = 0;
uint8_t puzzle[] = {5, 5, 5, 5, 5, 5, 5, 5};
uint8_t player_tap[] = {5, 5, 5, 5, 5, 5, 5, 5};
uint8_t index_player_tap = 0;
bool generate_now = true;
uint8_t current_beat = 0;
uint8_t bpm = 120;
bool show_puzzle = false;
uint16_t current_score = 0;
uint16_t target_score = 0;
uint8_t last_accuracy = -1;
uint8_t max_level = 0;
uint16_t animation_key_frame = 0;
uint8_t maximum_play = 50;
uint8_t perfect = 0, good = 0, bad = 0, miss = 0;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  // initiate arduboy instance
  arduboy.begin();

  arduboy.setFrameRate(DEFAULT_FRAME_RATE);
  arduboy.initRandomSeed();
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  frame++;

  // first we clear our screen to black
  arduboy.clear();
  arduboy.pollButtons();

  switch(game_scene) {
    case SPLASH_SCREEN:
      break;

    case MAIN_MENU:
      main_menu();
      break;

    case DANCE_SCENE:
      dance_scene();
      break;

    case CREDIT_SCENE:
      credit();
      break;

    case HELP:
      help();
      break;

    case GAME_OVER:
      game_over();
      break;

    case SETTING:
      setting();
      break;
  }

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}

//==================================================================================================//
//                                          SETTING
//==================================================================================================//

void draw_setting_menu() {
  arduboy.setCursor(5, 20);
  arduboy.print("Speed");

  arduboy.setCursor(15, 30);
  arduboy.print(select_frame_rate);

  arduboy.drawBitmap(0, 30, left_indicator, 8, 8, WHITE);
  arduboy.drawBitmap(31, 30, right_indicator, 8, 8, WHITE);

  if (arduboy.justPressed(LEFT_BUTTON)) {
    select_frame_rate -= 4;
    if (select_frame_rate < 20)
      select_frame_rate = 36;
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {
    select_frame_rate += 4;
    if (select_frame_rate > 36)
      select_frame_rate = 20;
  }

  if (arduboy.justPressed(A_BUTTON)) {
    init_dance_scene();
    game_scene = DANCE_SCENE;
    arduboy.setFrameRate(select_frame_rate);
  }

  if (arduboy.justPressed(B_BUTTON)) {
    game_scene = MAIN_MENU;
  }
}

void setting() {
  main_menu_animation_key_frame += (frame % 16 == 0) ? 1 : 0;

  if (main_menu_animation_key_frame % 2 == 0)
    arduboy.drawBitmap(0, 0, main_title_1, 128, 64, WHITE);
  else
    arduboy.drawBitmap(0, 0, main_title_2, 128, 64, WHITE);

  draw_setting_menu();
}

//==================================================================================================//
//                                          CREDIT
//==================================================================================================//

void credit() {
  arduboy.drawBitmap(0, 0, credit_image, 128, 64, WHITE);

  arduboy.setCursor(64 - (9 * 6 / 2), 48);
  arduboy.print("Developer");

  arduboy.setCursor(64 - (6 * 16 / 2), 56);
  arduboy.print("Vincentius Madya");

  if (arduboy.justPressed(B_BUTTON)) {
    game_scene = MAIN_MENU;
  }
}

//==================================================================================================//
//                                          HELP
//==================================================================================================//

void help() {
  arduboy.drawBitmap(0, 0, help_image, 128, 64, WHITE);
  arduboy.setCursor(40, 10);
  arduboy.print("Type the arrow!");

  arduboy.setCursor(5, 37);
  arduboy.print("Press (A)/(B) on");
  arduboy.setCursor(5, 45);
  arduboy.print("the correct beat!");

  if (arduboy.justPressed(B_BUTTON)) {
    game_scene = MAIN_MENU;
  }
}

//==================================================================================================//
//                                          GAME OVER
//==================================================================================================//

void game_over() {
  arduboy.drawBitmap(0, 0, game_over_left, 32, 64, WHITE);
  arduboy.drawBitmap(96, 0, game_over_right, 32, 64, WHITE);

  arduboy.setCursor(25, 0);
  arduboy.print("[FINAL SCORE]");

  uint8_t score_width = 0;
  if (target_score < 10) score_width = 6;
  else if (target_score < 100) score_width = 12;
  else if (target_score < 1000) score_width = 18;
  arduboy.setCursor(64 - (score_width / 2), 15);
  arduboy.print(target_score);

  arduboy.fillRect(32, 24, 64, 2, WHITE);

  arduboy.setCursor(50, 64 - 8);
  arduboy.print("M: ");
  arduboy.print(miss);

  arduboy.setCursor(50, 64 - (8 * 2));
  arduboy.print("B: ");
  arduboy.print(bad);

  arduboy.setCursor(50, 64 - (8 * 3));
  arduboy.print("G: ");
  arduboy.print(good);

  arduboy.setCursor(50, 64 - (8 * 4));
  arduboy.print("P: ");
  arduboy.print(perfect);
  
  if (arduboy.justPressed(B_BUTTON) || arduboy.justPressed(A_BUTTON)) {
    game_scene = MAIN_MENU;
  }
}

//==================================================================================================//
//                                          MAIN MENU
//==================================================================================================//

void draw_main_menu() {
  arduboy.setCursor(0, 20);
  if (main_menu_index == 0)
    arduboy.print(" Play");
  else arduboy.print("Play");

  arduboy.setCursor(0, 30);
  if (main_menu_index == 1)
    arduboy.print(" Help");
  else arduboy.print("Help");

  arduboy.setCursor(0, 40);
  if (main_menu_index == 2)
    arduboy.print(" Credit");
  else arduboy.print("Credit");

  arduboy.drawBitmap(-2, 20 + (main_menu_index * 10) - 1, right_indicator, 8, 8, WHITE);
}

void main_menu() {
  main_menu_animation_key_frame += (frame % 16 == 0) ? 1 : 0;

  if (main_menu_animation_key_frame % 2 == 0)
    arduboy.drawBitmap(0, 0, main_title_1, 128, 64, WHITE);
  else
    arduboy.drawBitmap(0, 0, main_title_2, 128, 64, WHITE);

  draw_main_menu();

  if (arduboy.justPressed(UP_BUTTON))
    main_menu_index = ((main_menu_index - 1) + 3) % 3;

  if (arduboy.justPressed(DOWN_BUTTON))
    main_menu_index = (main_menu_index + 1) % 3;

  if (arduboy.justPressed(A_BUTTON)) {
    if (main_menu_index == 0) {
      game_scene = SETTING;
    } else if (main_menu_index == 1) {
      game_scene = HELP;
    } else if (main_menu_index == 2)  {
      game_scene = CREDIT_SCENE;
    }
  }
}

//==================================================================================================//
//                                          DANCE SCENE
//==================================================================================================//

void init_dance_scene() {
  current_level = 1;
  current_play = 0;

  for (uint8_t i = 0; i < 8; i++) {
    puzzle[i] = 5;
    player_tap[i] = 5;
  }
  
  index_player_tap = 0;
  generate_now = true;
  current_beat = 0;
  bpm = 120;
  show_puzzle = false;
  current_score = 0;
  target_score = 0;
  last_accuracy = -1;
  max_level = 0;
  animation_key_frame = 0;
  maximum_play = 50;
  perfect = 0, good = 0, bad = 0, miss = 0;
}

void dance_animation() {
  if (current_beat % 32 == 0)
    animation_key_frame++;

  if (animation_key_frame % 2) {
    arduboy.drawBitmap(80, 2, left_light, 24, 24, WHITE);
    arduboy.drawBitmap(47 - 24, 2, right_light, 24, 24, WHITE);
    arduboy.drawBitmap(56, 9, dance_2, 16, 16, WHITE);
  } else {
    arduboy.drawBitmap(80, 2, right_light, 24, 24, WHITE);
    arduboy.drawBitmap(47 - 24, 2, left_light, 24, 24, WHITE);
    arduboy.drawBitmap(56, 9, dance_1, 16, 16, WHITE);
  }

  arduboy.fillRect(23, 47 - 24 + 2, (80 + 24) - 23, 2, WHITE);
}

void generate_puzzle() {
  if (!generate_now)
    return;
  
  // Generate puzzle
  for (uint8_t i = 0; i < current_level; i++) {
    puzzle[i] = random(0, 4);
  }

  generate_now = false;
}

void display_puzzle() {
  // 0 = RIGHT
  // 1 = UP
  // 2 = LEFT
  // 3 = DOWN

  if (!show_puzzle)
    return;

  uint8_t total_screen_used = current_level * 16;
  uint8_t x_offset = (128 / 2) - (total_screen_used / 2);
  uint8_t y_offset = 32;

  for (uint8_t i = 0; i < current_level; i++) {
    if (puzzle[i] == 0) {
      if (puzzle[i] != player_tap[i])
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, right_off_arrow, 16, 16, WHITE);\
      else
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, right_on_arrow, 16, 16, WHITE);\
    }
    if (puzzle[i] == 1) {
      if (puzzle[i] != player_tap[i])
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, up_off_arrow, 16, 16, WHITE);
      else
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, up_on_arrow, 16, 16, WHITE);
    }
    if (puzzle[i] == 2) {
      if (puzzle[i] != player_tap[i])
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, left_off_arrow, 16, 16, WHITE);
      else 
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, left_on_arrow, 16, 16, WHITE);
    }
    if (puzzle[i] == 3) {
      if (puzzle[i] != player_tap[i])
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, down_off_arrow, 16, 16, WHITE);
      else 
        arduboy.drawBitmap(x_offset + 16 * i, y_offset, down_on_arrow, 16, 16, WHITE);
    }
  }
}

void do_tap(uint8_t idx) {
  if (index_player_tap >= current_level || !show_puzzle)
    return;

  if (puzzle[index_player_tap] != idx) {
    reset_player_tap();
    return;
  }

  player_tap[index_player_tap++] = idx;
}

void reset_player_tap() {
  index_player_tap = 0;
    
  for (uint8_t i = 0; i < 8; i++) {
    player_tap[i] = 5;
  }
}

void display_bpm_bar() {
  current_beat = (current_beat + 2) % 128;
  if (current_beat == 0)
    current_play++;

  if (show_puzzle) {
    if (current_play % 2 == 1 && current_beat < 96) {
      if (show_puzzle) {
        last_accuracy = MISS;
        current_level = 1;
        max_level = 0;
        miss++;
      }
      
      show_puzzle = false;
    }
  } else {
    if (current_play % 2 == 1 && current_beat == 96) {
      show_puzzle = true;
      reset_player_tap();
      generate_now = true;
      generate_puzzle();
      last_accuracy = NO_ACCURACY;
    }
  }

  uint8_t beat_bar_width = 6;

  if (current_beat >= 32 && current_beat <= 36)   // 32 Beat
    beat_bar_width = 10;

  if (current_beat >= 64 && current_beat <= 68)   // 64 Beat
    beat_bar_width = 10;
  
  if (current_beat >= 96 && current_beat <= 100)   // 96 Beat
    beat_bar_width = 16;

  if (current_beat >= 0 && current_beat <= 4)   // 128 Beat
    beat_bar_width = 10;

  arduboy.fillRect(96 - (beat_bar_width / 2), 54, beat_bar_width, 3, WHITE);
  arduboy.fillRect(0, 60, current_beat, 4, WHITE);
}

void show_accuracy() {
  arduboy.setCursor(0, 48);
  
  switch (last_accuracy) {
    case PERFECT:
      arduboy.print("Perfect!");
      break;

    case GOOD:
      arduboy.print("Good!");
      break;

    case BAD:
      arduboy.print("Bad!");
      break;

    case MISS:
      arduboy.print("Miss!");
      break;
  }
}

void show_score_beat() {
  // arduboy.fillRect(0, 0, 32, 20, BLACK);
  
  arduboy.drawBitmap(-2, 0, score_icon, 16, 8, WHITE);
  arduboy.setCursor(16, 0);
  if (current_score < target_score)
    current_score++;
  arduboy.print(current_score);

  arduboy.drawBitmap(-2, 10, beat_icon, 16, 8, WHITE);
  arduboy.setCursor(16, 10);
  arduboy.print((maximum_play - current_play));
}

void dance_scene() {
  generate_puzzle();
  display_puzzle();
  display_bpm_bar();

  if ((arduboy.justPressed(A_BUTTON) + arduboy.justPressed(B_BUTTON)) && show_puzzle) {
    // Scoring
    if (index_player_tap == current_level) {
      if (current_beat >= 94 && current_beat <= 98) {         // PERFECT!
        target_score += 3 * current_level;
        last_accuracy = PERFECT;
        perfect++;
      } else if (current_beat >= 90 && current_beat <= 102) { // GOOD!
        target_score += 2 * current_level;
        last_accuracy = GOOD;
        good++;
      } else if (current_beat >= 86 && current_beat <= 106) { // BAD!
        target_score += 1 * current_level;
        last_accuracy = BAD;
        bad++;
      } else {                                                // MISS
        last_accuracy = MISS;
        current_level = 0;
        max_level = 0;
        miss++;
      }
    } else {
      last_accuracy = MISS;
      current_level = 0;
      max_level = 0;
      miss++;
    }

    show_puzzle = false;
    
    current_level = 1 + (current_level % 8);
    max_level = max(current_level, max_level);
    if (max_level >= 4)
      current_level = max(current_level, 4);
    
    reset_player_tap();
  }

  show_accuracy();

  if (arduboy.justPressed(RIGHT_BUTTON))
    do_tap(0);
  if (arduboy.justPressed(UP_BUTTON))
    do_tap(1);
  if (arduboy.justPressed(LEFT_BUTTON))
    do_tap(2);
  if (arduboy.justPressed(DOWN_BUTTON))
    do_tap(3);

  if (maximum_play - current_play == 1)
    show_puzzle = false;

  dance_animation();
  show_score_beat();

  if (current_play >= maximum_play) {
    arduboy.setFrameRate(DEFAULT_FRAME_RATE);
    delay(1000);
    game_scene = GAME_OVER;
  }
}
