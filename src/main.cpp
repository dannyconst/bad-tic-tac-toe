#include <SFML/Graphics.hpp>
#include <iostream>

class Square {
    private:
        sf::Sprite sprite;
        sf::Texture texture;

    public:
        Square(float x, float y) {
            if (!texture.loadFromFile("assets/x.png")) {
                std::cout << "Texture failed to load\n";
            }

            sprite.setPosition(sf::Vector2f(x, y));
            sprite.setScale(sf::Vector2f(6.25f, 6.25f));
            sprite.setTexture(texture);
            sprite.setColor(sf::Color::Red);
        }

        void render(sf::RenderTarget* window) {
            window->draw(sprite);
        }
};

class Circle {
    private:
        sf::Sprite sprite;
        sf::Texture texture;

    public:
        Circle(float x, float y) {
            if (!texture.loadFromFile("assets/o.png")) {
                std::cout << "Texture failed to load\n";
            }

            sprite.setPosition(sf::Vector2f(x, y));
            sprite.setScale(sf::Vector2f(6.25f, 6.25f));
            sprite.setTexture(texture);
            sprite.setColor(sf::Color::Blue);
        }

        void render(sf::RenderTarget* window) {
            window->draw(sprite);
        }
};

// Booleans
bool gameOver = false;
bool endGameOverLoop = false;
bool playersTurn = false;

// Score
int playerScore = 0;
int opponentScore = 0;

// Shapes
std::vector <Square> square;
std::vector <Circle> circle;

sf::RectangleShape boxes[9];

// Matrix
// 0 = empty
// 1 = square
// 2 = circle
int matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

// Mouse positions
sf::Vector2i mousePosWindow;
sf::Vector2f mousePosView;

bool mouseHeld = false;

// Delay
int delay = 0;
bool startDelay = false;

// Functions
void restart() {
    std::cout << "\nRestart\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = 0;
        }
    }

    int squareSize = square.size();

    for (int i = 0; i < squareSize; i++) {
        square.erase(square.begin() + 1);
    }

    int circleSize = circle.size();

    for (int i = 0; i < circleSize; i++) {
        circle.erase(circle.begin() + 1);
    }

    if (playersTurn) {
        std::cout << "Player's turn\n";
    }
    else {
        std::cout << "Opponent's turn\n";
    }

    delay = 0;
    startDelay = false;

    gameOver = false;
    endGameOverLoop = false;
}

