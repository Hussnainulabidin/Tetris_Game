/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * Shape of each piece is represented by rows in the array.
 * TIP: Name the array what is already been coded to avoid any unwanted errors.
 */

int BLOCKS[10][10] = {{0, 2, 4, 5}, {0, 1, 3, 5}, {0, 2, 3, 5}, {1, 2, 3, 4}, {0, 2, 3, 4}, {0, 2, 4, 6}, {0, 1, 3, 2}};

void lvlblocks(int lvl, int &z, int &m, int &n, int next_block[4][2])
{
    if (lvl == 1)    // lvl is one game is played with only four simplest blocks
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = BLOCKS[n][i] % 2;
            point_1[i][1] = BLOCKS[n][i] / 2;
        } 
    }
    if (lvl != 1)
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = BLOCKS[n][i] % 2;
            point_1[i][1] = BLOCKS[n][i] / 2;
        }
    }
}

void rotateblock(int &n, int &count)
{
    bool check = true;
    int row = point_1[0][1];
    int col = point_1[0][0];
    for (int i = 1; i < 4; ++i)
    {
        if (point_1[i][1] > row)
        {
            row = point_1[i][1];
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        if (point_1[i][0] + 1 > 9)
            check = false;
    }
    row -= 1;
    
    //cordinates for each block is set just changing the value ion rotate count when rotate is called 
    int J[4][4] = {{3, 2, 4, 6}, {0, 2, 4, 5}, {6, 3, 5, 7}, {2, 3, 5, 7}};
    int L[4][4] = {{1, 0, 4, 2}, {0, 2, 4, 5}, {4, 1, 3, 5}, {0, 1, 3, 5}};
    int S[3][4] = {{1, 2, 3, 4}, {0, 2, 3, 5}, {1, 2, 3, 4}};
    int Z[3][4] = {{0, 2, 3, 5}, {1, 2, 3, 4}, {0, 2, 3, 5}};
    int T[3][4] = {{1, 2, 3, 5}, {0, 2, 3, 4}};
    int I[3][4] = {{0, 2, 4, 6}};
    // if(check == true)
    //{
    if (n == 0)
    {
        if (count == 0)
        {
            col -= 1;
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = J[0][i] / 2 + col;
                point_1[i][1] = J[0][i] % 2 + row;
            }
        }
        if (count == 1)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = J[1][i] % 2 + col;
                point_1[i][1] = J[1][i] / 2 + row;
            }
        }
        if (count == 2)
        {
            col -= 1;
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = J[2][i] / 2 + col;
                point_1[i][1] = J[2][i] % 2 + row;
            }
        }
        if (count == 3)
        {
            col -= 1;
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = J[3][i] % 2 + col;
                point_1[i][1] = J[3][i] / 2 + row;
            }
        }
        count += 1;
    }
    if (n == 1)
    {
        if (count == 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = L[0][i] / 2 + col;
                point_1[i][1] = L[0][i] % 2 + row;
            }
        }
        if (count == 1)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = L[1][i] % 2 + col;
                point_1[i][1] = L[1][i] / 2 + row;
            }
        }
        if (count == 2)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = L[2][i] / 2 + col;
                point_1[i][1] = L[2][i] % 2 + row;
            }
        }
        if (count == 3)
        {
            col -= 1;
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = L[3][i] % 2 + col;
                point_1[i][1] = L[3][i] / 2 + row;
            }
        }
        count += 1;
    }
    if (n == 2)
    {
        if (count == 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = S[0][i] / 2 + col;
                point_1[i][1] = S[0][i] % 2 + row;
            }
        }
        if (count == 1)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = S[1][i] % 2 + col;
                point_1[i][1] = S[1][i] / 2 + row;
            }
        }
        if (count == 2)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = S[0][i] / 2 + col;
                point_1[i][1] = S[0][i] % 2 + row;
            }
        }
        if (count == 3)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = S[1][i] % 2 + col;
                point_1[i][1] = S[1][i] / 2 + row;
            }
        }
        count += 1;
    }
    if (n == 3)
    {
        if (count == 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = Z[0][i] / 2 + col;
                point_1[i][1] = Z[0][i] % 2 + row;
            }
        }
        if (count == 1)
        {
            col -= 1;
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = Z[1][i] % 2 + col;
                point_1[i][1] = Z[1][i] / 2 + row;
            }
        }
        if (count == 2)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = Z[0][i] / 2 + col;
                point_1[i][1] = Z[0][i] % 2 + row;
            }
        }
        if (count == 3)
        {
            col -= 1;
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = Z[1][i] % 2 + col;
                point_1[i][1] = Z[1][i] / 2 + row;
            }
        }
        count += 1;
    }
    if (n == 4)
    {
        if (count == 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = T[0][i] / 2 + col;
                point_1[i][1] = T[0][i] % 2 + row;
            }
        }
        if (count == 1)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = T[0][i] % 2 + col;
                point_1[i][1] = T[0][i] / 2 + row;
            }
        }
        if (count == 2)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = T[1][i] / 2 + col;
                point_1[i][1] = T[1][i] % 2 + row;
            }
        }
        if (count == 3)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = T[1][i] % 2 + col;
                point_1[i][1] = T[1][i] / 2 + row;
            }
        }
        count += 1;
    }
    if (n == 5)
    {
        if (count == 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = I[0][i] / 2 + col;
                point_1[i][1] = I[0][i] % 2 + row;
            }
        }
        if (count == 1)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = I[0][i] % 2 + col;
                point_1[i][1] = I[0][i] / 2 + row;
            }
        }
        if (count == 2)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = I[0][i] / 2 + col;
                point_1[i][1] = I[0][i] % 2 + row;
            }
        }
        if (count == 3)
        {
            for (int i = 0; i < 4; ++i)
            {
                point_1[i][0] = I[0][i] % 2 + col;
                point_1[i][1] = I[0][i] / 2 + row;
            }
        }
        count += 1;
    }
    //}
    int new_i = 0;
    bool check1 = false;
    for (int i = 0; i < 4; ++i)
    {
        if (point_1[i][0] > 9)
        {
            check1 = true;
        }
    }
    if (check1 == true)
    {
        new_i = point_1[1][0];
        for (int i = 1; i < 4; ++i)
        {
            if (point_1[1][0] > new_i)
            {
                new_i = point_1[i][0];
            }
        }
        new_i -= 7;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                point_1[i][j] -= new_i;
            }
        }
    }
}
