class Player
{
public:
    int x;
    int y;
    int velocity;
    int acceleration;
    int current_frame;
    SDL_Surface *images[10];
    SDL_Surface *screen;

    Player(SDL_Surface *screen);
    void logic();
    void render();
    void jump();
    void perder();
    virtual ~Player();
};

#endif // PLAYER_H
