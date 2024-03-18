#include "VehicleMovement.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
 
MV_EnginesOutput CalculateEnginesOuput(const MV_JoystickPosition jsPosition){

	MV_EnginesOutput output = {
								.Engines={
									.left ={.speedInPointsOfWorkingBand=0, .direction=MV_DIR_FORWARD},
									.right={.speedInPointsOfWorkingBand=0, .direction=MV_DIR_FORWARD}
										 }
							  };

	output = *TranslateReceivedVerticalStickPosition(&jsPosition,&output);
	return output;
}



void Test_PrintParams(MV_JoystickPosition position,MV_EnginesOutput engines){
	printf("For provided Joysctick state: y=%u, x=%u, output is:\n"
		    "Left speed = %u, Left direction = %u,\n"
			"Right speed = %u, Right direction = %u\n",
			position.y, position.x, engines.engines[MV_LEFT].speedInPointsOfWorkingBand,
			engines.engines[MV_LEFT].direction, engines.engines[MV_RIGHT].speedInPointsOfWorkingBand,
			engines.engines[MV_RIGHT].direction);
}


void Test_WhenMovingFromCenterToLeftValuesIncreaseInWorkingScope()
{
	for(int i=0; i<=20;++i)
	{	
		MV_JoystickPosition jsPosition={.y=140+i,.x=139};
		MV_EnginesOutput output = CalculateEnginesOuput(jsPosition);
		Test_PrintParams(jsPosition,output);
		assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == output.engines[MV_RIGHT].speedInPointsOfWorkingBand);
		assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == 1);
		assert(output.engines[MV_LEFT].direction != output.engines[MV_RIGHT].direction);
		assert(output.engines[MV_LEFT].direction == 1);
	}
}

void Test_StickIsSetCloseToUpperRightCornerMostlyRightEnginesWorks(){
	MV_JoystickPosition positionRightTop = {.y=190,.x=170};
	const MV_EnginesOutput output = CalculateEnginesOuput(positionRightTop);
	Test_PrintParams(positionRightTop,output);
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand== 30);
	assert(output.engines[MV_RIGHT].speedInPointsOfWorkingBand == 22);
	assert(output.engines[MV_RIGHT].direction == output.engines[MV_LEFT].direction);
}

void Test_WhenProvidedRightPositionWithoutThrotlleForwardLeftEngineSpinForwardAndRightBackward(){	
	MV_JoystickPosition positionRightMiddle ={ .y=150, .x=180};
	const MV_EnginesOutput output = CalculateEnginesOuput(positionRightMiddle);
	Test_PrintParams(positionRightMiddle,output);
	assert(output.engines[MV_LEFT].direction==0);
	assert(output.engines[MV_LEFT].direction != output.engines[MV_RIGHT].direction);
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == output.engines[MV_RIGHT].speedInPointsOfWorkingBand);
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == 20);
}

void Test_WhenProvidedOnlyThrottleForwardAllEnginesMoveTheSame(){
	MV_JoystickPosition positionTopMiddle   = {.y=190, .x=150};
	const MV_EnginesOutput output = CalculateEnginesOuput(positionTopMiddle);
	Test_PrintParams(positionTopMiddle,output);
	assert(output.engines[MV_LEFT].direction==0);
	assert(output.engines[MV_LEFT].direction == output.engines[MV_RIGHT].direction);
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == output.engines[MV_RIGHT].speedInPointsOfWorkingBand);
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == 30);
}

void Test_WhenProvidedBottomPositionSlightyRightButStillInsideIdleRangeWeStillMoveOnlyBackward(){
	MV_JoystickPosition positionBottomRight = {.y=110, .x=160};
	const MV_EnginesOutput output = CalculateEnginesOuput(positionBottomRight);
	Test_PrintParams(positionBottomRight,output);
	assert(output.engines[MV_LEFT].direction==1);
	assert(output.engines[MV_LEFT].direction == output.engines[MV_RIGHT].direction);
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == output.engines[MV_RIGHT].speedInPointsOfWorkingBand);
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == 30);
}

void Test_WhednProvidedBottomLeftPositionOfStickMostlyRightEngineSpinsBackward(){
	MV_JoystickPosition positionBottomLeft  = {.y=100, .x=112};
	const MV_EnginesOutput output = CalculateEnginesOuput(positionBottomLeft);
	Test_PrintParams(positionBottomLeft,output);
	assert(output.engines[MV_LEFT].direction==1);
	assert(output.engines[MV_LEFT].direction == output.engines[MV_RIGHT].direction);
	assert(output.engines[MV_RIGHT].speedInPointsOfWorkingBand == 40); 
	assert(output.engines[MV_LEFT].speedInPointsOfWorkingBand == 12);

}


int main(int numOfArgs, char *args[]){
	Test_WhenMovingFromCenterToLeftValuesIncreaseInWorkingScope();
	Test_StickIsSetCloseToUpperRightCornerMostlyRightEnginesWorks();
	Test_WhenProvidedRightPositionWithoutThrotlleForwardLeftEngineSpinForwardAndRightBackward();
	Test_WhenProvidedOnlyThrottleForwardAllEnginesMoveTheSame();
	Test_WhenProvidedBottomPositionSlightyRightButStillInsideIdleRangeWeStillMoveOnlyBackward();
	Test_WhednProvidedBottomLeftPositionOfStickMostlyRightEngineSpinsBackward();


	if(numOfArgs==4){
		MV_JoystickPosition userDefined = {.y=atoi(args[2]), .x=atoi(args[3])};
		printf("For y=%i, x=%i output is: \n", userDefined.y, userDefined.x);;
		MV_EnginesOutput output = CalculateEnginesOuput(userDefined);
		printf("For %s Lsp: %u, Ld: %u, Rsp: %u Rd: %u\n", " User defined -", 
		output.engines[MV_LEFT].speedInPointsOfWorkingBand, output.engines[MV_LEFT].direction, 
		output.engines[MV_RIGHT].speedInPointsOfWorkingBand, output.engines[MV_RIGHT].direction);
	}
	return 0;
}	
