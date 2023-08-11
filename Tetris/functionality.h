/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
using namespace sf;
using namespace std;

void lastgrid(int arr[20][10]);
void heavybomb(int arr[20][10], int, int newgrid[20][10]);
void shadowblock(int shadow_block[4][2]);
void showshadowblock(int shadow_block[4][2], int, RenderWindow &, int newgrid[][10]);
int linepoint(int);
void nextblock1(int &, int next_block[4][2]);
void shrinkgrid();

void fallingPiece(float &timer, float &delay, int &colorNum, int &rotatecheck, int &count, int &bomb, int arr[20][10], bool &newblockcheck,
                  int shadow_block[4][2], RenderWindow &window, int newgrid[][10], int next_block[4][2], int &z, int &m, int &color, int lvl)
{
    static int color1 = 1;
    static int shrinkcount = 0;
    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1; // How much units downward
        }
        shadowblock(shadow_block);                //saving every updated point 1 value in shaow block to show a perfect shadow
        showshadowblock(shadow_block, colorNum, window, newgrid);    //diplaying shaodow by using this function
        if (!anamoly())
        {
            newblockcheck = true;
            for (int i = 0; i < 4; ++i)
            {
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            }
            for (int i = 0; i < 20; ++i)   //saving all the gameGrid values in the new Grid for the shadow working
                for (int j = 0; j < 10; ++j)
                {
                    if (newgrid[i][j] == 8)
                        newgrid[i][j] = 0;
                    newgrid[i][j] = gameGrid[i][j];
                }

            if (bomb == 3)          //My bomb in on random value 3 so calling the function if bomb is 3
            {
                heavybomb(arr, colorNum, newgrid);
            }
            shrinkcount += 1;    //after every block shrink is counted to shrink on block reach 35
            if (shrinkcount > 35)
            {
                shrinkgrid();
                shrinkcount = 0;
            }
            lastgrid(arr);     //saving the gamegrid in this arr for bomb working
            colorNum = color1;
            int n = z;
            count = 0;         // Making count zero so it reset for rotation of every new block
            bomb = rand() % 7; // generating random number for Bomb and Bomb is at random number == 3
            if (bomb != 3)
            {
                lvlblocks(lvl, z, m, n, next_block);
                if (lvl == 1)
                {
                    m = rand() % 2 + 4;  //lvl one only 4 block will fall
                }
                if (lvl != 1)            //lvl geater than one all block will fall
                {
                    m = rand() % 7;
                }
            }
            else if (bomb == 3)
            {
                int m = rand() % 9; // generating random number so that Bomb will fall randomly
                for (int i = 0; i < 4; ++i)
                {
                    point_1[i][0] = 0 + m;
                    point_1[i][1] = 0;
                }
            }
            nextblock1(m, next_block);   //Creating the next block from the block array and dipling on screen 
            z = m; 
            color = rand() % 7 + 1;     //Creating color for very next block to display the block with its color
            color1 = color;
            rotatecheck = n; // Thiis check which Block from the array is Chosen to be rotated
        }
        timer = 0;
    }
}

//*************************** My Functions *******************************//

void pausegame(RenderWindow &window, int &choice2 , bool& newgame , bool& exit) //Function for game pause manu diplay and working on user choice
{
    Texture obj4;
    obj4.loadFromFile("img/pause.png");
    Sprite gamepause(obj4);

    while (window.isOpen())
    {

        Event n;
        while (window.pollEvent(n))
        {
            if (n.type == Event::Closed)
                window.close();
            if (n.type == Event ::KeyPressed)
            {
                if (n.key.code == Keyboard::Num1)
                    choice2 = 1;
                else if (n.key.code == Keyboard::Num2)
                {
                    newgame = false;    //IF start new game is pressed the new game is immediately started witout diplaying main menu
                    choice2 = 2;
                }
                else if (n.key.code == Keyboard::Num3)
                    choice2 = 3;
                else if (n.key.code == Keyboard::Num4)
                    choice2 = 4;
                else if (n.key.code == Keyboard::Num5) // Making Exit true so it will exit the main loop also when 5 is pressed
                    exit = true;
            }
        }
        if (choice2 != 0 || exit == true)
            break;

        window.draw(gamepause);
        window.display();
    }
}

