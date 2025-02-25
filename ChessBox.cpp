 #include <iostream>
 #include "ChessBox.hpp"
 
 /**
 * Default constructor
 * Default initializes P1_COLOR_ to "BLACK" and P2_COLOR_ to "WHITE"
 * Initializes ArrayBox members with capacity 64
 */
ChessBox::ChessBox() : P1_COLOR_("BLACK"), P2_COLOR_("WHITE"), P1_BOX_(64), P2_BOX_(64) {
  
}

 /**
  * Paramaterized Constructor
  * @param color1 A const reference to the color of the Chess Piece (a string)
  * @param color2 A const reference to the color of the Chess Piece (a string)
  * @param capacity An integer describing the capacity of each player's ArrayBox, with default capacity 64.
  * 
  * @note If either color1 or color2 contains non-alphabetic characters, set P1_COLOR_ to "BLACK" and P2_COLOR_ to "WHITE"
  *       Otherwise, if the string is purely alphabetic, it is converted and stored in uppercase.
  *       However, if the are equal, set color1 to "BLACK" and color2 to "WHITE"
  *
  *       If the specified capacity is not positive (ie. <= 0), 64 is used instead.
  * 
  * @post Initializes ArrayBox members with the specified capacity. All strings are initialized as described above. 
  */
ChessBox::ChessBox(const std::string& color1, const std::string& color2, int capacity) {
  bool equalColor = false;
  if(color1 == color2){ // If both colors are the same, set equalColor to true
    equalColor = true;
  }
  bool hasNonAlpha = false;
  for(size_t i = 0; i < color1.size() && !equalColor; i++){ //If color1 contains non-alphabetic characters, set hasNonAlpaha to true
    if(!std::isalpha(color1[i])){
      hasNonAlpha = true;
      break;
    }
  }
  for(size_t i = 0; i < color2.size() && !equalColor; i++){ // If color2 contains non-alphabetic characters, set hasNonAlpha to true
    if(!std::isalpha(color2[i])){
      hasNonAlpha = true;
      break;
    }
  }

  if(!hasNonAlpha && !equalColor){ //If color1 && color2 does not contain any non-alphabetic or is not equal, capitalize both colors and set P1_COLOR_ AND P2_COLOR_ to color1 and color2
    std::string uppercase1 = "";
    std::string uppercase2 = "";
    for (size_t i = 0; i < color1.size(); i++) {
      uppercase1 += std::toupper(color1[i]);
    } 
    for (size_t i = 0; i < color2.size(); i++) {
      uppercase2 += std::toupper(color2[i]);
    } 
    P1_COLOR_ = uppercase1;
    P2_COLOR_ = uppercase2;
  } else { // If color1 && color 2 contain non-alphabetic characters or is equal, set set P1_COLOR_ AND P2_COLOR_ TO BLACK AND WHITE
    P1_COLOR_ = "BLACK";
    P2_COLOR_ = "WHITE";
  }

  if(capacity <= 0){
    capacity = 64;
  }

  P1_BOX_ = ArrayBox<ChessPiece>(capacity);
  P2_BOX_ = ArrayBox<ChessPiece>(capacity);
}

 
 /**
  * @brief Adds a given ChessPiece object to the ArrayBox corresponding to its color:
  *      - If the color of the given piece matches P1_COLOR_, add it to P1_BOX_
  *      - If the color of the given piece matches P2_COLOR_, add it to P2_BOX_
  *      - If the color does not match either box, or the corresponding box doesn't have
  *   enough remaining space to add the piece, the add operation fails.
  * 
  * @param piece A const reference to a ChessPiece object that is to be added to one of the ArrayBoxes
  * @return True if the piece was added successfully. False otherwise.
  *
  */
bool ChessBox::addPiece(const ChessPiece& piece){
  if (piece.getColor() == P1_COLOR_ && P1_BOX_.size() + piece.size() <= P1_BOX_.capacity()) { //Checks if piece color matches P1_COLOR_ and P1_BOX_ has enough space to add piece
    P1_BOX_.addItem(piece);
    return true;
  } else if (piece.getColor() == P2_COLOR_ && P2_BOX_.size() + piece.size() <= P2_BOX_.capacity()) { //Checks if piece color matches P2_COLOR_ and P2_BOX_ has enough space to add piece
    P2_BOX_.addItem(piece);
    return true;
  }  
  return false;//Piece color does not match either box or not enough space within the corresponding box. 
  
}  

 
 /**
  * @brief Removes a ChessPiece of the given type if one exists in the ArrayBox corresponding to the given color
  * 
  * @param type A const reference to an uppercase string representing the type of the ChessPiece to remove
  * @param color A const referene to an uppercase string representing the color of the ChessPiece to remove
  * @return True if a piece is found and removed. False otherwise. 
  */
bool ChessBox::removePiece(const std::string& type, const std::string& color){
  if(P1_COLOR_ == color){ 
    return P1_BOX_.remove(type);
  } else if (P2_COLOR_ == color){
    return P2_BOX_.remove(type);
  } 
  return false; 
  
}
 
 /**
  * @brief Finds whether a ChessPiece of the given type exists within the ArrayBox corresponding to the given color
  * 
  * @param type A const reference to an uppercase string representing the type of the ChessPiece to find
  * @param color A const referene to an uppercase string representing the color of the ChessPiece to find
  * @return True if a piece is contained within the correct ArrayBox. False otherwise. 
  */
bool ChessBox::contains(const std::string& type, const std::string &color) const{
  if(P1_COLOR_ == color){
    return P1_BOX_.contains(type);
  } else if(P2_COLOR_ == color){
    return P2_BOX_.contains(type);
  } else {
    return false;
  }
}
 
 /**
  * @brief Getter for P1_Color
  * @return The string value stored in P1_COLOR
  */
std::string ChessBox::getP1Color() const{
  return P1_COLOR_;
}
 
 /**
  * @brief Getter for P2_Color
  * @return The string value stored in P2_COLOR
  */
std::string ChessBox::getP2Color() const{
  return P2_COLOR_;
}
 
 /**
  * @brief Getter for P1_BOX
  * @return The ArrayBox<ChessPiece> (ie. the value) of P1_BOX_
  */
 ArrayBox<ChessPiece> ChessBox::getP1Pieces() const{
  return P1_BOX_;
 }
 
 /**
  * @brief Getter for P2_BOX
  * @return The ArrayBox<ChessPiece> (ie. the value) of P2_BOX_
  */
 ArrayBox<ChessPiece> ChessBox::getP2Pieces() const{
  return P2_BOX_;
 }