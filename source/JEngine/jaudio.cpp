/// <J_MIXER> /////////////////////////////////////////////////////////////////

const std::string J_Mixer::AUDIO_FILE = RES_DIR_DATA "Audio.dat";
int J_Mixer::maxChannels = 0;
float J_Mixer::soundVolume = 0.0;
float J_Mixer::volumePiece = 0.0;
bool J_Mixer::muted = false;
float J_Mixer::mutedSoundVolume = 0.0;



void J_Mixer::initialise (void) {

    // Open the audio file and store the data.
    std::ifstream audioFile(AUDIO_FILE, std::ifstream::in);

    if (audioFile.is_open()) {

        std::string rawData = "\0";
        std::istringstream data;

        std::getline(audioFile, rawData);
        data.str(rawData);
        data >> maxChannels >> volumePiece;

        audioFile.close();
    }
    else { J_Error::log("J_ERROR_MIXER_FILE_READ"); }

    // Allocate the maximum number of channels.
    Mix_AllocateChannels(maxChannels);
}



void J_Mixer::handle (const SDL_Event& arg_event) {

    // Handle increasing or descreasing the volume.
    if (arg_event.type == SDL_KEYDOWN) {

        switch (arg_event.key.keysym.sym) {

            case (SDLK_EQUALS) : { if (!muted) { setSoundVolume(soundVolume + volumePiece); } break; }

            case (SDLK_MINUS) : { if (!muted) { setSoundVolume(soundVolume - volumePiece); } break; }

            case (SDLK_m) : { toggleMute(); break; }
        }
    }
}



J_Sound J_Mixer::createSound (const std::string arg_file) {

    // Create the directory to wherer the sound file is located.
    std::string directory = RES_DIR_SOUNDS + arg_file + ".wav";

    // Load the file into the sound's chunk.
    J_Sound sound;
    sound.chunk = Mix_LoadWAV(directory.c_str());
    if (sound.chunk == nullptr) { J_Error::log("J_ERROR_MIXER_CHUNK_LOAD"); }

    // Return the sound.
    return sound;
}



void J_Mixer::playSound (const J_Sound& arg_sound, const int arg_loops) {

    // Play the sound a set amount of times.
    Mix_PlayChannel(-1, arg_sound.chunk, arg_loops);
}



void J_Mixer::destroySound (J_Sound* arg_sound) {

    // Destroy the sound.
    Mix_FreeChunk(arg_sound->chunk);
    arg_sound->chunk = nullptr;
    arg_sound = nullptr;
}



void J_Mixer::setSoundVolume (const float arg_volume) {

    soundVolume = arg_volume;

    if (soundVolume > MIX_MAX_VOLUME) { soundVolume = MIX_MAX_VOLUME; }
    else if (soundVolume < 0.0) { soundVolume = 0.0; }

    Mix_Volume(-1, soundVolume);
}

void J_Mixer::toggleMute (void) {

    muted = !muted;

    if (muted) {

        mutedSoundVolume = getSoundVolume();
        setSoundVolume(0.0);
    }
    else {

        setSoundVolume(mutedSoundVolume);
        mutedSoundVolume = 0.0;
    }
}



float J_Mixer::getSoundVolume (void) { return soundVolume; }

bool J_Mixer::isMuted (void) { return muted; }



void J_Mixer::terminate (void) {

    // Terminate the audio.
    maxChannels = 0;
    soundVolume = 0.0;
    volumePiece = 0.0;
    muted = false;
    mutedSoundVolume = 0.0;
}

/// </J_MIXER> ////////////////////////////////////////////////////////////////
