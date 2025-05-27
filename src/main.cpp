

#include "GameController.h"

int main()
{
	GameController game;
	game.run();
}

//#include <SFML/Graphics.hpp>
//#include <cmath>
//using namespace sf;
//
//int width = 1024;
//int height = 768;
//int roadW = 2000;
//int segL = 200; //segment length
//float camD = 0.84; //camera depth
//
//void drawQuad(RenderWindow& w, Color c, int x1, int y1, int w1, int x2, int y2, int w2)
//{
//    ConvexShape shape(4);
//    shape.setFillColor(c);
//    shape.setPoint(0, Vector2f(x1 - w1, y1));
//    shape.setPoint(1, Vector2f(x2 - w2, y2));
//    shape.setPoint(2, Vector2f(x2 + w2, y2));
//    shape.setPoint(3, Vector2f(x1 + w1, y1));
//    w.draw(shape);
//}
//
//struct Line
//{
//    float x, y, z; //3d center of line
//    float X, Y, W; //screen coord
//    float curve, spriteX, clip, scale;
//    Sprite sprite;
//
//    Line()
//    {
//        spriteX = curve = x = y = z = 0;
//    }
//
//    void project(int camX, int camY, int camZ)
//    {
//        scale = camD / (z - camZ);
//        X = (1 + scale * (x - camX)) * width / 2;
//        Y = (1 - scale * (y - camY)) * height / 2;
//        W = scale * roadW * width / 2;
//    }
//
//    void drawSprite(RenderWindow& app)
//    {
//        Sprite s = sprite;
//        int w = s.getTextureRect().width;
//        int h = s.getTextureRect().height;
//
//        float destX = X + scale * spriteX * width / 2;
//        float destY = Y + 4;
//        float destW = w * W / 266;
//        float destH = h * W / 266;
//
//        destX += destW * spriteX; //offsetX
//        destY += destH * (-1);    //offsetY
//
//        float clipH = destY + destH - clip;
//        if (clipH < 0) clipH = 0;
//
//        if (clipH >= destH) return;
//        s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
//        s.setScale(destW / w, destH / h);
//        s.setPosition(destX, destY);
//        app.draw(s);
//    }
//};
//
//
//int main()
//{
//    RenderWindow app(VideoMode(width, height), "Outrun Racing!");
//    app.setFramerateLimit(60);
//
//    Texture t[50];
//    Sprite object[50];
//    for (int i = 1; i <= 7; i++)
//    {
//        t[i].loadFromFile( std::to_string(i) + ".png");
//        t[i].setSmooth(true);
//        object[i].setTexture(t[i]);
//    }
//
//    Texture bg;
//    bg.loadFromFile("bg.png");
//    bg.setRepeated(true);
//    Sprite sBackground(bg);
//    sBackground.setTextureRect(IntRect(0, 0, 5000, 411));
//    sBackground.setPosition(-2000, 0);
//
//    std::vector<Line> lines;
//
//    for (int i = 0; i < 1600; i++)
//    {
//        Line line;
//        line.z = i * segL;
//
//        if (i > 300 && i < 700) line.curve = 0.5;
//        if (i > 1100) line.curve = -0.7;
//
//        if (i < 300 && i % 20 == 0) { line.spriteX = -2.5; line.sprite = object[5]; }
//        if (i % 17 == 0) { line.spriteX = 2.0; line.sprite = object[6]; }
//        if (i > 300 && i % 20 == 0) { line.spriteX = -0.7; line.sprite = object[4]; }
//        if (i > 800 && i % 20 == 0) { line.spriteX = -1.2; line.sprite = object[1]; }
//        if (i == 400) { line.spriteX = -1.2; line.sprite = object[7]; }
//
//        if (i > 750) line.y = sin(i / 30.0) * 1500;
//
//        lines.push_back(line);
//    }
//
//    int N = lines.size();
//    float playerX = 0;
//    int pos = 0;
//    int H = 1500;
//
//    while (app.isOpen())
//    {
//        Event e;
//        while (app.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//                app.close();
//        }
//
//        int speed = 0;
//
//        if (Keyboard::isKeyPressed(Keyboard::Right)) playerX += 0.1;
//        if (Keyboard::isKeyPressed(Keyboard::Left)) playerX -= 0.1;
//        if (Keyboard::isKeyPressed(Keyboard::Up)) speed = 200;
//        if (Keyboard::isKeyPressed(Keyboard::Down)) speed = -200;
//        if (Keyboard::isKeyPressed(Keyboard::Tab)) speed *= 3;
//        if (Keyboard::isKeyPressed(Keyboard::W)) H += 100;
//        if (Keyboard::isKeyPressed(Keyboard::S)) H -= 100;
//
//        pos += speed;
//        while (pos >= N * segL) pos -= N * segL;
//        while (pos < 0) pos += N * segL;
//
//        app.clear(Color(105, 205, 4));
//        app.draw(sBackground);
//        int startPos = pos / segL;
//        int camH = lines[startPos].y + H;
//        if (speed > 0) sBackground.move(-lines[startPos].curve * 2, 0);
//        if (speed < 0) sBackground.move(lines[startPos].curve * 2, 0);
//
//        int maxy = height;
//        float x = 0, dx = 0;
//
//        ///////draw road////////
//        for (int n = startPos; n < startPos + 300; n++)
//        {
//            Line& l = lines[n % N];
//            l.project(playerX * roadW - x, camH, startPos * segL - (n >= N ? N * segL : 0));
//            x += dx;
//            dx += l.curve;
//
//            l.clip = maxy;
//            if (l.Y >= maxy) continue;
//            maxy = l.Y;
//
//            Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
//            Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
//            Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);
//
//            Line p = lines[(n - 1) % N]; //previous line
//
//            drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
//            drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
//            drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
//        }
//
//        ////////draw objects////////
//        for (int n = startPos + 300; n > startPos; n--)
//            lines[n % N].drawSprite(app);
//
//        app.display();
//    }
//
//    return 0;
//}
//
//
//
//
//


