#include "Game.h"

//===PRIVATE FUNCTIONS===//
void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");

    std::string title = "None";
    sf::VideoMode window_bounds(1280, 720);
    unsigned frame_limit = 120;
    bool vertical_sync_enabled = false;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> frame_limit;
        ifs >> vertical_sync_enabled;
    }

    ifs.close();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, settings);
    this->window->setFramerateLimit(frame_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);


    //this->fullScreen = false;
}

void Game::initBooleans()
{
    this->booleans.insert({"CreateGameState", new bool});
    this->booleans.insert({"RetryGameState", new bool});

    *this->booleans["CreateGameState"] = false;
    *this->booleans["RetryGameState"] = false;
}

void Game::initSupportedKeys()
{
    std::ifstream ifs("Config/supportedKeys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int keyValue = 0;

        while (ifs >> key >> keyValue)
        {
            this->supportedKeys[key] = keyValue;
        }
    }
    ifs.close();
}

void Game::initKeyBinds()
{
    std::ifstream ifs("Config/keyBinds.ini");

    if (ifs.is_open())
    {
        std::string keyOne = "";
        std::string keyTwo = "";

        while (ifs >> keyOne >> keyTwo)
        {
            this->keyBinds[keyOne] = this->supportedKeys.at(keyTwo);
        }
    }
    ifs.close();

    for (auto i : this->keyBinds)
    {
        this->keyBindPressed[i.first] = false;
    }

    // DEBUG REMOVE LATER
    /*
    for (auto i : this->keyBinds)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
    
    for (auto i : this->keyBindPressed)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
    */
}

void Game::initStates()
{
    this->states.push(new TitleState(this->window, &this->mosPosWindow, &this->mosPosView, &this->keyBinds, &this->keyBindPressed, this->booleans));
}
//---PRIVATE FUNCTIONS---//


//===CONSTRUCTORS||DESTRUCTORS===//
Game::Game()
{
    this->initWindow();
    this->initBooleans();
    this->initSupportedKeys();
    this->initKeyBinds();
    this->initStates();
}

Game::~Game()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}
//---CONSTRUCTORS||DESTRUCTORS---//


//===PUBLIC FUNCTIONS===//
//===REGULAR===//
void Game::endApplication()
{

}
//---REGULAR---//

//===UPDATE===//
void Game::updateDeltaTime()
{
    /*Updates Delta Time variable with time it takes to update and render one frame*/
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateEvents()
{
    //Event Polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            for (auto i : this->keyBinds)
            {
                if (ev.key.code == sf::Keyboard::Key(this->keyBinds[i.first]))
                {
                    this->keyBindPressed[i.first] = true;
                    break;
                }
            }
            break;        
        case sf::Event::KeyReleased:
            for (auto i : this->keyBinds)
            {
                if (ev.key.code == sf::Keyboard::Key(this->keyBinds[i.first]))
                {
                    this->keyBindPressed[i.first] = false;
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
}

void Game::updateMousePostions()
{
    /*
    @ return void

    Updates the mosue pos
    -Mouse position relative to window (Vector2i)
    */
    this->mosPosWindow = sf::Mouse::getPosition(*this->window);
    this->mosPosView = this->window->mapPixelToCoords(this->mosPosWindow);
}

void Game::updateBools()
{
    switch (*this->booleans["CreateGameState"])
    {
    case true:
        this->states.top()->resetButton();
        this->states.push(new GameState(this->window, &this->mosPosWindow, &this->mosPosView, &this->keyBinds, &this->keyBindPressed, this->booleans));
        *this->booleans["CreateGameState"] = false;
        break;
    default:
        break;
    }
    switch (*this->booleans["RetryGameState"])
    {
    case true:
        this->states.top()->confirmQuit();
        this->states.top()->endState();
        delete this->states.top();
        this->states.pop();
        this->states.push(new GameState(this->window, &this->mosPosWindow, &this->mosPosView, &this->keyBinds, &this->keyBindPressed, this->booleans));
        *this->booleans["RetryGameState"] = false;
        break;
    default:
        break;
    }
}

void Game::updateStates()
{
    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit())
        {
            this->states.top()->confirmQuit();
            if (this->states.top()->getQuit()) // Done Twice because the it will first confirm that user still chooses to quit, saving etc
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::update()
{
    this->updateEvents();
    this->updateMousePostions();
    this->updateBools();
    this->updateStates();
}
//---UPDATE--//

//===RENDER===//
void Game::renderStates()
{
    if (!this->states.empty()) // As long as the stack is not empty, it will render the top
    {
        this->states.top()->render(this->window);
    }
}

void Game::render()
{
    this->window->clear();

    this->renderStates();

    this->window->display();
}
//---RENDER---//

//===CORE===//
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}
//---CORE---//