#include "qcommon/q_math.h"
#include <math.h>
#include "snapvector.h"

#include <boost/test/unit_test.hpp>

#ifdef _WIN32
#include "windows.h"
HMODULE handle = LoadLibraryEx("jampgamex86_1.0.1.0.dll", NULL, NULL);
#else
int handle = 0;
#endif

BOOST_AUTO_TEST_SUITE(math)
float value_float = 1234.1234f;
double value_double = 1234.1234;

BOOST_AUTO_TEST_CASE(snap_vector)
{
	vec3_t snapDown = { 4.5f, 3.5f, 2.5f };
	vec3_t snapUp = { 2.51f, 3.51f, 2.51f };
	SnapVector(snapDown);
	SnapVector(snapUp);
 
	vec3_t sysSnapDown = { 4.5f, 3.5f, 2.5f };
	vec3_t sysSnapUp2 = { 2.51f, 3.51f, 2.51f };
	Sys_SnapVector(sysSnapDown);
	Sys_SnapVector(sysSnapUp2);

	vec3_t snapDownResult32Bit = { 4.0f, 3.0f, 2.0f };
	vec3_t SnapUpResult32Bit = { 3.0f, 4.0f, 3.0f };
	BOOST_CHECK_EQUAL(snapDown[0], snapDownResult32Bit[0]);
	BOOST_CHECK_EQUAL(snapUp[0], SnapUpResult32Bit[0]);
	BOOST_CHECK_EQUAL(sysSnapDown[0], snapDownResult32Bit[0]);
	BOOST_CHECK_EQUAL(sysSnapUp2[0], SnapUpResult32Bit[0]);
}

BOOST_AUTO_TEST_CASE(square_root)
{
	if (handle)
	{
		typedef double func(double);
		func* jamp_sqrt = (func*)0x200dc9d4;
		BOOST_CHECK_EQUAL(sqrt(value_double), jamp_sqrt(value_double));
		BOOST_CHECK_EQUAL((float)sqrt(value_double), (float)jamp_sqrt(value_double));
		BOOST_CHECK_EQUAL(sqrt(value_float), (float)jamp_sqrt(value_float));
	}	
}

BOOST_AUTO_TEST_CASE(precision)
{
	BOOST_CHECK_CLOSE(Q_rsqrt(value_float), 1 / sqrt(value_float), 0.1);
}

BOOST_AUTO_TEST_SUITE(same_as_base)
BOOST_AUTO_TEST_CASE(vector_length)
{
	vec3_t vec = { 0.065918f, -0.527344f, 10.0f };
	
	if (handle)
	{
		typedef float func(vec3_t);
		func* jamp_VectorLength = (func*)0x20044f40;
		BOOST_CHECK_EQUAL(VectorLength(vec), jamp_VectorLength(vec));
	}
	else
	{
		BOOST_CHECK_EQUAL(VectorLength(vec), 10.0141115f);
	}
}

BOOST_AUTO_TEST_CASE(vector_normalize)
{
	vec3_t ojk_normalize = { 3.065918f, -0.527344f, 10.0f };
	vec3_t jamp_normalize = { 3.065918f, -0.527344f, 10.0f };
	
	if (handle)
	{
		typedef vec_t func(vec3_t);
		func* jamp_VectorNormalize = (func*)0x200bf280;
		float ojk_length = VectorNormalize(ojk_normalize);
		float jamp_length = jamp_VectorNormalize(jamp_normalize);

		BOOST_CHECK_EQUAL(ojk_length, jamp_length);
		BOOST_CHECK_EQUAL(ojk_normalize[0], jamp_normalize[0]);
		BOOST_CHECK_EQUAL(ojk_normalize[1], jamp_normalize[1]);
		BOOST_CHECK_EQUAL(ojk_normalize[2], jamp_normalize[2]);
	}
	else
	{
		float ojk_length = VectorNormalize(ojk_normalize);
		float jamp_length = 10.472724f;

		vec3_t jamp_normalize_result = { 0.292752683f, -0.0503540412f, 0.954861403f };

		BOOST_CHECK_EQUAL(ojk_length, jamp_length);
		BOOST_CHECK_EQUAL(ojk_normalize[0], jamp_normalize_result[0]);
		BOOST_CHECK_EQUAL(ojk_normalize[1], jamp_normalize_result[1]);
		BOOST_CHECK_EQUAL(ojk_normalize[2], jamp_normalize_result[2]);
	}
}

BOOST_AUTO_TEST_SUITE_END() // SameAsBase

BOOST_AUTO_TEST_SUITE_END() // math
