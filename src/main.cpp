#include <SFML/Graphics.hpp>
#include <iostream>

class Square {
    private:
        sf::Sprite sprite;
        sf::Texture* texture;

    public:
        Square(float x, float y) {
            texture = new sf::Texture;
            if (!texture->loadFromFile("assets/x.png")) {
                std::cout << "Texture failed to load\n";
            }

            sprite.setPosition(sf::Vector2f(x, y));
            sprite.setScale(sf::Vector2f(6.25f, 6.25f));
            sprite.setTexture(*texture);
        }

        void render(sf::RenderTarget* window) {
            window->draw(sprite);
        }

        void addTransparency() {
            sprite.setColor(sf::Color(255, 255, 255, 128));
        }

        void removeTransparency() {
            sprite.setColor(sf::Color(255, 255, 255, 255));
        }

        void cleanUp() {
            delete texture;
        }
};

class Circle {
    private:
        sf::Sprite sprite;
        sf::Texture* texture;

    public:
        Circle(float x, float y) {
            texture = new sf::Texture;
            if (!texture->loadFromFile("assets/o.png")) {
                std::cout << "Texture failed to load\n";
            }

            sprite.setPosition(sf::Vector2f(x, y));
            sprite.setScale(sf::Vector2f(6.25f, 6.25f));
            sprite.setTexture(*texture);
        }

        void render(sf::RenderTarget* window) {
            window->draw(sprite);
        }

        void addTransparency() {
            sprite.setColor(sf::Color(255, 255, 255, 128));
        }

        void removeTransparency() {
            sprite.setColor(sf::Color(255, 255, 255, 255));
        }

        void cleanUp() {
            delete texture;
        }
};

// Booleans
bool gameOver = false;
bool endGameOverLoop = false;
bool playersTurn = false;
bool playerLost = false;
bool playerWon = false;

// Score
int playerScore = 0;
int opponentScore = 0;

// Shapes
std::vector <Square> square;
std::vector <Circle> circle;

// Grid
sf::RectangleShape lines[4];
sf::RectangleShape boxes[9];

// Font
sf::Font font;

// Text
sf::Text playerScoreText;
sf::Text opponentScoreText;
sf::Text winStatusText;
sf::Text restartText;

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
void cleanUp() {
    int squareSize = square.size();
    for (int i = 0; i < squareSize; i++) {
        square.at(i).cleanUp();
    }

    int circleSize = circle.size();
    for (int i = 0; i < circleSize; i++) {
        circle.at(i).cleanUp();
    }
}

void restart() {
    cleanUp();
    
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

    // Disable transparency
    for (int i = 0; i < square.size(); i++) {
        square.at(i).removeTransparency();
    }
    for (int i = 0; i < circle.size(); i++) {
        circle.at(i).removeTransparency();
    }
    for (int i = 0; i < 4; i++) {
        lines[i].setFillColor(sf::Color::Black);
    }

    delay = 0;
    startDelay = false;

    playerLost = false;
    playerWon = false;

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
    }
}

void win() {
    if (!playerWon) {
        playerScore++;
        playersTurn = false;
        playerWon = true;
        gameOver = true;
        winStatusText.setString("Player wins");
        winStatusText.setCharacterSize(250);
    }
}

void lose() {
    if (!playerLost) {
        opponentScore++;
        playersTurn = true;
        playerLost = true;
        gameOver = true;
        winStatusText.setString("Opponent wins");
        winStatusText.setCharacterSize(200);
    }
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
                randTurn();
                gameOver = true;
                winStatusText.setString("Draw");
                winStatusText.setCharacterSize(250);
                sf::FloatRect bounds = winStatusText.getLocalBounds();
                winStatusText.setPosition(sf::Vector2f(300.f - bounds.width / 2.f, bounds.height));
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
        }
        else if (matrix[i][0] == 2 && matrix[i][1] == 2 && matrix[i][2] == 2) {
            lose();
        }
    }

    // Columns
    for (int i = 0; i < 3; i++) {
        if (matrix[0][i] == 1 && matrix[1][i] == 1 && matrix[2][i] == 1) {
            win();
        }
        else if (matrix[0][i] == 2 && matrix[1][i] == 2 && matrix[2][i] == 2) {
            lose();
        }
    }

    // Diagonal 1
    if (matrix[0][2] == 1 && matrix[1][1] == 1 && matrix[2][0] == 1) {
        win();
    }
    else if (matrix[0][2] == 2 && matrix[1][1] == 2 && matrix[2][0] == 2) {
        lose();
    }

    // Diagonal 2
    if (matrix[0][0] == 1 && matrix[1][1] == 1 && matrix[2][2] == 1) {
        win();
    }
    else if (matrix[0][0] == 2 && matrix[1][1] == 2 && matrix[2][2] == 2) {
        lose();
    }
}

void initText() {
    if (!font.loadFromFile("assets/game_over.ttf")) {
        std::cout << "Failed to load font\n";
    }

    // Player score
    playerScoreText.setFont(font);
    playerScoreText.setPosition(sf::Vector2f(20.f, 0.f));
    playerScoreText.setString("Players score:");
    playerScoreText.setCharacterSize(100);
    playerScoreText.setFillColor(sf::Color::Black);

    
    // Opponent score
    opponentScoreText.setFont(font);
    opponentScoreText.setPosition(sf::Vector2f(20.f, 60.f));
    opponentScoreText.setString("Opponents score:");
    opponentScoreText.setCharacterSize(100);
    opponentScoreText.setFillColor(sf::Color::Black);

    // Win status
    winStatusText.setFont(font);
    winStatusText.setPosition(sf::Vector2f(20.f, 100.f));
    winStatusText.setString("Player wins");
    winStatusText.setCharacterSize(230);
    winStatusText.setFillColor(sf::Color::Black);
    winStatusText.setStyle(sf::Text::Bold);

    // Restart text
    restartText.setFont(font);
    restartText.setPosition(sf::Vector2f(100.f, 400.f));
    restartText.setString("Press space to continue");
    restartText.setCharacterSize(100);
    restartText.setFillColor(sf::Color::Black);
}

void initGrid() {
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
}

void gameOverMenu() {
    for (int i = 0; i < square.size(); i++) {
        square.at(i).addTransparency();
    }

    for (int i = 0; i < circle.size(); i++) {
        circle.at(i).addTransparency();
    }

    for (int i = 0; i < 4; i++) {
        lines[i].setFillColor(sf::Color(128, 128, 128, 255));
    }

    playerScoreText.setString("Players score: " + std::to_string(playerScore));
    opponentScoreText.setString("Opponents score: " + std::to_string(opponentScore));
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

    initText();

    window.setFramerateLimit(20);

    if (rand() % 2 == 0) {
        playersTurn = true;
    }
    else {
        playersTurn = false;
    }

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

    initGrid();

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
            gameOverMenu();
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

        // Text
        if (gameOver) {
            window.draw(playerScoreText);
            window.draw(opponentScoreText);
            window.draw(winStatusText);
            window.draw(restartText);
        }

        // Display
        window.display();
    }

    cleanUp();

    return 0;
}
