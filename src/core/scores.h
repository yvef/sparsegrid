#ifndef INCLUDE_CORE_SCORES_H_
#define INCLUDE_CORE_SCORES_H_

#define PAWN_SCORE 1
#define KNIGHT_SCORE 4
#define BISHOP_SCORE 5
#define ROOK_SCORE 6
#define QUEEN_SCORE 10
#define DUMMY_SCORE 0x00


#define INIT_MATERIAL (PAWN_SCORE*8 + KNIGHT_SCORE*2 + BISHOP_SCORE*2 + ROOK_SCORE*2 + QUEEN_SCORE)

#endif  // INCLUDE_CORE_SCORES_H_
