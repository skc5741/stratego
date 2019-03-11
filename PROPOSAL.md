# Proposal: Stratego

## Synopsis

### Elements

My game will have three elements:

- A 10x10 board with visible alternating colors and two unplayable
    lake areas
- A blue army of 40 pcs
- A red army of 40 pcs

Each army is made up of  soldiers with a numbered ranking, bombs, and
one flag.

The available pieces are as follows:
- 8 scouts (2)
- 5 miners (3)
- 4 Sergeants (4)
- 4 Lieutenants (5)
- 4 Captains (6)
- 3 Majors (7)
- 2 Colonels (8)
- 1 General (9)
- 1 Marshall (10)
- 1 Spy (S)
- 6 Bombs
- 1 Flag

### Goal

The objective of the game is to capture the flag of the other team,
or to eliminate every movable piece of your opponent's army. If any
player cannot move a piece during their turn, they lose the game.

### Game play

Each player begins by privately assembling their army on the board,
with the objective of protecting their flag. During the game, the
value of the opponent's pieces are not visible to each player.
Once each team has assembled their army, each team alternates
moving a movable piece in their army, beginning with the red army.
Each piece is able to move to one adjacent location, without moving
diagonally. If the current player moves their piece to a location
with an enemy piece, they have attacked, and whoever has the higher
rank wins. There are some exceptions to this:

- A scout (2) has increased movement ability, and can move as far
as they would like to in any given direction, as a rook in chess
would be able to do. Additionally, after their movement, they can
make an additional move to attack a piece.
- If any piece (with the exception of the miner (3) ) attempts to
attack a bomb, they are immediately removed from the game board.
If the attacking piece is a miner (3), then the bomb is defused
and removed from the game board, and the miner (3) remains. All bombs
remain on the board until they are defused by a miner (3).
- If the attacking and defending pieces are of the same rank, they
are both removed from the board.
- If a spy (S) attacks a marshall (10), the spy (S) wins and the
marshall (10) is removed from the game board. If the spy (S) attacks or
is attacked by any other piece on the board, or if the spy (S) is
attacked by the marshall (10), then the spy is removed from the board.
- No player is allowed to move over or  onto the lakes in the center of
the board.
- The flag and bombs cannot move during a player's turn.

## Functional requirements

1. Board must appear on the screen in alternating colors with two lake
spaces in the center.

2. Each player must be able to set up their army, with each player
having complete autonomy in which pieces go where.

3. The turn of each player must be tracked.

4. At any given turn the opponent's army should not be visible.

5. Between turns, neither army should be visible, until the current
player indicates they are ready to move.

6. Each player should be able to choose which piece they want to move.

7. If the player selects an invalid piece, they should be able to
select again.

8. The available moves for each piece should be highlighted, similar
to the reversi program.

9. The player should be able to select where they want to move their
piece.

10. If a player moves to an invalid space, they should be able to select
again.

11. If the player moves to a contested spot, battle ensues.

12. If battle ensues, the valid winner is selected by comparing values
                              and takes the contested space.

13. If the flag is taken, winner is declared and the game ends.

14. If any player has no more valid moves, the opponent wins and the
game ends.

## Open questions

- How can we best approach filling each army?

- How can we best represent the values of each piece?

- What should we use for the sprites of our players?

- How can we best maintain secrecy while switching turns on
a single computer?

- How can we test certain elements in a full size game?

