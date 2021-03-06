#include <catch2/catch.hpp>
#include <mpeg2/dct.h>
#include <array>

TEST_CASE("1D DCT test 1", "[dct]") {
	std::array<int16_t, 8> input = { -40, 0, 25, 127, -2304, 12, 34, 5 };
	std::array<int16_t, 8> output = { 0 };
	std::array<int16_t, 8> expected = { -2141, -79, 2142, -13, -2283, -11, 3, -2431 };
	dct_1d(input.data(), 1, output.data());
	REQUIRE(output == expected);
}

TEST_CASE("1D DCT Test 2", "[dct]") {
	std::array<int16_t, 8> input = { 1, -2, 3, -4, 5, -6, -7, 0 };
	std::array<int16_t, 8> output = { 0 };
	std::array<int16_t, 8> expected = { -10, 6, 0, -9, 14, -4, 6, 9 };
	dct_1d(input.data(), 1, output.data());
	REQUIRE(output == expected);
}

TEST_CASE("Matrix Preprocessing Test", "[dct]") {
	std::array<uint16_t, 64> matrix = {
		16, 11, 10, 16,  24,  40,  51,  61,
		12, 12, 14, 19,  26,  58,  60,  55,
		14, 13, 16, 24,  40,  57,  69,  56,
		14, 17, 22, 29,  51,  87,  80,  62,
		18, 22, 37, 56,  68, 109, 103,  77,
		24, 35, 55, 64,  81, 104, 113,  92,
		49, 64, 78, 87, 103, 121, 120, 101,
		72, 92, 95, 98, 112, 100, 103,  99
	};
	
	std::array<uint16_t, 64> expected = {
		 511, 1053, 1158, 1023, 341, 289, 227, 268,
		 965, 1365, 1170, 1219, 445, 282, 273, 421,
		 827, 1260, 1024,  965, 289, 287, 237, 413,
		1170, 1362, 1053, 1129, 321, 266, 289, 528,
		 455,  526,  313,  292, 120, 106, 112, 212,
		 482,  468,  297,  362, 143, 157, 144, 251,
		 236,  256,  210,  266, 112, 135, 136, 229,
		 227,  251,  243,  334, 146, 231, 224, 330
	};
	
	dct_preprocess(matrix.data());
	
	REQUIRE(matrix == expected);
}

TEST_CASE("DCT Quantization Test", "[dct]") {
	std::array<uint8_t, 64>  pixels = {
		52, 55, 61,  66,  70,  61, 64, 73,
		63, 59, 55,  90, 109,  85, 69, 72,
		62, 59, 68, 113, 144, 104, 66, 73,
		63, 58, 71, 122, 154, 106, 70, 69,
		67, 61, 68, 104, 126,  88, 68, 70,
		79, 65, 60,  70,  77,  68, 58, 75,
		85, 71, 64,  59,  55,  61, 65, 83,
		87, 79, 69,  68,  65,  76, 78, 94		
	};
	
	std::array<uint16_t, 64> matrix = {
		 511, 1053, 1158, 1023, 341, 289, 227, 268,
		 965, 1365, 1170, 1219, 445, 282, 273, 421,
		 827, 1260, 1024,  965, 289, 287, 237, 413,
		1170, 1362, 1053, 1129, 321, 266, 289, 528,
		 455,  526,  313,  292, 120, 106, 112, 212,
		 482,  468,  297,  362, 143, 157, 144, 251,
		 236,  256,  210,  266, 112, 135, 136, 229,
		 227,  251,  243,  334, 146, 231, 224, 330
	};
	
	std::array<int16_t, 64> output = {};
	std::array<int16_t, 64> expected = {
		-25, -1, -5, 2, 2, 0, 0, 0,
		  0, -1, -3, 0, 0, 0, 0, 0,
		 -3,  0,  4, 0, 0, 0, 0, 0,
		 -2,  0,  2, 0, 0, 0, 0, 0,
		  0,  0,  0, 0, 0, 0, 0, 0,
		 -1,  0,  0, 0, 0, 0, 0, 0,
		  0,  0,  0, 0, 0, 0, 0, 0,
		  0,  0,  0, 0, 0, 0, 0, 0
	};
	
	dct_sq(pixels.data(), matrix.data(), output.data());
	
	REQUIRE(output == expected);
}
