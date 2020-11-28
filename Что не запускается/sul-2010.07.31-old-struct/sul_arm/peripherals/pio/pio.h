 
#ifndef PIO_H
#define PIO_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>

//------------------------------------------------------------------------------
//         Global Definitions
//------------------------------------------------------------------------------

/// The pin is controlled by the associated signal of peripheral A.
#define PIO_PERIPH_A                0
/// The pin is controlled by the associated signal of peripheral B.
#define PIO_PERIPH_B                1
/// The pin is an input.
#define PIO_INPUT                   2
/// The pin is an output and has a default level of 0.
#define PIO_OUTPUT_0                3
/// The pin is an output and has a default level of 1.
#define PIO_OUTPUT_1                4

/// Default pin configuration (no attribute).
#define PIO_DEFAULT                 (0 << 0)
/// The internal pin pull-up is active.
#define PIO_PULLUP                  (1 << 0)
/// The internal glitch filter is active.
#define PIO_DEGLITCH                (1 << 1)
/// The pin is open-drain.
#define PIO_OPENDRAIN               (1 << 2)

//------------------------------------------------------------------------------
//         Global Macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Calculates the size of an array of Pin instances. The array must be defined
/// locally (i.e. not a pointer), otherwise the computation will not be correct.
/// \param pPins  Local array of Pin instances.
/// \return Number of elements in array.
//------------------------------------------------------------------------------
#define PIO_LISTSIZE(pPins)    (sizeof(pPins) / sizeof(Pin))

//------------------------------------------------------------------------------
//         Global Types
//------------------------------------------------------------------------------
typedef struct _ExtIntMode {
  ///indicate which pin to enable/disable additional Interrupt mode
  ///each of 32 bit field represents one PIO line.
  unsigned int itMask;
  ///select Edge or level interrupt detection source
  ///each of 32 bit field represents one PIO line, 0 is Edge, 1 is Level
  unsigned int edgeLvlSel;
  ///select rising/high or falling/low detection event
  ///each of 32 bit field represents one PIO line:
  ///0 is Falling Edge detection event (if selected Edge interrupt 
  ///   detection source, or Low Level detection (if selected
  ///   Level interrupt detection source;
  ///1 is Rising Edge detection(if selected Edge interrupt 
  ///   source, or Low Level detection event(if selected Level
  ///   interrupt detection source.
  unsigned int lowFallOrRiseHighSel;

} ExtIntMode;

typedef struct _GlitchDeBounceFilter {
  ///Select Glitch/Debounce filtering for PIO input
  ///each of 32 bit field represents one PIO line
  ///0 is Glitch, 1 is Debouncing
  unsigned int filterSel;
  ///slow clock divider selection for Debouncing filter
  unsigned int clkDivider:14;

} GlitchDebounceFilter;

//------------------------------------------------------------------------------
/// Describes the type and attribute of one PIO pin or a group of similar pins.
/// The #type# field can have the following values:
///    - PIO_PERIPH_A
///    - PIO_PERIPH_B
///    - PIO_OUTPUT_0
///    - PIO_OUTPUT_1
///    - PIO_INPUT
///
/// The #attribute# field is a bitmask that can either be set to PIO_DEFAULt,
/// or combine (using bitwise OR '|') any number of the following constants:
///    - PIO_PULLUP
///    - PIO_DEGLITCH
///    - PIO_OPENDRAIN
//------------------------------------------------------------------------------
typedef struct {

    /// Bitmask indicating which pin(s) to configure.
    unsigned int mask; 
    /// Pointer to the PIO controller which has the pin(s).
    AT91S_PIO    *pio;
    /// Peripheral ID of the PIO controller which has the pin(s).
    unsigned char id;
    /// Pin type.
    unsigned char type;
    /// Pin attribute.
    unsigned char attribute;
#if defined(AT91C_PIOA_AIMMR)
    ///Additional Interrupt Mode
    ExtIntMode itMode;
#endif

#if defined(AT91C_PIOA_IFDGSR)
    ///Glitch/Debouncing filter
    GlitchDebounceFilter inFilter;
#endif

} Pin;

//------------------------------------------------------------------------------
//         Global Access Macros 
//------------------------------------------------------------------------------

//Get Glitch input filter enable/disable status
#define PIO_GetIFSR(pPin)	((pPin)->pio->PIO_IFSR)

//Get Glitch/Deboucing selection status
#define PIO_GetIFDGSR(pPin) ((pPin)->pio->PIO_IFDGSR)

//Get Additional PIO interrupt mode mask status
#define PIO_GetAIMMR(pPin)  ((pPin)->pio->PIO_AIMMR)

//Get Interrupt status
#define PIO_GetISR(pPin)	((pPin)->pio->PIO_ISR)

//Get Edge or Level selection status
#define PIO_GetELSR(pPin)	((pPin)->pio->PIO_ELSR)

//Get Fall/Rise or Low/High selection status
#define PIO_GetFRLHSR(pPin)	((pPin)->pio->PIO_FRLHSR)

//Get PIO Lock Status
#define PIO_GetLockStatus(pPin) ((pPin)->pio->PIO_LOCKSR)

//------------------------------------------------------------------------------
//         Global Functions
//------------------------------------------------------------------------------

extern unsigned char PIO_Configure(const Pin *list, unsigned int size);

extern void PIO_Set(const Pin *pin);

extern void PIO_Clear(const Pin *pin);

extern unsigned char PIO_Get(const Pin *pin);

//extern unsigned int PIO_GetISR(const Pin *pin);

extern unsigned char PIO_GetOutputDataStatus(const Pin *pin);

#endif //#ifndef PIO_H

