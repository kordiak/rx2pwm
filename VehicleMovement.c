#include "VehicleMovement.h"

MV_EnginesOutput* TranslateReceivedVerticalStickPosition(const MV_JoystickPosition *const jsPosition, MV_EnginesOutput* output)
{
	if(	 jsPosition->x>MV_MAX_VALUE_FROM_RX || 
		 jsPosition->x<MV_MIN_VALUE_FROM_RX || 
		 jsPosition->y>MV_MAX_VALUE_FROM_RX ||
		 jsPosition->y<MV_MIN_VALUE_FROM_RX )
	{
		return output;
	}
	
	float  horizontalCoefficientRightEngine =1;
	float  horizontalCoefficientLeftEngine =1;
	
	if(jsPosition->x>MV_TOP_OF_REST_BAND){
		horizontalCoefficientRightEngine = (MV_MAX_VALUE_FROM_RX - jsPosition->x)/(float) MV_WORKING_SCOPE;
	} else if(jsPosition->x<MV_BOTTOM_OF_REST_BAND){
		horizontalCoefficientLeftEngine = (jsPosition->x - MV_MIN_VALUE_FROM_RX)/(float) MV_WORKING_SCOPE;
	}

	
	if(jsPosition->y>MV_TOP_OF_REST_BAND){
				output->engines[MV_LEFT].speedInPointsOfWorkingBand = MV_WORKING_SCOPE - ( MV_MAX_VALUE_FROM_RX-jsPosition->y);
				output->engines[MV_RIGHT].speedInPointsOfWorkingBand= output->engines[MV_LEFT].speedInPointsOfWorkingBand; 
				output->engines[MV_LEFT].speedInPointsOfWorkingBand *= horizontalCoefficientLeftEngine;
				output->engines[MV_RIGHT].speedInPointsOfWorkingBand *= horizontalCoefficientRightEngine;

	}
	else if(jsPosition->y<MV_BOTTOM_OF_REST_BAND){
				output->engines[MV_LEFT].speedInPointsOfWorkingBand = MV_WORKING_SCOPE - ( jsPosition->y - MV_MIN_VALUE_FROM_RX);
			    output->engines[MV_LEFT].direction = MV_DIR_BACKWARD;
				output->engines[MV_RIGHT]= output->engines[MV_LEFT];	
				output->engines[MV_LEFT].speedInPointsOfWorkingBand *= horizontalCoefficientLeftEngine; //We switch coefficient casue
				output->engines[MV_RIGHT].speedInPointsOfWorkingBand *= horizontalCoefficientRightEngine; //casue we move in oposite direction
	}else {

		if(jsPosition->x>MV_TOP_OF_REST_BAND){
			output->engines[MV_RIGHT].speedInPointsOfWorkingBand = jsPosition->x - MV_TOP_OF_REST_BAND;
			output->engines[MV_LEFT] = output->engines[MV_RIGHT];
			output->engines[MV_RIGHT].direction = MV_DIR_BACKWARD;
		} else if(jsPosition->x<MV_BOTTOM_OF_REST_BAND)
		{
			output->engines[MV_RIGHT].speedInPointsOfWorkingBand = MV_WORKING_SCOPE - (jsPosition->x - MV_MIN_VALUE_FROM_RX);
			output->engines[MV_LEFT]= output->engines[MV_RIGHT];
			output->engines[MV_LEFT].direction = MV_DIR_BACKWARD;
		}

	}
	
	return output;
}
