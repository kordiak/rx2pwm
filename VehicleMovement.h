#ifndef VEHICLE_MOVEMENT
#define VEHICLE_MOVEMENT
#include <stdint.h>

void HAL_DELAY(__uint32_t ms);

#define MV_MAX_VALUE_FROM_RX 200
#define MV_MIN_VALUE_FROM_RX 100
#define MV_CENTER_VALUE 150
#define MV_REST_VALUE 10
#define MV_WORKING_SCOPE (MV_MAX_VALUE_FROM_RX-MV_TOP_OF_REST_BAND)
#define MV_TOP_OF_REST_BAND (MV_CENTER_VALUE + MV_REST_VALUE)
#define MV_BOTTOM_OF_REST_BAND (MV_CENTER_VALUE - MV_REST_VALUE)

enum mv_RXsignalIndex{
	MV_RX_UPDOWN,
	MV_RX_LEFTRIGHT,

	MV_RX_MAX
};
typedef struct {
	__uint32_t y,x;
} MV_JoystickPosition;

typedef enum {
	MV_DIR_FORWARD,
	MV_DIR_BACKWARD,

	MV_DIR_MAX
} MV_DirectionOfRotation;

enum MV_WhichEngine {
	MV_LEFT,
	MV_RIGHT,

	MV_MAX
};

typedef struct {
	__uint32_t speedInPointsOfWorkingBand;
	MV_DirectionOfRotation direction;
} MV_EngineOutput;


typedef union {
	struct {
		MV_EngineOutput left,right;
	} Engines;
	MV_EngineOutput engines[MV_MAX];
} MV_EnginesOutput;



MV_EnginesOutput* TranslateReceivedVerticalStickPosition(const MV_JoystickPosition *const jsPosition, MV_EnginesOutput* output);

#endif

