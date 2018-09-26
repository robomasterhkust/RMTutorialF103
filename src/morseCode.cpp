#include "morseCode.hpp"

using namespace chibios_rt;

namespace MorseCode
{

const char str[] = "champion";

//morse code from a to z
const char *code[] =
    {".-", "-...", "-.-.", "-..", ".",     //abcde
     "..-.", "--.", "....", "..", ".---",  //fghij
     "-.-", ".-..", "--", "-.", "---",     //klmno
     ".--.", "--.-", ".-.", "...", "-",    //pqrst
     "..-", "...-", ".--", "-..-", "-.--", //uvwxy
     "--.."};                              //z

//just showcasing how threads can be created in a oop way
class MorseCodeThd : public BaseStaticThread<64>
{
  public:
    MorseCodeThd(const char *const c_str)
        : BaseStaticThread<64>(),
          c_str(c_str)
    {
    }

  protected:
    void main() override
    {
        bool was_interrupted = false;
        const char *current_char_ptr = c_str;
        chEvtRegister(&Button::ButtonPressedEvt, &buttonLis, 0);

        while (!BaseThread::shouldTerminate())
        {
            palWriteLine(LINE_LED, ~LED_ON_STATE);
            chThdSleepMilliseconds(500);

            if (!was_interrupted)
                chEvtWaitAny(EVENT_MASK(0)); //wait for button press
            was_interrupted = false;

            if (*current_char_ptr == '\0') //check whole string complete
                current_char_ptr = c_str;

            // find character index, a = 0, z = 25
            unsigned int index = 0;
            if (*current_char_ptr >= 'a' && *current_char_ptr <= 'z')
                index = *current_char_ptr - 'a';
            else if (*current_char_ptr >= 'A' && *current_char_ptr <= 'Z')
                index = *current_char_ptr - 'A';
            else
            {
                current_char_ptr++;
                continue; //wait for next button press if character is not alphabet
            }

            for (unsigned int subindex = 0;
                 code[index][subindex] != '\0';
                 subindex++)
            {
                unsigned int delayms;
                switch (code[index][subindex])
                {
                case '-':
                    delayms = 750;
                    break;
                case '.':
                    delayms = 250;
                    break;
                default:
                    continue; // not dash or dot?? probably wont happen anyway
                }
                palWriteLine(LINE_LED, LED_ON_STATE);
                if ((was_interrupted = chEvtWaitAnyTimeout(EVENT_MASK(0), TIME_MS2I(delayms))))
                    break;
                palWriteLine(LINE_LED, ~LED_ON_STATE);
                if ((was_interrupted = chEvtWaitAnyTimeout(EVENT_MASK(0), TIME_MS2I(250))))
                    break;
            }

            current_char_ptr++;
        }
    }

  private:
    const char *c_str;
    event_listener buttonLis;
}; // namespace MorseCode

static MorseCodeThd thd(str);

void morseCodeStart()
{
    thd.start(NORMALPRIO);
};
} // namespace MorseCode
