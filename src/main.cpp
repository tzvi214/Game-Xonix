#include <iostream>
#include "Object.h"
#include "Player.h"
#include "vector"
#include "memory"
#include <SFML/Graphics.hpp>
#include "GameInfromation.h"
int main()
{
    int row = 25, col = 25;

    // אתחול נכון של הווקטור הדו-ממדי עם מצביעים ריקים
    std::vector<std::vector<std::unique_ptr<Object>>> board;

	board.resize(row);
	for (int i = 0; i < row; i++)
	{
		board[i].resize(col);
	}
    sf::Texture t1;
    t1.loadFromFile("tiles.png");
    sf::Sprite sTile(t1);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sf::Vector2f pos(j * 18.f, i * 18.f);  
            if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
            {
                board[i][j] = std::make_unique<FilledTile>(sTile, pos);  // קצה - אזור בטוח
            }
            else
            {
                board[i][j] = std::make_unique<EmptyTile>(sTile, pos);  // שאר המקומות - שטח מסוכן
            }
        }
    }
	sf::RenderWindow window(sf::VideoMode(col * 18, row * 18), "Xonix Game!");
	window.setFramerateLimit(60);
	Player player{ sf::Vector2f(0, 0), sTile };
	Enemy enemy{ sf::Vector2f(5 *18, 5*18), sTile };
    sf::Clock clock;
    clock.restart();
    while (window.isOpen())
		
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		float deltaTime = clock.restart().asSeconds();

		clock.restart();
		enemy.move(board, deltaTime); // Move the enemy with a delta time of 0.1 seconds
		player.move(board, deltaTime); // Move the player with a delta time of 0.1 seconds
        if (player.needToDoRecursion())
        {
			int row = int(enemy.getLocation().x) / 18;
			int col = int(enemy.getLocation().y) / 18;
			enemy.conquer(board, row, col);
           
        }
        for (int i = 1; i <= 24; i++) {
            for (int j = 1; j <= 24; j++) {
                if ((!board[i][j]->exists())) {
                    sf::Vector2f pos(i * 18.f, j * 18.f);
                    board[i][j] = std::make_unique<FilledTile>(sTile, pos);
                   // board[i][j] = std::make_unique<EmptyTile>(sTile, pos);
                }
            }
        }
        board[3][3] = std::make_unique<FilledTile>(sTile, sf::Vector2f ( 3*18.f, 3*18.f));
        window.clear();
        for (int i = 0; i < row; i++)

            for (int j = 0; j < col; j++)
            {
                board[i][j]->draw(window);
            }
        player.draw(window);
		enemy.draw(window);

		window.display();
    }
    return EXIT_SUCCESS;
}
// stats
// grid[M][N] == -1 -> enemy place
// grid[M][N] == 0 -> riskPlace
// grid[M][N] == 1 -> savePlace
// grid[M][N] == 2 -> שובל







