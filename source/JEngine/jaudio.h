#ifndef INCLUDE_J_AUDIO
#define INCLUDE_J_AUDIO

#include <sstream>
#include "jerror.h"

/// <J_SOUND> /////////////////////////////////////////////////////////////////

struct J_Sound
{
    // The mixer has access to private members.
    friend class J_Mixer;

    private:

        // The raw SDL mixer chunk.
        Mix_Chunk* chunk;
};

/// </J_SOUND> ////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_MIXER> /////////////////////////////////////////////////////////////////

class J_Mixer {

    public:

        /// DESCRIPTION:
        // The constructor.
        //
        J_Mixer(void) = delete;
        J_Mixer(const J_Mixer&) = delete;
        J_Mixer(J_Mixer&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        J_Mixer& operator=(const J_Mixer&) = delete;
        J_Mixer& operator=(J_Mixer&&) = delete;

        /// DESCRIPTION:
        // Initialise the audio.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Handle any audio related events.
        //
        /// ARGUMENTS:
        // The event handler.
        //
        static void handle(const SDL_Event&);

        /// DESCRIPTION:
        // Create a sound from a WAV file.
        //
        /// ARGUMENTS:
        // The file to make the sound with.
        //
        /// RETURN VALUES:
        // The newly created sound.
        //
        static J_Sound createSound(const std::string);

        /// DESCRIPTION:
        // Play the specified sound a certain amount of times.
        //
        /// ARGUMENTS:
        // The sound to play.
        // The number of loops. (-1 makes it play forever.)
        //
        static void playSound(const J_Sound&, const int);

        /// DESCRIPTION:
        // Destroy a sound.
        //
        /// ARGUMENTS:
        // The sound to destroy.
        //
        static void destroySound(J_Sound*);

        /// DESCRIPTION:
        // Set the volume level of all sounds.
        //
        /// ARGUMENTS:
        // The new sound volume level.
        //
        static void setSoundVolume(const float);

        /// DESCRIPTION:
        // Toggle audio mute on and off.
        //
        static void toggleMute(void);

        /// DESCRIPTION:
        // Get the volume level of all sounds.
        //
        /// RETURN VALUES:
        // The sound volume.
        //
        static float getSoundVolume(void);

        /// DESCRIPTION:
        // Get whether audio is muted or not.
        //
        /// RETURN VALUES:
        // True if audio is muted.
        // False if audio is not muted.
        //
        static bool isMuted(void);

        /// DESCRIPTION:
        // Terminate the audio.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~J_Mixer(void) = delete;

    private:

        // The audio data file.
        static const std::string AUDIO_FILE;
        // The maximum number of channels.
        static int maxChannels;
        // The volume for all sounds.
        static float soundVolume;
        // The amount to increment/decement the volume by.
        static float volumePiece;
        // The flag stating whether audio is muted or not.
        static bool muted;
        // The sound volume before audio was muted.
        static float mutedSoundVolume;
};

/// </J_MIXER> ////////////////////////////////////////////////////////////////

#endif // INCLUDE_J_AUDIO
