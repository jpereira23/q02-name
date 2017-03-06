/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}


TEST(PiezasTest, didDropPieceWork)
{
	Piezas p; 
	p.dropPiece(1); 
	ASSERT_TRUE(p.pieceAt(0, 0) == X);
} 

TEST(PiezasTest, didDropPieceWorkII)
{
	Piezas p; 
	p.dropPiece(1);
	p.dropPiece(1);
	ASSERT_TRUE(p.pieceAt(0, 0) == O);
}

TEST(PiezasTest, checkIfGameStateWillReturnInvalid)
{
	Piezas p; 
	ASSERT_TRUE(p.gameState() == Invalid); 
}


TEST(PiezasTest, checkIfXWon)
{
	Piezas p; 
	p.dropPiece(1); 
	p.dropPiece(3); 
	p.dropPiece(1); 
	p.dropPiece(2); 
	p.dropPiece(1); 
	p.dropPiece(3); 
	p.dropPiece(3); 
	p.dropPiece(2); 
	p.dropPiece(2); 
	p.dropPiece(4); 
	p.dropPiece(4); 
	p.dropPiece(4); 
	ASSERT_TRUE(p.gameState() == Invalid); 

}
