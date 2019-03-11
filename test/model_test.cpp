#include "model.h"
#include <catch.h>

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//

TEST_CASE("Test 1") {
    Piece p1;
    place_piece(5, {4,2});
    CHECK(p1.space == {4,2});
};

TEST_CASE("Test 2") {
    CHECK(is_valid_space({4,2}))    // Valid
    CHECK(!is_valid_space({-4,2}))  // Outside bounds
    CHECK(!is_valid_space({3,7}))  // Lake 1
    CHECK(!is_valid_space({7,7}))  // Lake 2
}

TEST_CASE("Test 3") {
    CHECK(is_input_valid(2));   // Valid (lower limit)
    CHECK(is_input_valid(13));  // Valid (upper limit)
    CHECK(!is_input_valid(0));  // Too Low
    CHECK(!is_input_valid(13));  // Too High
    CHECK(!is_input_valid(2));
}

TEST_CASE("Test 4") {
    Piece p1;
    p1.value = 6; // Captain
    p1.is_red = true;
    Piece p2;
    p2.value = 8;  // Colonel
    p2.is_red = false;
    CHECK(battleLoser(p1, p2) == p1);  // Colonel should win, std value comparison
    battle(p1, p2);
    CHECK(p1.live = true); // Bomb should be defused
    CHECK(p2.live = false); // Bomb should be defused
}

TEST_CASE("Test 5") {
    Piece p1;
    p1.value = 3; // miner
    p1.is_red = true;
    Piece p2;
    p2.value = 1; // value of flag
    p2.is_red = false;
    battle(p1, p2); // Game should end when piece encounters flag
    CHECK(winner_ != Player::neither); // Checks game over
}

TEST_CASE("Test 6") {
    Piece p1;
    p1.value = 3; // miner
    p1.is_red = true;
    Piece p2;
    p2.value = 12; // bomb
    p2.is_red = false;
    CHECK(battleLoser(p1, p2) == p2); // Miner should defuse bomb, miner should win
    battle(p1, p2);
    CHECK(p1.live = true); // Bomb should be defused
    CHECK(p2.live = false); // Bomb should be defused
}