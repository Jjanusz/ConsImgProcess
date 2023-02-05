#pragma once
#include "pch.h"
#include "../ConsImgprocess/functions.h"
#include "../ConsImgprocess/imageprocessing.h"





TEST(factorParameterParser, singleDigit ) 
{
	std::string arg;
	EXPECT_EQ(getFactorParameter(arg="scale(2)"), 2);
	EXPECT_EQ(getFactorParameter(arg = "scale(1)"), 1);
	EXPECT_EQ(getFactorParameter(arg = "scale(0)"), 0);
}

TEST(factorparameterParser, negSingleDigit)
{
	std::string arg;
	EXPECT_EQ(getFactorParameter(arg = "scale(-2)"), -2);
	EXPECT_EQ(getFactorParameter(arg = "scale(-1)"), -1);
	EXPECT_EQ(getFactorParameter(arg = "scale(-0)"), -0);
}

TEST(factorparameterParser, oneDot) 
{
	std::string arg;
	EXPECT_EQ(getFactorParameter(arg = "scale(2.1)"), 2.1);
	EXPECT_EQ(getFactorParameter(arg = "scale(0.4)"), 0.4);
	EXPECT_EQ(getFactorParameter(arg = "scale(6.0)"), 6.0);
}

TEST(factorparameterParser, twodot) 
{
	std::string arg;
	EXPECT_EQ(getFactorParameter(arg = "scale(2.1.2)"), -2);
	
}

TEST(parameterParser, oneDot)
{
	std::string arg;
	EXPECT_EQ(getFactorParameter(arg = "scale(2.1)"), 2.1);
	EXPECT_EQ(getFactorParameter(arg = "scale(0.4)"), 0.4);
	EXPECT_EQ(getFactorParameter(arg = "scale(6.0)"), 6.0);
}

TEST(ParameterParser, singleDigit)
{
	std::string arg;
	EXPECT_EQ(getParameter(arg = "scale(2)"), std::string("2"));
	EXPECT_EQ(getParameter(arg = "scale(1)"), std::string("1"));
	EXPECT_EQ(getParameter(arg = "scale(0)"), std::string("0"));
}

TEST(parameterParser, negSingleDigit) 
{
	std::string arg;
	EXPECT_EQ(getParameter(arg = "scale(-2)"), std::string("-2"));
	EXPECT_EQ(getParameter(arg = "scale(-1)"), std::string("-1"));
	EXPECT_EQ(getParameter(arg = "scale(-0)"), std::string("-0"));
}


TEST(parameterParser, twodot)
{
	std::string arg;
	EXPECT_EQ(getParameter(arg = "scale(2.1.2)"), std::string("2.1.2"));

}