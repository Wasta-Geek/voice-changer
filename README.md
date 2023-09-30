# voice-changer

The initial goal was to developed a soundboard in C++ with the following features:
- Be able to play sound from files by pressing key, each key assigned to a sound => done
- Catching key input should be global and works passively without impacting any other software => done
- Some confort features (flush all sound played, manage volume, mute, record ourself and replay it, ...) => almost all done
- To add some sound effect (echo, reversed, high/low pitch voice, ...) => classes architecture prepared

## Libraries

- Portaudio: all sound related features
- Libsndfile: Be able to read / write audio sample from files

## !--- Archived ---!

It worked pretty well for my needs (have fun with friends while gaming) so I didn't feels to add more features. Even if some random crash occured from time to time but it was rare enough to just restart software.
Time have past and I wanted to continue this project but overall, C++ wasn't not that much enjoyable after time. So I thought it would be  time to try a new language and give it a try in Rust so....
See you in the next project :D