void nameinput(RenderWindow &window, string &name) //Function for Taking input player name When new game starts
{
    Texture obj1;
    obj1.loadFromFile("img/entername.png");
    Sprite nameenter(obj1);
    char a[20];
    bool check = false;

    Font font_score;    //Loading font for player name input from the file
    font_score.loadFromFile("img/open-sans/OpenSans-Bold.ttf"); 
    Text playername;    //Making the Text Obj to display on Screen
    playername.setFont(font_score);
    playername.setFillColor(Color::Black);
    playername.setPosition(120, 270);
    playername.setCharacterSize(30);
    int i = 0;

    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
                break;
            }
            if (e.type == Event::TextEntered)  //Taking input when key from keyboard is pressed
            {
                if (e.text.unicode == 8) //If backspace pressed removing the charcter 
                {
                    --i;
                    a[i] = ' ';
                    name =a;
                    playername.setString(a);
                }
                else if (e.text.unicode < 128 && e.text.unicode < 128)  //if any charater b/w this limit is pressed taking input
                {
                    a[i] = e.text.unicode;
                    ++i;
                    name =a;
                    playername.setString(a);   //Saving the inout after every new input into the tect object
                }
            }
            if (e.key.code == Keyboard::Enter) //Input ends on ENTER key is pressed
            {
                check = true;
                break;
            }
        }
        window.draw(nameenter);
        window.draw(playername);

        window.display();
        if (check == true)
            break;
    }
}

void shrinkgrid()   //Function will Shrink Grid when lvl is Increased
{
    int i = 0;
    bool check = true;
    for (i = 0; i < M; ++i)     //Checking when any block in tge grid from Top is Found
    {
        for (int j = 0; j < N; ++j)
        {
            if (gameGrid[i][j] != 0)
            {
                check = false; //using boolean to also break the outer loop
                break;
            }
        }
        if (check == false)
            break;
    }
    for (i; i < M; ++i)    //Taking that value if i and moving all the onr row up for shrink
    {
        for (int j = 0; j < N; ++j)
        {
            gameGrid[i - 1][j] = gameGrid[i][j];
        }
    }
    for (int j = 0; j < N; ++j) //Placing black color in the bottom to give an effect of the shrinked grid
    {
        gameGrid[19][j] = 8;
    }
}

void nextblock1(int &m, int next_block[4][2])   //Function for Saving the next block from the Blocks array to Display 
{
    static int temp;
    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        next_block[i][0] = BLOCKS[m][i] % 2;
        next_block[i][1] = BLOCKS[m][i] / 2;
    }
}

void showshadowblock(int shadow_block[4][2], int colorNum, RenderWindow &window, int newgrid[20][10])  //Function for Diplaying the shadow in a new Grid
{
   // static int newgrid1[20][10] = {0};
    for (int i = 0; i < 20; ++i)   
        for (int j = 0; j < 10; ++j)
        {
            if (newgrid[i][j] == 8)    //Making all the updated value zero to show only shadow 
                newgrid[i][j] = 0;
            newgrid[i][j] = gameGrid[i][j];
        }

    bool check = false;
    bool check2 = false;
    while (true)
    {
        for (int i = 0; i < 4; ++i)   //making the shadow immediatley fall down words when block block is update
            shadow_block[i][1] += 1;
        for (int i = 0; i < 4; i++)   //Taking the help of anomoly to fall the block in every other block and do not cross the limits
            if (shadow_block[i][0] < 0 || shadow_block[i][0] >= N || shadow_block[i][1] + 1 >= M)
                check = true;
            else if (gameGrid[shadow_block[i][1] + 1][shadow_block[i][0]])
            {
                check = true;
                check2 = true;
            }
        if (check == true)
            break;
    }
    for (int i = 0; i < 4; ++i)   //In Increment some value exceed 19 (out of grid) returning them back to avod any crash
    {
        if (shadow_block[i][1] > 19)
        {
            for (;;)
            {
                for (int j = 0; j < 4; ++j)
                    shadow_block[j][1] -= 1;
                if (shadow_block[i][1] == 19)
                    break;
            }
        }
    }
    for (int i = 0; i < 4; ++i)   //Displaying the updated newgrid which us under the game grid but onlu diaplays shadow
    {
        newgrid[shadow_block[i][1]][shadow_block[i][0]] = colorNum;
    }
}

void shadowblock(int shadow_block[4][2])   //Function for when point1 is updated showblock is also updated to show a perfect shadow
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 2; ++j)
            shadow_block[i][j] = point_1[i][j];
}

void Help(RenderWindow &window)   //Function for displaying the Helpmenu
{
    bool check = true;
    Texture obj6;
    obj6.loadFromFile("img/help.png");  //Loading the back ground help img from the file
    Sprite help(obj6);

    while (window.isOpen())    //Displing the help menu in an infinte loop unite Escape is pressed
    {
        window.draw(help);
        window.display();
        Event n;
        while (window.pollEvent(n))
        {
            if (n.type == Event::Closed)
                window.close();
            if (n.type == Event ::KeyPressed)   //If Escape is pressed breaking out if the infinte loop
            {
                if (n.key.code == Keyboard::Num3 || n.key.code == Keyboard::Escape)
                {
                    check = false;
                    break;
                }
            }
        }
        if (check == false)
            break;
    }
}

