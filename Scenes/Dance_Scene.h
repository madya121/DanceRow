#include <Arduboy2.h>

//==================================================================================================//
//                                          DANCE SCENE
//==================================================================================================//

Arduboy2 *arduboy;

void init_dance_scene(Arduboy2 *_arduboy) {
  arduboy = _arduboy;
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
  uint8_t y_offset = 24;

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
    if (current_play % 2 == 1 && current_beat < 96)
      show_puzzle = false;
  } else {
    if (current_play % 2 == 1 && current_beat == 96) {
      show_puzzle = true;
      reset_player_tap();
      generate_now = true;
      generate_puzzle();
    }
  }

  uint8_t beat_bar_width = 6;

  if (current_beat >= 28 && current_beat <= 36)   // 32 Beat
    beat_bar_width = 8;

  if (current_beat >= 60 && current_beat <= 68)   // 64 Beat
    beat_bar_width = 8;
  
  if (current_beat >= 92 && current_beat <= 100)   // 96 Beat
    beat_bar_width = 12;

  if (current_beat >= 124 || current_beat <= 4)   // 128 Beat
    beat_bar_width = 8;

  arduboy.fillRect(96 - (beat_bar_width / 2), 54, beat_bar_width, 3, WHITE);
  arduboy.fillRect(0, 60, current_beat, 4, WHITE);
}

void dance_scene() {
  generate_puzzle();
  display_puzzle();
  display_bpm_bar();

  if (arduboy.justPressed(B_BUTTON) && show_puzzle) {
    // Scoring
    if (index_player_tap == current_level) {
      if (current_beat >= 94 && current_beat <= 98)         // PERFECT!
        target_score += 5 * current_level;
      else if (current_beat >= 90 && current_beat <= 102)   // GOOD!
        target_score += 3 * current_level;
      else if (current_beat >= 86 && current_beat <= 106)   // BAD!
        target_score += 1 * current_level;
      // else   MISS!
    }

    show_puzzle = false;
    current_level = 1 + (current_level % 8);
    reset_player_tap();
  }

  if (arduboy.justPressed(RIGHT_BUTTON))
    do_tap(0);
  if (arduboy.justPressed(UP_BUTTON))
    do_tap(1);
  if (arduboy.justPressed(LEFT_BUTTON))
    do_tap(2);
  if (arduboy.justPressed(DOWN_BUTTON))
    do_tap(3);

  arduboy.setCursor(0, 0);

  if (current_score < target_score)
    current_score++;
  arduboy.print(current_score);
}
