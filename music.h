#ifndef MUSIC_H
#define MUSIC_H

#define NOTE_BUFFER     1
#define END_SONG        0

// FREC
# define C2             0
# define D2             1
# define E2             2
# define F2             3
# define G2             4
# define A2             5
# define B2             6

# define C3             7
# define D3             8
# define E3             9
# define F3             10
# define G3             11
# define A3             12
# define B3             13

# define C4             14
# define D4             15
# define E4             16
# define F4             17
# define G4             18
# define A4             19
# define B4             20

# define C5             21

const uint16_t frec_map[] = {
  NOTE_C2,
  NOTE_D2,
  NOTE_E2,
  NOTE_F2,
  NOTE_G2,
  NOTE_A2,
  NOTE_B2,

  NOTE_C3,
  NOTE_D3,
  NOTE_E3,
  NOTE_F3,
  NOTE_G3,
  NOTE_A3,
  NOTE_B3,

  NOTE_C4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4,
  NOTE_G4,
  NOTE_A4,
  NOTE_B4,

  NOTE_C5,
};

/*const uint8_t music_duration[] = {
  8,
   
  8,
  
  8,
  
  8,
  
  8,
  
  8,
  
  8,
  
  4,
  2,
  2,
  
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,

  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,

  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,

  2,
  2,
  2,
  2,
  4,
  4,

  2,
  1,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,

  2,
  1,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,

  2,
  1,
  1,
  2,
  1,
  1,
  1,
  1, 
  1,
  1,
  1,
  1,
  1,
  1,

  2,
  1,
  1,
  2,
  1,
  1,
  1,
  1, 
  1,
  1,
  1,
  1,
  1,
  1,

  8,

  8,

  8,

  8,

  8,

  8,

  8,

  8,
};*/

const uint8_t music_chord[] {
  // BAR 1
  E4, 

  // BAR 1
  D4, 

  // BAR 1
  C4, 

  // BAR 1
  B3, 

  // BAR 1
  A3, 

  // BAR 1
  G3, 

  // BAR 1
  A3, 

  // BAR 1
  B3, 
  C4, 
  D4, 

  // BAR 1
  C4, 
  B3, 
  C4, 
  E3, 
  G3, 
  A3, 
  G3, 
  F3, 

  // BAR 1
  E3, 
  A3, 
  G3, 
  F3, 
  G3, 
  F3, 
  E3, 
  D3, 

  // BAR 1
  C3, 
  B2, 
  A2, 
  B2, 
  C3, 
  B2, 
  A2, 
  B2, 

  // BAR 1
  C3, 
  B2, 
  A2, 
  C3, 
  E3, 
  D3, 

  // BAR 1
  G4, 
  E4, 
  F4, 
  G4, 
  E4, 
  F4, 
  G4, 
  B3, 
  C4, 
  D4, 
  E4, 
  F4, 
  D4, 
  F4, 

  // BAR 1
  E4, 
  C4, 
  D4, 
  E4, 
  E3, 
  F3, 
  G3, 
  A3, 
  G3, 
  F3, 
  G3, 
  C4, 
  B3, 
  C4, 

  // BAR 1
  A3, 
  C4, 
  B3, 
  A3, 
  G3, 
  F3, 
  G3, 
  F3, 
  E3, 
  F3, 
  G3, 
  C4, 
  B3, 
  C4, 

  // BAR 1
  A3, 
  C4, 
  B3, 
  A3, 
  B3, 
  C4, 
  B3, 
  A3, 
  B3, 
  C4, 
  D4, 
  C4, 
  B3, 
  C4, 

  C4,
  
  G3,

  A3,

  E3,

  F3,

  C3,

  F3,

  G3,

  C5,

  G4,

  A4,

  E4,

  F4,

  C4,

  F4,

  G4,

  C5,
};

const uint16_t music_data[] = {
  // INTRO

  // BAR 1
  14, 

  // BAR 1
  22, 

  // BAR 1
  30, 

  // BAR 1
  38, 

  // BAR 1
  46,  

  // BAR 1
  54, 

  // BAR 1
  62, 

  // BAR 1
  70, 
  74, 
  76, 

  // BAR 1
  78, 
  80, 
  82, 
  84, 
  86, 
  88, 
  90, 
  92, 

  // BAR 1
  94, 
  96, 
  98, 
  100, 
  102,
  104, 
  106, 
  108, 

  // BAR 1
  110, 
  112, 
  114, 
  116, 
  118, 
  120, 
  122, 
  124, 

  // BAR 1
  126, 
  128, 
  130, 
  132, 
  134, 
  138, 

  // BAR 1
  142,
  144, 
  145, 
  146, 
  148, 
  149, 
  150, 
  151, 
  152, 
  153, 
  154, 
  155, 
  156, 
  157, 

  // BAR 1
  158, 
  160, 
  161, 
  162, 
  164, 
  165, 
  166, 
  167, 
  168, 
  169, 
  170, 
  171, 
  172, 
  173, 

  // BAR 1
  174, 
  176, 
  177, 
  178, 
  180, 
  181, 
  182, 
  183, 
  184, 
  185, 
  186, 
  187, 
  188, 
  189, 

  // BAR 1
  190, 
  192, 
  193, 
  194, 
  196, 
  197, 
  198, 
  199, 
  200, 
  201, 
  202, 
  203, 
  204, 
  205, 

  206, 
  
  214, 

  222, 

  230, 

  238, 

  246, 

  254, 

  262, 

  270,

  278,

  286,

  294,

  302,

  310,

  318,

  326,

  334,
  
  END_SONG
};

int16_t get_music_duration(int16_t music_index) {
  if (music_data[music_index + 1] == END_SONG)
    return 16;
  return music_data[music_index + 1] - music_data[music_index];
}

#endif