//#include <SFML/Graphics.hpp>
//#include <time.h>
//using namespace sf;
//
//struct point
//{
//    int x, y;
//};
//
//int main()
//{
//    srand(time(0));
//
//    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
//    app.setFramerateLimit(60);
//
//    Texture t1, t2, t3;
//    t1.loadFromFile("background.png");
//    t2.loadFromFile("platform.png");
//    t3.loadFromFile("doodle.png");
//
//    Sprite sBackground(t1), sPlat(t2), sPers(t3);
//
//    point plat[20];
//
//    for (int i = 0; i < 10; i++)
//    {
//        plat[i].x = rand() % 400;
//        plat[i].y = rand() % 533;
//    }
//
//    int x = 100, y = 100, h = 200;
//    float dx = 0, dy = 0;
//
//    while (app.isOpen())
//    {
//        Event e;
//        while (app.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//                app.close();
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
//        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;
//
//        dy += 0.2;
//        y += dy;
//        if (y > 500)  dy = -10;
//
//        if (y < h)
//            for (int i = 0; i < 10; i++)
//            {
//                y = h;
//                plat[i].y = plat[i].y - dy;
//                if (plat[i].y > 533) { plat[i].y = 0; plat[i].x = rand() % 400; }
//            }
//
//        for (int i = 0; i < 10; i++)
//            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
//                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;
//
//        sPers.setPosition(x, y);
//
//        app.draw(sBackground);
//        app.draw(sPers);
//        for (int i = 0; i < 10; i++)
//        {
//            sPlat.setPosition(plat[i].x, plat[i].y);
//            app.draw(sPlat);
//        }
//
//        app.display();
//    }
//
//    return 0;
//}
//


//#include <iostream>
//#include "Object.h"
//#include "Player.h"
//#include "vector"
//#include "memory"
//#include <SFML/Graphics.hpp>
//#include "GameInfromation.h"
//int main()
//{
//    int row = 25, col = 25;
//
//    // אתחול נכון של הווקטור הדו-ממדי עם מצביעים ריקים
//    std::vector<std::vector<std::unique_ptr<Object>>> board;
//
//	board.resize(row);
//	for (int i = 0; i < row; i++)
//	{
//		board[i].resize(col);
//	}
//    sf::Texture t1;
//    t1.loadFromFile("tiles.png");
//    sf::Sprite sTile(t1);
//
//    for (int i = 0; i < row; i++)
//    {
//        for (int j = 0; j < col; j++)
//        {
//            sf::Vector2f pos(j * 18.f, i * 18.f);  
//            if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
//            {
//                board[i][j] = std::make_unique<FilledTile>(sTile, pos);  // קצה - אזור בטוח
//            }
//            else
//            {
//                board[i][j] = std::make_unique<EmptyTile>(sTile, pos);  // שאר המקומות - שטח מסוכן
//            }
//        }
//    }
//	sf::RenderWindow window(sf::VideoMode(col * 18, row * 18), "Xonix Game!");
//	window.setFramerateLimit(60);
//	Player player{ sf::Vector2f(0, 0), sTile };
//	Enemy enemy{ sf::Vector2f(5 *18, 5*18), sTile };
//    sf::Clock clock;
//    clock.restart();
//    while (window.isOpen())
//		
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//		float deltaTime = clock.restart().asSeconds();
//
//		clock.restart();
//		enemy.move(board, deltaTime); // Move the enemy with a delta time of 0.1 seconds
//		player.move(board, deltaTime); // Move the player with a delta time of 0.1 seconds
//        if (player.needToDoRecursion())
//        {
//			int row = int(enemy.getLocation().x) / 18;
//			int col = int(enemy.getLocation().y) / 18;
//			enemy.conquer(board, row, col);
//           
//        }
//        for (int i = 1; i <= 24; i++) {
//            for (int j = 1; j <= 24; j++) {
//                if ((!board[i][j]->exists())) {
//                    sf::Vector2f pos(i * 18.f, j * 18.f);
//                    board[i][j] = std::make_unique<FilledTile>(sTile, pos);
//                   // board[i][j] = std::make_unique<EmptyTile>(sTile, pos);
//                }
//            }
//        }
//        window.clear();
//        for (int i = 0; i < row; i++)
//
//            for (int j = 0; j < col; j++)
//            {
//                board[i][j]->draw(window);
//            }
//        player.draw(window);
//		enemy.draw(window);
//
//		window.display();
//    }
//    return EXIT_SUCCESS;
//}
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
