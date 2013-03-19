#include "../pps.h"
#include <errno.h>
#include <gtest/gtest.h>

namespace {

class ppsTest : public ::testing::Test {
 protected:
 	ppsTest(){}

//	PPSObject	creator("/pps/TestObject");
//	PPSObject	client("/pps/TestObject");
};

TEST_F(ppsTest, trim){
	PPSObject	creator("/pps/TestObject");

	EXPECT_TRUE();

	PPSObject	client("/pps/TestObject");

	tS = "Hello";
	EXPECT_TRUE(strTrimHead(tS, ' ') == "Hello");
	tS = "Hello";
	EXPECT_TRUE(strTrimTail(tS, ' ') == "Hello");
	tS = "Hello   ";
	EXPECT_TRUE(strTrimHead(tS, ' ') == "Hello   ");
	tS = "   Hello";
	EXPECT_TRUE(strTrimTail(tS, ' ') == "   Hello");

	// Trim leading spaces
	tS = "   Hello";
	EXPECT_TRUE(strTrimHead(tS, ' ') == "Hello");
	// Trim leading '0'
	tS = "0002";
	EXPECT_TRUE(strTrimHead(tS, '0') == "2");
	tS = "0000000000000000000000000000000000000042";
	EXPECT_TRUE(strTrimHead(tS, '0') == "42");
	// Trim toute!
	tS = "kkkkk";
	EXPECT_TRUE(strTrimHead(tS, 'k') == "");

	// Trim trailing spaces
	tS = "Hello   ";
	EXPECT_TRUE(strTrimTail(tS, ' ') == "Hello");
	tS = "Hello                                         ";
	EXPECT_TRUE(strTrimTail(tS, ' ') == "Hello");
	// Trim toute!
	tS = "kkkkk";
	EXPECT_TRUE(strTrimTail(tS, 'k') == "");

	// Trim leading spaces, trailing \n and trailing spaces.
	tS = "   Hello   \n";
	tS = strTrimHead(tS, ' ');
	tS = strTrimTail(tS, '\n');
	tS = strTrimTail(tS, ' ');
	EXPECT_TRUE(tS == "Hello");

	// Un mix
	tS = "  Hey, Hello!  \n ";
	tS = strTrimHead(tS, ' ');
	EXPECT_TRUE(tS == "Hey, Hello!  \n ");
	tS = strTrimTail(tS, ' ');
	EXPECT_TRUE(tS == "Hey, Hello!  \n");
	tS = strTrimTail(tS, '\n');
	EXPECT_TRUE(tS == "Hey, Hello!  ");
	tS = strTrimTail(tS, ' ');
	EXPECT_TRUE(tS == "Hey, Hello!");

	// Test strTrimAtFirst
	tS = "Hey, Hello!  \r\n Autre ligne";
	tS = strTrimAtFirst(tS, '\n');
	EXPECT_TRUE(tS == "Hey, Hello!  \r");
	tS = strTrimAtFirst(tS, '\r');
	EXPECT_TRUE(tS == "Hey, Hello!  ");
	tS = strTrimTail(tS, ' ');
	EXPECT_TRUE(tS == "Hey, Hello!");
}

TEST_F(ppsTest, makeFixedWidthString){
	tS = makeFixedWidthString("VOL NET", (string)"1254.3" + " L", 25);
	EXPECT_TRUE(tS.size() == 25);
	EXPECT_TRUE(tS == "VOL NET          1254.3 L" );

	tS = makeFixedWidthString("VOL NET", (string)"1254.3" + " L", 30);
	EXPECT_TRUE(tS.size() == 30);
	EXPECT_TRUE(tS == "VOL NET               1254.3 L" );

	tS = makeFixedWidthString("VOL NET", (string)"1254.3" + " L", 20);
	EXPECT_TRUE(tS.size() == 20);
	EXPECT_TRUE(tS == "VOL NET     1254.3 L" );

	// Coup de cochon: pas assez de place: trim la fin du membre gauche
	tS = makeFixedWidthString("VOL NET", (string)"1254.3" + " L", 10);
	EXPECT_TRUE(tS.size() == 10);
	EXPECT_TRUE(tS == "VO1254.3 L" );

	// Test avec des caractères accentués (FB2249)
	tS = makeFixedWidthString("Pépé", (string)"1254.3" + " L", 20);
	EXPECT_TRUE(tS.size() == 22);		// string::size() se fout des caractÃ¨res multibytes
	EXPECT_TRUE(UTF8strlen(tS) == 20);	// UTF8strlen(string) est bien meilleur
	EXPECT_TRUE(tS == "Pépé        1254.3 L" );

	tS = makeFixedWidthString("Pépé", "àÀéÉêëÇçù", 20);
	EXPECT_TRUE(tS.size() == 31);		// string::size() se fout des caractères multibytes
	EXPECT_TRUE(UTF8strlen(tS) == 20);	// UTF8strlen(string) est bien meilleur
	EXPECT_TRUE(tS == "Pépé       àÀéÉêëÇçù");
}

TEST_F(stringUtilsTest, toFromBool){
	// boolToStr
	EXPECT_TRUE(boolToStr(true) == "1");
	EXPECT_TRUE(boolToStr(false) == "0");

	// Test de strToBool
	EXPECT_TRUE(strToBool("1") == true);
	EXPECT_TRUE(strToBool("0") == false);
	EXPECT_TRUE(strToBool("fdjkal") == false);
}

TEST_F(stringUtilsTest, toStr_int){
	EXPECT_EQ("0", toStr(0));
	EXPECT_EQ("-1", toStr(-1));
	EXPECT_EQ("-354", toStr(-354));
	EXPECT_EQ("1", toStr(1));
	EXPECT_EQ("1352", toStr(1352));
}

TEST_F(stringUtilsTest, toStr_double){
	double d;
	d = 0.0;			EXPECT_EQ("0.0", toStr(d, 1));
	d = 0.24354; 	EXPECT_EQ("0.244", toStr(d, 3));
	d = 1479.572; EXPECT_EQ("1479.57", toStr(d, 2));
	d = -0.423;		EXPECT_EQ("-0.4", toStr(d, 1));
	d = -576.468;	EXPECT_EQ("-576.47", toStr(d, 2));
	// Précision par défaut: 2 
	d = 0.24354; 	EXPECT_EQ("0.24", toStr(d));
}	
	
TEST_F(stringUtilsTest, toStr_bool){
	EXPECT_EQ("1", toStr(true));
	EXPECT_EQ("0", toStr(false));
	// version textuelle
	EXPECT_EQ("true", toStr(true, true));
	EXPECT_EQ("false", toStr(false, true));
}

TEST_F(stringUtilsTest, toStr_string){
	EXPECT_EQ("toto", toStr(string("toto")));
	EXPECT_EQ("TATA", toStr(string("TATA")));
}

TEST_F(stringUtilsTest, pad){
	// Pad à droite
	EXPECT_TRUE(strPadRight("BLA", ' ', 15) == "BLA            ");
	// NE PAS BRISER LA STRING INITIALE!
	EXPECT_TRUE(strPadRight("BLABLABLA", ' ', 6) == "BLABLABLA");

	// Pad à gauche
	EXPECT_TRUE(strPadLeft("BLA", ' ', 15) == "            BLA");
	// NE PAS BRISER LA STRING INITIALE!
	EXPECT_TRUE(strPadLeft("BLABLABLA", ' ', 6) == "BLABLABLA");
}


TEST_F(stringUtilsTest, split){
	deque<string>	d;
	
	d = split("");
	EXPECT_TRUE(d.empty());
	
	d = split("TOTO");
	ASSERT_EQ(1, d.size());
	EXPECT_EQ("TOTO", d[0]);
	
	d = split("TOTO,");
	ASSERT_EQ(1, d.size());
	EXPECT_EQ("TOTO", d[0]);
	
	d = split(",TOTO,");
	ASSERT_EQ(1, d.size());
	EXPECT_EQ("TOTO", d[0]);
	
	d = split("TOTO,TATA");
	ASSERT_EQ(2, d.size());
	EXPECT_EQ("TOTO", d[0]);
	EXPECT_EQ("TATA", d[1]);
	
	d = split(",,,TOTO,,,,TATA,,,,");
	ASSERT_EQ(2, d.size());
	EXPECT_EQ("TOTO", d[0]);
	EXPECT_EQ("TATA", d[1]);
	
	d = split("TOTO TATA BOBO", ' ');
	ASSERT_EQ(3, d.size());
	EXPECT_EQ("TOTO", d[0]);
	EXPECT_EQ("TATA", d[1]);
	EXPECT_EQ("TATA", d[1]);
	
	d = split("TOTO|TATA|SALUT, COCO!", '|');
	ASSERT_EQ(3, d.size());
	EXPECT_EQ("TOTO", d[0]);
	EXPECT_EQ("TATA", d[1]);
	EXPECT_EQ("SALUT, COCO!", d[2]);
}

TEST_F(stringUtilsTest, toInt){
	EXPECT_EQ(0, toInt("0"));
	EXPECT_EQ(1, toInt("1"));
	EXPECT_EQ(-1, toInt("-1"));
	EXPECT_EQ(1436758, toInt("1436758"));
	EXPECT_EQ(-1436758, toInt("-1436758"));
	
	EXPECT_EQ(1, toInt("1.1"));
	EXPECT_EQ(1, toInt("1.9"));
}	

} // namespace
