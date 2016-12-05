#include "Convert.h"

namespace Maths
{

	namespace Convert
	{

		float convertDegreeToRadian(float angle)
		{
			return (angle * PI / 180.0f);
		}

		float convertRadianToDegree(float angle)
		{
			return (angle * 180.0f / PI);
		}

	}//End of Convert namespace

}//End of Maths namespace