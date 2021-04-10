#include <string.h>

class SheetMusic{
    
    public:
            
        void Bar(const int iBeatTimes[8]);
        int Whole_note(bool bdot);
        int Half_note(bool bdot);
        int Quarter_note(bool bdot);
        int Eigth_note();

    private:
        int m_iBeats[8];
};