void savescore(int &scores, string& playername)   //Function to save score of the player in high scores when game ends
{
    ifstream file_read;    
    ofstream file_write;
    string name;
    file_read.open("highscores.txt");   //Opening the file  
    int arr[10] = {0};
    string str;
    string names[10];
    string score;
    char a[20];
    int i = 0;
    int namelength;
    bool check = false;
    while (getline(file_read, str))  //Start taking input from the file untill the file ends
    {
        namelength = 0;
        name = "";
        for (int j = 0; str[j] != ' '; ++j)   //Checking for the First space which seperate Name from scores
        {
            namelength += 1;
        }
        for (int j = 0; j < namelength; ++j)  //Coping the name From str unitll name length
        {
            name += str[j];
        }
        int m = 0;
        for (int j = namelength + 1; str[j] != '\0'; ++j)   //Then copying the name from the namelength to \0
        {
            a[m] = str[j];
            ++m;
        }
        a[m] = '\0';
        score = a;
        arr[i] = stoi(score);  //storing the name in a string array
        names[i] = name;       //storing the score in the score array
        ++i;
    }

    int temp;
    string temp1;
    for (int i = 0; i < 10; ++i)  //Checking if the score player have made us greater than any of the score already in the file
    {
        if (arr[i] < scores)      //If found then
        {
            temp = arr[i];        //saing the score that is present in that index
            arr[i] = scores;      //Putting the new score in the array
            temp1 = names[i];     //same doing with name array to save the name
            names[i] = playername;
            for (int j = i + 1; j < 10; ++j)   //Then moving the each score downword to remove the lowest score and keep in the record of highst scores
            {
                scores = arr[j];
                arr[j] = temp;
                temp = scores;
            }
            for (int j = i + 1; j < 10; ++j)
            {
                playername = names[j];
                names[j] = temp1;
                temp1 = playername;
            }
            check = true;
        }
        if (check == true)
            break;
    }
    file_read.close();    //Closing the read mode of the file
    file_write.open("highscores.txt");
    for (int i = 0; i < 10; ++i)     //Wrting the updated data into the file
    {
        file_write << names[i] << " ";
        file_write << arr[i] << endl;
    }
    file_write.close();
}

void highscores(RenderWindow &window)          //Function to diplay High Scores Menu
{
    ifstream file_read;                        //opening file in read only mode
    file_read.open("highscores.txt");

    Texture obj7;                              //Making obj to display backgrund
    obj7.loadFromFile("img/highscores.png");
    Sprite highscorespic(obj7);

    Font font_score;
    font_score.loadFromFile("img/open-sans/OpenSans-ExtraBoldItalic.ttf");
    Text high_score;                           //Making the text obj to diplay the text on the screen
    high_score.setFont(font_score);
    high_score.setFillColor(Color::Black);
    high_score.setPosition(120, 100);
    high_score.setCharacterSize(25);

    string str;
    string allscores;
    while (getline(file_read, str))           //reading input from the file and storing it in a string
    {
        allscores += str;
        allscores += '\n';
    }
    file_read.close();
    bool check = false;
    while (window.isOpen())                   //Displaying the score untill escape is pressed
    {
        Event m;
        while (window.pollEvent(m))
        {
            if (m.type == Event::Closed)
                window.close();
            if (m.type == Event ::KeyPressed)
            {
                if (m.key.code == Keyboard::Num2 || m.key.code == Keyboard::Escape)
                {
                    check = true;
                    break;
                }
            }
        }
        if (check == true)
            break;
        high_score.setString(allscores);

        window.draw(highscorespic);
        window.draw(high_score);
        window.display();
    }
}

void fallingspeed(float &delay, bool &newblockcheck, int &newblockcount, int &lvl)  //Function to increse speed with increase in lvl
{
    static float delay1 = delay;
    if (newblockcheck == true)    //If new block come increament in the block to keep record and increase speed on certain limit reach
    {
        newblockcount += 1;
        newblockcheck = false;
    }
    if (newblockcount > 35)     //If block count has reached then increasing speed
    {
        delay = delay1 / 1.5;    
        lvl += 1;               //increment in lvl with every speed increase
        delay1 = delay;
        newblockcount = 0;
    }
    else                       //if space is pressed resetting the speed for the new block
    { 
        delay = delay1;   
    }
}

void lastgrid(int arr[20][10]) // Function for saving the Updated value of the gameGrid for comapring
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            arr[i][j] = gameGrid[i][j];
        }
    }
}

