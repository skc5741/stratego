#include "model.h"
#include <catch.h>

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//

using namespace ge211;

struct Test_access {
    Model &m_;
    bool setup_is_valid_space(Position pos, Player plyr)
        { return m_.setup_is_valid_space(pos, plyr); }
    //bool is_input_valid(int x) { return m_.is_value_valid(x); }
    void place_piece(Piece pc, Position pos)
        { return m_.place_piece(pc, pos); }
    void finish_setup() { m_.finish_setup(); }
    bool is_movable(Position pos) { return m_.is_movable(pos); }
    bool is_playable(Player plyr) { return m_.is_playable(plyr); }
    void compute_next_moves(Piece pc) { m_.compute_next_moves(pc); }
    bool is_valid_space(Position pos) { return m_.is_valid_space(pos); };
    void advance_turn() { m_.advance_turn(); }
    void end_game() { m_.end_game(); }
    void battle(Piece* pc1, Piece* pc2) { m_.battle(pc1, pc2); }
    Piece* battleLoser(Piece* pc1, Piece* pc2) { return m_.battleLoser(pc1, pc2); }
    void deleteLoser(Piece* pc) { m_.deleteLoser(pc); }
};

TEST_CASE("Test Place Piece") {
    Position pos = {4,2};

    Piece p1(Player::red, 5);
    Model m;
    Test_access t{m};

    //t.place_piece(5, pos);
    CHECK(p1.position() == pos);
};

TEST_CASE("Test Is Valid Space") {
    Model m;
    Test_access t{m};

    CHECK(t.is_valid_space({4,2}));    // Valid
    CHECK(!t.is_valid_space({-4,2}));  // Outside bounds
    CHECK(!t.is_valid_space({3,7}));  // Lake 1
    CHECK(!t.is_valid_space({7,7}));  // Lake 2
}

TEST_CASE("Test Setup Is Valid Space") {
    Model m;
    Test_access t{m};


    // Never used this function //
    //CHECK(t.is_input_valid(0));   // Valid (lower limit)
    //CHECK(t.is_input_valid(11));  // Valid (upper limit)
    //CHECK(!t.is_input_valid(-1));  // Too Low
    //CHECK(!t.is_input_valid(12));  // Too High

    CHECK(t.setup_is_valid_space({0,0}, Player::blue)); // Valid setup space
    CHECK(t.setup_is_valid_space({9,9}, Player::red));  // Valid setup space
    CHECK(!t.setup_is_valid_space({0,0}, Player::blue));  // In opposite setup space
    CHECK(!t.setup_is_valid_space({9,9}, Player::red));  // In opposite setup space
    CHECK(!t.setup_is_valid_space({2,4}, Player::blue));  // In lake
    CHECK(!t.setup_is_valid_space({2,4}, Player::red));  // In lake
}

TEST_CASE("Test Batt") {
    Piece p1(Player::red, 6); // Captain
    Piece p2(Player::blue, 8);  // Colonel
    Model m;
    Test_access t{m};

    p1.place_position({0,0});
    CHECK(t.battleLoser(&p1, &p2) == &p1);  // Colonel should win, std val comparison
    t.battle(&p1, &p2);
    CHECK(!p1.alive()); // Captain should be dead
    CHECK(p2.alive()); // Colonel should be fine
}

TEST_CASE("Test Flag Capture") {
    Piece p1(Player::red, 3); // miner
    Piece p2(Player::blue, 0); // val of flag
    Model m;
    Test_access t{m};

    //t.battle(p1, p2); // Game should end when piece encounters flag
    CHECK(m.is_game_over()); // Checks game over
    CHECK(m.winner() == Player::red); // Checks winner
}

TEST_CASE("Test Bomb Defuses") {
    Piece p1(Player::red, 3); // miner
    Piece p2(Player::blue, 11); // bomb
    Model m;
    Test_access t{m};

    CHECK(t.battleLoser(&p1, &p2) == &p2); // Miner should defuse bomb, miner should win
    t.battle(&p1, &p2);
    CHECK(p1.alive()); // Miner should be fine
    CHECK(!p2.alive()); // Bomb should be defused
}