//
//#include <SFML/Graphics.hpp>
//#include <time.h>
//using namespace sf;
//
//const int M = 25;
//const int N = 40;
//
//int grid[M][N] = { 0 };
//int ts = 18; //tile size
//
//struct Enemy
//{
//    int x, y, dx, dy;
//
//    Enemy()
//    {
//        x = y = 300;
//        dx = 4 - rand() % 8;
//        dy = 4 - rand() % 8;
//    }
//
//    void move()
//    {
//        x += dx; // תזוז בציר ה x
//       if (grid[y / ts][x / ts] == 1) //אם נגעת באיזור בטוח תלך ברוורס
//           { dx = -dx; x += dx; }
//       
//        y += dy;//תזוז בציר ה y
//        if (grid[y / ts][x / ts] == 1)//אם נגעת באיזור בטוח תלך ברוורס 
//        { dy = -dy; y += dy; }
//       
//    }
//};
//
//void drop(int y, int x)// the function getting the enemy location
//{
//    //כאן זה הרקורסיה
//   // כל שומר בודק מה הטח שהוא יכול ליהות בו וכל מה שהו יכול ליהות בו הוא מסמן את המשבצת ב -1
//    if (grid[y][x] == 0) 
//        grid[y][x] = -1;
//
//    if (grid[y - 1][x] == 0) 
//        drop(y - 1, x);
//
//    if (grid[y + 1][x] == 0)
//        drop(y + 1, x);
//
//    if (grid[y][x - 1] == 0) 
//        drop(y, x - 1);
//
//    if (grid[y][x + 1] == 0)
//        drop(y, x + 1);
//}
//
//int main()
//{
//    srand(time(0));
//
//    RenderWindow window(VideoMode(N * ts, M * ts), "Xonix Game!");
//    window.setFramerateLimit(60);
//
//    Texture t1, t2, t3;
//    t1.loadFromFile("tiles.png");
//    t2.loadFromFile("gameover.png");
//    t3.loadFromFile("enemy.png");
//
//    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
//    sGameover.setPosition(100, 100);
//    sEnemy.setOrigin(20, 20);
//
//    int enemyCount = 4;
//    Enemy a[10];
//
//    bool Game = true;
//    int x = 0, y = 0, dx = 0, dy = 0;
//    float timer = 0, delay = 0.07;
//    Clock clock;
//
//    for (int i = 0; i < M; i++)
//        for (int j = 0; j < N; j++)
//            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)  grid[i][j] = 1;// איתחול מסגרת
//
//    while (window.isOpen())
//    {
//        float time = clock.getElapsedTime().asSeconds();
//        clock.restart();
//        timer += time;
//
//        Event e;
//        while (window.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//                window.close();
//
//            if (e.type == Event::KeyPressed)
//                if (e.key.code == Keyboard::Escape)// analyze the bord
//                {
//                    for (int i = 1; i < M - 1; i++)
//                        for (int j = 1; j < N - 1; j++)
//                            grid[i][j] = 0;
//
//                    x = 10; y = 0;
//                    Game = true;
//                }
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; };
//        if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; };
//        if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; };
//        if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; };
//
//        if (!Game) continue;
//
//        if (timer > delay)//to do it avrey 0.07 second
//        {
//            x += dx;//move x
//            y += dy;//move y
//
//            if (x < 0) x = 0; if (x > N - 1) x = N - 1;//לא לחרוג מגבולות הלוח
//            if (y < 0) y = 0; if (y > M - 1) y = M - 1;//לא לחרוג מגבולות הלוח
//
//            if (grid[y][x] == 2) 
//                Game =  false;//אם נגעת בקוביה שהיא עכשיו שובל נפסלת 
//            if (grid[y][x] == 0) 
//                grid[y][x] = 2;// אם אתה נכנסת לאיזור סיכון הפוך את המשבצת לשובל
//            timer = 0;
//        }
//
//        for (int i = 0; i < enemyCount; i++) a[i].move();// move all the gurd
//
//        if (grid[y][x] == 1)//if you in a save zone
//        {
//            dx = dy = 0;// move only if you praceing the bouton
//
//            for (int i = 0; i < enemyCount; i++)
//                drop(a[i].y / ts, a[i].x / ts);
//            //אני עובר על כל המטריצה ומעדכן איפה שכל שומר אמר שהוא יכול ליהות 
//            // אני הופך את זה לאיזור סיכון ואם הוא לא יכול ליהות אז אני הופך את זה לאיזור בטוח
////
//            for (int i = 0; i < M; i++)
//                for (int j = 0; j < N; j++)
//                    if (grid[i][j] == -1) grid[i][j] = 0;
//                    else grid[i][j] = 1;
//        }
//
//        for (int i = 0; i < enemyCount; i++)// אם האויב נגע בשובל נפסלת
//            if (grid[a[i].y / ts] [a[i].x / ts] == 2) Game = false;
//
//        /////////draw//////////
//        window.clear();
//
//        for (int i = 0; i < M; i++)
//            for (int j = 0; j < N; j++)
//            {
//                if (grid[i][j] == 0) continue;
//                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
//                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
//                sTile.setPosition(j * ts, i * ts);
//                window.draw(sTile);
//            }
//
//        sTile.setTextureRect(IntRect(36, 0, ts, ts));
//        sTile.setPosition(x * ts, y * ts);// drow the player
//        window.draw(sTile);
//
//        sEnemy.rotate(10);
//        for (int i = 0; i < enemyCount; i++)// drow the enemy
//        {
//            sEnemy.setPosition(a[i].x, a[i].y);
//            window.draw(sEnemy);
//        }
//
//        if (!Game) window.draw(sGameover);
//
//        window.display();
//    }
//
//    return 0;
//}