void heavybomb(int arr[20][10], int colorNum, int newgrid[20][10])  //Function for the working of the Bomb of bomb falls
{
    bool check = false;
    int newcolor;
    int new_i, new_j;
    for (int i = 0; i < 20; ++i)  //Checking for change in the gameGrid if the bomb falls 
    {                             //the Grid value changing and with that help of change knowing the place where that bomb have falled
        for (int j = 0; j < 10; ++j)
        {
            if (arr[i][j] != gameGrid[i][j])
            {
                newcolor = gameGrid[i + 1][j];  //saning the color of the block under the bomb block
                new_j = j;
                new_i = i + 1;
                break;
            }
        }
    }
    for (int i = 0; i < 20; ++i) // removing the bomb at the instant it falls down
    {
        for (int j = 0; j < 10; ++j)
        {
            if (arr[i][j] != gameGrid[i][j])
            {
                gameGrid[i][j] = 0;
            }
        }
    }

    if (newcolor == colorNum)  //if colors are equal making the Grid zero
    {
        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                if (gameGrid[i][j] != 8)
                    gameGrid[i][j] = 0;
            }
        }
    }
    else if (newcolor != colorNum)   //if color do not match removing the 4 block under
    {
        if (gameGrid[new_i][new_j] != 8)
            gameGrid[new_i][new_j] = 0;
        if (gameGrid[new_i + 1][new_j] != 8)
            gameGrid[new_i + 1][new_j] = 0;
        if (gameGrid[new_i][new_j + 1] != 8)
            gameGrid[new_i][new_j + 1] = 0;
        if (gameGrid[new_i + 1][new_j + 1] != 8)
            gameGrid[new_i + 1][new_j + 1] = 0;
    }
}

void rotate_block(int &rotatecheck, int &count) // Function for the rotation of the Block
{
    rotateblock(rotatecheck, count);
    if (count == 4) // making the counter for rotation zero so that it can be rotated again
        count = 0;
}

void move(int &delta_x) // Function for the movement of the block left right
{
    bool check = true;
    bool check1 = true;
    for (int i = 0; i < 4; ++i)
    {
        if (point_1[i][0] + 1 > 9)   //Making movement false if it exceeds the limit
            check = false;
    }
    for (int i = 0; i < 4; ++i)     //Making movement false if it exceeds the limit
    {
        if (point_1[i][0] - 1 < 0)
            check1 = false;
    }
    int col = point_1[0][0];
    int col1 = point_1[0][0];
    int row = point_1[0][1];
    for(int i = 1 ; i < 4; ++i )
    {
        if(point_1[i][0] > col)
            col = point_1[i][0];
    }
      for (int i = 1; i < 4; ++i)
    {
        if (point_1[i][1] > row)
            row = point_1[i][1];
        
    }
      //checking if does the go inside any block from side
    if(gameGrid[row][col+1] != 0 )
        check = false;
    if(gameGrid[row][col1-1] != 0 )
        check1 = false;
    

    //Making the movement by simply adding and substracting the coloum value in point 1

    if (check == true)
    {
        if (delta_x == 1)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] += 1; 
            }
        }
    }
    if (check1 == true)
    {
        if (delta_x == -1)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] -= 1;
            }
        }
    }
}

void linebreak(int &score, int &line) // Function for breaking the line which is full of blocks
{
    int count = 0;
    int line1 = 0;
    for (int i = 0; i < 20; ++i)     //Countinf the block present on each row
    {
        count = 1;
        for (int j = 0; j < 10; ++j)
        {
            if (gameGrid[i][j] > 0 && gameGrid[i][j] < 8)
            {
                count += 1;   
            }
        }

        if (count == 11)    //if Row is full
        {
            line1 += 1;
            for (int k = i; k >= 0; --k)      //Bringing all the block downward on that index one by one
            {
                for (int m = 0; m < 10; ++m)
                {
                    gameGrid[k][m] = gameGrid[k - 1][m];
                }
                if (k == 0)     // Making the row 0 equal to 0 to avoid any exception and garbage values
                {
                    for (int i = 0; i < 10; ++i)
                        gameGrid[k][i] = 0;
                }
            }
        }
    }
    score += linepoint(line1);
    line += line1;
}

int linepoint(int line1)  //Function for counting point on every line break
{
    if (line1 == 1)
        return 10;
    else if (line1 == 2)
        return 30;
    else if (line1 == 3)
        return 60;
    else if (line1 >= 4)
        return 100;
    return 0;
}

bool losegame()   //Function to check if any blokc hits the top of the Grid
{
    bool check = false;
    for (int i = 0; i < 10; ++i)
    {
        if (gameGrid[0][i] > 0)
        {
            check = true;
        }
    }
    return check;
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