void input() {
    if (!gameOver) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (playersTurn && delay == 0) {
                if (!mouseHeld) {
                    mouseHeld = true;

                    for (int i = 0; i < 9; i++) {
                        if (boxes[i].getGlobalBounds().contains(mousePosView)) {
                            switch(i) {
                                case 0:
                                    if (matrix[0][0] == 0) {
                                        square.push_back(Square(50.f, 50.f));
                                        matrix[0][0] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 1:
                                    if (matrix[0][1] == 0) {
                                        square.push_back(Square(250.f, 50.f));
                                        matrix[0][1] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 2:
                                    if (matrix[0][2] == 0) {
                                        square.push_back(Square(450.f, 50.f));
                                        matrix[0][2] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 3:
                                    if (matrix[1][0] == 0) {
                                        square.push_back(Square(50.f, 250.f));
                                        matrix[1][0] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 4:
                                    if (matrix[1][1] == 0) {
                                        square.push_back(Square(250.f, 250.f));
                                        matrix[1][1] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 5:
                                    if (matrix[1][2] == 0) {
                                        square.push_back(Square(450.f, 250.f));
                                        matrix[1][2] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 6:
                                    if (matrix[2][0] == 0) {
                                        square.push_back(Square(50.f, 450.f));
                                        matrix[2][0] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 7:
                                    if (matrix[2][1] == 0) {
                                        square.push_back(Square(250.f, 450.f));
                                        matrix[2][1] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                case 8:
                                    if (matrix[2][2] == 0) {
                                        square.push_back(Square(450.f, 450.f));
                                        matrix[2][2] = 1;
                                        playersTurn = false;
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
        }
        else {
            mouseHeld = false;
        }
    }

    if (gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            restart();
        }
    }
}

void updateMousePos(sf::RenderWindow* window) {
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void chooseRand() {
    bool chosen = false;
    while (!chosen) {
        int randNum = rand() % 9;

        switch (randNum) {
            case 0:
                if (matrix[0][0] == 0) {
                    circle.push_back(Circle(50.f, 50.f));
                    matrix[0][0] = 2;
                    chosen = true;
                }
                break;
            case 1:
                if (matrix[0][1] == 0) {
                    circle.push_back(Circle(250.f, 50.f));
                    matrix[0][1] = 2;
                    chosen = true;
                }
                break;
            case 2:
                if (matrix[0][2] == 0) {
                    circle.push_back(Circle(450.f, 50.f));
                    matrix[0][2] = 2;
                    chosen = true;
                }
                break;
            case 3:
                if (matrix[1][0] == 0) {
                    circle.push_back(Circle(50.f, 250.f));
                    matrix[1][0] = 2;
                    chosen = true;
                }
                break;
            case 4:
                if (matrix[1][1] == 0) {
                    circle.push_back(Circle(250.f, 250.f));
                    matrix[1][1] = 2;
                    chosen = true;
                }
                break;
            case 5:
                if (matrix[1][2] == 0) {
                    circle.push_back(Circle(450.f, 250.f));
                    matrix[1][2] = 2;
                    chosen = true;
                }
                break;
            case 6:
                if (matrix[2][0] == 0) {
                    circle.push_back(Circle(50.f, 450.f));
                    matrix[2][0] = 2;
                    chosen = true;
                }
                break;
            case 7:
                if (matrix[2][1] == 0) {
                    circle.push_back(Circle(250.f, 450.f));
                    matrix[2][1] = 2;
                    chosen = true;
                }
                break;
            case 8:
                if (matrix[2][2] == 0) {
                    circle.push_back(Circle(450.f, 450.f));
                    matrix[2][2] = 2;
                    chosen = true;
                }
                break;
            default:
                break;
        }
    }
}

void AI() {
    // Row
    if (matrix[0][0] == 1 && matrix[0][2] == 1 && matrix[0][1] == 0) {
        circle.push_back(Circle(250.f, 50.f));
        matrix[0][1] = 2;
    }
    else if (matrix[1][0] == 1 && matrix[1][2] == 1 && matrix[1][1] == 0) {
        circle.push_back(Circle(250.f, 250.f));
        matrix[1][1] = 2;
    }
    else if (matrix[2][0] == 1 && matrix[2][2] == 1 && matrix[2][1] == 0) {
        circle.push_back(Circle(250.f, 450.f));
        matrix[2][1] = 2;
    }
    // Column
    else if (matrix[0][0] == 1 && matrix[2][0] == 1 && matrix[1][0] == 0) {
        circle.push_back(Circle(50.f, 250.f));
        matrix[1][0] = 2;
    }
    else if (matrix[0][1] == 1 && matrix[2][1] == 1 && matrix[1][1] == 0) {
        circle.push_back(Circle(250.f, 250.f));
        matrix[1][1] = 2;
    }
    else if (matrix[0][2] == 1 && matrix[2][2] == 1 && matrix[1][2] == 0) {
        circle.push_back(Circle(450.f, 250.f));
        matrix[1][2] = 2;
    }
    // Diagonal
    else if (matrix[0][0] == 1 && matrix[2][2] == 1 && matrix[1][1] == 0) {
        circle.push_back(Circle(250.f, 250.f));
        matrix[1][1] = 2;
    }
    else if (matrix[0][2] == 1 && matrix[2][0] == 1 && matrix[1][1] == 0) {
        circle.push_back(Circle(250.f, 250.f));
        matrix[1][1] = 2;
    }
    // Left
    else if (matrix[0][0] == 1 && matrix[0][1] == 1 && matrix[0][2] == 0) {
        circle.push_back(Circle(450.f, 50.f));
        matrix[0][2] = 2;
    }
    else if (matrix[1][0] == 1 && matrix[1][1] == 1 && matrix[1][2] == 0) {
        circle.push_back(Circle(450.f, 250.f));
        matrix[1][2] = 2;
    }
    else if (matrix[2][0] == 1 && matrix[2][1] == 1 && matrix[2][2] == 0) {
        circle.push_back(Circle(450.f, 450.f));
        matrix[2][2] = 2;
    }
    // Right
    else if (matrix[0][1] == 1 && matrix[0][2] == 1 && matrix[0][0] == 0) {
        circle.push_back(Circle(50.f, 50.f));
        matrix[0][0] = 2;
    }
    else if (matrix[1][1] == 1 && matrix[1][2] == 1 && matrix[1][0] == 0) {
        circle.push_back(Circle(50.f, 250.f));
        matrix[1][0] = 2;
    }
    else if (matrix[2][1] == 1 && matrix[2][2] == 1 && matrix[2][0] == 0) {
        circle.push_back(Circle(50.f, 450.f));
        matrix[2][0] = 2;
    }
    // Up
    else if (matrix[0][0] == 1 && matrix[1][0] == 1 && matrix[2][0] == 0) {
        circle.push_back(Circle(50.f, 450.f));
        matrix[2][0] = 2;
    }
    else if (matrix[0][1] == 1 && matrix[1][1] == 1 && matrix[2][1] == 0) {
        circle.push_back(Circle(250.f, 450.f));
        matrix[2][1] = 2;
    }
    else if (matrix[0][2] == 1 && matrix[1][2] == 1 && matrix[2][2] == 0) {
        circle.push_back(Circle(450.f, 450.f));
        matrix[2][2] = 2;
    }
    // Down
    else if (matrix[1][0] == 1 && matrix[2][0] == 1 && matrix[0][0] == 0) {
        circle.push_back(Circle(50.f, 50.f));
        matrix[0][0] = 2;
    }
    else if (matrix[1][1] == 1 && matrix[2][1] == 1 && matrix[0][1] == 0) {
        circle.push_back(Circle(250.f, 50.f));
        matrix[0][1] = 2;
    }
    else if (matrix[1][2] == 1 && matrix[2][2] == 1 && matrix[0][2] == 0) {
        circle.push_back(Circle(450.f, 50.f));
        matrix[0][2] = 2;
    }
    // Diagonal
    else if (matrix[0][0] == 1 && matrix[1][1] == 1 && matrix[2][2] == 0) {
        circle.push_back(Circle(450.f, 450.f));
        matrix[2][2] = 2;
    }
    else if (matrix[1][1] == 1 && matrix[2][2] == 1 && matrix[0][0] == 0) {
        circle.push_back(Circle(50.f, 50.f));
        matrix[0][0] = 2;
    }
    else if (matrix[0][2] == 1 && matrix[1][1] == 1 && matrix[2][0] == 0) {
        circle.push_back(Circle(50.f, 450.f));
        matrix[2][0] = 2;
    }
    else if (matrix[1][1] == 1 && matrix[2][0] == 1 && matrix[0][2] == 0) {
        circle.push_back(Circle(450.f, 50.f));
        matrix[0][2] = 2;
    }
    else {
        chooseRand();
        std::cout << "Random\n";
    }
}

void win() {
    std::cout << "\nPlayer wins!\n";
    playerScore++;
    playersTurn = false;
}

void lose() {
    std::cout << "\nOpponent wins!\n";
    opponentScore++;
    playersTurn = true;
}

void randTurn() {
    if (rand() % 2 == 0) {
        playersTurn = true;
    }
    else {
        playersTurn = false;
    }
}

void game() {
    int marked = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] != 0) {
                marked++;
            }
        }
    }

    if (!playersTurn || marked >= 9) {
        startDelay = true;

        if (delay >= 15) {
            if (marked < 2) {
                chooseRand();

                playersTurn = true;
                delay = 0;
            }
            else if (marked > 1 && marked < 9) {
                AI();

                playersTurn = true;
                delay = 0;
            }
            else if (marked >= 9) {
                std::cout << "\nDraw\n";
                randTurn();
                gameOver = true;
            }
        }
        else if (delay < 30 && startDelay) {
            delay++;
        }
    }

    // Rows
    for (int i = 0; i < 3; i++) {
        if (matrix[i][0] == 1 && matrix[i][1] == 1 && matrix[i][2] == 1) {
            win();
            gameOver = true;
        }
        else if (matrix[i][0] == 2 && matrix[i][1] == 2 && matrix[i][2] == 2) {
            lose();
            gameOver = true;
        }
    }

    // Columns
    for (int i = 0; i < 3; i++) {
        if (matrix[0][i] == 1 && matrix[1][i] == 1 && matrix[2][i] == 1) {
            win();
            gameOver = true;
        }
        else if (matrix[0][i] == 2 && matrix[1][i] == 2 && matrix[2][i] == 2) {
            lose();
            gameOver = true;
        }
    }

    // Diagonal 1
    if (matrix[0][2] == 1 && matrix[1][1] == 1 && matrix[2][0] == 1) {
        win();
        gameOver = true;
    }
    else if (matrix[0][2] == 2 && matrix[1][1] == 2 && matrix[2][0] == 2) {
        lose();
        gameOver = true;
    }

    // Diagonal 2
    if (matrix[0][0] == 1 && matrix[1][1] == 1 && matrix[2][2] == 1) {
        win();
        gameOver = true;
    }
    else if (matrix[0][0] == 2 && matrix[1][1] == 2 && matrix[2][2] == 2) {
        lose();
        gameOver = true;
    }
}

int main() {
    srand(time(NULL));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::VideoMode videoMode;
    videoMode.width = 600;
    videoMode.height = 600;

    sf::RenderWindow window(videoMode, "Tic Tac Toe", sf::Style::Close, settings);

    window.setPosition(sf::Vector2i(
        (videoMode.getDesktopMode().width / 2) - videoMode.width / 2,
        (videoMode.getDesktopMode().height / 2) - videoMode.height / 2)
    );

    window.setFramerateLimit(20);

    if (rand() % 2 == 0) {
        playersTurn = true;
        std::cout << "Player starts\n";
    }
    else {
        playersTurn = false;
        std::cout << "Opponent starts\n";
    }

    sf::RectangleShape lines[4];

    // Init Boxes
    for (int i = 0; i < 3; i++) {
        boxes[i].setPosition(sf::Vector2f(i * 200, 0.f));
        boxes[i].setSize(sf::Vector2f(200.f, 200.f));
    }
    for (int i = 3; i < 6; i++) {
        boxes[i].setPosition(sf::Vector2f((i - 3) * 200, 200.f));
        boxes[i].setSize(sf::Vector2f(200.f, 200.f));
    }
    for (int i = 6; i < 9; i++) {
        boxes[i].setPosition(sf::Vector2f((i - 6) * 200, 400.f));
        boxes[i].setSize(sf::Vector2f(200.f, 200.f));
    }

    // Init lines
    for (int i = 0; i < 2; i++) {
        lines[i] = sf::RectangleShape(sf::Vector2f(600.f, 8.f));
        lines[i].setFillColor(sf::Color::Black);
    }
    for (int i = 2; i < 4; i++) {
        lines[i] = sf::RectangleShape(sf::Vector2f(8.f, 600.f));
        lines[i].setFillColor(sf::Color::Black);
    }

    // Set position
    lines[0].setPosition(sf::Vector2f(0.f, 200.f - 4.f));
    lines[1].setPosition(sf::Vector2f(0.f, 400.f - 4.f));
    lines[2].setPosition(sf::Vector2f(200.f - 4.f, 0.f));
    lines[3].setPosition(sf::Vector2f(400.f - 4.f, 0.f));

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        updateMousePos(&window);

        input();
        
        if (!gameOver) {
            game();
        }
        else if (gameOver && !endGameOverLoop) {
            std::cout << "Player score: " << playerScore << "\n";
            std::cout << "Opponent's score: " << opponentScore << "\n";
            std::cout << "\nPress 'Space' to continue\n";
            endGameOverLoop = true;
        }

        // Refresh
        window.clear(sf::Color::White);

        // Draw crosses
        for (int i = 0; i < square.size(); i++) {
            square.at(i).render(&window);
        }

        // Draw circles
        for (int i = 0; i < circle.size(); i++) {
            circle.at(i).render(&window);
        }

        // Draw grid
        for (int i = 0; i < 4; i++) {
            window.draw(lines[i]);
        }

        // Display
        window.display();
    }

    return 0;
}