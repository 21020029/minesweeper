class Time {
private:
    LTexture gTime;
    int timer;
    Uint32 start, currentTime;
public:
    Time();
    ~Time();
    void printTime();
};

Time::Time() {
    start = SDL_GetTicks();
    timer = 0;
}
Time::~Time() {
    gTime.free();
}
void Time::printTime() {
    currentTime = SDL_GetTicks();
    if(currentTime - start >= 1000) {
        timer++;
        start = currentTime;
    }
    gTime.loadFromRenderedText(std::to_string(timer), {140, 140, 140});
    gTime.render(SCREEN_WIDTH - gTime.getWidth() - 20, 30);
}
