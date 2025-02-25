#include <iostream>
#include "ArrayBox.hpp"
#include "ChessPiece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "ChessBox.hpp"
using namespace std;

int main() {
    //ChessPiece Constructor and Accessor Function Test
    cout << "Testing ChessPiece Default Constructor" << endl;
    ChessPiece test1;
    cout << "default size (0) + size accessor test: " << test1.size() << endl;
    cout << "default type (NONE) + type accessor test: " << test1.getType() << endl;
    cout << endl;

    cout << "Testing ChessPiece Parameterized Constructor" << endl;
    ChessPiece test2("BLUE",1,1,true,3,"QUEEN");
    cout << "Size (3): " << test2.size() << endl;
    cout << "Type (QUEEN): " << test2.getType() << endl;
    cout << endl;

    //Pawn and Rook Constructor Tests
    cout << "Testing Pawn Default Constructor" << endl;
    Pawn test3;
    cout << "default size (1): " << test3.size() << endl;
    cout << "default type (PAWN): " << test3.getType() << endl;
    cout << endl;

    cout << "testing Rook Default Constructor" << endl;
    Rook test4;
    cout << "default size (2): " << test4.size() << endl;
    cout << "default type (ROOK): " << test4.getType() << endl;
    cout << endl;

    cout << "Testing Pawn Parameterized Constructor" << endl;
    Pawn test5("BLUE",1,1,true, true);
    cout << "default size (1): " << test5.size() << endl;
    cout << "default type (PAWN): " << test5.getType() << endl;
    cout << endl;

    cout << "Testing Pawn Parameterized Constructor" << endl;
    Rook test6("BLUE",1,1,true, 3);
    cout << "default size (2): " << test6.size() << endl;
    cout << "default type (Rook): " << test6.getType() << endl;
    cout << endl;

    //ArrayBox Testing
    cout << "Testing ArrayBox Default Constructor" << endl;
    ArrayBox<ChessPiece> test7;
    test7.displayArray();
    cout << "Default Size (0): " << test7.size() << endl;
    cout << "Default Capacity (64): " << test7.capacity() << endl;
    cout << endl;

    cout << "Testing ArrayBox Parameterized Constructor" << endl;
    ArrayBox<ChessPiece> test8(10);
    test8.displayArray();
    cout << "Size (0): "<< test8.size() << endl;
    cout << "Parameterized Capacity (10): " << test8.capacity() << endl;
    cout << endl;

    cout << "Testing adding items function in Parameterized Constructor: ";
    Pawn pawn;
    Rook rook;
    test8.addItem(pawn);   // Pawn size = 1
    test8.addItem(pawn);   // Pawn size = 1
    test8.addItem(rook);   // Rook size = 2
    test8.addItem(pawn);   // Pawn size = 1
    test8.addItem(rook);   // Rook size = 2
    cout << endl;
    test8.displayArray();
    cout << endl << "Testing remove function: " << endl;
    test8.remove("ROOK");
    test8.displayArray();

    cout << "Testing count function (3 Pawns): " << test8.count("PAWN") << endl;
    cout << "Testing contains function (false/0 Queens): " << test8.contains("QUEEN") << endl;
    cout << "Testing contains function (true/1 ROOK): " << test8.contains("ROOK") << endl;
    cout << endl;

    cout << "Testing ChessBox Default Constructor and Accessor Functions" << endl;
    ChessBox test9;
    cout << "P1_COLOR_ (BLACK): " << test9.getP1Color() << endl;
    cout << "P2_COLOR_ (WHITE): " << test9.getP2Color() << endl;
    cout << endl;

    cout << "Testing ChessBox Parameterized Constructor" << endl;
    ChessBox test10("Red", "Blue", 20);
    cout << "P1_COLOR_ (RED): " << test10.getP1Color() << endl;
    cout << "P2_COLOR_ (BLUE): " << test10.getP2Color() << endl;

    ChessPiece test11("Black",1,1,true,3,"QUEEN");
    cout << test9.addPiece(test11) << endl;



    return 0;
}
