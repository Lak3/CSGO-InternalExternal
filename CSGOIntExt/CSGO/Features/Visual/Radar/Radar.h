#pragma once

#include "../../../SDK/SDK.h"

class C_Radar
{
public:
	void Run();

private:
	bool ShouldRun();

};

extern C_Radar gRadar;