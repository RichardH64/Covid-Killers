#include "Game.h"

//===PRIVATE FUNCTIONS===//
void Game::initWindow()
{
    std::ifstream ifs("Setting/window.ini");

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

    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close);
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

void Game::initStates()
{
    this->states.push(new TitleState(this->window, &this->mosPosWindow, &this->mosPosView, this->booleans));
}
//---PRIVATE FUNCTIONS---//


//===CONSTRUCTORS||DESTRUCTORS===//
Game::Game()
{
    this->initWindow();
    this->initBooleans();
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
        this->states.push(new GameState(this->window, &this->mosPosWindow, &this->mosPosView, this->booleans));
        *this->booleans["CreateGameState"] = false;
        break;
    default:
        break;
    }
    switch (*this->booleans["RetryGameState"])
    {
    case true:
        this->states.top()->confirmQuit();
        /*
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
            this->states.push(new GameState(this->window, &this->mosPosWindow, &this->mosPosView, this->booleans));
        }
        */
        this->states.top()->endState();
        delete this->states.top();
        this->states.pop();
        this->states.push(new GameState(this->window, &this->mosPosWindow, &this->mosPosView, this->booleans));
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