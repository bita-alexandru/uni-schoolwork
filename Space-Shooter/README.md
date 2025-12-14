Current playable iteration: https://we.tl/t-gX4s0Y4P3q

Current YouTube demo: https://youtu.be/MfpM1RGme1Q (not the latest release but still relevant)


# Week 1

The members of our team are: Bita Mihai-Alexandru, Nastasa Petru-Alexandru and Radeanu Dragos.

The game that we want to implement is a space shooter. The game mode consists of a single-player campaign and it will be available only on desktop PC platforms.

The player pilots a spaceship and his goal is to destroy the enemy ships, being rewarded with money for each enemy destroyed. The money can be invested in improving the ship or in hiring some help to deal with the more difficult enemies.
The winning condition is to defeat the boss at the end, an enemy that will put the player's abilities to a great test.

**Similar concepts:**

Chicken Invaders - https://www.interactionstudios.com/chickeninvaders.php

Space Impact - https://moraviagames.com/retro-space-impact/

# Week 2

## Game Prototype

In this prototype the player can control his spaceship using the keyboard.
There are 2 types of enemies which will spawn randomly (the higher the score, the faster they spawn) and try to destroy. One will shoot in a single direction while the other will shoot in two directions.

The player can destroy them in order to accumulate points and can be destroyed if their HP goes to 0. If this happens, pressing R will restart the game. Pressing Escape will quit it.

An executable prototype can be found here: https://we.tl/t-HuFQUSeRkT

# Week 3

## Money mechanics

In this iteration we've implemented a *punish and reward* system, in other words, **money mechanics**.

In order to have access to stronger equipment, the player needs to have some money. Money can be obtained by destroying enemies: the tougher the enemies, the better the reward!
If the player fails to destroy an enemy (it manages to leave the visible screen), some amount of money will be lost: the weaker the enemy, the greater the loss!


# Week 4

## Level manager

This iteration sketches out a *level-design solution* currently applicable for our first level of the game (changes may occur).

The entity will spawn a fixed number of certain enemies (depending on the level) at predefined intervals of time. Takes as parameters an array of *enemy types* and computes a list of tuples containing the **enemy** to be spawned, the **position** to be spawned at and the **time** to spawn at. 
After the list is successfully initialised, we iterate through it and spawn the enemies as described by the current tuple.

# Week 5

## New enemy type & UI

This week we're introducing a new enemy. Besides regular bullets, it can launch a special ability after a set amount of time. If the ability hits the player it will produce a certain disabling effect on their spaceship, in this case it will keep the player in place for 3 seconds (the player can still shoot). 

Also, we've set up some basic UI elements, such as buttons which can be controlled using the arrow keys and some pieces of text designed to display in-game meaningful information like *Player's HP* and *Gained money*.

That being said, the game is composed of 3 levels:
1. the first level will spawn enemies of type A (the weakest type)
2. the second level will spawn enemies of type A, type B (a slightly stronger type) and one of type C (the new type which we discussed about above)
3. the third level will spawn four enemies of type C (try and beat that)

\**the levels are subject to change*

# Week 6

## Bonuses & upgrade menu

With this iteration, the player will dispose of more tools to flawlessly beat a level: *bonuses*. These things will drop from the enemies with a certain probability (50% for now) and once they make contact with the player's spaceship the following effects may result: 
1. **HP bonus** (represented by a green circle) will heal up our player by 1 HP (cannot exceed player's maximum hp)
2. **Attack Speed bonus** (represented by a yellow circle) will reduce our player's reloading cooldown by 50%
3. **Movement Speed bonus** (represented by a purple circle) will increase our player's spaceship speed
4. **Bullets bonus** (represented by a red circle) will increase our player's number of bullets being shot a time (cannot exceed 4)

\**the numbers are subject to change*

After completing a level, the player will by greeted by a menu presenting a list of upgrading options (increase in HP; decrease in reloading time; increase in speed) and the basic buttons denoting *Advance*, *Retry* and *Quit*. Every upgrade costs 1$ for now.

# Week 7

## Special abilities & Pause/Resume System (done)

# Week 8

## New enemies & Revamping from Level System to an "Endless" game mode (75% done)

# Week 9

## Refactoring the Upgrade Menu, Level Design & Boss Fight (wip)
