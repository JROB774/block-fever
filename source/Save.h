#ifndef INCLUDE_SAVE
#define INCLUDE_SAVE

class Save
{
    public:

        static const bool DEFAULT_FULLSCREEN;
        static const int DEFAULT_WINDOW_WIDTH;
        static const int DEFAULT_WINDOW_HEIGHT;

        static void step();
        static void load();
        static void save();

    private:

        static const std::string SAVE_FILE;

        static bool fullscreen;
};

#endif // INCLUDE_SAVE
