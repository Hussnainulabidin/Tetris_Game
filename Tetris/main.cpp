/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(400, 480), title);
    Texture obj1, obj2, obj3 , obj4 , obj5, obj6, obj7 , obj8 , obj9;

    Texture hint;

    //loading images from fil
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/shadowtiles.png");
    obj5.loadFromFile("img/homepage.png");
    obj7.loadFromFile("img/scores.png");
    obj8.loadFromFile("img/nextblockframe.png");
    obj9.loadFromFile("img/bombs.png");

    Sprite sprite(obj1), background(obj2), frame(obj3) , showshadow(obj4) , homepage(obj5), help(obj6), mainscores(obj7), nextblockframe(obj8) , bombpic(obj9);

    Music music;                       //obj for game music
    music.openFromFile("img/sound.ogg");
    music.setVolume(50);
    music.play();

    Music music1;
    music1.openFromFile("img/sound1.ogg");
    music1.setVolume(30);
    music1.play();

    
    nextblockframe.setPosition(235 , 100);
    mainscores.setPosition(235, 220);

    Font font_score;
    font_score.loadFromFile("img/open-sans/OpenSans-ExtraBoldItalic.ttf");
    Text game_score;
    game_score.setFont(font_score);
    game_score.setPosition(270, 230);
    game_score.setCharacterSize(23);

    ifstream file_read;
    file_read.open("highscores.txt");

    int choice, choice2;
    bool exit = false;
    bool newgame = true;
    string name = "";
    while (window.isOpen())
    {
        music.pause();
        music1.setLoop(true);
        choice = 0;
        choice2 = 0;
       
        //******************************************* Main Menu Working *******************************************//
        Event m;
        while (window.pollEvent(m)) // condition false on choice2 == 2 so that it restart the game instead of show new menu
        {
            if (m.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();
            if (m.type == Event ::KeyPressed)
            {
                if (m.key.code == Keyboard::Num1)
                    choice = 1;
                else if (m.key.code == Keyboard::Num2)
                    choice = 2;
                else if (m.key.code == Keyboard::Num3)
                    choice = 3;
                else if (m.key.code == Keyboard::Num4)
                    exit = true;
            }
        }
        if (choice == 3)
        {
            Help(window);
        }
        if (exit == true)
        {
            window.close();
            break;
        }
        if (newgame == true)
        {
            window.draw(homepage);
            window.display();
        }
        if (choice == 2)
            highscores(window);
        //********************************************************************************//
      
        if (choice == 1 || !newgame)
        {
            nameinput(window , name);  // Input the Player name when new game starts
            music1.pause();            //Puting music1 on pause so that only game music will play
            music.play();
            music.setLoop(true);       //Setting Game music on loop so that it play again after ends
            
            // reset the grid to make evey block disapear when game restarts
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    gameGrid[i][j] = 0;

            // reset the block array to make evey block disapear
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 2; ++j)
                    point_1[i][j] = 0;

            newgame = true;
            int delta_x = 0, colorNum = 1;
            float timer = 0, delay = 0.4;
            bool rotate = 0;
            Clock clock;
            int rotatecheck = 0;
            int count = 0;
            int bomb;
            bool pause = false; // for Pause button press
            bool space = false; // for instant drop
            int arr[20][10] = {0};
            int shadow_block[4][2];
            bool newblockcheck = false;
            int newblockcount = 0;
            int newgrid[20][10] = {0};
            int next_block[4][2];
            int next_block_color = 1;
            int z = rand() % 7, m;
            char a[20];

            int scores = 0, lvl = 1, lines = 0;   //Variables for the Score count
            string str = "";

            while (window.isOpen())
            {                
                //delay = 0.3;
                float time = clock.getElapsedTime().asSeconds();
                clock.restart();
                timer += time;
                //*****************************Event Listening Part***********************************//
                Event e;
                while (window.pollEvent(e))
                {                                // Event is occurring - until the game is in running state
                    if (e.type == Event::Closed) // If cross/close is clicked/pressed
                        window.close();          // Opened window disposes
                    if (e.type == Event::KeyPressed)
                    {                                           // If any other key (not cross) is pressed
                        if (e.key.code == Keyboard::Up)         // Check if the other key pressed is UP key
                            rotate = true;                      // Rotation gets on
                        else if (e.key.code == Keyboard::Left)  // Check if the other key pressed is LEFT key
                            delta_x = -1;                       // Change in X-Axis - Negative
                        else if (e.key.code == Keyboard::Right) // Check if the other key pressed is RIGHT key
                            delta_x = 1;                        // Change in X-Axis - Positive
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) // Just another way to detect key presses without event listener
                    delay = 0.05;                           // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

                if (Keyboard ::isKeyPressed(Keyboard::Space)) // block fall instantly when space is pressed
                {
                    for (int j = 4; j >= 0; --j)
                    {
                        if (point_1[j][1] == 0) // checking if new block comes speed will be reset
                        {
                            space = false;
                        }
                    }
                    if (space == true && bomb != 3)
                    {
                        delay = 0.001; // increaing the speed of the block untill new block comes
                    }  
                    space = true;
                }

                if (Keyboard::isKeyPressed(Keyboard::P)) // Keyboard input P for pause
                    pause = true;

                //*******************PAUSE MENU WORKING ***********************//
                choice2 = 0;
               
                if (pause == true) // pause the game during playing
                {
                    music.pause();
                    music1.play();
                    pausegame(window , choice2 , newgame , exit ); //calling pause game function to display pause menu
                    if (exit == true || choice2 == 2)
                        break;
                    else if (choice2 == 3)
                    {
                        highscores(window);
                        pause = true;
                    }
                    else if (choice2 == 4)
                    {
                        Help(window);
                        pause = true;
                    }
                    else
                        pause = false;
                    music.play();
                    music1.pause();
                }
                //*******************************************************************//

            
                //****************START CALLING YOUR FUNCTIONS HERE*****************//
                fallingPiece(timer, delay, colorNum, rotatecheck, count, bomb, arr, newblockcheck, shadow_block, window, newgrid , next_block , z , m , next_block_color , lvl) ; // fallingPiece() function is called here
                //Increasing the Lvl and speed of the BLocks when certain amount of blocks have falled
                fallingspeed(delay, newblockcheck, newblockcount, lvl);  
                if (bomb == 3)
                {
                    rotate = false; //Bomb cannot be controlled so making the movement false
                    delta_x = 0;
                }
                if (rotate == true)
                {
                    rotate_block(rotatecheck, count);
                    rotate = false;
                }
                if (delta_x == -1 || delta_x == 1)
                {
                    move(delta_x);
                    delta_x = 0;
                }
                linebreak(scores, lines);   //Checking for line break after evey alteration
                bool check = false;
                check = losegame();         //Checking if Any block hits the 0 index of gameGrid it will return true
                if (check == true)
                {
                    savescore(scores,name); //Saving the score of the player when he loses
                    music1.play();
                    break;
                }
                string str = "SCORES \n    " + to_string(scores) + "\nLEVEL\n    " + to_string(lvl) + "\nLINES\n    " + to_string(lines);
                game_score.setString(str);

                //**********************************************************//
                window.clear(Color::Black);
                window.draw(background);
                window.draw(nextblockframe);
                //Drawing one new Grid under the gamegrid for shadow block
                for (int i = 0; i < M; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        if (newgrid[i][j] == 0)
                            continue;
                        showshadow.setTextureRect(IntRect(newgrid[i][j] * 18, 0, 18, 18));
                        showshadow.setPosition(j * 18, i * 18);
                        showshadow.move(28, 31); // offset
                        window.draw(showshadow);
                    }
                }
                for (int i = 0; i < M; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        if (gameGrid[i][j] == 0)
                            continue;
                        sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                        sprite.setPosition(j * 18, i * 18);
                        sprite.move(28, 31); // offset
                        window.draw(sprite);
                    }
                }
                if(bomb == 3)
                {
                for (int i = 0; i < 4; i++)
                {
                    bombpic.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    bombpic.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                    bombpic.move(28, 31);
                    window.draw(bombpic);
                }

                }
                else
                {
                for (int i = 0; i < 4; i++)
                {
                    sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                    sprite.move(28, 31);
                    window.draw(sprite);
                }
                }

                //For Next Block Diplaying it on the Exteme right with new 4 By 2 array
                for (int i = 0; i < 4; i++)
                {
                    sprite.setTextureRect(IntRect(next_block_color * 18, 0, 18, 18));
                    sprite.setPosition(next_block[i][0] * 18, next_block[i][1] * 18);
                    sprite.move(290,125);
                    window.draw(sprite);    
                }
                

                window.draw(mainscores);
                window.draw(game_score);
                //---The Final on Which Everything is Drawn Over is Loaded---//
                window.draw(frame);
                // window.draw(box);
                //---The Window that now Contains the Frame is Displayed---//
                window.display();
            }
        }
    }
    return 0;
}
